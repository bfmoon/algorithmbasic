#include<iostream>
using namespace std;

class Tree
{
public:
  int value;
  Tree*left;
  Tree*right;
  Tree(int data):value(data),left(nullptr),right(nullptr){}
};

//利用递归方法
class Info
{
public:
  int maxBSTSubtreeSize;
  int allSize;
  int xValue;
  int nValue;
  Info(int mBST,int all,int xV,int nV)
  {
    this->maxBSTSubtreeSize=mBST;
    this->allSize=all;
    this->mValue=xV;
    this->nValue=nV;
  }
};

Info* process(Tree*root)
{
  if(root==nullptr)
  {
    return nullptr;
  }
  Info*leftInfo=process(root->left);
  Info*rightInfo=process(root->right);

  int maxValue=root->value;
  int minValue=root->value;
  int allSize=1;
  int p1=-1;
  int p2=-1;
  int p3=-1;
  if(leftInfo!=nullptr)
  {
    maxValue=max(maxValue,leftInfo->mValue);
    minValue=min(minValue,leftInfo->nValue);
    allSize+=leftInfo->allSize;
    p1=leftInfo->maxBSTSubtreeSize;
  }
  if(rightInfo!=nullptr)
  {
    maxValue=max(maxValue,rightInfo->mValue);
    minValue=min(minValue,rightInfo->nValue);
    allSize+=rightInfo->allSize;
    p2=rightInfo->maxBSTSubtreeSize
  }
  //判断是否是搜索二叉树
  bool leftBST=leftInfo==nullptr?true:leftInfo->allSize==leftInfo->maxBSTSubtreeSize;
  bool rightBST=rightInfo==nullptr?true:rightInfo->allSize==rightInfo->maxBSTSubtreeSize;
  if(leftBST&&rightBST)
  {
    bool legalLeft=leftInfo==nullptr?true:leftInfo->mValue<root->value;
    bool legalRight=rightInfo==nullptr?true:rightInfo->nValue>root->value;
    if(legalLeft&&legalRight)
    {
      p3=(leftInfo==nullptr?0:leftInfo->allSize)+(rightInfo==nullptr?0:rightInfo->allSize)+1;
    }
  }
  int maxBSTSubtreeSize=max(max(p1,p2),p3);
  return new Info(maxBSTSubtreeSize,allSize,maxValue,minValue);
}

int largestBSTSubtree(Tree*root)
{
  if(root==nullptr)
  {
    return 0;
  }
  Info*info =process(root);
  int size=info->maxBSTSubtreeSize;
  delete info;
  info=nullptr;
  return size;
}

  
