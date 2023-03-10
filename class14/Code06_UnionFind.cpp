//利用数组实现并查集，一般面试，都是用数组实现的
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

template<class T>
class UnionFind
{
private:
  vector<T>parents;
  vector<int>sizeMap;
  vector<T>help;
  int size;
public:
  UnionFind(int N)
  {
    parents.resize(N);
    sizeMap.resize(N);
    help.resize(N);
    size=N;
    for(int i=0;i<N;i++)
    {
      //集合的父亲节点
      parents[i]=i;
      //该集合的节点个数
      sizeMap[i]=1;
    }
  }

  //返回集合的代表节点
  T find(T i)
  {
    int hi=0;
    while(i!=parents[i])
    {
      help[hi++]=i;
      i=parents[i];
    }
    //路径压缩
    //相当与利用数组实现了栈结构
    for(hi--;hi>=0;hi--)
    {
      parents[help[hi]]=i;
    }
    return i;
  }

  //判断两个值是否在同一个集合中
  bool isSameSet(T a,T b)
  {
    return find(a)==find(b);
  }

  //合并两个集合
  void Union(T a,T b)
  {
    T fx=find(a);
    T fy=find(b);
    if(fx!=fy)
    {
      if(sizeMap[fx]>=sizeMap[fy])
      {
        sizeMap[fx]+=sizeMap[fy];
        parents[fy]=fx;
      }
      else
      {
        sizeMap[fy]+=sizeMap[fx];
        parents[fx]=fy;
      }
    }
  }
};







