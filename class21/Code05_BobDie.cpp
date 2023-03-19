//给定5个参数，N，M，row，col，k
//表示在N*M的区域上，醉汉Bob初始在(row,col)位置
//Bob一共要迈出k步，且每步都会等概率向上下左右四个方向走一个单位
//任何时候Bob只要离开N*M的区域，就直接死亡
//返回k步之后，Bob还在N*M的区域的概率
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

//暴力尝试
int process(int N,int M,int x,int y,int rest)
{
	if(x<0||y<0||x==N||y==M)
	{
		return 0;
	}
	if(rest==0)
	{
		return 1;
	}
	int up=process(N,M,x-1,y,rest-1);
	int down=process(N,M,x+1,y,rest-1);
	int left=process(N,M,x,y-1,rest-1);
	int right=process(N,M,x,y+1,rest-1);
	return up+down+left+right;
}

double livePosibility1(int N,int M,int row,int col,int k)
{
	return (double)process(N,M,row,col,k)/pow(4,k);
}

//动态规划版本
int pick(int N,int M,int row,int col,int k,vector<vector<vector<int>>>&dp)
{
	if(row<0||col<0||row==N||col==M)
	{
		return 0;
	}
	return dp[row][col][k];
}

double livePosibility2(int N,int M,int row,int col,int k)
{
	vector<vector<vector<int>>>dp(N,vector<vector<int>>(M,vector<int>(k+1,0)));
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			dp[i][j][0]=1;
		}
	}
	for(int rest=1;rest<=k;rest++)
	{
		for(int x=0;x<N;x++)
		{
			for(int y=0;y<M;y++)
			{
				int up=pick(N,M,x-1,y,rest-1,dp);
				int down=pick(N,M,x+1,y,rest-1,dp);
				int left=pick(N,M,x,y-1,rest-1,dp);
				int right=pick(N,M,x,y+1,rest-1,dp);
				dp[x][y][rest]=up+down+left+right;
			}
		}
	}
	return (double)dp[row][col][k]/pow(4,k);
}

int main()
{
	cout<<livePosibility1(50,50,6,6,10)<<endl;
	cout<<livePosibility2(50,50,6,6,10)<<endl;
	return 0;
}
