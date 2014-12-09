#include "gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString arg = argv[1];
    if(argc == 2 && arg == "--gui"){
    Gui w;
    w.show();
    }

    return a.exec();
}
