#include "gui.h"
#include "ui_gui.h"
#include<QWidget>
#include<QMessageBox>
#include "Code.h"
#include "Decode.h"


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

       int exit = zip(name).first;
       QString newname = zip(name).second;
       if(exit == 0){
          ui->arqNovo->setText(newname);
          QMessageBox::information(this, "", "  Arquivo comprimido com sucesso!");
       }
       else{
           QMessageBox::information(this, "Erro", "  Arquivo "+name+" corrompido!");
       }


    }

    void Gui::on_descomprime_clicked()
    {
        //descomprime
        QString name = ui->arqOriginal->text();
        int exit = unzip(name).first;
        QString newname = unzip(name).second;
        if(exit == 0){
           ui->arqNovo->setText(newname);
           QMessageBox::information(this, "", "  Arquivo descomprimido com sucesso!");
        }

        else if(exit == 2){
            QMessageBox::information(this, "Erro", "  Arquivo inválido!");
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
