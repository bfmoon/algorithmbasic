#include<iostream>
#include<vector>
using namespace std;

//在一个数组中，任何一个前面的数a，和任何一个后面的数b，如果（a，b）是降序的，就称为降序对
//给定一个数组arr，求数组的降序对总数量


int merge(vector<int>&arr,int L,int M,int R)
{
  vector<int>help(R-L+1);
  int i=help.size()-1;
  int p1=M;
  int p2=R;
  int res=0;
  while(p1>=L&&p2>M)
  {
    res+=arr[p1]>arr[p2]?(p2-M):0;
    help[i--]=arr[p1]>arr[p2]?arr[p1--]:arr[p2--];
  }
  while(p1>=L)
  {
    help[i--]=arr[p1--];
  }
  while(p2>M)
  {
    help[i--]=arr[p2--];
  }
  for(i=0;i<help.size();i++)
  {
    arr[L+i]=help[i];
  }
  return res;
}

int process(vector<int>&arr,int L,int R)
{
  if(L==R)
  {
    return 0;
  }
  int mid=L+((R-L)>>1);
  return process(arr,L,mid)+process(arr,mid+1,R)+merge(arr,L,mid,R);
}


int reverPairNumber(vector<int>&arr)
{
  if(arr.size()<2)
  {
    return 0;
  }
  return process(arr,0,arr.size()-1);
}

//for test
int compter(vector<int>&arr)
{
  if(arr.size()<2)
  {
    return 0;
  }
  int res=0;
  for(int i=0;i<arr.size();i++)
  {
    for(int j=i+1;j<arr.size();j++)
    {
      if(arr[i]>arr[j])
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
    int res1=reverPairNumber(arr1);
    int res2=compter(arr2);
    if(res1!=res2)
    {
      cout<<"Opes!!!"<<endl;
      cout<<res1<<endl;
      cout<<res2<<endl;
      printArray(arr1);
      printArray(arr2);
      break;
    }
  }
  cout<<"test begin"<<endl;
  return 0;
}
