//给定一个由字符串组成的数组strs，必须把所有的字符串拼接起来，返回所有可能的拼接结果中字典序最小的结果
#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<algorithm>
using namespace std;

bool comp(const string &s1,const string &s2)
{
  return s1+s2<s2+s1;
}

//贪心
string lowestString1(vector<string>& strs)
{
  if(strs.size()==0)
  {
    return "";
  }
  sort(strs.begin(),strs.end(),comp);
  string res="";
  for(int i=0;i<strs.size();;i++)
  {
    res+=strs[i];
  }
  return res;
}



