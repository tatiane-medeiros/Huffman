#ifndef DECODE_H
#define DECODE_H
#include <QList>
#include <QByteArray>
#include <Node.h>
#include <QString>
#include <QPair>
#include <Code.h>

//Recebe o codigo binario dos dois primeiros caracteres:
QByteArray FromHead(char c1, char c2);

//Retorna o tamanho do lixo e da arvore:
QPair<int, int> Sizes(QByteArray code);

//Reconstrói o texto original
 QByteArray Rebuild(QByteArray text, Node* root, int trash);

//Cria o arquivo descompactado:
QPair<int, QString> unzip(QString name);



#endif // DECODE_H
