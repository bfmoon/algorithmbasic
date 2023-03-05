//判断二叉树是不是完全二叉树
#include<iostream>
#include<queue>
using namespace std;

class Tree
{
public:
  int value;
  Tree*left;
  Tree*right;
  Tree(int data):value(data),left(nullptr),right(nullptr){}
};

//递归套路
class Info
{
public:
  int height;
  bool isFull;
  bool isCBT;
  Info(int h,bool f,bool c)
  {
    this->height=h;
    this->isFull=f;
    this->isCBT=c;
  }
};

Info* process(Tree*root)
{
	if(root==nullptr)
	{
		return new Info(0,true,true);
	}
	Info*leftInfo=process(root->left);
	Info*rightInfo=process(root->right);
	int height=max(leftInfo->height,rightInfo->height)+1;
	bool isCBT=false;
	bool isFull=leftInfo->isFull&&rightInfo->isFull&&leftInfo->height==rightInfo->height;
	if(leftInfo->isFull&&rightInfo->isFull&&leftInfo->height==rightInfo->height)
	{
		isCBT=true;
	}
	else if(leftInfo->isFull&&rightInfo->isFull&&(leftInfo->height==rightInfo->height+1))
	{
		isCBT=true;
	}
	else if(leftInfo->isCBT&&rightInfo->isFull&&(leftInfo->height==rightInfo->height+1))
	{
		isCBT=true;
	}
	else if(leftInfo->isFull&&rightInfo->isCBT&&(leftInfo->height==rightInfo->height))
	{
		isCBT=true;
	}
	return new Info(height,isFull,isCBT);
}

bool isCBT(Tree*root)
{
	if(root==nullptr)
	{
		return true;
	}
	Info*info=process(root);
	bool isCBT=info->isCBT;
	delete info;
	info=nullptr;
	return isCBT;
}
