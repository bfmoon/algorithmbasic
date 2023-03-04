#include<iostream>
#include<ctime>
using namespace std;

//判断二叉树是不是平衡二叉树
class Tree
{
public:
  int value;
  Tree*left;
  Tree*right;
  Tree(int data):value(data),left(nullptr),right(nullptr){}
};

//利用二叉树的递归套路

class Info
{
public:
  int height;
  bool isBalanced;
  Info(int h,bool b):height(h),isBalanced(b){}
};

Info* process(Tree*root)
{
  if(root==nullptr)
  {
    return new Info(0,true);
  }
  Info *leftInfo=process(root->left);
  Info *rightInfo=process(root->right);
  bool isBalanced=(leftInfo->isBalanced&&rightInfo->isBalanced)&&abs(leftInfo->height-rightInfo->height)<2?true:false;
  int height=max(leftInfo->height,rightInfo->height)+1;
  return new Info(height,isBalanced);
}

bool isBalanced1(Tree*root)
{
  Info * info=process(root);
  bool b=info->isBalanced;
  delete info;
  info=nullptr;
  return b;
}

//利用递归
int getHeight(Tree* root)
{
  if(root==nullptr)
  {
    return 0;
  }
  return max(getHeight(root->left),getHeight(root->right))+1;
}


bool isBalanced2(Tree*root)
{
  if(root==nullptr)
  {
    return true;
  }
  return isBalanced2(root->left)&&isBalanced2(root->right)&&abs(getHeight(root->left)-getHeight(root->right))<2;
}

//for test
Tree *generate(int level, int maxLevel, int maxVal) {
    if (level > maxLevel || (rand() % 100 /(double)101)  < 0.5) 
        return nullptr;

    Tree *root = new Tree(rand() % maxVal);
    root->left = generate(level + 1, maxLevel, maxVal);
    root->right = generate(level + 1, maxLevel, maxVal);
    return root;
}


Tree *generateRandomBST(int maxLevel, int maxVal) 
{
    return generate(1, maxLevel, maxVal);
}

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

int main()
{
  int testTime=100000;
  int maxlevel=5;
  int maxValue=100;
  cout<<"test begin"<<endl;
  for(int i=0;i<testTime;i++)
  {
    Tree* head=generateRandomBST(maxlevel,maxValue);
    if(isBalanced1(head)!=isBalanced2(head))
    {
      cout<<"Opes!!!"<<endl;
      Destory(head);
      break;
    }
    Destory(head);
  }
  cout<<"test finsh"<<endl;
  return 0;
}











