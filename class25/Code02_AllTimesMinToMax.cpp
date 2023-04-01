//给定一个只包含正数的数组arr，arr中任何一个子数组sub，
//一定都可以算出(sub累加和 )* (sub中的最小值)是什么，
//那么所有子数组中，这个值最大是多少？

//https://leetcode.cn/problems/maximum-subarray-min-product/submissions/
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int max1(vector<int>&arr)
{
  if(arr.size()==0)
  {
    return 0;
  }
  int N=arr.size();
  vector<long>sum(N);
  sum[0]=arr[0];
  //求累加和数组
  for(int i=1;i<N;i++)
  {
    sum[i]=sum[i-1]+arr[i];
  }
  stack<int>sta;
  long ma=INT_MIN;
  for(int i=0;i<arr.size();i++)
  {
    while(!sta.empty()&&arr[sta.top()]>arr[i])
    {
      int j=sta.top();
      sta.pop();
      ma=max(ma,(sta.empty?sum[i-1]:(sum[i-1]-sum[sta.top()]))*arr[j]);
    }
    sta.push(i);
  }
  while(!sta.empty())
  {
    int j=sta.top();
    sta.pop();
    ma=max(ma,(sta.empty()?sum[N-1]:(sum[N-1]-sum[sta.top()]))*arr[j]);
  }
  return ma%1000000007;
}

    


