#include "huffman.h"
#include <QApplication>
#include "zip.h"
#include "help.h"



int main(int argv, char* argc[])
{
    clockid_t s, e;
s=clock();
     if(argv == 2){

         QString name =argc[1];
         if(name == "--gui"){
             QApplication a(argv, argc);
             Huffman w;
             w.show();
             return a.exec();

         }
         else if(name.right(5) == ".huff") decompress(name);

         else help();
     }
     else if(argv == 3){
       QString name;

       if(!strcmp(argc[1],"-c")){
           name = argc[2];
           compress(name);
       }
       else if(!strcmp(argc[2],"-d")){
           name = argc[1];
           decompress(name);
       }

       else help();
     }

     else if(argv == 4){
         if(!strcmp(argc[2],"-d")){
             QString name = argc[1];
             QString local = argc[3];
             decompress(name, local);
         }
         else help();
     }

     else if(argv == 5){
          QString name = argc[2];
          QString newname = argc[4];
         if(!strcmp(argc[1],"-c") && !strcmp(argc[3],"-o")){
              compress(name, newname);
          }
          else help();

     }
     else help();
e=clock();
    double time = (e-s)/1000;
    qDebug()<<time<<'s';

    return 0;
}
