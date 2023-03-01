//非递归实现树的先序，中序，后序遍历

#include<iostream>
#include<vector>
#include<stack>
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

//先序遍历
void pre(Tree* root)
{
  if(root==nullptr)
  {
    return ;
  }
  stack<Tree*>sta;
  sta.push(root);
  //先右，后左
  while(!sta.empty())
  {
    Tree*node=sta.top();
    sta.pop();
    cout<<node->value<<" ";
    if(node->right!=nullptr)
    {
      sta.push(node->right);
    }
    if(node->left!=nullptr)
    {
      sta.push(node->left);
    }
  }
  cout<<endl;
}

//后序遍历
void end(Tree*root)
{
  if(root==nullptr)
  {
    return ;
  }
  stack<Tree*>sta1;
  stack<Tree*>sta2;
  sta1.push(root);
    while(!sta1.empty())
    {
      Tree*node=sta1.top();
      sta1.pop();
      sta2.push(node);
      if(node->left!=nullptr)
      {
        sta1.push(node->left);
      }
      if(node->right!=nullptr)
      {
        sta1.push(node->right);
      }
    }
    while(!sta2.empty())
    {
      cout<<sta2.top()->value<<" ";
      sta2.pop();
    }
    cout<<endl;
}

//中序遍历
void in(Tree* root)
{
  if(root==nullptr)
  {
    return ;
  }
  stack<Tree*>sta;
  while(!sta.empty()||root!=nullptr)
  {
    if(root!=nullptr)
    {
      sta.push(root);
      root=root->left;
    }
    else
    {
      root=sta.top();
      sta.pop();
      cout<<root->value<<" ";
      root=root->right;
    }
  }
  cout<<endl;
}

//利用一个栈实现后序遍历
void oneEnd(Tree*root)
{
  if(root==nullptr)
  {
    return ;
  }
  stack<Tree*>sta;
  sta.push(root);
  Tree*cur=nullptr;
  while(!sta.empty())
  {
    cur=sta.top();
    if(cur->left!=nullptr&&root!=cur->left&&root!=cur->right)
    {
      sta.push(cur->left);
    }
    else if(cur->right!=nullptr&&root!=cur->right)
    {
      sta.push(cur->right);
    }
    else
    {
      cout<<sta.top()->value<<" ";
      sta.pop();
      root=cur;
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
  cout<<"先序遍历"<<endl;
  pre(head);
  cout<<"中序遍历"<<endl;
  in(head);
  cout<<"后序遍历"<<endl;
  end(head);
  cout<<"一个栈实现后序遍历"<<endl;
  oneEnd(head);
  Destory(head);
  return 0;
}

