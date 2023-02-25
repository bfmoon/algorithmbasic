#include<iostream>
#include<vector>
using namespace std;

//在一个数组中，一个数左边比它小的数的总和，叫该数的小和
//所有数的小和累加起来，叫数组小和
/*例子： [1,3,4,2,5]
1左边比1小的数：没有
3左边比3小的数：1
4左边比4小的数：1、3
2左边比2小的数：1
5左边比5小的数：1、3、4、 2
所以数组的小和为1+1+3+1+1+3+4+2=16
给定一个数组arr，求数组小和*/

int merge(vector<int>&arr,int L,int M,int R)
{
  int p1=L;
  int p2=M+1;
  int i=0;
  vector<int>help(R-L+1);
  int res=0;
  while(p1<=M&&p2<=R)
  {
    res+=arr[p1]<arr[p2]?(R-p2+1)*arr[p1]:0;
    help[i++]=arr[p1]<arr[p2]?arr[p1++]:arr[p2++];
  }
  while(p1<=M)
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

int smallSum(vector<int>&arr)
{
  if(arr.size()<2)
  {
    return 0;
  }
  return process(arr,0,arr.size()-1);
}

//暴力
int compter(vector<int>&arr)
{
  int N=arr.size();
  int res=0;
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<i;j++)
    {
      res+=arr[j]<arr[i]?arr[j]:0;
    }
  }
  return res;
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

void printArray(vector<int>arr)
{
  for(int i=0;i<arr.size();i++)
  {
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}
void copyArray(vector<int>arr,vector<int>&arr2)
{
  int N=arr.size();
  arr2.resize(N);
  for(int i=0;i<N;i++)
  {
    arr2[i]=arr[i];
  }
}

int main()
{
  int testTime=5000;
  int maxLen=10;
  int maxValue=100;
  vector<int>arr;
  vector<int>arr2;
  cout<<"test begin"<<endl;
  for(int i=0;i<testTime;i++)
  {
    generateRandomArray(arr,maxLen,maxValue);
    copyArray(arr,arr2);
    int res1=smallSum(arr);
    int res2=compter(arr2);
    if(res1!=res2)
    {
      cout<<"Opes!!!"<<endl;
      cout<<res1<<endl;
      cout<<res2<<endl;
      printArray(arr);
      break;
    }

  }
  cout<<"test finsh"<<endl;
  return 0;
}
