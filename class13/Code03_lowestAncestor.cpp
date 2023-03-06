//给定一棵二叉树的头节点head，和另外两个节点a和b，返回a和b的最低公共祖先
#include<iostream>
#include<unordered_map>
#include<unordered_set>
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

//方法一：树的递归套路
class Info
{
public:
  bool existA;
  bool existB;
  Tree*node;
  Info(bool a,bool b,Tree*n)
  {
    this->existA=a;
    this->existB=b;
    this->node=n;
  }
};

Info*process(Tree*head,Tree*nodeA,Tree*nodeB)
{
  if(head==nullptr)
  {
    return new Info(false,false,nullptr);
  }
  Info*leftInfo=process(head->left,nodeA,nodeB);
  Info*rightInfo=process(head->right,nodeA,nodeB);
  
  bool existA=(head==nodeA)||leftInfo->existA||rightInfo->existA;
  bool existB=(head==nodeB)||leftInfo->existB||rightInfo->existB;

  Tree*node=nullptr;
  if(leftInfo->node!=nullptr)
  {
    node=leftInfo->node;
  }
  else if(rightInfo->node!=nullptr)
  {
    node=rightInfo->node;
  }
  else
  {
    if(existA&&existB)
    {
      node=head;
    }
  }
  return new Info(existA,existB,node);

}
Tree*lowestAncestor1(Tree*head,Tree*nodeA,Tree*nodeB)
{
  Info * info=process(head,nodeA,nodeB);
  Tree*node=info->node;
  delete info;
  info=nullptr;
  return node;
}

//利用表保存父节点
void fillParentMap(Tree*head,unordered_map<Tree*,Tree*>&parents)
{
  if(head->left!=nullptr)
  {
    parents[head->left]=head;
    fillParentMap(head->left,parents);
  }
  if(head->right!=nullptr)
  {
    parents[head->right]=head;
    fillParentMap(head->right,parents);
  }
}

Tree*lowestAncestor2(Tree*head,Tree*nodeA,Tree*nodeB)
{
  if(head==nullptr)
  {
    return nullptr;
  }
  unordered_map<Tree*,Tree*>parents;
  parents[head]=nullptr;
  unordered_set<Tree*>o1set;
  fillParentMap(head,parents);

  Tree*o1=nodeA;
  //将o1的父节点进入set中
  while(o1!=nullptr)
  {
    o1set.insert(o1);
    o1=parents[o1];
  }
  o1=nodeB;
  while(!o1set.count(o1))
  {
    o1=parents[o1];
  }
  return o1;
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


void fillPrelist(Tree *root, vector<Tree*> &arr) {
    if (root == nullptr) return ;

    arr.push_back(root);
    fillPrelist(root->left, arr);
    fillPrelist(root->right, arr);
}

Tree *pickRandomOne(Tree *root) {
    if (root == nullptr) return nullptr;

    vector<Tree*> arr;
    fillPrelist(root, arr);
    int randInd = rand() % arr.size();

    return arr[randInd];
}


int main() {
    srand(time(0));
    int maxLevel = 4;
    int maxValue = 100;
    int testTimes = 100001;

    cout << "Test begin:" << endl;
    for (int i = 0; i < testTimes; i++) {
        Tree *root = generateRandomBST(maxLevel, maxValue);
        Tree *a = pickRandomOne(root);
        Tree *b = pickRandomOne(root);
        if (lowestAncestor1(root, a, b) != lowestAncestor2(root, a, b)) {
            cout << "Failed!" << endl;
            Destory(root);
            return 0;
        }
        Destory(root);

   }

    cout << "Success!!" << endl;
    return 0;
}
