//给定一个整型数组arr，和一个整数num
//某个arr中的子数组sub，如果想达标，必须满足：sub中最大值 – sub中最小值 <= num，
//返回arr中达标子数组的数量
#include<iostream>
#include<vector>
#include<deque>
using namespace std;

//暴力解
int right(vector<int>&arr,int num)
{
  if(arr.size()==0||num<0)
  {
    return 0;
  }
  int count=0;
  int N=arr.size();
  for(int L=0;L<N;L++)
  {
    for(int R=L;R<N;R++)
    {
      int ma=arr[L];
      int mi=arr[L];
      for(int i=L+1;i<=R;i++)
      {
        ma=max(ma,arr[i]);
        mi=min(mi,arr[i]);
      }
      if(ma-mi<=num)
      {
        count++;
      }
    }
  }
  return count;
}

//滑动窗口
int getSumWindow(vector<int>&arr,int num)
{
  if(arr.size()==0||num<0)
  {
    return 0;
  }
  //建立两个窗口，最大与最小
  deque<int>maxWindow;
  deque<int>minWindow;
  int N=arr.size();
  int count=0;
  int R=0;
  for(int L=0;L<N;L++)
  {
    while(R<N)
    {
      //更新最大值的窗口
      while(!maxWindow.empty()&&arr[maxWindow.back()]<=arr[R])
      {
        maxWindow.pop_back();
      }
      maxWindow.push_back(R);
      //更新最小值的窗口
      while(!minWindow.empty()&&arr[minWindow.back()]>=arr[R])
      {
        minWindow.pop_back();
      }
      minWindow.push_back(R);

      if(arr[maxWindow.front()]-arr[minWindow.front()]>num)
      {
        break;
      }
      else
      {
        R++;
      }
    }
    count+=R-L;
    if(maxWindow.front()==L)
    {
      maxWindow.pop_front();
    }
    if(minWindow.front()==L)
    {
      minWindow.pop_front();
    }
  }
  return count;
}

//for test
vector<int> generateRandomArray(int maxL, int maxV) 
{
    int len = rand() % (maxL + 1);
    vector<int> arr(len);
    for (int i = 0; i < len; i++) 
    {
        arr[i] = (rand() % (maxV + 1)) - (rand() % (maxV + 1));
    }

    return arr;
}

void printArray(vector<int> &arr) {
    if (arr.size()) {
        for (int i = 0; i < arr.size(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
} 

int main() {
    int maxL = 100;
    int maxV = 200;
    int testTime = 100000;
    cout << "Begin to test: " << endl;
    for (int i = 0; i < testTime; i++) {
        vector<int> arr = generateRandomArray(maxL, maxV);
        int sum = rand() % (maxV + 1);
        int ans1 = right(arr, sum);
        int ans2 = getSumWindow(arr, sum);
        if (ans1 != ans2) {
            cout << "Oops!" << endl;
            printArray(arr);
            cout << sum << endl;
            cout << ans1 << endl;
            cout << ans2 << endl;
            break;
        }
    }
    cout << "Test end!" << endl;
    return 0;
}





















