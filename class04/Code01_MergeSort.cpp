#include<iostream>
#include<vector>
using namespace std;


void merge(vector<int>&arr,int L,int mid,int R)
{
  vector<int>help(R-L+1);
  int p1=L;
  int p2=mid+1;
  int i=0;
  //两边准备排序
  while(p1<=mid&&p2<=R)
  {
    help[i++]=arr[p1]<=arr[p2]?arr[p1++]:arr[p2++];
  }
  //当跳出循环之后，有一个结束
  while(p1<=mid)
  {
    help[i++]=arr[p1++];
  }
  while(p2<=R)
  {
    help[i++]=arr[p2++];
  }
  for(i=0;i<help.size();i++)
  {
    arr[L+i]=help[i];
  }
}


void process(vector<int>&arr,int L,int R)
{
  if(L==R)
  {
    return ;
  }
  int mid=L+((R-L)>>1);
  process(arr,L,mid);
  process(arr,mid+1,R);
  merge(arr,L,mid,R);

}

//利用递归的方法
void MergeSort1(vector<int>&arr)
{
  if(arr.size()<2)
  {
    return ;
  }
  process(arr,0,arr.size()-1);
}


//利用非递归的方法
void MergeSort2(vector<int>&arr)
{
  if(arr.size()<2)
  {
    return ;
  }
  int N=arr.size();
  int megerSize=1;
  while(megerSize<N)
  {
    int L=0;
    while(L<N)
    {
      if(megerSize>=N-L)
      {
        break;
      }
      int M=L+megerSize-1;
      int R=M+min(megerSize,N-M-1);
      merge(arr,L,M,R);
      L=R+1;
    }
    if(megerSize>N/2)
    {
      break;
    }
    megerSize<<=1;
  }
}

//for test 
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
  for(int i=0;i<arr1.size();i++)
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
    MergeSort1(arr1);
    MergeSort2(arr2);
   if(!isEqul(arr1,arr2))
    {
      cout<<"Opes!!!"<<endl;
      break;
    }
  }
   cout<<"test finsh"<<endl;
   return 0;
} 

