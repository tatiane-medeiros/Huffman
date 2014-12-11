#include "gui.h"
#include "ui_gui.h"
#include<QWidget>
#include<QMessageBox>
#include<QFileDialog>
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

       int exit = zip(name,"").first;
       QString newname = zip(name,"").second;
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
        int exit = unzip(name,"").first;
        QString newname = unzip(name,"").second;
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





void Gui::on_toolButton_2_clicked()
{

}


