//李白打酒问题
//话说大诗人李白, 一生好饮。幸好他从不开车。
//一天, 他提着酒壶, 从家里出来, 酒壶中有酒 2 斗。他边走边唱:
//无事街上走，提壶去打酒。 逢店加一倍, 遇花喝一斗。
//这一路上, 他一共遇到店 N 次, 遇到花 M 次。已知最后一次遇到的是花，他正好把酒喝光了。
//请你计算李白这一路遇到店和花的顺序, 有多少种不同的可能?
//注意: 壶里没酒 ( 0 斗) 时遇店是合法的, 加倍后还是没酒; 但是没酒时遇 花是不合法的。
#include<iostream>
#include<vector>
using namespace std;

//暴力递归
int process01(int N,int M,int rest)
{
	if(N<0||M<0||rest<0)
	{
		return 0;
	}
	if(N==0&&M==1&&rest==1)
	{
		return 1;
	}
	return (process01(N-1,M,rest*2)+process01(N,M-1,rest-1))%1000000007;
}
		
int ways1(int N,int M)
{
	return process01(N,M,2);
}
//记忆化搜索
int process02(int N,int M,int rest,vector<vector<vector<int>>>&dp)
{
	if (N < 0 || M < 0 || rest < 0)
	{
		return 0;
	}
	if(rest>M)
	{
		return 0;
	}
	if(dp[N][M][rest]!=-1)
	{
		return dp[N][M][rest];
	}
	
	//最后一次遇见的是花
	if(N==0&&M==1&&rest==1)
	{
		return 1;
	}
	int sum=0;
	sum=(process02(N-1,M,2*rest,dp)+process02(N,M-1,rest-1,dp))%1000000007;
	dp[N][M][rest]=sum;
	return sum;
}
	
int ways2(int N,int M)
{
	vector<vector<vector<int>>>dp(101,vector<vector<int>>(101,vector<int>(101,-1)));
	return process02(N,M,2,dp);
}

int main()
{
	int maxValue=100;
	int testTimes=1000;
	cout<<"测试开始"<<endl;
	for(int i=0;i<testTimes;i++)
	{
		int N=rand()%maxValue;
		int M=rand()%maxValue;
		
		int ans1=ways1(N,M);
		int ans2=ways2(N,M);
		if(ans1!=ans2)
		{
			cout<<"Opes!!!"<<endl;
			cout<<ans1<<" "<<ans2<<endl;
			cout<<N<<" "<<M<<endl;
			break;
		}
	}
	cout<<"测试结束"<<endl;
	return 0;
}