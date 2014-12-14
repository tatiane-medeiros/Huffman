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

         if(encode.size()%8 == 0) return 0;

        else
        return (8 - encode.size()%8);
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
       //set(trash_size,3);
       QByteArray tree_size = QByteArray::number(Tsize,2);
      // set(tree_size,13);
       QByteArray head;
       head.append(set(trash_size,3)).append(set(tree_size,13));
       return head;
    }


    QString newName(QString name){
       QString newname = name;
       int j;

       for(j = newname.size() - 1; j>=0; --j){
       if(newname.at(j) == '.'){
             newname.remove(j,(name.size() - j ));
             newname.append(".huff");
             break;

        }

       if(j == 0){
           newname = name;
           newname.append(".huff");
       }
       }
       qDebug() <<j;

       return newname;
    }

     QString newLocal(QString name, QString local){

             for(int i = name.size() - 1; i>0 ; --i){
                 if(name.at(i) == '/' ){
                     name.remove(0, i+1);
                     local.append('/');
                     name.insert(0, aux);
                     break;
                 }
             }
         }
         return name;
     }



    int zip(QString name, QString newname){
        if(newname.isEmpty() || newname.isNull()){
            newname = newName(name);
        }

      int char_f[256] = {0};
      
    // Abre o arquivo
      QFile file(name);

        if(!file.open(QIODevice::ReadOnly)) {
            return 1

         }
        if(file.size()<1) return 1;

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


         QFile newfile(newname);
         if(!newfile.open(QIODevice::WriteOnly)){
             return 1;

         }

        QByteArray encode;
         file.open(QIODevice::ReadOnly);
         while (!file.atEnd()) {
            QByteArray Line = file.read(1024);

             for(int i = 0; i < Line.size(); ++i) {
                  unsigned char current = Line.at(i);
                  encode.append(code[current]);
             }
         }
         file.close();

         int tr = trashSize(encode);
         int tamArv = tree->ToByteArray(tree).size();
         int tamName = name.size();

         encode = Complete(encode);

        QByteArray head = Head(tr,tamArv);

        unsigned char x = tamName;
        head.append(set(QByteArray::number(x,2),8));


      //Cria o novo arquivo:

        QByteArray aux;
        aux = (ToString(head));

        newfile.write(aux);
        aux.clear();
        aux.append(name);
        newfile.write(aux);

        aux = tree->ToByteArray(tree);
        qDebug() <<a;
        newfile.write(aux);
        aux = ToString(encode);
        newfile.write(aux);

        newfile.close();

        return 0);


    }


