#include "HTree.h"

HTree::HTree()
{
    m_root = new Node();
    m_curr = new Node();
}

HTree::HTree(Node* root)
{
    m_root = root;
    m_curr = m_root;
}

HTree::~HTree()
{
    delete this;
}

void HTree::buildTree(int *array){

    QList<Node* > nodeList;

    for(int i = 0; i<256; ++i){
        if(array[i] != 0){
            Node* tmp = new Node(i, array[i], NULL, NULL);
            nodeList.append(tmp);

        }
    }


    while(nodeList.size() > 1){
        nodeList = insort(nodeList);
        Node* left = nodeList.at(0); Node* right = nodeList.at(1);
        Node* aux = new Node(0x21, left->m_freq + right->m_freq, left, right);
        nodeList.removeFirst();
        nodeList.removeFirst();
        nodeList.prepend(aux);

    }

    m_root = nodeList.at(0);

}


QByteArray HTree::representation(){
    QByteArray aux;
    if(m_root == 0) return "";

       if(m_root->isLeaf()){
           if(m_root->m_content == 0x21 || m_root->m_content == 0x2A) aux.append(0x2A);
           aux.append(m_root->m_content);
       }
        else{

            HTree* sub1 = new HTree(m_root->m_left);
            HTree* sub2 = new HTree(m_root->m_right);

            aux.append('!').append(sub1->representation()).append(sub2->representation());

        }

    return aux;

}




QList<Node*> HTree::insort(QList<Node *> mylist){

    for(int i = 0; i< mylist.size() - 1; ++i){
         for(int j=i+1; j< mylist.size(); ++j){
             if(mylist.at(j)->m_freq < mylist.at(i)->m_freq){
                 mylist.swap(i, j);
             }
           }
       }

      return mylist;
}


QByteArray HTree::code(const uchar cont){
    QByteArray Code;
    if(m_root->isLeaf()){
        if(m_root->m_content == cont && m_root->m_freq != 0) return "";
    }
    else{
        HTree *sub1 = new HTree(m_root->m_right);
        HTree *sub2 = new HTree(m_root->m_left);

        if(!sub1->code(cont).isNull()){
            Code.append("1").append(sub1->code(cont));
        }
        else if(!sub2->code(cont).isNull()){
            Code.append("0").append(sub2->code(cont));
        }
    }

    return Code;

}

QHash<uchar, QByteArray> HTree::codeRef(int *array){
    QByteArray aux;
    QHash<uchar, QByteArray> ref;
    for(int i = 0; i<256; ++i){
        if(array[i] != 0){
            aux = this->code(uchar(i));
            ref.insert(uchar(i), aux);

        }
    }
    return ref;

}


QPair<Node *, int> HTree::FromByteArray(QByteArray data, int pos){
    uchar current = data.at(pos);

    if(current != 0x21){
        if(current == 0x2A){
            ++pos;
            current = data.at(pos);
        }

        return QPair<Node*, int> (new Node(current,0,NULL,NULL), pos);
    }
    QPair<Node*, int> leftNode = FromByteArray(data, pos+1);
    QPair<Node*, int> rightNode = FromByteArray(data, leftNode.second +1);
    Node* node = new Node(0x21, 0, leftNode.first, rightNode.first);
    return QPair<Node*, int> (node , rightNode.second);
}


void HTree::rebuildTree(const QByteArray rep){
    m_root = FromByteArray(rep, 0).first;

}

Node *HTree::getCurr() {
    return m_curr;
}

void HTree::setCurrRoot(){
    m_curr = m_root;
}


bool HTree::find(bool value)
{

    if(value) m_curr = m_curr->m_right;
    else m_curr = m_curr->m_left;

    if(m_curr->isLeaf()) return true;
    else return false;

}


void HTree::showTree(){
    qDebug("arvore:\n%s", qPrintable(m_root->toLine(0,m_root)));
}


