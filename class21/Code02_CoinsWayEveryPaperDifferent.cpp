//arr是货币数组，其中的值都是正数。再给定一个正数aim。
//每个值都认为是一张货币，
//即便是值相同的货币也认为每一张都是不同的，
//返回组成aim的方法数
//例如：arr = {1,1,1}，aim = 2
//第0个和第1个能组成2，第1个和第2个能组成2，第0个和第2个能组成2
//一共就3种方法，所以返回3
#include<iostream>
#include<vector>
using namespace std;

//暴力尝试---要与不要两种情况相加
int process(vector<int>&arr,int index,int rest)
{
	if(rest<0)
	{
		return 0;
	}
	if(index==arr.size())
	{
		return rest==0?1:0;
	}
	return process(arr,index+1,rest)+process(arr,index+1,rest-arr[index]);
}

int coinWays1(vector<int>&arr,int aim)
{
	return process(arr,0,aim);
}

//动态规划版本
int coinWays2(vector<int>&arr,int aim)
{
	int N=arr.size();
	vector<vector<int>>dp(N+1,vector<int>(aim+1,0));
	dp[N][0]=1;
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=aim;rest++)
		{
			dp[index][rest] = dp[index + 1][rest] + 
			(rest - arr[index] >= 0 ? dp[index + 1][rest - arr[index]] : 0);
		}
	}
	return dp[0][aim];
}

//for test
vector<int>randomArray(int maxLen,int maxValue)
{
	int N=rand()%maxLen;
	vector<int>arr(N,0);
	for(int i=0;i<N;i++)
	{
		arr[i]=rand()%maxValue;
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
	int maxLen = 20;
	int maxValue = 30;
	int testTime = 1000000;
	cout<<"测试开始"<<endl;
	for(int i=0;i<testTime;i++)
	{
		vector<int>arr=randomArray(maxLen,maxValue);
		int aim=rand()%maxValue;
		int ans1=coinWays1(arr,aim);
		int ans2=coinWays2(arr,aim);
		if(ans1!=ans2)
		{
			cout<<"Opes!!!"<<endl;
			printArray(arr);
			cout<<ans1<<endl;
			cout<<ans2<<endl;
			break;
		}
	}
	cout<<"测试结束"<<endl;
	return 0;
}
	
	
	