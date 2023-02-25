#include<iostream>
#include<vector>
using namespace std;


// arr中，只有一种数，出现奇数次
//利用位运算
void printOddTimesNum1(vector<int>&arr)
{
  int eor=0;
  //出现偶数次时，两数异或就会变为0
  for(int i=0;i<arr.size();i++)
  {
    eor^=arr[i];
  }
  cout<<eor<<endl;
}

// arr中，有两种数，出现奇数次
void printOddTimesNum2(vector<int>&arr)
{
  int eor=0;
  //先将所有数异或，获得两个不同数的异或和
  for(int i=0;i<arr.size();i++)
  {
    eor^=arr[i];
  }

  //然后提取数最右边的1
  int rightOne=eor&((~eor)+1);
  int onlyOne=0;//定义其中一个数
  for(int i=0;i<arr.size();i++)
  {
    //按位与之后不等于0，说明刚好是两个出现奇数次数
    if((arr[i]&rightOne)!=0)
    {
      onlyOne^=arr[i];
    }
  }
  //此时onlyOne就是其中一个，另一个就是之前相异或的所有结果，在异或这个
  cout<<onlyOne<<" "<<(onlyOne^eor)<<endl;
}

//判断一个数的二进制中有几个1
int howOne(int value)
{
  int count=0;
  int rightOne=0;
  while(value!=0)
  {
    rightOne=value&((~value)+1);
    count++;
    value^=rightOne;
  }
  return count;
}


int main()
{
  vector<int>arr1={2,4,3,2,4};
  vector<int>arr2={4,2,4,3};
  printOddTimesNum1(arr1);
  printOddTimesNum2(arr2);

  int value=7;
  cout<<howOne(value)<<endl;
  return 0;
}

