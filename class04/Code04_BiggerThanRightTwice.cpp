//https://leetcode.com/problems/reverse-pairs/
//在一个数组中，对于任何一个数num，求有多少个（后面的数*2）依然<num，返回总个数

#include<iostream>
#include<vector>
using namespace std;

int merge(vector<int>&arr,int l,int m,int r)
{
  int res=0;
  int windows=m+1;
  for(int i=l;i<=m;i++)
  {
    while(windows<=r&&arr[i]>arr[windows]*2)
    {
      windows++;
    }
    res+=windows-m-1;
  }

  vector<int>help(r-l+1);
  int p1=l;
  int p2=m+1;
  int i=0;
  while(p1<=m&&p2<=r)
  {
    help[i++]=arr[p1]<=arr[p2]?arr[p1++]:arr[p2++];
  }
  while(p1<=m)
  {
    help[i++]=arr[p1++];
  }
  while(p2<=r)
  {
    help[i++]=arr[p2++];
  }
  for(i=0;i<help.size();i++)
  {
    arr[l+i]=help[i];
  }
  return res;
}

int process(vector<int>&arr,int l,int r)
{
  if(l==r)
  {
    return 0;
  }
  int mid=l+((r-l)>>1);
  return process(arr,l,mid)+process(arr,mid+1,r)+merge(arr,l,mid,r);
}

int reversePairs(vector<int>& nums)
{
  if(nums.size()<2)
  {
    return 0;
  }
  return process(nums,0,nums.size()-1);
}

//for test
int compter(vector<int>arr)
{
  int res=0;
  for(int i=0;i<arr.size();i++)
  {
    for(int j=i+1;j<arr.size();j++)
    {
      if(arr[i]>2*arr[j])
      {
        res++;
      }
    }
  }
  return res;
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

void copyArray(vector<int>arr1,vector<int>&arr2)
{
  int N=arr1.size();
  arr2.resize(N);
  for(int i=0;i<N;i++)
  {
    arr2[i]=arr1[i];
  }
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
  int testTime=500000;
  int maxLen=100;
  int maxValue=100;
  vector<int>arr1;
  vector<int>arr2;
  cout<<"test begin"<<endl;
  for(int i=0;i<testTime;i++)
  {
    generateRandomArray(arr1,maxLen,maxValue);
    copyArray(arr1,arr2);
    int res1=reversePairs(arr1);
    int res2=compter(arr2);
    if(res1!=res2)
    {
      cout<<"Opees!!!"<<endl;
      printArray(arr1);
      printArray(arr2);
      cout<<res1<<endl;
      cout<<res2<<endl;
      break;
    }
  }
  cout<<"test finsh"<<endl;
  return 0;
}
