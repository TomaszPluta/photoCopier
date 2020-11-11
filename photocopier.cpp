#include "photocopier.h"
#include "./ui_photocopier.h"

#include <QFileDialog>
#include <QDir>
#include <QComboBox>

#include <iostream>
#include <functional>

PhotoCopier::PhotoCopier(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhotoCopier)
{
    ui->setupUi(this);
   // connect(ui->pushButtonSource, SIGNAL(clicked()), SLOT(browse()));
    QObject::connect(ui->pushButtonSource, &QPushButton::clicked, this, [](){
        return &PhotoCopier::browseSource;
    }());
    QObject::connect(ui->pushButtoDestination, &QPushButton::clicked, this, [](){return &PhotoCopier::browseDestination;}());
}

PhotoCopier::~PhotoCopier()
{
    delete ui;
}


QString PhotoCopier::browse()
{
    return QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath());
}

void PhotoCopier::browseSource(void)
{
     ui->lineEditSource->setText(browse());
}

void PhotoCopier::browseDestination(void)
{
     ui->lineEditDestination->setText(browse());
}

//std::function<void()> X(void){
//    QLineEdit * le = new (QLineEdit);
//    std::function<void()> z = std::bind(&PhotoCopier::browse, le);
//    return z;
//}



//void PhotoCopier::browseX(QLineEdit * le)
//{
//    QString directory = QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath());
//    if (!directory.isEmpty()) {
//       le->setText(directory);
//    }
//}
