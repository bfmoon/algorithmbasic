//https://leetcode.cn/problems/number-of-islands/
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<stack>
using namespace std;


//方法一：利用感染法，遍历数组，将每个位置连着的1改为其他字符，每个位置都判断一遍
void process(vector<vector<char>>& grid,int N,int M,int i,int j)
{
	if(i<0||i==N||j<0||j==M||grid[i][j]!='1')
	{
		return ;
	}
	grid[i][j]='0';
	process(grid,N,M,i+1,j);
	process(grid,N,M,i-1,j);
	process(grid,N,M,i,j+1);
	process(grid,N,M,i,j-1);
}

int numIslands1(vector<vector<char>>& grid)
{
	if(grid.size()==0)
	{
		return 0;
	}
	int N=grid.size();
	int M=grid[0].size();
	int sum=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			if(grid[i][j]=='1')
			{
				sum++;
				process(grid,N,M,i,j);
			}
		}
	}
	return sum;
}

//方法二：利用并查集,new出来不同的地址来辨别不同的1
class Dot{};
//节点类
template<class T>
class Node
{
public:
	T value;
	Node(T data):value(data){}
};
//并查集类
template<class T>
class UnionFind
{
private:
	unordered_map<T,Node<T>*>nodes;//一个节点的集合
	unordered_map<Node<T>*,Node<T>*>parents;//父节点的集合
	unordered_map<Node<T>*,int>sizeMap;//集合的节点个数
public:
	UnionFind(vector<T>&arr)
	{
		for(T cur:arr)
		{
			Node* node=new Node(cur);
			nodes[cur]=node;
			parents[node]=node;
			sizeMap[node]=1;
			delete node;
		}
	}
	
	//找到集合的父节点
	Node<T>*find(Node<T>* cur)
	{
		stack<Node<T>*>sta;//做路径压缩的栈
		while(cur!=parenst[cur])
		{
			sta.push(cur);
			cur=parents[cur];
		}
		
		while(!sta.empty())
		{
			parents[sta.top()]=cur;
			sta.pop();
		}
		return cur;
	}
	
	//判断两个集合的父节点是否相同
	bool isSameSet(Node<T>*node1,Node<T>*node2)
	{
		return parents[node1]==parents[node2];
	}
	
	//合并两个集合
	void myUnion(T node1,T node2)
	{
		Node<T>*aHead=find(nodes[node1]);
		Node<T>*bHead=find(nodes[node2]);
		if(aHead!=bHead)
		{
			int bigSize=sizeMap[aHead];
			int smallSize=sizeMap[bHead];
			Node<T>*bigHead=bigSize>=smallSize?aHead:bHead;
			Node<T>*smallHead=bigHead==aHead?bHead:aHead;
			
			parents[smallHead]=bigHead;
			sizeMap[bigHead]=bigSize+smallSize;
			sizeMap.erase(smallHead);
		}
	}
	
	//返回有多少个集合
	int size()
	{
		return sizeMap.size();
	}
};

int numIslands2(vector<vector<char>>& grid)
{
	int row=grid.size();
	int col=gird[0].size();
	
	vector<vector<Dot*>>dot(row,vector<Dot*>(col));
	vector<Dot*>dotArray;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			if(grid[i][j]=='1')
			{
				dot[i][j]=new Dot();
				dotArray.push_back(dot[i][j]);
				
			}
		}
	}
	
	UnionFind<Dot*>*Union=new UnionFind<Dot*>(dotArray);
	//处理第0行
	for(int i=1;i<col;i++)
	{
		if(grid[0][i-1]=='1'&&grid[0][i]=='1')
		{
			Union->myUnion(dot[0][i-1],dot[0][i]);
		}
	}
	//处理第0列
	for(int j=1;j<row;j++)
	{
		if(grid[j-1][0]=='1'&&grid[j][0]=='1')
		{
			Union->myUnion(dot[j-1][0],dot[j][0]);
		}
	}
	//处理剩下的
	for(int i=1;i<row;i++)
	{
		for(int j=1;j<col;j++)
		{
			if(grid[i][j]=='1')
			{
				if(grid[i-1][j]=='1')
				{
					Union->myUnion(dot[i][j],dot[i-1][j])
				}
				if(grid[i][j-1]=='1')
				{
					Union->myUnion(dot[i][j],dot[i][j-1])
				}
			}
		}
	}
	
	return Union->size();
}
			
//方法三：利用数组形式的并查集实现
//将二位坐标变化为一维坐标
class UnionFind
{
private:
	vector<int>parents;
	vector<int>sizeMap;
	vector<int>help;
	int col;
	int sets;
public:
	UnionFind(vector<vector<char>>&grid)
	{
		int N=grid.size();
		col=grid[0].size();
		sets=0;
		int len=N*col;
		parents.resize(len);
		sizeMap.resize(len);
		help.resize(len);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<col;j++)
			{
				if(grid[i][j]=='1')
				{
					int cur=index(i,j);
					parents[cur]=cur;
					sizeMap[cur]=1;
					sets++;
				}
			}
		}
	}
	
private:
	int index(int i,int j)
	{
		return i*col+j;
	}
public:
	//找到父亲节点
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
	
	//合并两个集合
	void myUnion(int a,int b,int c,int d)
	{
		int aIndex=index(a,b);
		int bIndex=index(c,d);
		int aHead=find(aIndex);
		int bHead=find(bIndex);
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

int numIslands3(vector<vector<char>>& grid)
{
	int row=grid.size();
	int col=grid[0].size();
	UnionFind MyUnion(grid);
	//处理第0行
	for(int i=1;i<col;i++)
	{
		if(grid[0][i-1]=='1'&&grid[0][i]=='1')
		{
			MyUnion.myUnion(0,i-1,0,i);
		}
	}
	//处理第0列
	for(int j=1;i<row;j++)
	{
		if(grid[j-1][0]=='1'&&grid[j][0]=='1')
		{
			MyUnion.myUnion(j-1,0,j,0);
		}
	}
	//处理剩下的
	for(int i=1;i<row;i++)
	{
		for(int j=1;j<col;j++)
		{
			if(grid[i][j]=='1')
			{
				if(grid[i-1][j]=='1')
				{
					MyUnion.myUnion(i-1,j,i,j);
				}
				
				if(grid[i][j-1]=='1')
				{
					MyUnion.myUnion(i,j-1,i,j]);
				}
			}
		}
	}
	return MyUnion.size();
}

