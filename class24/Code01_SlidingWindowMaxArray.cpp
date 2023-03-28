//窗口内最大值或最小值更新结构的实现
//假设一个固定大小为W的窗口，依次划过arr，
//返回每一次滑出状况的最大值
//例如，arr = [4,3,5,4,3,3,6,7], W = 3
//返回：[5,5,5,4,6,7]
#include<iostream>
#include<vector>
#include<deque>
using namespace std;

//暴力方法
vector<int>right(vector<int>&arr,int w)
{
  if(w<1||arr.size()<w)
  {
    return vector<int>();
  }
  int N=arr.size();
  vector<int>ans(N-w+1);
  for(int i=0;i<=N-w;i++)
  {
    ans[i]=arr[i];
    for(int j=i;j<w+i&&j<N;j++)
    {
      ans[i]=max(ans[i],arr[j]);
    }
  }
  return ans;
}

//滑动窗口
vector<int>getMaxWindow(vector<int>&arr,int w)
{
  if(w<1||arr.size()<w)
  {
    return vector<int>();
  }
  int N=arr.size();
  vector<int>ans(N-w+1);
  int index=0;
  deque<int>qmax;
  for(int R=0;R<N;R++)
  {
    while(!qmax.empty()&&arr[qmax.back()]<=arr[R])
    {
      qmax.pop_back();
    }
    qmax.push_back(R);
    if(qmax.front()==R-w)
    {
      //前面的窗口过期了
      qmax.pop_front();
    }

    //赋值
    if(R>=w-1)
    {
      ans[index++]=arr[qmax.front()];
    }
  }
  return ans;
}

// for test
vector<int> generateRandomArray(int maxSize, int maxValue) 
{
    vector<int> arr(rand() % (maxSize + 1));

    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % (maxValue + 1);
    }

    return arr;
}

bool isEqual(vector<int> &arr1, vector<int> &arr2) 
{
    if (arr1.size() != arr2.size()) return false;

    for (int i = 0; i < arr1.size(); i++) {
        if (arr1[i] != arr2[i])
            return false;
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


int main() {
    int testTime = 100000;
    int maxSize = 100;
    int maxValue = 100;
    cout << "Test begin: " << endl;
    for (int i = 0; i < testTime; i++) {
        vector<int> arr = generateRandomArray(maxSize, maxValue);
        int w = rand() % (arr.size() + 1);

        vector<int> ans1 = getMaxWindow(arr, w);
        vector<int> ans2 = right(arr, w);
        if (!isEqual(ans1, ans2)) 
        {
            cout << "Oops!" << endl;
            cout<<w<<endl;
            printArray(ans1);
            printArray(ans2);
            break;
        }
    }
    cout << "Test finish!" << endl;
    return 0;
}


