//给定一个正数n，求n的裂开方法数，
//规定：后面的数不能比前面的数小
//比如4的裂开方法有：
//1+1+1+1、1+1+2、1+3、2+2、4
//5种，所以返回5

#include<iostream>
#include<vector>
using namespace std;

//暴力尝试
// 上一个拆出来的数是pre
// 还剩rest需要去拆
// 返回拆解的方法数
int process(int pre,int rest)
{
	if(rest==0)
	{
		return 1;//说明拆完了
	}
	if(pre>rest)
	{
		return 0;
	}
	int ways=0;
	for(int i=pre;i<=rest;i++)
	{
		ways+=process(i,rest-i);
	}
	return ways;
}
int ways1(int n)
{
	if(n<=0)
	{
		return 0;
	}
	if(n==1)
	{
		return 1;
	}
	return process(1,n);
}

//动态规划
int ways2(int n)
{
	if(n<=0)
	{
		return 0;
	}
	if(n==1)
	{
		return 1;
	}
	vector<vector<int>>dp(n+1,vector<int>(n+1));
	//pre从1开始裂
	for(int pre=1;pre<=n;pre++)
	{
		dp[pre][0]=1;
		dp[pre][pre]=1;
	}
	for(int pre=n-1;pre>0;pre--)
	{
		for(int rest=pre+1;rest<=n;rest++)
		{
			int ways=0;
			for(int first=pre;first<=rest;first++)
			{
				ways+=dp[first][rest-first];
			}
			dp[pre][rest]=ways;
		}
	}
	return dp[1][n];
}

//优化的动态规划
int ways3(int n)
{
	if(n<=0)
	{
		return 0;
	}
	if(n==1)
	{
		return 1;
	}
	vector<vector<int>>dp(n+1,vector<int>(n+1));
	//pre从1开始裂
	for(int pre=1;pre<=n;pre++)
	{
		dp[pre][0]=1;
		dp[pre][pre]=1;
	}
	for(int pre=n-1;pre>0;pre--)
	{
		for(int rest=pre+1;rest<=n;rest++)
		{
			dp[pre][rest]=dp[pre+1][rest];
			if(rest-pre>=0)
			{
				dp[pre][rest]+=dp[pre][rest-pre];
			}
		}
	}
	return dp[1][n];
}

int main()
{
	int n=4;
	cout<<ways1(n)<<endl;
	cout<<ways2(n)<<endl;
	cout<<ways3(n)<<endl;
	return 0;
}