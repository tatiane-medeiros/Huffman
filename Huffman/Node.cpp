#include "Node.h"


Node::Node(){
    m_freq = 0;
    m_left = NULL;
    m_right = NULL;
}

Node::Node(uchar content, int freq, Node *left, Node *right){
    m_content = content;
    m_freq = freq;
    m_left = left;
    m_right = right;
}

bool Node::isLeaf(){
    if(m_left == NULL && m_right == NULL) return true;

    return false;
}

QString Node::toLine(int num, Node *n){
    QString aux;
    aux += QString("   ").repeated(num);
    aux.append(n->m_content).append('\n');

    if(n->isLeaf()) return aux;

    else{
        aux.insert(0,toLine(num + 1, n->m_right));
        aux.append(toLine(num + 1, n->m_left));

        return aux;
    }
}
