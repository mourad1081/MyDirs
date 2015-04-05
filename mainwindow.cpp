#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), dirDir("."), dirImages(".")
{
    ui->setupUi(this);
    creerImages();
    creerDossiers();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gridImages;
}

void MainWindow::creerImages()
{
    QFileInfoList lesImages = dirImages.entryInfoList(QDir::AllEntries
                                                      | QDir::Hidden
                                                      | QDir::NoDotAndDotDot,
                                                      QDir::DirsFirst);
    if(gridImages != nullptr)
        retirerLayout(gridImages);

    gridImages = new QGridLayout(ui->images);
    int ligne = 0, colonne = -1;
    for(auto img : lesImages)
    {
        Fichier *fichier = new Fichier(img.absoluteFilePath());
        if(fichier->getExploitable())
        {
            colonne++;
            if(colonne%4 == 0) ligne++;
            gridImages->addWidget(fichier,ligne, colonne%4,
                                  Qt::AlignVCenter | Qt::AlignHCenter);
            QObject::connect(fichier, SIGNAL(doubleClicked(Fichier*)),
                             this, SLOT(entrerDirImages(Fichier*)));
        }
    }
}

void MainWindow::creerDossiers()
{

    QFileInfoList lesDossiers = dirDir.entryInfoList(
                QDir::Dirs | QDir::NoDotAndDotDot);

    if(gridDossiers != nullptr)
        retirerLayout(gridDossiers);

    gridDossiers = new QGridLayout(ui->dossiers);

    int ligne = 0, colonne = -1;
    for(auto dir : lesDossiers)
    {
        Fichier *fichier = new Fichier(dir.absoluteFilePath());
        colonne++;
        if(colonne%4 == 0) ligne++;
        gridDossiers->addWidget(fichier,ligne, colonne%4,
                                Qt::AlignVCenter | Qt::AlignHCenter);
        fichier->setAcceptDrops(true);
        QObject::connect(fichier, SIGNAL(doubleClicked(Fichier*)),
                         this, SLOT(entrerDirDir(Fichier*)));

        QObject::connect(fichier, SIGNAL(dropped(Fichier*,Fichier*)),
                         this, SLOT(creerPersonnalisation(Fichier*,Fichier*)));
    }
}

void MainWindow::retirerLayout(QLayout *layout)
{
    //Detruire layout
    QLayoutItem * item;
    QWidget * widget;
    //QLayout *sublayout;
    while ((item = layout->takeAt(0)))
    {
        //if ((sublayout = item->layout()) != 0) {/* do the same for sublayout*/}
        if ((widget = item->widget()) != 0) {
            widget->hide();
            delete widget;
        }
        else delete item;
    }
    delete layout;
}

void MainWindow::remonter(QDir &dir)
{
    if(!dir.isRoot())
    {
        dir.cdUp();
        if(dir == dirImages)
            creerImages();
        else if(dir == dirDir)
            creerDossiers();
    }
    else
        QMessageBox::warning(this, "T'es fou ou quoi ?", QString()
             + "On peut pas monter"
             + " plus haut que ça a gros, 3ayaq pas");
}

void MainWindow::entrerDirDir(Fichier *file)
{
    if(file->getPath().isDir())
    {
        dirDir.setPath(file->getPath().absoluteFilePath());
        creerDossiers();
    }
}

void MainWindow::entrerDirImages(Fichier *file)
{
    if(file->getPath().isDir())
    {
        dirImages.setPath(file->getPath().absoluteFilePath());
        creerImages();
    }
}

void MainWindow::on_remonterDirDraggables_clicked()
{
    remonter(dirImages);
}

void MainWindow::on_remonterDirDroppables_clicked()
{
    remonter(dirDir);
}

void MainWindow::on_aideCheminRelatif_clicked()
{
    QMessageBox::information(this, "Aide", QString() +
                             "<html><head/><body><p align=\"center\"><span styl"
                             + "e=\" font-size:11pt; font-weight:600; color:#ff"
                             + "ffff;\">Qu'est-ce qu'un fichier relatif Ô grand"
                             + " Mourad ?</span></p><p align=\"center\"><span st"
                             + "yle=\" font-size:11pt; font-weight:600; text-de"
                             + "coration: underline; color:#ff0004;\">C'EST TA "
                             + "MÈRE</span></p><p><br/></p><p align=\"justify\""
                             + "><span style=\" font-size:11pt; color:#ffffff; "
                             + "\">Tu peux sélectionner cette option si ton ima"
                             + "ge compte rester toujours au même endroit PAR R"
                             + "APPORT au dossier que tu veux personnaliser. <b"
                             + "r/><br/>Par exemple, une image X se trouvant DA"
                             + "NS le dossier Y. Si on bouge le dossier X, l'im"
                             + "age sera toujours au même endroit par rapport à"
                             + " Y.</span></p><p align=\"justify\"><br/></p><p a"
                             + "lign=\"justify\"><span style=\" font-size:11pt;"
                             + "color:#ffffff;\">Cette option est très utile si"
                             + " tu veux que la personnalisation du dossier fonc"
                             + "tionne même sur d'autres PC (mets l'image à l'i"
                             + "ntérieur du dossier à personnaliser et ce sera "
                             + "parfait !)</span></p><p><br/></p></body></html>"
                             , "Wesh", "Lol");
}



void MainWindow::creerPersonnalisation(Fichier *src, Fichier *dest)
{
    QString cheminImage;
    QDir dir(dest->getPath().absoluteFilePath());

    //Pour avoir le chemin relatif par rapport à un autre.
    if(ui->radioMethodeMourad->isChecked())
    {
        cheminImage = src->getPath().fileName();
        QFile::copy(src->getPath().absoluteFilePath(),
                    dest->getPath().absoluteFilePath() + "/" + src->getPath().fileName());
    } else if (ui->radioCheminAbsolu->isChecked())
        cheminImage = src->getPath().absoluteFilePath();
    else
        cheminImage = dir.relativeFilePath(src->getPath().absoluteFilePath());

    QString path = dest->getPath().absoluteFilePath() + "/desktop.ini";
    QString drive = QString(path.at(0)) + QString(path.at(1));
    QFile desktopIni(path);

    if(!desktopIni.exists())
    {
        desktopIni.open(QFile::WriteOnly| QIODevice::Text);
        desktopIni.write("[.ShellClassInfo]");
        desktopIni.write("\n");
        desktopIni.write(QString("IconResource=" + cheminImage + ",0").toUtf8().data());
        desktopIni.flush();
        desktopIni.close();
        QProcess p1, p2;
        p1.startDetached("S.bat", QStringList()
                         << QString(dest->getPath().absoluteFilePath())
                         << drive);
        p2.startDetached("HSA.bat", QStringList() << QString(path)
                         << drive);

        p1.waitForFinished();
        p2.waitForFinished();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QDialog *choiceDevice = new QDialog(this);
    QVBoxLayout *lay = new QVBoxLayout(choiceDevice);
    QDir drives;
    QFileInfoList qfi = drives.drives();
    lay->addWidget(new QLabel("Choisissez le périphérique souhaité."));
    QRadioButton *defaultValue = new QRadioButton("Changer les deux");
    defaultValue->setChecked(true);
    lay->addWidget(new QRadioButton("Changer à gauche"));
    lay->addWidget(new QRadioButton("Changer à droite"));
    lay->addWidget(defaultValue);
    for(QFileInfo file : qfi)
    {
        QPushButton *b = new QPushButton(file.absoluteFilePath());
        lay->addWidget(b);
        QObject::connect(b, SIGNAL(clicked()), this, SLOT( clicDrive() ) );
    }
    choiceDevice->setModal(true);
    choiceDevice->exec();
}

void MainWindow::clicDrive()
{
    QString text = ((QPushButton *)sender())->text();
    QObjectList elements = (( QDialog *) sender()->parent())->children();
    for(QObject *o : elements)
    {
        //Si res = NULL, alors ce n'est pas un QRadioButton
        QRadioButton *res = dynamic_cast<QRadioButton *> (o);
        if(res != NULL && res->isChecked())
        {
            if(!res->text().compare(res->text(), "Changer à gauche"))
                dirDir.setPath(text);
            else if(!res->text().compare(res->text(), "Changer à droite"))
                dirImages.setPath(text);
            else if(!res->text().compare(res->text(), "Changer les deux"))
            {
                dirDir.setPath(text);
                dirImages.setPath(text);
            }
        }
    }

    creerDossiers();
    creerImages();
}
