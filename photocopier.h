#ifndef PHOTOCOPIER_H
#define PHOTOCOPIER_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class PhotoCopier; }
QT_END_NAMESPACE

class PhotoCopier : public QMainWindow
{
    Q_OBJECT

public:
    PhotoCopier(QWidget *parent = nullptr);
    ~PhotoCopier();
    QString browse();
    void browseSource();
    void browseDestination();

private:
    Ui::PhotoCopier *ui;

};
#endif // PHOTOCOPIER_H
