//判断二叉树是不是搜索二叉树
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

//利用二叉树套路
class Info
{
public:
  bool isBST;
  int leftMax;
  int rightMin;
  Info(bool bs,int lmax,int rmin)
  {
    this->isBST=bs;
    this->leftMax=lmax;
    this->rightMin=rmin;
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

  int max_value=root->value;
  if(leftInfo!=nullptr)
  {
    max_value=max(max_value,leftInfo->leftMax);
  }
  if(rightInfo!=nullptr)
  {
    max_value=max(max_value,rightInfo->leftMax);
  }
  int min_value=root->value;
  if(leftInfo!=nullptr)
  {
    min_value=min(min_value,leftInfo->rightMin);
  }
  if(rightInfo!=nullptr)
  {
    min_value=min(min_value,rightInfo->rightMin);
  }
  bool isBST=true;
  if(leftInfo!=nullptr&&(!leftInfo->isBST || leftInfo->leftMax>=root->value))
  {
    isBST=false;
  }
  if(rightInfo!=nullptr&&(!rightInfo->isBST || rightInfo->rightMin<=root->value))
  {
    isBST=false;
  }
  return new Info(isBST,max_value,min_value);
}

bool isBST1(Tree* root)
{
  if(root==nullptr)
  {
    return true;
  }
  Info * info=process(root);
  bool is=info->isBST;
  delete info;
  info=nullptr;
  return is;
}


//方法二，中序遍历
void in(Tree*root,vector<int>&arr)
{
  if(root==nullptr)
  {
    return ;
  }
  in(root->left,arr);
  arr.push_back(root->value);
  in(root->right,arr);
}
bool isBST2(Tree*root)
{
  if(root==nullptr)
  {
    return true;
  }
  vector<int>arr;
  in(root,arr);
  for(int i=1;i<arr.size();i++)
  {
    if(arr[i]<arr[i-1])
    {
      return false;
    }
  }
  return true;
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

Tree *generate(int level, int maxlevel, int maxval) {
    if (level > maxlevel || (rand() % 100 / 101) < 0.5)
        return nullptr;

    Tree *root = new Tree(rand() % maxval);
    root->left = generate(level + 1, maxlevel, maxval);
    root->right = generate(level + 1, maxlevel, maxval);

    return root;
}

Tree *generateRandomBST(int maxlevel, int maxval) {
    return generate(1, maxlevel, maxval);
}

int main() {
    srand(time(0));

    int level = 4;
    int value = 100;
    int testTime = 1000001;
    cout<<"test begin"<<endl;
    for (int i = 0; i < testTime; i++) {
        Tree *root = generateRandomBST(level, value);
        if (isBST1(root) != isBST2(root)) {
            cout << "Failed!" << endl;
            Destory(root);
            break;
        }
        Destory(root);
    }
    cout<<"test finsh"<<endl;
    return 0;
}





