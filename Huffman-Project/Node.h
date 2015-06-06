#ifndef NODE_H
#define NODE_H

#include<QString>
#include<QList>
#include<QPair>

class Node{

     public:

      unsigned char content;
      int freq;
      Node *left;
      Node *right;
      Node();

      Node(int freq, unsigned char content , Node *left , Node *right );

      ~Node();

      //Retorna se o Nó é uma folha
        bool isLeaf();

      //Cria a representação para a árvore
        QByteArray ToByteArray(Node *node);

      //ordena a lista de Node;
        void ordenList(QList<Node*> list);


};

#endif // NODE_H
