//给定一个只包含正数的数组arr，arr中任何一个子数组sub，
//一定都可以算出(sub累加和 )* (sub中的最小值)是什么，
//那么所有子数组中，这个值最大是多少？

//https://leetcode.cn/problems/maximum-subarray-min-product/submissions/
#include<iostream>
#include<vector>
#include<stack>
#include<climits>
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
      ma=max(ma,(sta.empty()?sum[i-1]:(sum[i-1]-sum[sta.top()]))*arr[j]);
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

//暴力方法
int max2(vector<int>&arr)
{
  if(arr.size()==0)
  {
    return 0;
  }
  int N=arr.size();
  int ma=INT_MIN;
  for(int i=0;i<N;i++)
  {
    for(int j=i;j<N;j++)
    {
      int sum=0;
      int mi=INT_MAX;
      for(int k=i;k<=j;k++)
      {
        sum+=arr[k];
        mi=min(mi,arr[k]);
      }
      ma=max(ma,sum*mi);
    }
  }
  return ma%1000000007;
}

//for test
vector<int> getRandomArray(int value, int size) {
    vector<int> arr(rand() % size + 1);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = abs((rand() % value) - (rand() % value));
    }

    return arr;
}

bool is_equal(int v1, int v2) {
    return v1 == v2;
}


void printArray(vector<int> &arr) {
    cout << "arr:";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    int value = 20;
    int size = 10;
    int times = 200000 + 1;

    cout << "Begin to test:" << endl;

    for (int i = 0; i < times; i++) {
        vector<int> arr = getRandomArray(value, size);
        if (!is_equal(max2(arr), max1(arr))) {
            cout << "Oops!" << endl;
            printArray(arr);
            cout << "Test Failed!" << endl;
            break;
            return -1;
        }

    }
    cout << "Test ends!" << endl;

    return 0;
}



    


