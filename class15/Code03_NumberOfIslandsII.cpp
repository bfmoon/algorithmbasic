//本题为leetcode原题
// 测试链接：https://leetcode.com/problems/number-of-islands-ii/
// 所有方法都可以直接通过
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

//数组实现并查集
class UnionFind
{
private:
	vector<int>parents;
	vector<int>sizeMap;
	vector<int>help;
	int row;
	int col;
	int sets;
	
public:
	UnionFind(int r,int c)
	{
		row=r;
		col=c;
		int len=row*col;
		parents.resize(len);
		sizeMap.resize(len);
		help.resize(len);
		sets=0;
	}
private:
	int index(int i.int j)
	{
		return i*col+j;
	}
public:
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
public:
	void Union(int r1,int c1,int r2,int c2)
	{
		if(r1==row||r1<0||r2 < 0 || r2 == row || c1 < 0 || c1 == col || c2 < 0 || c2 == col)
		{
			return ;
		}
		int i1=index(r1,c1);
		int i2=index(r2,c2);
		//如果sizeMap==0,说明该点没有1，不能合并
		if(sizeMap[i1]==0||sizeMap[i2]==0)
		{
			return ;
		}
		int aHead=find(i1);
		int bHead=find(i2);
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
		
	int connt(int r,int c)
	{
		int i1=index(r,c);
		if(sizeMap[i1]==0)
		{
			parents[i1]=i1;
			sizeMap[i1]=1;
			sets++;
			Union(r-1,c,r,c);
			Union(r+1,c,r,c);
			Union(r,c-1,r,c);
			Union(r,c+1,r,c);
		}
			return sets;
	}
};
	
vector<int>numIslands21(int m,int n,vector<vector<int>>&positions)
{
	UnionFind myUnion(m,n);
	vector<int>ans;
	for(vector<int>res:positions)
	{
		ans.push_back(myUnion.connt(res[0],res[1]));
	}
	return ans;
}