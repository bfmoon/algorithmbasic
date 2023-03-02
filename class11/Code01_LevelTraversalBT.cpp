#include<iostream>
#include<queue>
#include<vector>
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

void level(Tree* root)
{
  if(root==nullptr)
  {
    return ;
  }
  queue<Tree*>que;
  que.push(root);
  while(!que.empty())
  {
    Tree* cur=que.front();
    cout<<cur->value<<" ";
    que.pop();
    if(cur->left!=nullptr)
    {
      que.push(cur->left);
    }
    if(cur->right!=nullptr)
    {
      que.push(cur->right);
    }
  }
  cout<<endl;
}

int main()
{
  Tree*head=new Tree('A');
  Tree*node1=new Tree('B');
  Tree*node2=new Tree('C');
  Tree*node3=new Tree('D');
  Tree*node4=new Tree('E');
  Tree*node5=new Tree('F');
  Tree*node6=new Tree('G');

  head->left=node1;
  head->right=node2;
  node1->left=node3;
  node1->right=node4;
  node2->left=node5;
  node2->right=node6;

  cout<<"层序遍历"<<endl;
  level(head);

  Destory(head);
  return 0;
}
