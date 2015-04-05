#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QProcess>
#include "fichier.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:
    void on_remonterDirDraggables_clicked();
    void on_remonterDirDroppables_clicked();

    void entrerDirDir(Fichier *file);
    void entrerDirImages(Fichier *file);
    void creerPersonnalisation(Fichier *src, Fichier *dest);
    void on_aideCheminRelatif_clicked();

    void on_pushButton_clicked();
    void clicDrive();
private:
    /**
     * @brief Vérifie si un Fichier est contenu dans un layout
     * @param layout
     * @param widget
     * @return
     */
    bool contient(QGridLayout *layout, Fichier *widget);
    void creerImages();
    void creerDossiers();
    void retirerLayout(QLayout *layout);
    void remonter(QDir &dir);
    Ui::MainWindow *ui;
    QGridLayout *gridImages = nullptr;
    QGridLayout *gridDossiers = nullptr;
    QDir dirDir;
    QDir dirImages;
};

#endif // MAINWINDOW_H
