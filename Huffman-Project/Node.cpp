#include "Node.h"

Node::Node(){
    freq = 0;
    content = 0;
}

bool Node:: isLeaf(){
    return((this->left == NULL)&&(this->right == NULL));
  }


QByteArray Node:: ToByteArray(Node *node)
{
    QByteArray ret;
   if(node->isLeaf())
      {
        if(node->content == 0x21)
           {

              ret.append(0x23);
           }
        ret.append(node->content);
        return ret;
      }
   else{
        return (ret.append(0x21).append(ToByteArray(node->left)).append(ToByteArray(node->right)));
   }
}



QPair<Node*, int> Node::FromByteArray(QByteArray data, int pos){
    char current = data.at(pos);
    if(current != 0x21){
        if(current == 0x23){
            ++pos;
            current = data.at(pos);
        }
        return QPair<Node*, int> (new Node(0,current), pos);
    }

        QPair<Node*, int> left = this->FromByteArray(data, pos+1);
        QPair<Node*, int> right = this->FromByteArray(data, left.second +1);
        Node* node = new Node(0,0x21, left.first, right.first);
        return QPair<Node*, int> (node , right.second);

}

void Node::ordenList(QList<Node*> list){
        for(int i = 0; i<list.size(); ++i){

            for(int j = i+1; j<list.size(); ++j){
                if(list.at(i)->freq < list.at(j)->freq){
                    list.move(j,i);
                    list.move(i+1,j);
                }
            }
        }
    }
