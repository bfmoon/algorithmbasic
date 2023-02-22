#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


void InsertSort(vector<int>&arr1)
{
  int N=arr1.size();
  //先将0~~i排好序
  for(int i=1;i<N;i++)
  {
    for(int j=i-1;j>=0&&arr1[j]>arr1[j+1];j--)
    {
      int temp=arr1[j];
      arr1[j]=arr1[j+1];
      arr1[j+1]=temp;
    }
  }
}

void compter(vector<int>&arr2)
{
  sort(arr2.begin(),arr2.end());
}

void generateRandomArray(vector<int>&arr1,int maxLen,int maxValue)
{
  int N=rand()%maxLen;
  arr1.resize(N);
  for(int i=0;i<N;i++)
  {
    arr1[i]=rand()%maxValue;
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

bool isEqul(vector<int>arr1,vector<int>arr2)
{
  if(arr1.size()!=arr2.size())
  {
    return false;
  }
  for(int i=0;i<arr1.size();i++)
  {
    if(arr1[i]!=arr2[i])
    {
      return false;
    }
  }
  return true;
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
  int maxLen=100;
  int maxValue=100;
  int testTime=500000;
  vector<int>arr1;
  vector<int>arr2;
  cout<<"test begin"<<endl;
  for(int i=0;i<testTime;i++)
  {
    generateRandomArray(arr1,maxLen,maxValue);
    copyArray(arr1,arr2);
    InsertSort(arr1);
    compter(arr2);
    if(!isEqul(arr1,arr2))
    {
      cout<<"Opes!!!"<<endl;
      printArray(arr1);
      printArray(arr2);
      break;
    }
  }
  cout<<"test finsh!!!!"<<endl;
 
  return 0;
}
