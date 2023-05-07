//https://leetcode.com/problems/sum-of-subarray-minimums/
//给定一个数组arr，返回所有子数组最小值的累加和
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

//纯暴力解法,O(N^3)
int sumSubarrayMins1(vector<int>& arr)
{
	int N=arr.size();
	int ans=0;
	for(int i=0;i<N;i++)
	{
		for(int j=i;j<N;j++)
		{
			int mi=arr[i];
			for(int k=i;k<=j;k++)
			{
				mi=min(mi,arr[k]);
			}
			ans+=mi;
		}
	}
	return ans;
}

void nearLessEqualLeft(vector<int>arr,vector<int>&left)
{
	int N=arr.size();
	for(int i=0;i<N;i++)
	{
		int ans=-1;
		for(int j=i-1;j>=0;j--)
		{
			if(arr[j]<=arr[i])
			{
				ans=j;
				break;
			}
		}
		left[i]=ans;
	}
}

void nearLessRight(vector<int>arr,vector<int>&right)
{
	int N=arr.size();
	for(int i=0;i<N;i++)
	{
		int ans=N;
		for(int j=i+1;j<N;j++)
		{
			if(arr[j]<arr[i])
			{
				ans=j;
				break;
			}
		}
		right[i]=ans;
	}
}

//没有用单调栈
int sumSubarrayMins2(vector<int>& arr)
{
	int N=arr.size();
	vector<int>left(N,0);
	vector<int>right(N,0);
	//left[i] = x : arr[i]左边，离arr[i]最近，<=arr[i]，位置在x
	nearLessEqualLeft(arr,left);
	// right[i] = y : arr[i]右边，离arr[i]最近，< arr[i],的数，位置在y
	nearLessRight(arr,right);
	long long ans=0;
	for(int i=0;i<N;i++)
	{
		int start=i-left[i];
		int end=right[i]-i;
		ans+=start*end*arr[i];
	}
	return ans;
}

//根据上述方法利用单调栈
//利用单调栈，优化构成上述数组的方式
int sumSubarrayMins(vector<int>& arr)
{
	if(arr.size()==0)
	{
		return 0;
	}
	int N=arr.size();
	vector<int>left(N,0);
	vector<int>right(N,0);
	nearLessLeftAndLessEqualRight(arr,left,right);
	long long ans=0;
	for(int i=0;i<N;i++)
	{
		int start=i-left[i];
		int end=right[i]-i;
		ans+=start*end*(long)arr[i];
	}
	return ans%1000000007;
}

void nearLessLeftAndLessEqualRight(vector<int> &arr, vector<int> &left, vector<int> &right)
{
	int N=arr.size();
	stack<int>sta;
	for(int i=0;i<N;i++)
	{
		while(!sta.empty()&&arr[sta.top()]>=arr[i])
		{
			int cur=sta.top();
			sta.pop();
			left[cur]=sta.empty()?-1:sta.top();
			right[cur]=i;
		}
		sta.push(i);
	}
	while(!sta.empty())
	{
		int cur=sta.top();
		sta.pop();
		left[cur]=sta.empty()?-1:sta.top();
		right[cur]=N;
	}
}