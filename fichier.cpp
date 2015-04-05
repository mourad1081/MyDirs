#include "fichier.h"

Fichier::Fichier(QFileInfo path, QWidget *parent)
    : QWidget (parent), path(path)
{
    lay = new QVBoxLayout(this);
    descr = new QLabel();
    descr->setWordWrap(true);
    QString newName = path.fileName();

    if(!newName.contains(' '))
        for(int i = 0; i < newName.length(); i++)
            if(i%10 == 0)
                newName.insert(i, ' ');

    descr->setText(newName);
    descr->setAlignment(Qt::AlignCenter);
    image = new QLabel();
    QString extension = path.completeSuffix();
    exploitable = true;
    if(path.isDir())
        imageData = new QPixmap(imageDir);
    else if  (extension == "ico")
        imageData = new QPixmap(path.absoluteFilePath());
    else
    {
        exploitable = false;
        imageData = new QPixmap(imageFile);
    }

    image->setPixmap(imageData->scaled(72, 72,
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
    lay->addWidget(image, 0, Qt::AlignHCenter);
    lay->addWidget(descr, 0, Qt::AlignHCenter);
}

Fichier::~Fichier()
{
    delete descr;
    delete image;
    delete imageData;
    delete lay;
}
bool Fichier::getExploitable() const
{
    return exploitable;
}

void Fichier::setExploitable(bool value)
{
    exploitable = value;
}
QFileInfo Fichier::getPath() const
{
    return path;
}

void Fichier::setPath(const QFileInfo &value)
{
    path = value;
}

void Fichier::mousePressEvent(QMouseEvent *event)
{
    if (!path.isDir()
             && event->button() == Qt::LeftButton
             && image->geometry().contains(event->pos()))
    {

             QDrag *drag = new QDrag(this);
             QMimeData *mimeData = new QMimeData();

             mimeData->setText("commentEdit->toPlainText()");
             drag->setMimeData(mimeData);
             drag->setPixmap(imageData->scaled(64, 64, Qt::KeepAspectRatio));

             Qt::DropAction dropAction = drag->exec();
    }
}

void Fichier::mouseDoubleClickEvent(QMouseEvent *event)
{

    emit doubleClicked(this);
}

void Fichier::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void Fichier::dragLeaveEvent(QDragLeaveEvent *event)
{

}

void Fichier::dropEvent(QDropEvent *event)
{
    emit dropped((Fichier *) event->source(), this);
}

void Fichier::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}
QVBoxLayout *Fichier::getLay() const
{
    return lay;
}

void Fichier::setLay(QVBoxLayout *value)
{
    lay = value;
}

QLabel *Fichier::getDescr() const
{
    return descr;
}

void Fichier::setDescr(QLabel *value)
{
    descr = value;
}

QLabel *Fichier::getImage() const
{
    return image;
}

void Fichier::setImage(QLabel *value)
{
    image = value;
}

QPixmap *Fichier::getImageData() const
{
    return imageData;
}

void Fichier::setImageData(QPixmap *value)
{
    imageData = value;
}


