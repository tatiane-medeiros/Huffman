#include "gui.h"
#include "ui_gui.h"
#include<QWidget>
#include<QMessageBox>
#include<QFileDialog>
#include "Code.h"
#include "Decode.h"
#include <QDebug>


    Huffman::Huffman(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Huffman)
    {
        ui->setupUi(this);

    }

    Huffman::~Huffman()
    {
        delete ui;
    }

      void Huffman::on_comprime_clicked()
    {
        //comprime
       QString name = ui->arqOriginal->text();

       QString newname = newName(name);
        
       QString aux = ui->arqNovo->text();
       if(aux.size() > 1){
           
           newname = newLocal(newname, aux);

       }

       int _exit = zip(name,newname);

       if(_exit == 0){
          ui->arqNovo->setText(newname);
          QMessageBox info;
             info.setText("O arquivo foi comprimido com sucesso!");
             info.exec();

       }
       else{
           QMessageBox::information(this, "Erro", "  Não foi possivel abrir o arquivo!");
        }
    }

    void Huffman::on_descomprime_clicked()
    {
        //descomprime
        QString name = ui->arqOriginal->text();

        QString aux = ui->arqNovo->text();
        if(aux.size() < 2) aux = "";

        int _exit = unzip(name, aux).first;
        QString newname = unzip(name,aux).second;

         if(_exit == 0){
           ui->arqNovo->setText(newname);
           QMessageBox info;
              info.setText("O arquivo foi descomprimido com sucesso!");
              info.exec();
        }

        else if(_exit == 2){
            QMessageBox::information(this, "Erro", "  Insira um arquivo HUFF!");
        }
        else{
            QMessageBox::information(this, "Erro", "  Arquivo "+name+ " corrompido!");
        }


    }

    void Huffman::on_limpar_clicked()
    {
        ui->arqOriginal->clear();
        ui->arqNovo->clear();

    }

    void Huffman::on_toolButton_clicked()
    {
           ui->arqNovo->setText(QFileDialog::getExistingDirectory(this,tr("Save File"), "/home"));
    }

void Huffman::on_toolButton_2_clicked()
{
    ui->arqOriginal->setText(QFileDialog::getOpenFileName(this,tr("Open File"), "/home"));
}
