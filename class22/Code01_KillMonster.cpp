//给定3个参数，N，M，K
//怪兽有N滴血，等着英雄来砍自己
//英雄每一次打击，都会让怪兽流失[0~M]的血量
//到底流失多少？每一次在[0~M]上等概率的获得一个值
//求K次打击之后，英雄把怪兽砍死的概率
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

//暴力尝试
int process(int times,int M,int hp)
{
	if(times==0)
	{
		return hp<=0?1:0;
	}
	if(hp<=0)
	{
		return (int)pow(M+1,times);
	}
	int ways=0;
	for(int i=0;i<=M;i++)
	{
		ways+=process(times-1,M,hp-i);
	}
	return ways;
}

double right(int N,int M,int K)
{
	if(N<1||M<1||K<1)
	{
		return 0;
	}
	int all=(int)pow(M+1,K);
	int kill=process(K,M,N);
	return (double)(double)kill/(double)all;
}

//动态规划(有枚举行为)
double dp1(int N,int M,int K)
{
	if(N<1||M<1||K<1)
	{
		return 0;
	}
	int all=(int)pow(M+1,K);
	vector<vector<int>>dp(K+1,vector<int>(N+1,0));
	dp[0][0]=1;
	for(int times=1;times<=K;times++)
	{
		dp[times][0]=(int)pow(M+1,times);
		for(int hp=1;hp<=N;hp++)
		{
			int ways=0;
			for(int i=0;i<=M;i++)
			{
				if(hp-i>=0)
				{
					ways+=dp[times-1][hp-i];
				}
				else
				{
					ways+=pow(M+1,times-1);
				}
			}
			dp[times][hp]=ways;
		}
	}
	int kill=dp[K][N];
	return (double)(double)kill/(double)all;
}

//动态规划---对枚举行为进行优化
double dp2(int N,int M,int K)
{
	if(N<1||M<1||K<1)
	{
		return 0;
	}
	int all=(int)pow(M+1,K);
	vector<vector<int>>dp(K+1,vector<int>(N+1,0));
	dp[0][0]=1;
	for(int times=1;times<=K;times++)
	{
		dp[times][0]=(int)pow(M+1,times);
		for(int hp=1;hp<=N;hp++)
		{
			dp[times][hp]=dp[times][hp-1]+dp[times-1][hp];
			if(hp-1-M>=0)
			{
				dp[times][hp]-=dp[times-1][hp-1-M];
			}
			else
			{
				dp[times][hp]-=(int)pow(M+1,times-1);
			}
		}
	}
	int kill=dp[K][N];
	return (double)(double)kill/(double)all;
}

int main()
{
	int NMax = 10;
	int MMax = 10;
	int KMax = 10;
	int testTime = 2000;
	cout<<"测试开始"<<endl;
	for (int i = 0; i < testTime; i++) 
	{
		int N = rand()% NMax;
		int M = rand()%MMax;
		int K = rand()% KMax;
		double ans1 = right(N, M, K);
		double ans2 = dp1(N, M, K);
		double ans3 = dp2(N, M, K);
		if (ans1 != ans2 || ans1 != ans3) {
			cout<<i<<endl;
			cout<<"Oops!"<<endl;
			cout<<ans1<<" "<<ans2<<" "<<ans3<<endl;
			cout<<N<<" "<<M<<" "<<K<<endl;
			break;
		}
	}
	cout<<"测试结束"<<endl;
	return 0;
}
	
	