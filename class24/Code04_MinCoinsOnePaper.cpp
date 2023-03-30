//动态规划中利用窗口内最大值或最小值更新结构做优化（难）
//arr是货币数组，其中的值都是正数。再给定一个正数aim。
//每个值都认为是一张货币，
//返回组成aim的最少货币数
//注意：因为是求最少货币数，所以每一张货币认为是相同或者不同就不重要了

#include<iostream>
#include<deque>
#include<vector>
#include<unordered_map>
using namespace std;

//暴力递归(要与不要问题)
int process01(vector<int>&arr,int index,int rest)
{
  if(rest<0)
  {
    return -1;
  }
  if(index==arr.size())
  {
    return rest==0?0:-1;
  }
  else
  {
    //不要当前货币
    int p1=process01(arr,index+1,rest);
    //要当前位置的货币
    int p2=process01(arr,index+1,rest-arr[index]);
    if(p2!=-1)
    {
      //说明有效，则货币数++
      p2++;
    }
    return min(p1,p2);
  }
}

int ways1(vector<int>&arr,int aim)
{
  if(arr.size()==0||aim==0)
  {
    return 0;
  }
  return process01(arr,0,aim);
}

//动态规划
int ways2(vector<int>&arr,int aim)
{
  if(arr.size()==0||aim==0)
  {
    return 0;
  }
  int N=arr.size();
  vector<vector<int>>dp(N+1,vector<int>(aim+1,0));
  for(int i=1;i<=aim;i++)
  {
    dp[N][i]=-1;
  }
  for(int index=N-1;index>=0;index--)
  {
    for(int rest=0;rest<=aim;rest++)
    {
      int p1=dp[index+1][rest];
      int p2=rest-arr[index]>=0?dp[index+1][rest-arr[index]]:-1;
      if(p2!=-1)
      {
        p2++;
      }
      dp[index][rest]=min(p1,p2);
    }
  }
  return dp[0][aim];
}

//解法二：将张数与面值分开统计
//有一个张数的枚举行为

int process02(vector<int>&arr,vector<int>&zhangs,vector<int>&coins,int index,int rest)
{
  if(rest<0)
  {
    return -1;
  }
  if(index==coins.size())
  {
    return rest==0?0:-1;
  }
  //不要当前位置
  int p1=process02(arr,zhangs,coins,index+1,rest);
  int p2=0;
  for(int zhang=0;zhang<=zhangs[index]&&rest-zhang*coins[index]>=0;zhang++)
  {
    p2=process02(arr,zhangs,coins,index+1,rest-zhang*coins[index]);
  }
  return min(p1,p2);
}

void MergeArray(vector<int>&arr,vector<int>&zhangs,vector<int>coins)
{
  unordered_map<int,int>counts;
  for(int cur:arr)
  {
    if(!counts.count(cur))
    {
      counts[cur]=1;
    }
    else
    {
      counts[cur]++;
    }
  }
  int index=0;
  int N=counts.size();
  zhangs.resize(N);
  coins.resize(N);
  for(auto cur:counts)
  {
    coins[index]=cur.first;
    zhangs[index++]=cur.second;
  }
}

int ways3(vector<int>&arr,int aim)
{
  if(arr.size()==0||aim==0)
  {
    return 0;
  }
  int N=arr.size();
  vector<int>zhangs;
  vector<int>coins;
  //分离数组，将纸币与张数分开
  MergeArray(arr,zhangs,coins);
  return process02(arr,zhangs,coins,0,aim);
}

int ways4(vector<int>&arr,int aim)
{
  if(arr.size()==0||aim==0)
  {
    return 0;
  }
 vector<int>zhangs;
 vector<int>coins;
 MergeArray(arr,zhangs,coins);
 int N=coins.size();
 vector<vector<int>>dp(N+1,vector<int>(aim+1,0));
 for(int i=1;i<=aim;i++)
 {
   dp[N][i]=-1;
 }
 for(int index=N-1;index>=0;index--)
 {
   for(int rest=0;rest<=aim;rest++)
   {
     //不要当前位置
     int p1=dp[index+1][rest];
     //要当前位置
     for(int zhang=1;zhang<=zhangs[index]&&zhang*coins[index]<=aim;zhang++)
     {
       if(rest-zhang*coins[index]>=0&&dp[index+1][rest-zhang*coins[index]]!=-1)
       {
         int p2=dp[index+1][rest-zhang*coins[index]];
         dp[index][rest]=min(p1,p2);
       }
     }
   }
 }
 return dp[0][aim];
}

//测试代码
vector<int> randomArray(int n, int maxValue) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = (rand() % maxValue) + 1;
    }

    return arr;
}

void printArray(vector<int> &arr) {
    cout << "arr : ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int maxLen = 20;
    int maxValue = 30;
    int testTime = 300000 + 1;

    cout << "Function Test begin:" << endl;
    for (int i = 0; i < testTime; i++) {
        int n = rand() % maxLen;
        vector<int> arr = randomArray(n, maxValue);
        int aim = rand() % maxValue;

        int ans = ways1(arr, aim);
        int ans1 = ways2(arr, aim);
        int ans2 = ways3(arr, aim);
        int ans3=ways4(arr,aim);
        if (ans != ans1 || ans2 != ans3||ans1!=ans2) {
            cout << "Oops!" << endl;
            printArray(arr);
            cout << "aim = " << aim << endl;
            cout << "ans = " << ans << endl;
            cout << "ans1 = " << ans1 << endl;
            cout << "ans2 = " << ans2 << endl;
            cout<<"ans3 = "<<ans3<<endl;
            break;
        }

    }
    cout << "Function Test ends!" << endl;
  return 0;
}










