//返回二叉树最宽层的节点个数
#include<iostream>
#include<queue>
#include<unordered_map>
using namespace std;

class Tree
{
public:
  Tree*left;
  Tree*right;
  int value;
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

//中序遍历
void in(Tree*root)
{
  if(root==nullptr)
  {
    return;
  }
  in(root->left);
  cout<<root->value<<" ";
  in(root->right);
}

void pre(Tree*root)
{
  if(root==nullptr)
  {
    return ;
  }
  cout<<root->value<<" ";
  pre(root->left);
  pre(root->right);
}

//利用几个有序的变量
int maxWidth(Tree* root)
{
  if(root==nullptr)
  {
    return 0;
  }
  int curSize=0;
  int ans=0;
  Tree*endNode=nullptr;//下一层的最后节点
  Tree*curNode=root;//当前层的最后节点
  queue<Tree*>que;
  que.push(root);
  while(!que.empty())
  {
    Tree*cur=que.front();
    //cout<<cur->value<<endl; 层序遍历的
    que.pop();
    if(cur->left!=nullptr)
    {
      que.push(cur->left);
      endNode=cur->left;
    }
    if(cur->right!=nullptr)
    {
      que.push(cur->right);
      endNode=cur->right;
    }
    curSize++;
    //若当前节点等于下一层的最后节点，则获取最大的宽度
    if(cur==curNode)
    {
      ans=max(ans,curSize);
      curSize=0;
      curNode=endNode;
    }
  }
  return ans;
}

//利用hashMap存储
//key:表示当前节点，value:表示当前节点所在的层数
int maxWidthUseMap(Tree*root)
{
  if(root==nullptr)
  {
    return 0;
  }
  queue<Tree*>que;
  unordered_map<Tree*,int>nodeMap;
  int curLevel=1;//当前层
  int curLevelNodeCnt=0;//当前层的节点个数
  int ans=0;

  que.push(root);
  nodeMap[root]=1;
  while(!que.empty())
  {
    Tree*cur=que.front();
    que.pop();
    int curNodelevel=nodeMap[cur];
    if(cur->left!=nullptr)
    {
      nodeMap[cur->left]=curNodelevel+1;
      que.push(cur->left);
    }
    if(cur->right!=nullptr)
    {
      nodeMap[cur->right]=curNodelevel+1;
      que.push(cur->right);
    }

    //若是同一层，节点数++
    if(curNodelevel==curLevel)
    {
      curLevelNodeCnt++;
    }
    else
    {
      ans=max(ans,curLevelNodeCnt);
      curLevel++;//则跳到下一层
      curLevelNodeCnt=1;//下一层的节点数，重新从1开始
    }
  }
  ans=max(ans,curLevelNodeCnt);
  return ans;
}

//for test
Tree*generate(int level,int maxLevel,int maxValue)
{
  if(level>maxLevel|| rand() % 100 < 0.5)
  {
    return nullptr;
  }
  Tree*head=new Tree(rand()%maxValue);
  head->left=generate(level+1,maxLevel,maxValue);
  head->right=generate(level+1,maxLevel,maxValue);
  return head;
}

Tree*generateRandomBST(int maxLevel,int maxValue)
{
  return generate(1,maxLevel,maxValue);
}


int main()
{
  srand(time(0));
  int maxLevel = 4;
  int maxValue = 100;
  int testTime = 1000000;
  cout<<"test begin"<<endl;
  for(int i=0;i<testTime;i++)
  {
    Tree* root=generateRandomBST(maxLevel,maxValue);
    if(maxWidth(root)!=maxWidthUseMap(root))
    {
      cout << maxWidth(root) << ", " << maxWidthUseMap(root) << endl;
      cout<<"Opes!!!"<<endl;
      in(root);
      cout<<endl;
      pre(root);
      cout<<endl;
      Destory(root);
      break;
    }
    Destory(root);
  }
  cout<<"test finsh"<<endl;
  return 0;
}




