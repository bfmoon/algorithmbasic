#include<iostream>
#include<vector>
using namespace std;

//实现堆结构
//大根堆
class MyMaxHeap
{
private:
  int * heap;
  int limit;
  int heapSize;
public:
  MyMaxHeap(int limit)
  {
    heap=new int[limit];
    this->limit=limit;
    heapSize=0;
  }
  ~MyMaxHeap()
  {
    delete [] heap;
  }

  bool isEqul()
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
      cout<<"堆满了"<<endl;
      return ;
    }
    heap[heapSize]=value;
    heapInsert(heap,heapSize++);

  }

  int pop()
  {
    int ans=heap[0];
    swap(heap,0,--heapSize);
    heapify(heap,0,heapSize);
    return ans;
  }
  void top()
  {
    cout<<heap[0]<<endl;
  }

private:
  void swap(int *arr,int i,int j)
  {
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
  }

  // 新加进来的数，现在停在了index位置，请依次往上移动，
// 移动到0位置，或者干不掉自己的父亲了，停！
  void heapInsert(int *arr,int index)
  {
    while(arr[index] > arr[(index-1)/2])
    {
      swap(arr,index,(index-1)/2);
      index=(index-1)/2;
    }
  }

  // 从index位置，往下看，不断的下沉
// 停：较大的孩子都不再比index位置的数大；已经没孩子了
  void heapify(int *arr,int index,int heapSize)
  {
    int left=index*2+1;
    while(left<heapSize)
    {
      int largest=(left+1<heapSize)&&arr[left+1]>arr[left]?left+1:left;
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
};

//for test
class RightMaxHeap {
private:
    int *arr;
    int limit;
    int size;
public:
    RightMaxHeap(int limit) {
        arr = new int[limit];
        this->limit = limit;
        size = 0;
    }
    ~RightMaxHeap()
    {
      delete []arr;
    }

    bool empty() {
        return size == 0;
    }

    bool isFull() {
        return size == limit;
    }

    void push(int value) {
        if (size == limit) {
            cout << "The heap is full" << endl;
            return ;
        }

        arr[size++] = value;
    }

    int pop() {
        int maxValInd = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] > arr[maxValInd]) {
                maxValInd = i;
            }
        }
        int ans = arr[maxValInd];
        arr[maxValInd] = arr[--size];
        return ans;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    srand(time(0));
    int value = 1000;
    int limit = 100;
    int testTime = 1000000;

    bool success = true;
    for (int i = 0; i < testTime + 1; i++) {
        int curLimit = rand() % limit + 1;
        MyMaxHeap myHeap(curLimit);
        RightMaxHeap test(curLimit);

        int curOpTimes = rand() % limit;

        for (int j = 0; j < curOpTimes; j++) {
            if (myHeap.isEqul() != test.empty()) {
                cout << "Oops! empty() function occurs error!" << endl;
                success = false;
                break;
            }

            if (myHeap.isFull() != test.isFull()) {
                cout << "Oops! isFull() function occurs error!" << endl;
                success = false;
                break;
            }

            if (myHeap.isEqul()) {
                int curValue = rand() % value;
                myHeap.push(curValue);
                test.push(curValue);
            } else if (myHeap.isFull()) {
                if (myHeap.pop() != test.pop()) {
                    cout << "Oops! pop() function occurs error!" << endl;
                    success = false;
                    break;
                }
            } else {
                if (((rand() % 101)/ (double)101) < 0.5) {
                    int curValue = rand() % value;
                    myHeap.push(curValue);
                    test.push(curValue);
                } else {
                    int ans1 = myHeap.pop();
                    int ans2 = test.pop();
                    if (ans1 != ans2) {
                        test.print();
                        cout << "ans1 = " << ans1 << ", ans2 = " << ans2 << endl;
                        cout << "Oops! pop() function occurs error again!" << endl;
                        success = false;
                        break;
                    }
                }
            }
        }
        if(i==499999)
        {
          test.print();
        }
    }
    cout << "finish!" << endl;

    return 0;
}
