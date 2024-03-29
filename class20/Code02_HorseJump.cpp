//请同学们自行搜索或者想象一个象棋的棋盘，
//然后把整个棋盘放入第一象限，棋盘的最左下角是(0,0)位置
//那么整个棋盘就是横坐标上9条线、纵坐标上10条线的区域
//给你三个 参数 x，y，k
//返回“马”从(0,0)位置出发，必须走k步
//最后落在(x,y)上的方法数有多少种? 
#include<iostream>
#include<vector>
using namespace std;


//暴力尝试
int process(int a,int b,int x,int y,int rest)
{
	if(x<0||y<0||x>9||y>8)
	{
		return 0;
	}
	if(rest==0)
	{
		return (x==a&&y==b);
	}
	//八个方向都要尝试
	int ways=process(a,b,x+2,y+1,rest-1);
	ways+=process(a,b,x+2,y-1,rest-1);
	ways+=process(a,b,x+1,y+2,rest-1);
	ways+=process(a,b,x+1,y-2,rest-1);
	ways+=process(a,b,x-2,y+1,rest-1);
	ways+=process(a,b,x-2,y-1,rest-1);
	ways+=process(a,b,x-1,y+2,rest-1);
	ways+=process(a,b,x-1,y-2,rest-1);
	
	return ways;
}
	
int jump1(int a,int b,int k)
{
	return process(a,b,0,0,k);
}


//动态规划
int pick(vector<vector<vector<int>>>&dp,int x,int y,int rest)
{
	if(x<0||x>9||y<0||y>8)
	{
		return 0;
	}
	return dp[x][y][rest];
}
int jump2(int a,int b,int k)
{
	vector<vector<vector<int>>>dp(10,vector<vector<int>>(9,vector<int>(k+1,0)));
	dp[a][b][0]=1;
	for(int rest=1;rest<=k;rest++)
	{
		for(int x=0;x<10;x++)
		{
			for(int y=0;y<9;y++)
			{
				int ways=pick(dp,x+2,y+1,rest-1);
				ways+=pick(dp,x+2,y-1,rest-1);
				ways+=pick(dp,x+1,y+2,rest-1);
				ways+=pick(dp,x+1,y-2,rest-1);
				ways+=pick(dp,x-2,y+1,rest-1);
				ways+=pick(dp,x-2,y-1,rest-1);
				ways+=pick(dp,x-1,y+2,rest-1);
				ways+=pick(dp,x-1,y-2,rest-1);
				dp[x][y][rest]=ways;
			}
		}
	}
	return dp[0][0][k];
}

int main()
{
	int a=7;
	int b=7;
	int k=10;
	cout<<jump1(a,b,10)<<endl;
	cout<<jump2(a,b,10)<<endl;
	return 0;
}