//给定一个字符串str，只由'X'和'.'两种字符构成
//'X'表示墙，不能放灯，也不需要点亮；'.'表示居民点，可以放灯，需要点亮
//如果灯放在i位置，可以让i-1，i和i+1三个位置被点亮
//返回如果点亮str中所有需要点亮的位置，至少需要几盏灯
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<cstring>
#include<climits>
using namespace std;

int minLights1(string str)
{
  if(str.length()==0)
  {
    return 0;
  }
  int i=0;
  int ans=0;
  int N=str.length();
  while(i<N)
  {
    if(str[i]=='X')
    {
      i++;
    }
    else
    {
      ans++;
      if(i+1==N)
      {
        break;
      }
      else
      {
        if(str[i+1]=='X')
        {
          i=i+2;
        }
        else
        {
          i=i+3;
        }
      }
    }
  }
  return ans;
}


//暴力解法
int process(string str, int index, unordered_set<int> &lights) {
    if (index == str.length()) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] != 'X') {
                if (!lights.count(i - 1) && !lights.count(i) && !lights.count(i + 1)) {
                    return INT_MAX;
                }
            }
        }

        return lights.size();
    } else {
        int no = process(str, index + 1, lights);
        int yes = INT_MAX;

        if (str[index] == '.') {
            lights.insert(index);
            yes = process(str, index + 1, lights);
            lights.erase(index);
        }

        return min(no, yes);
    }
}


int minLights2(string road) {
    if (road.length() == 0) 
        return 0;

    unordered_set<int> lights;
    return process(road, 0, lights);
}

//for test
string randomString(int len) {
    char res[(rand() % len) + 1];

    for (int i = 0; i < strlen(res); i++) {
        res[i] = (rand() % 100 / (double)101) < 0.5 ? 'X' : '.';
    }

    return res;
}


int main() {
    srand(time(0));

    int len = 20;
    int testTimes = 100000;
    cout<<"test begin"<<endl;
    for (int i = 0; i < testTimes + 1; i++) {
        string test = randomString(len);
        int ans1 = minLights1(test);
        int ans2 = minLights2(test);
        if (ans1 != ans2) {
            cout << "Oops!" << endl;
            return 0;
        }


    }

    cout << "Finish!" << endl;
    return 0;
}


  
