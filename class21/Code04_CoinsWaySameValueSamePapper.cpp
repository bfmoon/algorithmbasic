//arr是货币数组，其中的值都是正数。再给定一个正数aim。
//每个值都认为是一张货币，
//认为值相同的货币没有任何不同，
//返回组成aim的方法数
//例如：arr = {1,2,1,1,2,1,2}，aim = 4
//方法：1+1+1+1、1+1+2、2+2
//一共就3种方法，所以返回3

#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

//暴力方法
int process(vector<int>&coings,vector<int>&zhang,int index,int rest)
{
	if(index==coings.size())
	{
		return rest==0?1:0;
	}
	int ways=0;
	for(int zhangs=0;(zhangs<=zhang[index])&&(zhangs*coings[index])<=rest;zhangs++)
	{
		ways+=process(coings,zhang,index+1,rest-(zhangs*coings[index]));
	}
	return ways;
}

void getInfo(vector<int>&arr,vector<int>&coings,vector<int>&zhang)
{
	unordered_map<int,int>sum;
	for(int cur:arr)
	{
		if(!sum.count(cur))
		{
			sum[cur]=1;
		}
		else
		{
			sum[cur]+=1;
		}
	}
	int index=0;
	for(auto value:sum)
	{
		coings[index]=value.first;
		zhang[index++]=value.second;
	}
}

int coinsWay1(vector<int>&arr,int aim)
{
	if(arr.size()==0||aim<0)
	{
		return 0;
	}
	int N=arr.size();
	vector<int>coings(N,0);
	vector<int>zhang(N,0);
	//将arr中的面值与张数分别统计在coings,zhang的数组中
	getInfo(arr,coings,zhang);
	return process(coings,zhang,0,aim);
}

//动态规划
int coinsWay2(vector<int>&arr,int aim)
{
	if(arr.size()==0||aim<0)
	{
		return 0;
	}
	int N=arr.size();
	vector<int>coings(N,0);
	vector<int>zhang(N,0);
	getInfo(arr,coings,zhang);
	vector<vector<int>>dp(N+1,vector<int>(aim+1,0));
	dp[N][0]=1;
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=aim;rest++)
		{
			int ways=0;
			for(int zhangs=0;(zhangs*coings[index])<=rest&&(zhangs<=zhang[index]);zhangs++)
			{
				ways+=dp[index+1][rest-(zhangs*coings[index])];
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
	vector<int>coings(N,0);
	vector<int>zhang(N,0);
	getInfo(arr,coings,zhang);
	vector<vector<int>>dp(N+1,vector<int>(aim+1,0));
	dp[N][0]=1;
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=aim;rest++)
		{
			dp[index][rest]=dp[index+1][rest];
			if(rest-coings[index]>=0)
			{
				dp[index][rest]+=dp[index][rest-coings[index]];
			}
			if(rest-coings[index]*(zhang[index]+1)>=0)
			{
				dp[index][rest]-=dp[index+1][rest-coings[index]*(zhang[index]+1)];
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
	for(int i=0;i<N;i++)
	{
		arr[i]=rand()%maxValue+1;
	}
	return arr;
}

//for test 
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
	int maxLen=10;
	int maxValue=20;
	int testTime=100000;
	cout<<"测试开始"<<endl;
	for(int i=0;i<testTime;i++)
	{
		vector<int>arr=randomArray(maxLen,maxValue);
		int aim=rand()%maxValue;
		int ans1=coinsWay1(arr,aim);
		int ans2=coinsWay2(arr,aim);
		int ans3=coinsWay3(arr,aim);
		if(ans1!=ans2||ans2!=ans3)
		{
			cout<<"Opes!!!"<<endl;
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