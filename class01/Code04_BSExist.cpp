#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//二分查找
bool isExist(vector<int>&arr,int num)
{
  if(arr.size()==0)
  {
    return false;
  }
  int L=0;
  int R=arr.size()-1;
  int mid=0;
  while(L<R)
  {
    mid=L+((R-L)>>1);
    if(arr[mid]==num)
    {
      return true;
    }
    else if(arr[mid]>num)
    {
      R=mid-1;
    }
    else
    {
      L=mid+1;
    }
  }
  return arr[L]==num;
}

//for test

bool compter(vector<int>&arr,int num)
{
  if(arr.size()==0)
  {
    return false;
  }

  for(int cur:arr)
  {
    if(cur==num)
    {
      return true;
    }
  }
  return false;
}

void generateRandomArray(vector<int>&arr,int maxLen,int maxValue)
{
  int N=rand()%maxLen;
  arr.resize(N);
  for(int i=0;i<N;i++)
  {
    arr[i]=rand()%maxValue;
  }
}


void printArray(vector<int>&arr)
{
  for(int i=0;i<arr.size();i++)
  {
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}

int main()
{
  int testTime=500000;
  int maxLen=10;
  int maxValue=100;
  vector<int>arr;
  cout<<"test begin"<<endl;
  for(int i=0;i<testTime;i++)
  {
    generateRandomArray(arr,maxLen,maxValue);
    sort(arr.begin(),arr.end());
    int value=rand()%(maxValue+1)-rand()%maxValue;
    if(compter(arr,value)!=isExist(arr,value))
    {
      cout<<"Opes!!!"<<endl;
      printArray(arr);
      cout<<value<<endl;
      break;
    }
  }
  cout<<"test finsh!!!!"<<endl;

  return 0;
}
