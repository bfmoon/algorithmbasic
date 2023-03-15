//背包问题（从左往右的尝试模型，要与不要问题）
//给定两个长度都为N的数组weights和values，weights[i]和values[i]分别代表 i号物品的重量和价值
//给定一个正数bag，表示一个载重bag的袋子，装的物品不能超过这个重量
//返回能装下的最大价值
#include<iostream>
#include<vector>
using namespace std;
//暴力尝试入手
int process01(vector<int>&weight,vector<int>&value,int rest,int index)
{
	if(rest<0)
	{
		return -1;
	}
	if(index==weight.size())
	{
		return 0;
	}
	//不要当前位置的值
	int p1=process01(weight,value,rest,index+1);
	int p2=0;
	//要当前位置的值
	int next=process01(weight,value,rest-weight[index],index+1);
	if(next!=-1)
	{
		//所以钱数要加上当前位置的钱数
		p2=next+value[index];
	}
	return max(p1,p2);
}


int maxValue1(vector<int>&weight,vector<int>&value,int bag)
{
	if(bag<0||weight.size()!=value.size())
	{
		return 0;
	}
	return process01(weight,value,bag,0);
	
}

//动态规划
int maxValue2(vector<int>&weight,vector<int>&value,int bag)
{
	if(bag<0||weight.size()!=value.size())
	{
		return 0;
	}
	int N=weight.size();
	vector<vector<int>>dp(N+1,vector<int>(bag+1,0));
	for(int index=N-1;index>=0;index--)
	{
		for(int rest=0;rest<=bag;rest++)
		{
			int p1=dp[index+1][rest];
			int p2=0;
			if(rest-weight[index]>=0)
			{
				p2=dp[index+1][rest-weight[index]]+value[index];
			}
			dp[index][rest]=max(p1,p2);
		}
	}
	return dp[0][bag];
}

int main()
{
	vector<int>weight={ 3, 2, 4, 7, 3, 1, 7};
	vector<int>value={5, 6, 3, 19, 12, 4, 2};
	int bag=15;
	cout<<maxValue1(weight,value,bag)<<endl;
	cout<<maxValue2(weight,value,bag)<<endl;
	return 0;
}

	
	
	
	
	
	
	