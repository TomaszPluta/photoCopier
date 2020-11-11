#include "photocopier.h"
#include "./ui_photocopier.h"

#include <QFileDialog>
#include <QDir>
#include <QComboBox>

#include <iostream>

PhotoCopier::PhotoCopier(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhotoCopier)
{
    ui->setupUi(this);
   // connect(ui->pushButtonSource, SIGNAL(clicked()), SLOT(browse()));
    QObject::connect(ui->pushButtonSource, &QPushButton::clicked, this, &PhotoCopier::browse);
}

PhotoCopier::~PhotoCopier()
{
    delete ui;
}



void PhotoCopier::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath());
    if (!directory.isEmpty()) {
//        if (directoryComboBox->findText(directory) == -1)
//            directoryComboBox->addItem(directory);
//        directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
    }
}
