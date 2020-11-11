#ifndef PHOTOCOPIER_H
#define PHOTOCOPIER_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>


QT_BEGIN_NAMESPACE
namespace Ui { class PhotoCopier; }
QT_END_NAMESPACE

class PhotoCopier : public QMainWindow
{
    Q_OBJECT

public:
    PhotoCopier(QWidget *parent = nullptr);
    ~PhotoCopier();
    void browse();

private:
    Ui::PhotoCopier *ui;

};
#endif // PHOTOCOPIER_H
