//假设有排成一行的N个位置记为1~N，N一定大于或等于2
//开始时机器人在其中的M位置上(M一定是1~N中的一个)
//如果机器人来到1位置，那么下一步只能往右来到2位置；
//如果机器人来到N位置，那么下一步只能往左来到N-1位置；
//如果机器人来到中间位置，那么下一步可以往左走或者往右走；
//规定机器人必须走K步，最终能来到P位置(P也是1~N中的一个)的方法有多少种
//给定四个参数 N、M、K、P，返回方法数
#include<iostream>
#include<vector>
using namespace std;

//从暴力尝试入手
// 机器人当前来到的位置是cur，
// 机器人还有rest步需要去走，
// 最终的目标是aim，
// 有哪些位置？1~N
// 返回：机器人从cur出发，走过rest步之后，最终停在aim的方法数，是多少？
int process01(int N,int cur,int aim,int rest)
{
  if(rest==0)
  {
    return cur==aim?1:0;
  }
  if(cur==1)
  {
    return process01(N,2,aim,rest-1);
  }
  if(cur==N)
  {
    return process01(N,N-1,aim,rest-1);
  }
  return process01(N,cur+1,aim,rest-1)+process01(N,cur-1,aim,rest-1);
}

int ways1(int N, int start, int aim, int K)
{
  if(N<2||start < 1 || start > N || aim < 1 || aim > N || K < 1)
  {
    return -1;
  }
  return process01(N,start,aim,K);
}

//挂缓存法
int process02(int cur,int rest,int aim,int N,vector<vector<int>>&dp)
{
  if(dp[cur][rest]!=-1)
  {
    return dp[cur][rest];
  }
  
  //之前没走过
  int ans=0;
  if(rest==0)
  {
    ans=cur==aim?1:0;
  }
  else if(cur==1)
  {
    ans=process02(2,rest-1,aim,N,dp);
  }
  else if(cur==N)
  {
    ans=process02(N-1,rest-1,aim,N,dp);
  }
  else
  {
    ans=process02(cur+1,rest-1,aim,N,dp)+process02(cur-1,rest-1,aim,N,dp);
  }
  dp[cur][rest]=ans;
  return ans;
}

int ways2(int N,int start,int aim,int K)
{
  if(N<2||start < 1 || start > N || aim < 1 || aim > N || K < 1)
  {
    return -1;
  }
  vector<vector<int>>dp(N+1,vector<int>(K+1,-1));
  
  return process02(start,K,aim,N,dp);
}


//动态规划版本
int ways3(int N,int start,int aim,int K)
{
  if(N<2||start < 1 || start > N || aim < 1 || aim > N || K < 1)
  {
    return -1;
  }
  vector<vector<int>>dp(N+1,vector<int>(K+1));
  dp[aim][0]=1;

  for(int rest=1;rest<=K;rest++)
  {
    dp[1][rest]=dp[2][rest-1];
    for(int cur=2;cur<N;cur++)
    {
      dp[cur][rest]=dp[cur-1][rest-1]+dp[cur+1][rest-1];
    }
    dp[N][rest]=dp[N-1][rest-1];
  }
  return dp[start][K];
}

int main()
{
  cout<<ways1(5,2,4,6)<<endl;
  cout<<ways2(5,2,4,6)<<endl;
  cout<<ways3(5,2,4,6)<<endl;
  return 0;
}






















