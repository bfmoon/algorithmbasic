//判断是否为满二叉树
//节点数要满足2高度的次方减一才是
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

//方法一：递归套路
//第一种，左树满，右树满，高度一样就是满
class Info
{
public:
  bool isFull;
  int height;
  Info(bool fu,int he)
  {
    this->isFull=fu;
    this->height=he;
  }
};
Info* process01(Tree*root)
{
  if(root==nullptr)
  {
    return new Info(true,0);
  }
  Info* leftInfo=process01(root->left);
  Info* rightInfo=process01(root->right);
  int height=max(leftInfo->height,rightInfo->height)+1;
  bool isFull=leftInfo->isFull&&rightInfo->isFull&&leftInfo->height==rightInfo->height;
  /*if(leftInfo->isFull&&rightInfo->isFull&&leftInfo->height==rightInfo->height)
  {
    isFull=true;
  }*/
  return new Info(isFull,height);
}
bool isFull1(Tree*root)
{
  Info* info=process01(root);
  bool isFull=info->isFull;
  delete info;
  info=nullptr;
  return isFull;
}

//方法二：递归套路
//统计树的高度和树的节点个数，最后进行计算即可 
class Info2
{
public:
  int height;
  int nodeCnt;
  Info2(int h,int n):height(h),nodeCnt(n){}
};

Info2* process02(Tree*root)
{
  if(root==nullptr)
  {
    return new Info2(0,0);
  }
  Info2* leftInfo=process02(root->left);
  Info2* rightInfo=process02(root->right);
  int nodeCnt=leftInfo->nodeCnt+rightInfo->nodeCnt+1;
  int height=max(leftInfo->height,rightInfo->height)+1;
  return new Info2(height,nodeCnt);
}


bool isFull2(Tree*root)
{
  if(root==nullptr)
  {
    return true;
  }
  Info2* info=process02(root);
  int height=info->height;
  int node=info->nodeCnt;
  delete info;
  info=nullptr;
  return (1<<height)-1==node;
}


//for test
void Destory(Tree*root)
{
  if(root==nullptr)
  {
    return ;
  }
  Destory(root->left);
  Destory(root->right);
  delete root;
}

Tree *generate(int level, int maxl, int maxv) {
    if (level > maxl || (rand() % 100 / (double)101) < 0.5)
        return nullptr;

    Tree *root = new Tree(rand() % maxv);
    root->left = generate(level + 1, maxl, maxv);
    root->right = generate(level + 1, maxl, maxv);

    return root;
}

Tree *generateRandomBST(int level, int value) {
    return generate(1, level, value);
}

int main() {
    srand(time(0));

    int level = 5;
    int value = 100;
    int testTimes = 1000001;

    cout << "Test begin:" << endl;
    for (int i = 0; i < testTimes; i++) {
        Tree *root = generateRandomBST(level, value);
        if (isFull1(root) != isFull2(root)) {
            cout << "Failed!" << endl;
            return 0;
        }
    }
    cout << "Success!" << endl;
    return 0;
}



















