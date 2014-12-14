#include "gui.h"
#include "ui_gui.h"
#include<QWidget>
#include<QMessageBox>
#include<QFileDialog>
#include "Code.h"
#include "Decode.h"
#include <QDebug>


    Gui::Gui(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Gui)
    {
        ui->setupUi(this);
    }

    Gui::~Gui()
    {
        delete ui;
    }

    void Gui::on_comprime_clicked()
    {
        //comprime
       QString name = ui->arqOriginal->text();
       
       QString newname = newName(name);
        
       QString aux = ui->arqNovo->text();
       if(aux.size() > 1){
           
           newname = newLocal(newname, aux);
           }
       }       

       int exit = zip(name,newname);

       if(exit == 0){
          ui->arqNovo->setText(newname);
          QMessageBox info;
             info.setText("O arquivo foi comprimido com sucesso!");
             info.exec();

       }
       else{
           QMessageBox::information(this, "Erro", "  Não foi possivel abrir o arquivo!");
        }
    }

    void Gui::on_descomprime_clicked()
    {
        //descomprime
        QString name = ui->arqOriginal->text();

        QString aux = ui->arqNovo->text();
        if(aux.size() < 2) aux = "";

        int exit = unzip(name, aux).first;
        QString newname = unzip(name,aux).second;

         if(exit == 0){
           ui->arqNovo->setText(newname);
           QMessageBox info;
              info.setText("O arquivo foi descomprimido com sucesso!");
              info.exec();
        }

        else if(exit == 2){
            QMessageBox::information(this, "Erro", "  Insira um arquivo HUFF!");
        }
        else{
            QMessageBox::information(this, "Erro", "  Arquivo "+name+ " corrompido!");
        }


    }

    void Gui::on_limpar_clicked()
    {
        ui->arqOriginal->clear();
        ui->arqNovo->clear();
    }

    void Gui::on_toolButton_clicked()
    {
           ui->arqNovo->setText(QFileDialog::getExistingDirectory(this,tr("Save File"), "/home"));
    }


