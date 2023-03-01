//二叉树的递归遍历
//
#include<iostream>
using namespace std;

class Tree
{
public:
  Tree(char value)
  {
    this->left=nullptr;
    this->right=nullptr;
    this->value=value;
  }
  Tree* left;
  Tree* right;
  char value;
};

void Destory(Tree* root)
{
  if(root==nullptr)
  {
    return ;
  }
  Destory(root->left);
  Destory(root->right);
  delete root;
}

void pre(Tree* root)
{
  if(root==nullptr)
  {
    return ;
  }
  cout<<root->value<<" ";
  pre(root->left);
  pre(root->right);
}

void in(Tree* root)
{
  if(root==nullptr)
  {
    return ;
  }
  in(root->left);
  cout<<root->value<<" ";
  in(root->right);
}

void end(Tree* root)
{
  if(root==nullptr)
  {
    return ;
  }
  end(root->left);
  end(root->right);
  cout<<root->value<<" ";
}



int main()
{
  Tree* head=new Tree('A');
  Tree* node1=new Tree('B');
  Tree* node2=new Tree('C');
  Tree* node3=new Tree('D');
  Tree* node4=new Tree('E');
  Tree* node5=new Tree('F');
  Tree* node6=new Tree('G');
  head->left=node1;
  head->right=node2;
  node1->left=node3;
  node1->right=node4;
  node2->left=node5;
  node2->right=node6;

  //先序遍历
  pre(head);
  cout<<"==================="<<endl;
  //中序遍历
  in(head);
  cout<<"==================="<<endl;
  //后序遍历
  end(head);
  cout<<endl;
  Destory(head);
  return 0;
}




