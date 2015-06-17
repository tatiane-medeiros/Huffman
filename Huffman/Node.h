#ifndef NODE
#define NODE
#include <QDebug>
#include <QObject>

class Node{

public:
    uchar m_content;
    int m_freq;
    Node* m_left;
    Node* m_right;

    Node();
    Node(uchar content, int freq, Node* left, Node* right);

    //Retorna se o nó é folha
    bool isLeaf();
    //Exibe a arvore
    QString toLine(int num, Node* n);



};

#endif // NODE

