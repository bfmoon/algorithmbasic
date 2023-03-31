//给定一个数组arr
//求每一个元素左边最近最小的，以及右边最近最小的元素
#include<iostream>
#include<vector>
#include<stack>
#include<list>
using namespace std;


//利用单调栈，存放的是下标
vector<vector<int>>getNearLessNoRepeat(vector<int>&arr)
{
  int N=arr.size();
  vector<vector<int>>res(N,vector<int>(2,0));
  stack<int>sta;
  //遍历每一个元素
  for(int i=0;i<N;i++)
  {
    while(!sta.empty()&&arr[sta.top()]>arr[i])
    {
      int j=sta.top();
      sta.pop();
      int leftIndex=sta.empty()?-1:sta.top();
      res[j][0]=leftIndex;
      res[j][1]=i;
    }
    sta.push(i);
  }
  while(!sta.empty())
  {
    int j=sta.top();
    sta.pop();
    int leftIndex=sta.empty()?-1:sta.top();
    res[j][0]=leftIndex;
    res[j][1]=-1;
  }
  return res;
}

//暴力方法
vector<vector<int>>rightWay(vector<int>&arr)
{
  int N=arr.size();
  vector<vector<int>>res(N,vector<int>(2,0));
  //从左往右遍历
  for(int i=0;i<N;i++)
  {
    for(int j=i;j<N;j++)
    {
      if(arr[i]>arr[j])
      {
        res[i][1]=j;
        break;
      }
      else
      {
        res[i][1]=-1;
      }
    }
  }
  //从右往左遍历
  for(int i=N-1;i>=0;i--)
  {
    for(int j=i;j>=0;j--)
    {
      if(arr[i]>arr[j])
      {
        res[i][0]=j;
        break;
      }
      else
      {
        res[i][0]=-1;
      }
    }
  }
  return res;
}

//数组中有重复值的单调栈
vector<vector<int>>getNearLess(vector<int>&arr)
{
  int N=arr.size();
  vector<vector<int>>res(N,vector<int>(2,0));
  //遇到值相同的都存放在一个数组里
  stack<vector<int>>sta;
  for(int i=0;i<N;i++)
  {
    while(!sta.empty()&&arr[sta.top()[0]]>arr[i])
    {
      vector<int>help=sta.top();
      sta.pop();
      int leftIndex=sta.empty()?-1:sta.top()[sta.top().size()-1];
      for(int j:help)
      {
        res[j][0]=leftIndex;
        res[j][1]=i;
      }
    }
    //当有相同值时，追加到后面
    if(!sta.empty()&&arr[sta.top()[0]]==arr[i])
    {
      sta.top().push_back(i);
    }
    else
    {
      //说明没有重复的
      vector<int>temp;
      temp.push_back(i);
      sta.push(temp);
    }
  }
  //遍历完后单独结算
  //最后的没有右边最小的
  while(!sta.empty())
  {
    vector<int>help=sta.top();
    sta.pop();
    int leftIndex=sta.empty()?-1:sta.top()[sta.top().size()-1];
    for(int v:help)
    {
      res[v][0]=leftIndex;
      res[v][1]=-1;
    }
  }
  return res;
}


//for test
vector<int> getRandomArrayNoRepeat(int size) {
    vector<int> arr(rand() % size + 1);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = i;
    }

    for (int i = 0; i < arr.size(); i++) {
        int swapIndex = rand() % arr.size();
        int tmp = arr[swapIndex];
        arr[swapIndex] = arr[i];
        arr[i] = tmp;
    }
    return arr;
}

//for test
vector<int> getRandomArray(int size, int maxV) {
    vector<int> arr(rand() % size + 1);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = (rand() % maxV) - (rand() % maxV);
    }

    return arr;
}


//for test
bool is_equal(vector<vector<int> > res1, vector<vector<int> > res2) {
    if (res1.size() != res2.size()) return false;

    for (int i = 0; i < res1.size(); i++) {
        if (res1[i][0] != res2[i][0] || res1[i][1] != res2[i][1]) {
            return false;
        }
    }

    return true;
}

void printArray(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int size = 10;
    int maxV = 20;
    int testTimes = 2000000 + 1;
    cout << "Begin to test:" << endl;
    for (int i = 0; i < testTimes; i++) {
        vector<int> arr1 = getRandomArrayNoRepeat(size);
        vector<int> arr2 = getRandomArray(size, maxV);
        if (!is_equal(getNearLessNoRepeat(arr1), rightWay(arr1))) {
            cout << "No repeat Oops!" << endl;
            printArray(arr1);
            return -1;
        }

        if (!is_equal(getNearLess(arr2), rightWay(arr2))) {
            cout << "Repeat Oops!" << endl;
            printArray(arr2);
            return -1;
        }

    }
    cout << "100% cases passed!" << endl;
    cout << "Test ends!" << endl;
    return 0;
}



