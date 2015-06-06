#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

namespace Ui {
class Huffman;
}

class Huffman : public QMainWindow
{
    Q_OBJECT

public:
    explicit Huffman(QWidget *parent = 0);
    ~Huffman();


private slots:
    void on_comprime_clicked();

    void on_descomprime_clicked();

    void on_limpar_clicked();

    void on_toolButton_clicked();


    void on_toolButton_2_clicked();

private:
    Ui::Huffman *ui;
};

#endif // GUI_H
