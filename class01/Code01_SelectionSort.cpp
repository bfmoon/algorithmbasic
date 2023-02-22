#include<iostream>
#include<vector>
#include<ctime>
#include<algorithm>
using namespace std;
void SelectSort(vector<int>&arr1)
{
  int N=arr1.size();
  for(int i=0;i<N;i++)
  {
    int loc=i;
    for(int j=i+1;j<N;j++)
    {
      if(arr1[j]<arr1[loc])
      {
        loc=j;
      }
    }
    int temp=arr1[i];
    arr1[i]=arr1[loc];
    arr1[loc]=temp;
  }
}

//foe test
void compter(vector<int>&arr2)
{
  sort(arr2.begin(),arr2.end());
}

void generateRandomArray(vector<int>&arr1,int maxValue,int maxLen)
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

bool isEuql(vector<int>arr1,vector<int>arr2)
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
    std::cout<<arr[i]<<" ";
  }
  std::cout<<std::endl;
}


int main()
{
  int testTime = 500000;
  int maxSize = 100;
  int maxValue = 100;
  vector<int>arr1;
  vector<int>arr2;
  std::cout<<"test begin"<<std::endl;
  for(int i=0;i<testTime;i++)
  {
    generateRandomArray(arr1,maxValue,maxSize);
    copyArray(arr1,arr2);
    SelectSort(arr1);
    compter(arr2);
    if(!isEuql(arr1,arr2))
    {
      std::cout<<"Opes"<<std::endl;
      printArray(arr1);
      printArray(arr2);
      break;
    }
  }
  std::cout<<"test finsh!!!"<<std::endl;
  return 0;
}
