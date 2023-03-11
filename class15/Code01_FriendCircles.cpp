//https://leetcode.cn/problems/number-of-provinces/
#include<iostream>
#include<vector>
using namespace std;

//建立并查集
class UnionFind
{
private:
	vector<int>parents;
	vector<int>sizeMap;
	vector<int>help;
	int sets;
public:
	UnionFind(int N)
	{
		parents.resize(N);
		sizeMap.resize(N);
		help.resize(N);
		sets=N;
		for(int i=0;i<N;i++)
		{
			parents[i]=i;
			sizeMap[i]=1;
		}
	}
	
	//找到节点的父节点
	int find(int i)
	{
		int hi=0;
		while(i!=parents[i])
		{
			help[hi++]=i;
			i=parents[i];
			
		}
		//路径压缩
		for(hi--;hi>=0;hi--)
		{
			parents[help[hi]]=i;
		}
		return i;
	}
	
	//判断两个节点是否在一个集合
	bool isSameSet(int a,int b)
	{
		return parents[a]==parents[b];
	}
	
	//将两个集合合并
	void Myunion(int a,int b)
	{
		int aHead=find(a);
		int bHead=find(b);
		if(aHead!=bHead)
		{
			if(sizeMap[aHead]>=sizeMap[bHead])
			{
				sizeMap[aHead]+=sizeMap[bHead];
				parents[bHead]=aHead;
			}
			else
			{
				sizeMap[bHead]+=sizeMap[aHead];
				parents[aHead]=bHead;
			}
			sets--;
		}
	}
	
	int size()
	{
		return sets;
	}
};

int findCircleNum(vector<vector<int>>& isConnected)
{
	int N=isConnected.size();
	UnionFind myUnion(N);
	for(int i=0;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			if(isConnected[i][j]==1)
			{
				myUnion.Myunion(i,j);
			}
		}
	}
	return myUnion.size();
}