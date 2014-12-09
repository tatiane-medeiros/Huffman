#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

private slots:
    void on_comprime_clicked();

    void on_descomprime_clicked();


    void on_limpar_clicked();

private:
    Ui::Gui *ui;
};

#endif // GUI_H
