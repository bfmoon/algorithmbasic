//给定很多线段，每个线段都有两个数[start, end]，
//表示线段开始位置和结束位置，左右都是闭区间
//规定：
//1）线段的开始和结束位置一定都是整数值
//2）线段重合区域的长度必须>=1
//返回线段最多重合区域中，包含了几条线段
//
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<climits>
using namespace std;

//暴力方法
int maxCover1(vector<vector<int>>&arr)
{
  int mi=INT_MAX;
  int ma=INT_MIN;
  for(int i=0;i<arr.size();i++)
  {
    mi=min(mi,arr[i][0]);
    ma=max(ma,arr[i][1]);
  }
  int cover=0;
  for(double p=mi+0.5;p<ma;p+=1)
  {
    int cur=0;
    for(int i=0;i<arr.size();i++)
    {
      if(p>arr[i][0]&&p<arr[i][1])
      {
        cur++;
      }
    }
    cover=max(cover,cur);
  }
  return cover;
}


//优化利用堆结构
struct Line
{
  Line(){}
  Line(int s,int e)
  {
    start=s;
    end=e;
  }
  int start;
  int end;
};

bool cmp(const Line &l1,const Line &l2)
{
  return l1.start<l2.start;
}

int maxCover2(vector<vector<int>>&arr)
{
  vector<Line>line(arr.size());
  for(int i=0;i<arr.size();i++)
  {
    line[i]=Line(arr[i][0],arr[i][1]);
  }
  sort(line.begin(),line.end(),cmp);
  priority_queue<int, vector<int>, greater<int>>heap;//小根堆
  int res=0;
  for(int i=0;i<line.size();i++)
  {
    while(!heap.empty()&&heap.top()<=line[i].start)
    {
      heap.pop();
    }
    heap.push(line[i].end);
    res=max(res,(int)heap.size());
  }
  return res;
}

vector<vector<int> > generateLines(int n, int l, int r) {
    int size = (rand() % n) + 1;
    vector<vector<int> > ans(size, vector<int>(2));

    for (int i = 0; i < size; i++) {
        int a = l + ((rand() % (r - l + 1)));
        int b = l + (rand() % (r- l + 1));
        if (a == b) b = a + 1;

        ans[i][0] = min(a, b);
        ans[i][1] = max(a, b);
    }
    return ans;
}    
void printArray(vector<vector<int>>arr)
{
  for(int i=0;i<arr.size();i++)
  {
    for(int j=0;j<arr[0].size();j++)
    {
      cout<<arr[i][j]<<" ";
    }
    cout<<endl;
  }
}

int main()
{
    cout << "test begin" << endl;
    int n = 100;
    int l = 0;
    int r = 200;
    int testTimes = 20000;


    for (int i = 0; i < testTimes + 1; i++) {
        vector<vector<int> > lines = generateLines(n, l, r);
        int ans1 = maxCover1(lines);
        int ans2 = maxCover2(lines);

        if (ans1 != ans2) {
            cout << "Oops!!" << endl;
            printArray(lines);
            cout<<ans1<<" "<<ans2<<endl;
            break;
        }
        
    }

    cout << "test end" << endl;
    return 0;
}



