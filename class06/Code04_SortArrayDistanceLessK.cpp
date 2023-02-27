//已知一个几乎有序的数组。几乎有序是指，如果把数组排好顺序的话，每个元素移动的距离一定不超过k
//k相对于数组长度来说是比较小的。请选择一个合适的排序策略，对这个数组进行排序。

#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
//利用小根堆

class MyminHeap
{
private:
  int *heap;
  int limit;
  int heapSize;
public:
  MyminHeap(int limit)
  {
    heap=new int[limit];
    this->limit=limit;
    this->heapSize=0;
  }
  ~MyminHeap()
  {
    delete [] heap;
  }

public:
  bool isEmpty()
  {
    return heapSize==0;
  }
  bool isFull()
  {
    return heapSize==limit;
  }

  void push(int value)
  {
    if(heapSize==limit)
    {
      cout<<"is full"<<endl;
      return ;
    }
    heap[heapSize]=value;
    heapInsert(heap,heapSize++);
  }

  int pop()
  {
    int res=heap[0];
    swap(heap,0,--heapSize);
    heapify(heap,0,heapSize);
    return res;
  }

private:
  void heapInsert(int *arr,int index)
  {
    while(arr[index]<arr[(index-1)/2])
    {
      swap(arr,index,(index-1)/2);
      index=(index-1)/2;
    }
  }

  void heapify(int *arr,int index,int heapSize)
  {
    int left=index*2+1;
    while(left<heapSize)
    {
      int largest=(left+1<heapSize)&&arr[left+1]<arr[left]?left+1:left;
      largest=arr[largest]<arr[index]?largest:index;
      if(largest==index)
      {
        break;
      }
      swap(arr,largest,index);
      index=largest;
      left=index*2+1;
    }
  }

  void swap(int *arr,int i,int j)
  {
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
  }

};

void sortedArrDistanceLessK(vector<int>&arr,int k)
{
  if(k==0)
  {
    return ;
  }
  MyminHeap heap(arr.size());
  int index=0;
  int N=arr.size();
  for(;index<=min(N-1,k-1);index++)
  {
    heap.push(arr[index]);
  }
  int i=0;
  for(;index<arr.size();i++,index++)
  {
    heap.push(arr[index]);
    arr[i]=heap.pop();
  }
  
  while(!heap.isEmpty())
  {
    arr[i++]=heap.pop();
  }
}

//for test
void comparator(vector<int> &arr, int k) {
    sort(arr.begin(), arr.end());
}

vector<int> randomArrayNoMoveMoreK(int maxSize, int maxVal, int k) {
    vector<int> arr(rand() % (maxSize + 1));
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = (rand() % (maxVal + 1)) - (rand() % (maxVal + 1));
    }
    //排序
    sort(arr.begin(), arr.end());
    //随意交换，但保证每个数距离不超过k
    //swap[i] == true，表示i位置已经参与过交换
    //swap[i] == false, 表示 i 位置没有参与过交换
    vector<bool> isSwapped(arr.size());
    int N=arr.size();
    for (int i = 0; i < arr.size(); i++) {
        int j = min(i + (rand() % (k + 1)) , N- 1);
        if (!isSwapped[i] && !isSwapped[j]) {
            isSwapped[i] = true;
            isSwapped[j] = true;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
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
    if (arr1.size() != arr2.size())
        return false;

    for (int i = 0; i < arr1.size(); i++) {
        if (arr1[i] != arr2[i]) {
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
    srand(time(0));
    int testTime = 500000;
    int maxSize = 100;
    int maxValue = 100;
    bool success = true;
    cout<<"test begin"<<endl;
    for (int i = 0; i < testTime + 1; i++) {
        int k = (rand() % maxSize) + 1;
        vector<int> arr = randomArrayNoMoveMoreK(maxSize, maxValue, k);
        vector<int> arr1 = copyArray(arr);
        vector<int> arr2 = copyArray(arr);

        sortedArrDistanceLessK(arr1, k);
        comparator(arr2, k);
        if (!isEqual(arr1, arr2)) {
            success = false;
            cout << "k : " << k <<endl;
            printArray(arr);
            printArray(arr1);
            printArray(arr2);
            break;
        }
        if(i==499999)
        {
          printArray(arr1);
          printArray(arr2);
        }
      }
    

    cout << (success ? "Nice!" : "Fucking fucked!") << endl;
    return 0;
}



































