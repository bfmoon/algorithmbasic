//规定1和A对应、2和B对应、3和C对应...26和Z对应
//那么一个数字字符串比如"111”就可以转化为:
//"AAA"、"KA"和"AK"
//给定一个只有数字字符组成的字符串str，返回有多少种转化结果
//从左往右的尝试模型
#include<iostream>
#include<vector>
#include<string>
using namespace std;


//暴力尝试
int process01(string str,int index)
{
	if(index==str.length())
	{
		//说明之前的转化成功
		return 1;
	}
	if(str[index]=='0')
	{
		return 0;
	}
	//第一中方法一个一个尝试
	int way1=process01(str,index+1);
	//第二种，两个数一组
	int way2=0;
	if((index+1<str.length())&&(str[index]-'0')*10+str[index+1]-'0'<27)
	{
		way2=process01(str,index+2);
	}
	return way1+way2;
}
	
int number1(string str)
{
	if(str.length()==0||str=="")
	{
		return 0;
	}
	
	return process01(str,0);
}

//动态规划(从右往左的动态规划)
int number2(string str)
{
	if(str.length()==0||str=="")
	{
		return 0;
	}
	int N=str.length();
	vector<int>dp(N+1);
	dp[N]=1;
	for(int index=N-1;index>=0;index--)
	{
		if(str[index]!='0')
		{
			int way=dp[index+1];
			if(index+1<N&&((str[index]-'0')*10+str[index]-'0')<27)
			{
				way+=dp[index+2];
			}
			dp[index]=way;
		}
	}
	return dp[0];
}

int main()
{
	string str="111";
	cout<<number1(str)<<endl;
	cout<<number2(str)<<endl;
	return 0;
}
		
		
		
		
		
		
		
		
		
		
		
		
	