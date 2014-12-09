#ifndef CODE_H
#define CODE_H

#include <QList>
#include <QByteArray>
#include <Node.h>
#include <QString>
#include <QFile>


//  Constrói a arvore utilizando a frequencia:
   Node *ordenTree(QList<Node*> list);

//  Retorna o codigo de cada caractere na árvore:
   QByteArray Coding( char c, Node *node);

//  Completa o ultimo byte do texto
    QByteArray Complete(QByteArray encode );

//  retorna o tamanho do lixo
    int trashSize(QByteArray encode);

//constói o novo texto do arquivo
    QByteArray ToString(QByteArray encode);

//  Posiciona os bits:
    QByteArray set(QByteArray str, int n);

//  Constrói o cabeçalho do arquivo
   QByteArray Head(int trash, int Tsize);

//  Retorna o nome do novo arquivo:
   QString newName(QString name);

//Cria o arquivo compactado:
   QPair<int, QString> zip(QString name);



#endif // CODE_H
