#include "Decode.h"


    //Recebe o codigo binario dos dois primeiros caracteres:
    QByteArray FromHead(char c1, char c2){
        QByteArray code;
        code.append(set(QByteArray::number((unsigned char)c1,2),8));
        code.append(set(QByteArray::number((unsigned char)c2,2),8));
        return code;
    }

    //Retorna o tamanho do lixo e da arvore:
    QPair<int, int> Sizes(QByteArray code){
        bool ok;
        QByteArray y = code, z = code.right(13);
        y.truncate(3);

        int trash = y.toInt(&ok,2) ;
        int treeSize =z.toInt(&ok,2);
        return QPair<int,int> (trash, treeSize);
    }

    //Reconstrói o texto original
     QByteArray Rebuild(QByteArray text, Node* root, int trash){
         text.truncate(text.size() - trash);

        QByteArray newtext;
        Node* current = root;
        for(int i=0; i<text.size(); i++){
           if(text.at(i) == '0'){
               current = current->left;
           }
           else{
               current = current->right;
           }
           if(current->isLeaf()){
               char c = current->content;
               newtext.append(c);
               current = root;
           }
        }
        return newtext;
    }


     QPair<int, QString> unzip(QString name){
         //decodificar

         if(name.right(5) != (QString)".huff"){
               return QPair<int, QString> (2,"");
        }

         QFile newfile(name);
           if(!newfile.open(QIODevice::ReadOnly)) {
               return QPair<int, QString> (1,"");
            }

     // Lendo o cabeçalho:
           QByteArray aux = newfile.read(2);

            aux = FromHead(aux[0],aux[1]);

           int tr = Sizes(aux).first ;
           int tamArv = Sizes(aux).second;
            aux = newfile.read(1);
           int tamName = aux.at(0);


     // Recebe o nome do arquivo original:
           QByteArray original = newfile.read(tamName);


     // Recebe a representação da árvore:
            QByteArray T;
            T.append(newfile.read(tamArv));


           Node *tree;
           tree = tree->FromByteArray(T, 0).first;

     // Converte os caracteres do arquivo em binário:
          QByteArray aux2;
           while (!newfile.atEnd()) {
               QByteArray line = newfile.read(1024);
               for(int i=0; i<line.size(); ++i){
                  unsigned char current = line.at(i);
                    QByteArray a = set(QByteArray::number(current,2),8);

                    aux2.append(a);
               }
           }

     // Reconstrói o arquivo original:

           QByteArray text = Rebuild(aux2, tree, tr);


           QFile myfile(original);
          if(!myfile.open(QIODevice::WriteOnly)){
              return QPair<int, QString>(1,"");
          }
          else{

           myfile.write(text);

           myfile.close();
           return QPair<int, QString> (0,original);
          }

     }

