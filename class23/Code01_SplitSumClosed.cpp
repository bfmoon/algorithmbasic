//给定一个正数数组arr，
//请把arr中所有的数分成两个集合，尽量让两个集合的累加和接近
//返回最接近的情况下，较小集合的累加和
#include<iostream>
#include<vector>
using namespace std;


//暴力尝试
//思路：两个集合累加和不可能超过数组累加和的一半
//所以只需要在原数组中选取不超过原数组累加和一半的最大接近即可
int process(vector<int>&arr,int index,int rest)
{
	if(index==arr.size())
	{
		return 0;
	}
	int p1=process(arr,index+1,rest);
	int p2=0;
	if(arr[index]<=rest)
	{
		p2=process(arr,index+1,rest-arr[index]);
	}
	return max(p1,p2);
}
	
int right(vector<int>&arr)
{
	if(arr.size()<=1)
	{
		return 0;
	}
	int sum=0;
	for(int cur:arr)
	{
		sum+=cur;
	}
	return process(arr,0,sum/2);
}

//动态规划
int dp1(vector<int>&arr)
{
	if(arr.size()<=1)
	{
		return 0;
	}
	int sum=0;
	for(int cur:arr)
	{
		sum+=cur;
	}
	sum/=2;
	int N=arr.size();
	vector<vector<int>>dp(N+1,vector<int>(sum+1,0));
	
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=sum;rest++)
		{
			int p1=dp[index+1][rest];
			int p2=0;
			if(arr[index]<=rest)
			{
				p2=dp[index+1][rest-arr[index]];
			}
			dp[index][rest]= max(p1,p2);
		}
	}
	return dp[0][sum];
}

//for test 
vector<int>randomArray(int maxLen,int maxValue)
{
	int N=rand()%maxLen;
	vector<int>arr(N);
	for(int i=0;i<N;i++)
	{
		arr[i]=rand()%maxValue;
	}
	return arr;
}

int main()
{
	int maxLen=20;
	int maxValue=50;
	int testTimes=10000;
	cout<<"测试开始"<<endl;
	for(int i=0;i<testTimes;i++)
	{
		vector<int>arr=randomArray(maxLen,maxValue);
		int ans1=right(arr);
		int ans2=dp1(arr);
		if(ans1!=ans2)
		{
			cout<<"Opes!!!"<<endl;
			cout<<ans1<<" "<<ans2<<endl;
			break;
		}
	}
	cout<<"测试结束"<<endl;
	return 0;
}