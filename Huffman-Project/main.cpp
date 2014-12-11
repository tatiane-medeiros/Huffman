#include <QApplication>
#include <QDebug>
#include <QString>
#include "gui.h"
#include "help.h"
#include "Code.h"
#include "Decode.h"

int main(int argc, char *argv[])
{


    if(argc == 2){

        if(argv[1] == "--help"){
            help();
        }

        else if(argv[1] == "--gui" ){
            QApplication a(argc, argv);

            Gui w;
            w.show();
            return a.exec();
        }


        else{
            QString name = argv[1];
            if(name.right(5) == ".huff"){
                int exit = unzip(name,"").first;

                check_desc(exit);
            }
            else{
                qDebug() << "   Erro! Insira um arquivo HUFF.\n";
            }
        }

    }

    else if( argc == 3 && argv[1] == "-c"){
        QString name = argv[2];
        QString newname = newName(name);
        int exit = zip(name, newname).first;
        check_comp(exit);

    }

    else if( argc == 5 && argv[1] == "-c" && argv[3] == "-o"){
        QString name = argv[2];
        QString newname = argv[4];
        int exit = zip(name, newname).first;
        check_comp(exit);

    }

    else if( argc == 4 && argv[2] == "-d"){
        QString name = argv[1];
        QString local = argv[3];
        int exit = unzip(name, local).first;
        check_desc(exit);
    }

    else{
        help();
    }



}
