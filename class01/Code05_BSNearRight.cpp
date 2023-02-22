#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//找<=value最右的位置
int nearesRight(vector<int>&arr,int value)
{
  int L=0;
  int R=arr.size()-1;
  int index=-1;
  while(L<=R)
  {
    int mid=L+((R-L)>>1);
    if(arr[mid]<=value)
    {
      index=mid;
      L=mid+1;
    }
    else
    {
      R=mid-1;
    }
  }
  return index;
}

//for test
int test(vector<int>&arr,int value)
{
  int N=arr.size();
  for(int i=N-1;i>=0;i--)
  {
    if(arr[i]<=value)
    {
      return i;
    }
  }
  return -1;
}

void generaterandomArray(vector<int>&arr,int maxLen,int maxValue)
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
    generaterandomArray(arr,maxLen,maxValue);
    sort(arr.begin(),arr.end());
    int value=rand()%(maxValue+1)-rand()%maxValue;
    if(nearesRight(arr,value)!=test(arr,value))
    {
      cout<<"Opes!!!"<<endl;
      printArray(arr);
      cout<<value<<endl;
      break;
    }
  }
  cout<<"test finsh"<<endl;
  return 0;
}


