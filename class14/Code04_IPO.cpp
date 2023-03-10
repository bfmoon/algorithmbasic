#include<iostream>
#include<queue>
using namespace std;

class Program
{
public:
  int capital;
  int profits;
  Program(int c,int p):capital(c),profits(p){}
};

//优先队列的排序方式重载运算符
struct mincapitalCMP
{
  bool operator()(Program* const &p1,Program*  const  &p2)
{
  return p1->capital>p2->capital;
}
};

struct maxcapitalCMP
{
  bool operator()(Program* const &p1,Program*const &p2)
{
  return p1->profits<p2->profits;
}
};


int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital)
{
  priority_queue<Program*, vector<Program*>, mincapitalCMP> mincapitalQue;
  priority_queue<Program*, vector<Program*>, maxcapitalCMP> maxprofitsQue;
  for(int i=0;i<profits.size();i++)
  {
    mincapitalQue.push(new Program(capital[i],profits[i]));
  }

  for(int i=0;i<k,i++)
  {
    while(!mincapitalQue.empty()&&mincapitalQue.top()<=w)
    {
      maxprofitsQue.push(mincapitalQue.top());
      mincapitalQue.pop();
    }
    if(maxprofitsQue.empty())
    {
      return w;
    }
    w+=maxprofitsQue.top().profits;
    maxprofitsQue.pop();
  }
  return w;
}




