#ifndef FICHIER_H
#define FICHIER_H
#include <QPixmap>
#include <QLabel>
#include <QFileInfo>
#include <QString>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QDir>
class Fichier : public QWidget
{
    Q_OBJECT

    public:
            Fichier(QFileInfo path, QWidget *parent = 0);
            virtual ~Fichier();
            bool getExploitable() const;
            void setExploitable(bool value);

            QFileInfo getPath() const;
            void setPath(const QFileInfo &value);

            QPixmap *getImageData() const;
            void setImageData(QPixmap *value);

            QLabel *getImage() const;
            void setImage(QLabel *value);

            QLabel *getDescr() const;
            void setDescr(QLabel *value);

            QVBoxLayout *getLay() const;
            void setLay(QVBoxLayout *value);

protected:
            void mousePressEvent(QMouseEvent  *event);
            void mouseDoubleClickEvent(QMouseEvent *event);
            void dragEnterEvent(QDragEnterEvent* event);
            void dragLeaveEvent(QDragLeaveEvent* event);
            void dropEvent(QDropEvent *event);
            void dragMoveEvent(QDragMoveEvent *event);
    signals:
            void doubleClicked(Fichier *file);
            void dropped(Fichier *src, Fichier *dest);
    private:
            const QString imageDir = "://img/Folder.png";
            const QString imageFile = "://img/Finger.png";
            QPixmap *imageData;
            QLabel *image;
            QLabel *descr;
            QVBoxLayout *lay;
            bool exploitable;
            QFileInfo path;
};

#endif // FICHIER_H
