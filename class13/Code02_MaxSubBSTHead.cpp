//给定一棵二叉树的头节点head，返回这颗二叉树中最大的二叉搜索子树的头节点
#include<iostream>
#include<vector>
using namespace std;

class Tree
{
public:
  int value;
  Tree*left;
  Tree*right;
  Tree(int data):value(data),left(nullptr),right(nullptr){}
};

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


//利用递归套路解决
class Info
{
public:
  Tree* node;
  int maxSubBSTSize;
  int xValue;
  int nValue;
  Info(Tree*no,int m,int x,int n)
  {
    node=no;
    maxSubBSTSize=m;
    xValue=x;
    nValue=n;
  }
};

Info*process(Tree*root)
{
  if(root==nullptr)
  {
    return nullptr;
  }
  Info*leftInfo=process(root->left);
  Info*rightInfo=process(root->right);
  
  int maxValue=root->value;
  int minValue=root->value;
  int maxSubBSTSize=0;
  Tree*node=nullptr;
  if(leftInfo!=nullptr)
  {
    maxValue=max(maxValue,leftInfo->xValue);
    minValue=min(minValue,leftInfo->nValue);
    //可能性1：最大二叉搜索子树在左树上
    maxSubBSTSize=leftInfo->maxSubBSTSize;
    node=leftInfo->node;
  }
  if(rightInfo!=nullptr)
  {
    maxValue=max(maxValue,rightInfo->xValue);
    minValue=min(minValue,rightInfo->nValue);
    if(maxSubBSTSize<rightInfo->maxSubBSTSize)
    {
      maxSubBSTSize=rightInfo->maxSubBSTSize;
      node=rightInfo->node;
    }
  }

  bool leftBST=leftInfo==nullptr?true:(leftInfo->node==root->left)&&(leftInfo->xValue<root->value);
  bool rightBST=rightInfo==nullptr?true:(rightInfo->node==root->right)&&(rightInfo->nValue>root->value);
  if(leftBST&&rightBST)
  {
    node=root;
    maxSubBSTSize=(leftInfo==nullptr?0:leftInfo->maxSubBSTSize)+(rightInfo==nullptr?0:rightInfo->maxSubBSTSize)+1;
  }
  return new Info(node,maxSubBSTSize,maxValue,minValue);
}

Tree*maxSubBSTHead1(Tree*root)
{
  if(root==nullptr)
  {
    return nullptr;
  }
  Info* info=process(root);
  Tree*node=info->node;
  delete info;
  info=nullptr;
  return node;
}

//方法二
void inOrder(Tree *root, vector<Tree *> &arr) {
    if (root == nullptr) return ;

    inOrder(root->left, arr);
    arr.push_back(root);
    inOrder(root->right, arr);
}

int getBSTSize(Tree *root) {
    if (root == nullptr) return 0;

    vector<Tree *> arr;
    inOrder(root, arr);
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i]->value <= arr[i - 1]->value)
            return 0;
    }
    return arr.size();
}

Tree *maxSubBSTRoot2(Tree *root) {
    if (root == nullptr) return nullptr;

    if (getBSTSize(root) != 0) return root;

    Tree *leftAns = maxSubBSTRoot2(root->left);
    Tree *rightAns = maxSubBSTRoot2(root->right);

    return getBSTSize(leftAns) >= getBSTSize(rightAns) ? leftAns : rightAns;
}


//for test
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
    int maxLevel = 4;
    int maxValue = 100;
    int testTimes = 1000001;

    cout << "Test begin:" << endl;
    for (int i = 0; i < testTimes; i++) {
        Tree *root = generateRandomBST(maxLevel, maxValue);
        if (maxSubBSTHead1(root) != maxSubBSTRoot2(root)) {
            cout << "Failed!" << endl;
            Destory(root);
            break;
        }
        Destory(root);
    }

    cout << "Success!!" << endl;
    return 0;
}
























