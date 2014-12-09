#ifndef NODE_H
#define NODE_H

#include<QString>
#include<QList>
#include<QPair>

class Node{

     public:

      char content;
      int freq;
      Node *left;
      Node *right;
      Node();
      Node(int freq = 0,  char content = 0, Node *left = NULL, Node *right = NULL){
        this->content = content;
          this->freq = freq;
        this->left = left;
        this->right = right;
       }
      ~Node();

      //Retorna se o Nó é uma folha
        bool isLeaf();

      //Cria a representação para a árvore
        QByteArray ToByteArray(Node *node);

      //Retorna a árvore a partir da representação em string
        QPair<Node*, int> FromByteArray(QByteArray data, int pos);

      //ordena a lista de Node;
        void ordenList(QList<Node*> list);


};

#endif // NODE_H
