//给定一棵二叉树的头节点head，任何两个节点之间都存在距离，返回整棵二叉树的最大距离
#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>
#include<unordered_set>
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
class Info
{
public:
  int maxDistance;
  int height;
  Info(int m,int h):maxDistance(m),height(h){}
};

Info*process(Tree*root)
{
  if(root==nullptr)
  {
    return new Info(0,0);
  }
  Info*leftInfo=process(root->left);
  Info*rightInfo=process(root->right);
  int height=max(leftInfo->height,rightInfo->height)+1;
  int p1=leftInfo->maxDistance;
  int p2=rightInfo->maxDistance;
  int p3=leftInfo->height+rightInfo->height+1;
  return new Info(max(max(p1,p2),p3),height);
}

int maxDistance1(Tree* root)
{
  Info*info=process(root);
  int maxDistance=info->maxDistance;
  delete info;
  info=nullptr;
  return maxDistance;
}

//方法二：暴力枚举，先序遍历获得序列，暴力枚举两个节点之间的距离
void fillPrelist(Tree *root, vector<Tree*> &arr) {
    if (root == nullptr) return ;

    arr.push_back(root);
    fillPrelist(root->left, arr);
    fillPrelist(root->right, arr);
}

vector<Tree *> getPrelist(Tree *root) {
    vector<Tree*> arr;
    fillPrelist(root, arr);
    return arr;
}
//记录每个节点的父节点
void fillParentMap(Tree *root, unordered_map<Tree*, Tree*> &parentMap) {
    if (root->left != nullptr) {
        parentMap[root->left] = root;
        fillParentMap(root->left, parentMap);
    }

    if (root->right != nullptr) {
        parentMap[root->right] = root;
        fillParentMap(root->right, parentMap);
    }
}

unordered_map<Tree *, Tree *> getParentMap(Tree *root) {
    unordered_map<Tree*, Tree*> _map;
    _map[root] = nullptr;
    fillParentMap(root, _map);
    return _map;
}


//获取两个节点之间的距离
int distance(unordered_map<Tree*, Tree*> &parentMap, Tree *o1, Tree *o2) {
    unordered_set<Tree*> o1set;
    Tree *cur = o1;
    o1set.insert(cur);

    while (parentMap[cur] != nullptr) {
        cur = parentMap[cur];
        o1set.insert(cur);
    }

//找到o1和o2的最低公共祖先
    cur = o2;
    while (!o1set.count(cur)) {
        cur = parentMap[cur];
    }

//统计o1和o2到最低公共祖先的距离
    Tree *lowestAncestor = cur;
    cur = o1;
    int distance1 = 1;
    while (cur != lowestAncestor) {
        cur = parentMap[cur];
        distance1++;
    }

    cur = o2;
    int distance2 = 1;
    while (cur != lowestAncestor) {
        cur = parentMap[cur];
        distance2++;
    }

    return distance1 + distance2 - 1;
}

int maxDistance2(Tree *root) {
    if (root == nullptr) return 0;

    vector<Tree*> arr = getPrelist(root);

    unordered_map<Tree *, Tree *> parentMap = getParentMap(root);

    int ans = 0;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i; j < arr.size(); j++) {
            ans = max(ans, distance(parentMap, arr[i], arr[j]));
        }
    }
    return ans;
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
        if (maxDistance1(root) != maxDistance2(root)) {
            cout << "Failed!" << endl;
            Destory(root);
            return 0;
        }
        Destory(root);
    }
    cout << "Success!" << endl;
    return 0;
}




