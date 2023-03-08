//一些项目要占用一个会议室宣讲，会议室不能同时容纳两个项目的宣讲，给你每一个项目开始的时间和结束的时间
//你来安排宣讲的日程，要求会议室进行的宣讲的场次最多，返回最多的宣讲场次
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//会议的结构
class Program
{
public:
  int start;
  int end;
  Program(){}
  Program(int s,int e)
  {
    this->start=s;
    this->end=e;
  }
};

//方法一：最优贪心
bool comp(Program&a,Program&b)
{
  return a.end<b.end;
}

int bestArrange1(vector<Program>&arr)
{
  if(arr.size()==0)
  {
    return 0;
  }
  sort(arr.begin(),arr.end(),comp);
  int res=0;
  int timeLine=0;
  for(int i=0;i<arr.size();i++)
  {
    if(timeLine<=arr[i].start)
    {
      res++;
    timeLine=arr[i].end;
    }
  }
  return res;
}


//暴力解
vector<Program> copyButExcept(vector<Program> &programs, int i) {
    vector<Program> ans(programs.size() - 1);
    int index = 0;
    for (int k = 0; k < programs.size(); k++) {
        if (k != i) ans[index++] = programs[k];
    }
    return ans;
}

int process(vector<Program> &programs, int done, int timeLine) {
    if (programs.size() == 0) return done;

    int _max = done;
    for (int i = 0; i < programs.size(); i++) {
        if (programs[i].start >= timeLine) {
            vector<Program> next = copyButExcept(programs, i);
            _max = max(_max, process(next, done + 1, programs[i].end));
        }
    }

    return _max;
}

int bestArrange2(vector<Program> &programs) {
    if (programs.size() == 0) return 0;

    return process(programs, 0, 0);
}

//for test
vector<Program> generatePrograms(int size, int timeMax) {
    vector<Program> ans(rand() % (size + 1));

    for (int i = 0; i < ans.size(); i++) {
        int r1 = rand() % (timeMax + 1);
        int r2 = rand() % (timeMax + 1);

        if (r1 == r2) ans[i] = Program(r1, r1 + 1);
        else ans[i] = Program(min(r1, r2), max(r1, r2));
    }

    return ans;
}

int main() {
    srand(time(0));

    int size = 12;
    int timeMax = 20;
    int timeTimes = 1000000;
    cout<<"test begin"<<endl;

    for (int i = 0; i < timeTimes + 1; i++) {
        vector<Program> programs = generatePrograms(size, timeMax);
        if (bestArrange1(programs) != bestArrange2(programs)) {
            cout << "Oops!" << endl;
            break;
        }

    }

    cout << "finish!" << endl;

    return 0;
}


