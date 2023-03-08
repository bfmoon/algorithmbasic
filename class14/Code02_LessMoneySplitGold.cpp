/*
一块金条切成两半，是需要花费和长度数值一样的铜板
比如长度为20的金条，不管怎么切都要花费20个铜板，一群人想整分整块金条，怎么分最省铜板? 
例如，给定数组{10,20,30}，代表一共三个人，整块金条长度为60，金条要分成10，20，30三个部分。
如果先把长度60的金条分成10和50，花费60；再把长度50的金条分成20和30，花费50；一共花费110铜板
但如果先把长度60的金条分成30和30，花费60；再把长度30金条分成10和20，花费30；一共花费90铜板
输入一个数组，返回分割的最小代价
*/
#include<vector>
#include<iostream>
#include<queue>
#include<climits>
using namespace std;

//利用小根堆

int lessMoney1(vector<int>&arr)
{
  if(arr.size()==0)
  {
    return 0;
  }

  priority_queue<int,vector<int>,greater<int> >heap;
  for(int i=0;i<arr.size();i++)
  {
    heap.push(arr[i]);
  }

  int sum=0;
  int res=0;
  while(heap.size()>1)
  {
    int cur1=heap.top();
    heap.pop();
    int cur2=heap.top();
    heap.pop();
    res=cur1+cur2;
    sum+=res;
    heap.push(res);
  }
  return sum;
}

//暴力解法

vector<int> copyAndMergeTwo(vector<int> &arr, int i, int j) {
    vector<int> ans(arr.size() - 1);

    int ansi = 0;

    for (int arri = 0; arri < arr.size(); arri++) {
        if (arri != i && arri != j) {
            ans[ansi++] = arr[arri];
        }
    }

    ans[ansi] = arr[i] + arr[j];

    return ans;
}

//等待合并的数都在 arr 里，pre之前的合并行为产生了多少总代价
// arr 中只剩一个数字的时候，停止合并，返回最小的总代价
int process(vector<int> arr, int pre) {
    if (arr.size() == 1) return pre;

    int ans = INT_MAX;
    //尝试每两个数合并
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            ans = min(ans, process(copyAndMergeTwo(arr, i, j), pre + arr[i] + arr[j]) );
        }
    }

    return ans;
}

int lessMoney_test(vector<int> &arr) {
    if (arr.size() == 0) return 0;

    return process(arr, 0);
}

//for test
vector<int> generateRandomArray(int maxSize, int maxVal) {
    vector<int> arr(rand() % (maxSize + 1));
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % (maxVal + 1);
    }

    return arr;
}


int main() {
    srand(time(0)); //设置随机数种子
    int testTimes = 100000;
    int maxSize = 6;
    int maxVal = 1000;

    for (int i = 0; i < testTimes + 1; i++) {
        vector<int> arr = generateRandomArray(maxSize, maxVal);
        if (lessMoney1(arr) != lessMoney_test(arr)) {
            cout << "Oops!" << endl;
            return 0;
        }


    }

    cout << "Finish!" << endl;
    return 0;
}
