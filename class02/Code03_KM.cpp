#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

//一个数组中有一种数出现K次，其他数都出现了M次，
//已知M > 1，K < M，找到出现了K次的数
//要求额外空间复杂度O（1），时间复杂度O（N）


//暴力版本
int test(vector<int>arr,int K,int M)
{
  unordered_map<int,int>hashMap;
  for(int num:arr)
  {
    if(hashMap.count(num))
    {
      hashMap[num]+=1;
    }
    else
    {
      hashMap[num]=1;
    }
  }
  for(auto value:hashMap)
  {
    if(auto.second==K)
    {
      return value;
    }
  }
  return -1;
}

//最优版
int onlyKTimes(vector<int>arr)
{




int main()
{

  return 0;
}
