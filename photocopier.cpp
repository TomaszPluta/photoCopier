#include "photocopier.h"
#include "./ui_photocopier.h"

#include <QFileDialog>
#include <QDir>
#include <QComboBox>

#include <iostream>
#include <functional>






#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <stdarg.h>
#include <map>
#include <fstream>

#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <QScrollBar>


namespace fs = std::filesystem;
using namespace std::string_literals;

void CopyFromDirs( QTextEdit *textEditOutput, const fs::path &dirInpput, const fs::path &dirOutput);

PhotoCopier::PhotoCopier(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhotoCopier)
{
    ui->setupUi(this);
   // connect(ui->pushButtonSource, SIGNAL(clicked()), SLOT(browse()));
    QObject::connect(ui->pushButtonSource, &QPushButton::clicked, this, [](){ return &PhotoCopier::browseSource;}());
    QObject::connect(ui->pushButtoDestination, &QPushButton::clicked, this, [](){return &PhotoCopier::browseDestination;}());
    QObject::connect(ui->pushButtonStart, &QPushButton::clicked, this, &PhotoCopier::startCopying);
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



void PhotoCopier::startCopying(){
    CopyFromDirs(ui->textEditOutput, ui->lineEditSource->text().toStdString(),  ui->lineEditDestination->text().toStdString());
}



using recursive_directory_iterator = fs::recursive_directory_iterator;

void CopyFromDirs( QTextEdit *textEditOutput, const fs::path &dirInpput, const fs::path &dirOutput){
      //fs::create_directories(argv[2]);
    int i = 0;
    fs::path dirOutputAbsoulte = fs::absolute(dirOutput);
    std::cout<<dirOutputAbsoulte;
    textEditOutput->append(QString::fromStdString(std::string(dirOutputAbsoulte)));
    fs::create_directory(dirOutputAbsoulte);
    for (const auto& dirEntry : recursive_directory_iterator(dirInpput)){
        if (fs::is_regular_file(dirEntry)){
            fs::copy(dirEntry, dirOutput / dirEntry.path().filename() );
                std::cout << "copied: "<<dirEntry << std::endl;
                   textEditOutput->append(QString::fromStdString(std::string( "copied: " + std::string(dirEntry.path().string()) + " ")));
                if (size_t pos = dirEntry.path().filename().string().find("BURST"); pos != std::string::npos){
                     std::string newFileName{dirEntry.path().filename().string()};
                     newFileName = newFileName.substr(pos + std::string("BURST").length());
                     try
                     {
                        fs::rename(dirOutput / dirEntry.path().filename(), dirOutput / newFileName);
                        std::cout << " after renaming to:  "<<dirOutput / newFileName  << std::endl  << std::endl;
                        std::string renamedPath (dirOutput / newFileName );
                         textEditOutput->append(QString::fromStdString(std::string( " after renaming to:  " + renamedPath + "\n" )));
                     }
                     catch (fs::filesystem_error const& error)
                     {
                        std::cout << error.code() << "\n" << error.what() << "\n";
                        textEditOutput->append(QString::fromStdString(std::string( "error  " + std::string(error.what() ) + "\n" )));
                     }
                }else{
                    std::cout << " to:  "<<dirOutput / dirEntry.path().filename()  << std::endl  << std::endl;
                    std::string renamedPath (dirOutput / dirEntry.path().filename() );
                    textEditOutput->append(QString::fromStdString(std::string( " to:  " + renamedPath + "\n" )));
                }


            i++;
        }
    }
    std::cout<<"copied: "<<i<< " files";
     textEditOutput->append(QString::fromStdString("copied: " + std::to_string(i))+ "");
      textEditOutput->append(QString("SUCCESS!\n"));
      textEditOutput->verticalScrollBar()->setValue(textEditOutput->verticalScrollBar()->maximum());
}

