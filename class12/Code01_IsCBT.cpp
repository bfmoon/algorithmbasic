//判断是否为完全二叉树
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


//利用递归套路解决
class Info
{
public:
  int height;
  bool isCBT;
  bool isFull;
  Info(int h,bool isC,bool isF)
  {
    this->height=h;
    this->isCBT=isC;
    this->isFull=isF;
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
  bool isFull=leftInfo->isFull&&rightInfo->isFull&&(leftInfo->height==rightInfo->height);
  if(leftInfo->isFull&&rightInfo->isFull&&(leftInfo->height==rightInfo->height))
  {
    isCBT=true;
  }
  else if(leftInfo->isFull&&rightInfo->isFull&&leftInfo->height==rightInfo->height+1)
  {
    isCBT=true;
  }
  else if(leftInfo->isCBT&&rightInfo->isFull&&leftInfo->height==rightInfo->height+1)
  {
    isCBT=true;
  }
  else if(leftInfo->isFull&&rightInfo->isCBT&&leftInfo->height==rightInfo->height)
  {
    isCBT=true;
  }

  return new Info(height,isCBT,isFull);
}

bool isCBT1(Tree*root)
{
  Info *info=process(root);
  bool is=info->isCBT;
  delete info;
  info=nullptr;
  return is;
}

//方法二：常规方法，实质层序遍历
bool isCBT2(Tree*root)
{
  if(root==nullptr)
  {
    return true;
  }
  queue<Tree*>que;
  que.push(root);
  bool isCBT=false;
  while(!que.empty())
  {
    Tree*cur=que.front();
    que.pop();
    if(isCBT&&(cur->left!=nullptr||cur->right!=nullptr)||(cur->left==nullptr&&cur->right!=nullptr))
    {
      return false;
    }
    if(cur->left!=nullptr)
    {
      que.push(cur->left);
    }
    if(cur->right!=nullptr)
    {
      que.push(cur->right);
    }
    if(cur->left==nullptr||cur->right==nullptr)
    {
      isCBT=true;
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
    for (int i= 0; i < testTimes; i++) {
        Tree *root = generateRandomBST(maxLevel, maxValue);
        if (isCBT1(root) != isCBT2(root)) {
            cout << "Failed!" << endl;
            return 0;
        }

    }

    cout << "Success!!" << endl;
    return 0;
}































