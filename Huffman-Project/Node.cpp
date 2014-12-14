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
        char c = node->content;
        ret.append(c);
        return ret;
      }
   else{
        return (ret.append(0x21).append(ToByteArray(node->left)).append(ToByteArray(node->right)));
   }
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
