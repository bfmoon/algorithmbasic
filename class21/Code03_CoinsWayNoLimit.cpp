//arr是面值数组，其中的值都是正数且没有重复。再给定一个正数aim。
//每个值都认为是一种面值，且认为张数是无限的。
//返回组成aim的方法数
//例如：arr = {1,2}，aim = 4
//方法如下：1+1+1+1、1+1+2、2+2
//一共就3种方法，所以返回3

#include<iostream>
#include<vector>
using namespace std;


//暴力尝试--一一枚举出来
int process(vector<int>arr,int index,int rest)
{
	if(index==arr.size())
	{
		return rest==0?1:0;
	}
	int ways=0;
	for(int zhangs=0;zhangs*arr[index]<=rest;zhangs++)
	{
		ways+=process(arr,index+1,rest-(zhangs*arr[index]));
	}
	return ways;
}

int coinsWay1(vector<int>&arr,int aim)
{
	if(arr.size()==0||aim<0)
	{
		return 0;
	}
	return process(arr,0,aim);
}

//动态规划
int coinsWay2(vector<int>&arr,int aim)
{
	if(arr.size()==0||aim<0)
	{
		return 0;
	}
	int N=arr.size();
	vector<vector<int>>dp(N+1,vector<int>(aim+1,0));
	dp[N][0]=1;
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=aim;rest++)
		{
			int ways=0;
			for(int zhangs=0;zhangs*arr[index]<=rest;zhangs++)
			{
				ways+=dp[index+1][rest-zhangs*arr[index]];
			}
			dp[index][rest]=ways;
		}
	}
	return dp[0][aim];
}

//斜率优化
int coinsWay3(vector<int>&arr,int aim)
{
	if(arr.size()==0||aim<0)
	{
		return 0;
	}
	int N=arr.size();
	vector<vector<int>>dp(N+1,vector<int>(aim+1,0));
	dp[N][0]=1;
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=aim;rest++)
		{
			dp[index][rest]=dp[index+1][rest];
			if(rest-arr[index]>=0)
			{
				dp[index][rest]+=dp[index][rest-arr[index]];
			}
		}
	}
	return dp[0][aim];
}


//for test
vector<int>randomArray(int maxLen,int maxValue)
{
	int N=rand()%maxLen;
	vector<int>arr(N,0);
	vector<bool>has(maxValue+1);
	for(int i=0;i<N;i++)
	{
		do{
		    arr[i] = rand()%maxValue + 1;	
		  } while (has[arr[i]]);
			has[arr[i]] = true;
	}
	return arr;
}

void printArray(vector<int>arr)
{
	for(int i=0;i<arr.size();i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	int maxLen = 10;
	int maxValue = 30;
	int testTime = 1000000;
	cout<<"测试开始"<<endl;;
	for (int i = 0; i < testTime; i++) 
	{
		vector<int>arr = randomArray(maxLen, maxValue);
		int aim = rand()%maxValue;
		int ans1 = coinsWay1(arr, aim);
		int ans2 = coinsWay2(arr, aim);
		int ans3=coinsWay3(arr,aim);
		if (ans1 != ans2||ans2!=ans3) 
		{
			cout<<"Oops!"<<endl;
			printArray(arr);
			cout<<aim<<endl;
			cout<<ans1<<endl;
			cout<<ans2<<endl;	
			cout<<ans3<<endl;
			break;
		}
	}
	cout<<"测试结束"<<endl;
	return 0;
}
	