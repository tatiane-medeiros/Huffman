#include "gui.h"
#include "ui_gui.h"


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
          QString file = ui->nameFile->text();
           QString local = ui->newFile->text();
           QString new_file;
           if(!local.isEmpty()) new_file = newDirectory(file, local);
           new_file = Rename(file);
          compress(file, new_file);

          ui->newFile->setText(new_file);
          QMessageBox info;
          info.setText(QString("O arquivo \"")+file+ QString("\" foi comprimido com sucesso!"));
          info.exec();

    }

    void Huffman::on_descomprime_clicked()
    {
        //descomprime
        QString file = ui->nameFile->text();
        QString local = ui->newFile->text();

        decompress(file, local);
         QMessageBox info;
         info.setText("O arquivo foi descomprimido com sucesso!");
         info.exec();

    }

    void Huffman::on_limpar_clicked()
    {
       ui->nameFile->clear();
       ui->newFile->clear();

    }

    void Huffman::on_toolButton_clicked()
    {
         ui->nameFile->setText(QFileDialog::getOpenFileName(this,tr("Open File"), "/home"));
    }

    void Huffman::on_toolButton_2_clicked()
    {
       ui->newFile->setText( QFileDialog::getExistingDirectory(this,tr("Save File"), "/home"));


    }
