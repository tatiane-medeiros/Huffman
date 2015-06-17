#ifndef HTREE_H
#define HTREE_H
#include "Node.h"
#include "bitvector.h"
#include <QList>
#include <iostream>
#include <QPair>
#include <QHash>


class HTree
{
private:
    Node* m_root;
    Node* m_curr;

    //ordena a lista
    QList<Node*> insort(QList<Node*> mylist);
    //Retorna um nó a partir da representação em string
    QPair<Node*, int> FromByteArray(QByteArray data, int pos);

public:
    HTree();
    HTree(Node* root);
    ~HTree();
    //constói a arvore de Huffman
    void buildTree(int *array);
    //cria a representação da arvore
    QByteArray representation();
    //retorna a codificação de um caractere na arvore
    QByteArray code(const uchar cont);
    //lista as codificações de todos os caracteres do arquivo
    QHash<uchar, QByteArray> codeRef(int *array);
    //reconstói a arvore a arvore a partir da representação
    void rebuildTree(const QByteArray rep);

    Node *getCurr();
    void setCurrRoot();

    bool find(bool value);
    //exibe a arvore
    void showTree();



};

#endif // HTREE_H
