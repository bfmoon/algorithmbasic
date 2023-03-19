//arr是面值数组，其中的值都是正数且没有重复。再给定一个正数aim。
//每个值都认为是一种面值，且认为张数是无限的。
//返回组成aim的最少货币数

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

//暴力尝试
int process(vector<int>&arr,int index,int rest)
{
	if(index==arr.size())
	{
		//如果index到最后了,若rest刚好为0，
		//则已经满足了，否则就利用INT_MAX标记
		return rest==0?0:INT_MAX;
	}
	int ans=INT_MAX;
	for(int zhangs=0;zhangs*arr[index]<=rest;zhangs++)
	{
		int next=process(arr,index+1,rest-zhangs*arr[index]);
		if(next!=INT_MAX)
		{
			ans=min(ans,next+zhangs);
		}
	}
	return ans;
}

int MinCoinsNoLimit1(vector<int>&arr,int aim)
{
	if(arr.size()==0||aim<0)
	{
		return 0;
	}
	return process(arr,0,aim);
}

//动态规划(有枚举行为的)
int MinCoinsNoLimit2(vector<int>&arr,int aim)
{
	if(arr.size()==0||aim<0)
	{
		return 0;
	}
	int N=arr.size();
	vector<vector<int>>dp(N+1,vector<int>(aim+1));
	dp[N][0]=0;
	for(int j=1;j<=aim;j++)
	{
		dp[N][j]=INT_MAX;
	}
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=aim;rest++)
		{
			int ans=INT_MAX;
			for(int zhangs=0;zhangs*arr[index]<=rest;zhangs++)
			{
				int next=dp[index+1][rest-zhangs*arr[index]];
				if(next!=INT_MAX)
				{
					ans=min(ans,next+zhangs);
				}
			}
			dp[index][rest]=ans;
		}
	}
	return dp[0][aim];
}

//动态规划(斜率优化)
int MinCoinsNoLimit3(vector<int>&arr,int aim)
{
	if(arr.size()==0||aim<0)
	{
		return 0;
	}
	int N=arr.size();
	vector<vector<int>>dp(N+1,vector<int>(aim+1,0));
	dp[N][0]=0;
	for(int j=1;j<=aim;j++)
	{
		dp[N][j]=INT_MAX;
	}
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=aim;rest++)
		{
			dp[index][rest]=dp[index+1][rest];
			if(rest-arr[index]>=0&&dp[index][rest-arr[index]]!=INT_MAX)
			{
				dp[index][rest]=min(dp[index][rest],dp[index][rest-arr[index]]+1);
			}
		}
	}
	return dp[0][aim];
}

//for test
vector<int>randomArray(int maxLen,int maxValue)
{
	int N=rand()%maxLen;
	vector<int>arr(N);
	vector<bool>has(maxValue+1);
	for(int i=0;i<N;i++)
	{
		do{
			arr[i]=rand()%maxValue+1;
		}while(has[arr[i]]);
		has[arr[i]]=true;
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
	int maxLen=10;
	int maxValue=20;
	int testTimes=100000;
	cout<<"测试开始"<<endl;
	for(int i=0;i<testTimes;i++)
	{
		vector<int>arr=randomArray(maxLen,maxValue);
		int aim=rand()%maxValue;
		int ans1=MinCoinsNoLimit1(arr,aim);
		int ans2=MinCoinsNoLimit2(arr,aim);
		int ans3=MinCoinsNoLimit3(arr,aim);
		if(ans1!=ans2||ans2!=ans3)
		{
			cout<<"Opes!!!"<<endl;
			printArray(arr);
			cout<<aim<<endl;
			cout<<ans1<<" "<<ans2<<" "<<ans3<<endl;
			break;
		}
	}
	cout<<"测试结束"<<endl;
	return 0;
}
	
