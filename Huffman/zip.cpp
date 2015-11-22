#include "zip.h"



int* countbytes(const QString name){
    int* array = new int[256];

    for(int i = 0; i<256; ++i) array[i] = 0;

    QFile file(name);

    Q_ASSERT_X(file.open(QIODevice::ReadOnly), Q_FUNC_INFO, "file not found.");

    while (!file.atEnd()) {
         QByteArray line = file.read(1024);
              for(int i = 0; i < line.size(); ++i) {
                 ++array[(unsigned char) line.at(i)];
              }
     }
    file.close();
    return array;

}


void show(int *array){
    for(int i=0; i<256; ++i){
        bool ok;
        uchar a = QByteArray::number(i).toInt(&ok,16);

        if(array[i] != 0) std::cout <<i<<' '<< a<<' '<< array[i]<< std::endl;

    }
   std::cout <<"\n\n";

}



QPair<QByteArray, int> toByte(QByteArray bits){
    int len = bits.size();
    int trash = 0;
    if( len%8 != 0){
        trash = 8 - len%8;
        bits.append(QByteArray("0").repeated(trash));
    }

    QByteArray bytes;
    QByteArray aux;
    for(int i=0; i<len; i+=8){
        for(int j=i; j<i+8; ++j){
           aux += bits.at(j);
        }
        bool ok;

        bytes.append(uchar(aux.toInt(&ok, 2)));
        aux.clear();
    }

    return QPair<QByteArray, int> (bytes, trash);

}



QByteArray Head(int trash, int Tsize){

   BitVector t, tree, aux;
   t.setValue(trash, 3);
   tree.setValue(Tsize, 13);
   aux.append(t);
   aux.append(tree);

   QByteArray head = aux.toBytes();

   return head;
}




void compress(QString name, QString newName)
{
    if(newName.right(5) != QString(".huff")) qDebug("Insira um arquivo huff!");
    else{

        clock_t  start, end;
        start = clock();

        int* freq = countbytes(name);
        HTree* tree = new HTree();
        tree->buildTree(freq);      //constrói a arvore
        QHash<uchar, QBitArray> ref = tree->codeRef(freq);   //codificação de cada caractere na arvore
        QFile myfile(name);
        myfile.open(QIODevice::ReadOnly);
       // QByteArray bitArray;

         BitVector bits;
        while (!myfile.atEnd()) {       //codifica o arquivo
             QByteArray line = myfile.read(1024);
             for(int i=0; i<line.size(); ++i){
                //bitArray.append(ref.value(line.at(i)));
                 bits.append(ref.value(line.at(i)));
             }
            // bits += bits.binCode(bitArray);
            // bitArray.clear();
        }
        myfile.close();

        int trashSize = bits.complete();
        QByteArray code = bits.toBytes();
        QByteArray treeRep = tree->representation();
        int treeSize = treeRep.size();

        QFile newfile(newName);
        newfile.open(QIODevice::WriteOnly);     //constroi arquivo compactado
        int nameSize = name.size();

        QByteArray aux;
        aux = Head(trashSize, treeSize);
        aux.append(uchar(nameSize));
        newfile.write(aux);
        aux.clear();
        aux.append(name);

        newfile.write(aux);
        aux.clear();
        newfile.write(treeRep);
        newfile.write(code);

        end = clock();
        code.clear();

        newfile.close();
        double time = (end-start)/1000;
        qDebug()<<"Arquivo" << newName <<"criado com sucesso!" <<time<<'s';
      }

}

void compress(QString name){
     QString newname = Rename(name);
     compress(name, newname);

}


QString Rename(const QString name){
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

    return newname;
}



int trashSize(QByteArray data){
    BitVector bits;
    bits = bits.toBits(data);
    BitVector aux;
    aux += bits.binCode("111");
    aux &= bits;
    int trash = aux.value();
    return trash;
}


int treeSize(QByteArray data){
    BitVector bits;
    bits = bits.toBits(data);
    BitVector aux;
    aux += bits.binCode("0001111111111111");
    aux &= bits;
    int tree_size = aux.value();
    return tree_size;
}


QBitArray toBits(const QByteArray bytes){
    QBitArray bits(bytes.count()*8);

    for(int i=0; i<bytes.count(); ++i) {
        for(int b=0; b<8;++b) {
            bits.setBit( i*8+b, bytes.at(i)&(1<<(7-b)) );
        }
    }
    return bits;
}


QString newDirectory(QString name, QString local){
    local.append('\\');
       for(int i = name.size() - 1; i>0 ; --i){
           if((name.at(i) == '/') || (name.at(i) == '\\') ){
               name.remove(0, i+1);
               break;
           }
       }
       name.insert(0,local);
   return name;
}


void decompress(QString name, QString local){

    QFile compFile(name);
    Q_ASSERT_X(compFile.open(QIODevice::ReadOnly), Q_FUNC_INFO, "file not found.");
    if(name.right(5) != QString(".huff")) qDebug()<<"insira um arquivo \".huff\"";
    else{
        clock_t  start, end;
        start = clock();

    QByteArray aux = compFile.read(3);  // Lendo o cabeçalho
    int nameSize = uchar(aux.at(2));
    aux.chop(1);

    int trash = trashSize(aux);
    int treesize = treeSize(aux);
    aux.clear();


    aux = compFile.read(nameSize);  //nome original
    QString myName = aux;
    aux.clear();
    aux = compFile.read(treesize);  //representação da arvore

    HTree *tree = new HTree();
    tree->rebuildTree(aux);  //reconstrói a arvore
    aux.clear();

    QBitArray code;
    QByteArray fileText;
    bool bit;
     tree->setCurrRoot();
    while(!compFile.atEnd()){
        aux = compFile.read(1024);
        code = toBits(aux);

        if(compFile.atEnd()) code.resize(code.size() - trash);

        for(int i=0; i<code.size(); ++i){
           bit = tree->find(code.at(i));
           if(bit){
                uchar c = tree->getCurr()->m_content;                
                fileText.append(c);
                tree->setCurrRoot();
            }
        }
        code.clear();
        aux.clear();

    }

    compFile.close();
   if(!local.isEmpty()) myName = newDirectory(myName, local);

   QFile original(myName);
   original.open(QIODevice::WriteOnly);
   original.write(fileText);
   original.close();


    end = clock();
    double time = (end-start)/1000 ;
    qDebug()<<"arquivo"<<myName<<"descomprimido!" << time<<'s';
    }

}


void decompress(QString name)
{
    decompress(name, "");
}










