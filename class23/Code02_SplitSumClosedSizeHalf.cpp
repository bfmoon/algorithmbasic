//给定一个正数数组arr，请把arr中所有的数分成两个集合
//如果arr长度为偶数，两个集合包含数的个数要一样多
//如果arr长度为奇数，两个集合包含数的个数必须只差一个
//请尽量让两个集合的累加和接近
//返回最接近的情况下，较小集合的累加和
#include<iostream>
#include<vector>
using namespace std;


//暴力尝试
//思路：两个集合累加和不可能超过数组累加和的一半
//所以只需要在原数组中选取不超过原数组累加和一半的最大接近即可
int process(vector<int>&arr,int index,int picks,int rest)
{
	if(index==arr.size())
	{
		return picks==0?0:-1;
	}
	//不要当前位置
	int p1=process(arr,index+1,picks,rest);
	//要当前位置的值
	int p2=-1;
	int next=-1;
	if(arr[index]<=rest)
	{
		next=process(arr,index+1,picks-1,rest-arr[index]);
	}
	if(next!=-1)
	{
		p2=next+arr[index];
	}
	return max(p1,p2);
}

int ways1(vector<int>&arr)
{
	if(arr.size()<2)
	{
		return 0;
	}
	int sum=0;
	for(int cur:arr)
	{
		sum+=cur;
	}
	if(arr.size()&1==0)
	{
		return process(arr,0,arr.size()/2,sum/2);
	}
	else
	{
		return max(process(arr,0,arr.size()/2,sum/2),process(arr,0,arr.size()/2+1,sum/2));
	}
}
		