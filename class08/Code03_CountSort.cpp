//计数排序
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<ctime>
using namespace std;

void countSort(vector<int>&arr)
{
  if(arr.size()<2)
  {
    return ;
  }
  int maxValue=INT_MIN;
  for(int i=0;i<arr.size();i++)
  {
    maxValue=max(maxValue,arr[i]);
  }
  vector<int>help(maxValue+1,0);
  for(int i=0;i<arr.size();i++)
  {
    help[arr[i]]++;
  }

  int j=0;
  for(int i=0;i<help.size();i++)
  {
    while(help[i]-->0)
    {
      arr[j++]=i;
    }
  }
}

//for test

void comparator(vector<int> &arr) {
    sort(arr.begin(), arr.end());
}

vector<int> generateRandomArray(int maxSize, int maxVal) {
    vector<int> arr(rand() % (maxSize + 1));
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % (maxVal + 1);
    }
    return arr;
}

vector<int> copyArray(vector<int> &arr) {
    vector<int> res(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        res[i] = arr[i];
    }
    return res;
}


bool isEqual(vector<int> &arr1, vector<int> &arr2) {
    if (arr1.size() != arr2.size()) return false;

    for (int i = 0; i < arr1.size(); i++) {
        if (arr1[i] != arr2[i])
            return false;
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
    srand(time(0));

    int testTime = 500000;
    int maxSize = 100;
    int maxVal = 150;
    cout<<"test begin"<<endl;
    for (int i = 0; i < testTime; i++) {
        vector<int> arr1 = generateRandomArray(maxSize, maxVal);
        vector<int> arr2 = copyArray(arr1);
        countSort(arr1);
        comparator(arr2);
        if (!isEqual(arr1, arr2)) {
            cout<<"test Opes!!!"<<endl;
            printArray(arr1);
            printArray(arr2);
            break;
        }
    }
    cout<<"test finsh"<<endl;
    return 0;
}
