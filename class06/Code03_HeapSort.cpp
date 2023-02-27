#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//堆排序，利用heapInsert和heapify
void swap(vector<int>&arr,int i,int j)
{
  int temp=arr[i];
  arr[i]=arr[j];
  arr[j]=temp;
}

//插入数据往上走
void heapInsert(vector<int>&arr,int index)
{
  while(arr[index]>arr[(index-1)/2])
  {
    swap(arr,index,(index-1)/2);
    index=(index-1)/2;
  }
}

//数据向下比较
void heapify(vector<int>&arr,int index,int heapSize)
{
  int left=index*2+1;
  while(left<heapSize)
  {
    //找两个孩子的较大者
    int largest=left+1<heapSize&&arr[left+1]>arr[left]?left+1:left;
    largest=arr[largest]>arr[index]?largest:index;
    if(largest==index)
    {
      break;
    }
    swap(arr,largest,index);
    index=largest;
    left=index*2+1;
  }
}

void heapSort(vector<int>&arr)
{
  if(arr.size()<2)
  {
    return ;
  }
  for(int i=arr.size()-1;i>=0;i--)
  {
    heapify(arr,i,arr.size());
  }
  int heapSize=arr.size();
  swap(arr,0,--heapSize);
  while(heapSize>0)
  {
    heapify(arr,0,heapSize);
    swap(arr,0,--heapSize);
  }
}

//for test
//利用快排，做测试
vector<int>partition(vector<int>&arr,int L,int R)
{
  vector<int>res(2);
  if(L>R)
  {
    res[0]=res[1]=-1;
    return res;
  }
  if(L==R)
  {
    res[0]=res[1]=1;
    return res;
  }
  int less=L-1;
  int more=R;
  int index=L;
  while(index<more)
  {
    if(arr[index]==arr[R])
    {
      index++;
    }
    else if(arr[index]<arr[R])
    {
      swap(arr,index++,++less);
    }
    else
    {
      swap(arr,index,--more);
    }
  }
  swap(arr,more,R);
  res[0]=less+1;
  res[1]=more;
  return res;
}

void process(vector<int>&arr,int L,int R)
{
  if(L>=R)
  {
    return ;
  }
  vector<int>ans=partition(arr,L,R);
  process(arr,0,ans[0]-1);
  process(arr,ans[1]+1,R);
}

void quackSort(vector<int>&arr)
{
  if(arr.size()<2)
  {
    return ;
  }
  process(arr,0,arr.size()-1);
}

//for test
void generateRandomArray(vector<int>&arr,int maxLen,int maxValue)
{
  int N=rand()%maxLen;
  arr.resize(N);
  for(int i=0;i<arr.size();i++)
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
  int testTime=50000;
  int maxLen=100;
  int maxValue=100;
  vector<int>arr1;
  vector<int>arr2;
  cout<<"test begin"<<endl;
  for(int i=0;i<testTime;i++)
  {
    generateRandomArray(arr1,maxLen,maxValue);
    copyArray(arr1,arr2);
    heapSort(arr1);
    quackSort(arr2);
    if(!isEqul(arr1,arr2))
    {
      cout<<"Opes!!!"<<endl;
      printArray(arr1);
      printArray(arr2);
      break;
    }
  }
  cout<<"test finsh"<<endl;
  printArray(arr1);
  return 0;
}























