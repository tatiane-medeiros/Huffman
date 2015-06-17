#ifndef ZIP
#define ZIP
#include <QFile>
#include <QTextStream>
#include "HTree.h"
#include <time.h>



//frequência de cada caractere no arquivo
int* countbytes(const QString name);
//exbe o array das frequências
void show(int *array);
//cria os dois primeiros bytes do cabeçalho
QByteArray Head(int trash, int Tsize);
//transforma a codificação binaria em bytes
QPair<QByteArray, int> toByte(QByteArray bits);
//codifica o arquivo usando a arvore de huffman.
void compress(QString name, QString newN);
void compress(QString name);
//retorna o tamanho do lixo e da arvore
QPair<int,int> sizes(QByteArray data);
//transforma qbytearray em qbitarray
QBitArray toBits(const QByteArray);
//descomprime o arquivo
void decompress(QString name, QString local);
void decompress(QString name);
//nome do arquivo ".huff"
QString newName(const QString name);
//altera local do arquivo
QString newDirectory(QString name, QString local);




#endif // ZIP

