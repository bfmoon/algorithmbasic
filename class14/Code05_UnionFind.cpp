//利用hashmap实现并查集
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<stack>
#include<vector>
using namespace std;
//单独的一个点类
template<class T>
class Node
{
public:
  T value;
  Node(T data):value(data){}
};

template<class T>
class UnionFind
{
private:
  //自己节点构成的集合
  unordered_map<T,Node<T>*>nodes;
  //该节点的父节点的集合
  unordered_map<Node<T>*,Node<t>*>parents;
  //该集合有多少个节点
  unordered_map<Node<T>*,int>sizeMap;
public:
  UnionFind(vector<T>& arr)
  {
    for(T cur:arr)
    {
      Node<T>* node=new Node<T>(cur);
      nodes[cur]=node;
      parents[node]=node;
      sizeMap[node]=1;
      delete node;
    }
  }

  // 给你一个节点，请你往上到不能再往上，把代表返回
  // 返回父节点
  Node<T>*findFather(Node<T>*cur)
  {
    stack<Node<T>*>sta;
    //第一个while结束后，就已经找到父节点了
    while(cur!=parents[cur])
    {
      sta.push(cur);
      cur=parents[cur];
    }
    //这个while是做路径压缩
    while(!sta.empty())
    {
      parents[sta.top()]=cur;
      sta.pop();
    }
    return cur;
  }

  //判断两个值是否在一个集合中
  bool isSameSet(T a,T b)
  {
    //就是看两个值的父节点是否是同一个
    return findFather(nodes[a])==findFather(nodes[b]);
  }

  //将两个数，合并为同一个集合
  void Union(T a,T b)
  {
    //找两个节点的父节点
    Node<T>*aHead=findFather(nodes[a]);
    Node<T>*bHead=findFather(nodes[b]);

    if(aHead!=bHead)
    {
      //查看两个父节点的子节点个数
      int aSize=sizeMap[aHead];
      int bSize=sizeMap[bHead];

      //两个节点要合并到，节点个数多的集合上
      Node<T>*bigNode=aSize>=bSize?aHead:bHead;
      Node<T>*smallNode=bigNode==aHead?bHead:aHead;
      //找到较小的节点将整个都挂在大的节点上，修改父节点和节点个数
      parents[smallNode]=bigNode;
      sizeMap[bigNode]=aSize+bSize;
      sizeMap.erase(smallNode);
    }
  }

  int size()
  {
    return sizeMap.size();
  }
};







