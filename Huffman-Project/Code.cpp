#include "Code.h"



    Node *ordenTree(QList<Node*> list){
       Node *node;
       if(list.size() > 1){
        while(list.size() >1){
             for(int i = 0; i<list.size(); ++i){
                 for(int j = i+1; j<list.size(); ++j){
                     if(list.at(i)->freq > list.at(j)->freq){
                         list.move(j,i);
                         list.move(i+1,j);
                     }
                 }
             }

              node = new Node(list.at(0)->freq + list.at(1)->freq, 0x21, list.at(0), list.at(1));
             list.replace(0,node);list.removeAt(1);

         }
       }

       else
        node = list.at(0);

        return node;
    }


    QByteArray Coding( char c, Node *node){
          QByteArray  code;
          if(node->isLeaf())
             {
               if(node->content == c)
                  {
                    code = "";
                  }
             }
          else{

              if(!Coding(c, node->right).isNull()){
                  code.append("1").append(Coding(c, node->right));
              }
              if(!Coding(c, node->left).isNull()){
                  code.append("0").append(Coding(c, node->left));
              }
          }

          return code;

    }


    QByteArray Complete(QByteArray encode ){

         while(encode.size()%8 != 0){
             encode.append('0');
        }
        return encode;
    }


    int trashSize(QByteArray encode){
        return (Complete(encode).size() - encode.size());
    }


    QByteArray ToString(QByteArray encode){
        QByteArray s;
        QString aux;

        int i = 0;int j;
        bool ok;

        while(i<encode.size()){
            aux.clear();
            j = i;
            i += 8;
            while(j < i){
                aux.append(encode.at(j));
                ++j;
            }
            unsigned char c = aux.toInt(&ok,2);
            s.append(c);

        }
        return s;

    }


    QByteArray set(QByteArray str, int n){

        while(str.size() < n){
            str.insert(0,'0');
        }
        return str;
    }


    QByteArray Head(int trash, int Tsize){
       QByteArray trash_size = QByteArray::number(trash,2);
       
       QByteArray tree_size = QByteArray::number(Tsize,2);
      
       QByteArray head;
       head.append(set(trash_size,3)).append(set(tree_size,13));
       return head;
    }


    QString newName(QString name){
       QString newname = name;
       for(int j = newname.size() - 1; newname[j]!='.'; --j){
           newname.remove(j,1);
       }
       newname.remove(newname.size()-1,1);
       newname.append(".huff");

       return newname;
    }



    QPair<int,QString> zip(QString name){

      int char_f[256] = {0};
      QFile file(name);

        if(!file.open(QIODevice::ReadOnly)) {
            return QPair<int,QString> (1,"");

         }

     //contagem de caracteres:
         while (!file.atEnd()) {
             QByteArray line = file.readLine();
             for(int i = 0; i < line.size(); ++i) {
                 ++char_f[(unsigned char) line.at(i)];
             }
         }
         file.close();

      // lista:
         QList<char> l;
         QList<Node*> list;

         for(int j = 0; j < 256; ++j) {
             if(char_f[j]){

                l.append(j);

                 Node *n;
                 n = new Node(char_f[j],j);
                 list.append(n);
             }
         }

     // arvore:

         Node *tree;
         tree = ordenTree(list);

         QByteArray a = tree->ToByteArray(tree);

    // codificação:
       QString code[256];
       QString simb[l.size()];
         for(int i = 0; i < l.size(); ++i){
            unsigned char current = l.at(i);
             simb[i] = Coding(current,tree);
             code[current] = simb[i];
         }

        QByteArray encode;
         file.open(QIODevice::ReadOnly);
         while (!file.atEnd()) {
            QByteArray Line = file.readLine();
             for(int i = 0; i < Line.size(); ++i) {
                  unsigned char current = Line.at(i);
                  encode.append(code[current].toLocal8Bit());
             }
         }

         int tr = trashSize(encode);
         int tamArv = tree->ToByteArray(tree).size();
         int tamName = name.size();

         encode = Complete(encode);

        QByteArray head = Head(tr,tamArv);

        unsigned char x = tamName;
        head.append(set(QByteArray::number(x,2),8));


      //Cria o novo arquivo:

        QString newname = newName(name);

        QFile newfile(newname);
        if(!newfile.open(QIODevice::WriteOnly)){
            return QPair<int,QString> (1,"");

        }

        QByteArray aux;
        aux = (ToString(head));

        newfile.write(aux);
        aux.clear();
        aux.append(name);
        newfile.write(aux);

        aux = tree->ToByteArray(tree);
        newfile.write(aux);
        aux = ToString(encode);
        newfile.write(aux);

        newfile.close();

        return QPair<int,QString> (0,newname);



    }


