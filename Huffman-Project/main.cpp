#include <QApplication>
#include <QDebug>
#include <QString>
#include "gui.h"
#include "help.h"
#include "Code.h"
#include "Decode.h"

int main(int argc, char *argv[])
{
    QString arg[argc];
    for(int i=1;i<argc;++i){
        arg[i]=argv[i];
    }

    if(argc == 2){

        if(arg[1] == "--help"){
            help();
        }

        else if(arg[1] == "--gui" ){
            QApplication a(argc, argv);

            Huffman w;
            w.show();
            return a.exec();
        }


        else{
            QString name = arg[1];
            if(name.right(5) == ".huff"){
                int exit = unzip(name,"").first;

                check_desc(exit);
            }
            else{
                qDebug() << "   Erro! Insira um arquivo HUFF.\n";
            }
        }

    }

    else if( argc == 3 && arg[1] == "-c"){
        QString name = arg[2];
        QString newname = newName(name);
        int exit = zip(name, newname);
        check_comp(exit);

    }

    else if( argc == 5 && arg[1] == "-c" && arg[3] == "-o"){
        QString name = arg[2];
        QString newname = arg[4];
        int exit = zip(name, newname);
        check_comp(exit);

    }

    else if( argc == 4 && arg[2] == "-d"){
        QString name = arg[1];
        QString local = arg[3];
        int exit = unzip(name, local).first;
        check_desc(exit);
    }

    else{
        help();
    }

return 0;

}
