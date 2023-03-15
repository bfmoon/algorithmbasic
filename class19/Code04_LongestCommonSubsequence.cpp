//给定两个字符串str1和str2，
//返回这两个字符串的最长公共子序列长度
//比如 ： str1 = “a12b3c456d”,str2 = “1ef23ghi4j56k”
//最长公共子序列是“123456”，所以返回长度6

//样本对应模型

//题目连接：https://leetcode.cn/problems/longest-common-subsequence/

//暴力尝试---会超时
int process(string str1, string str2,int i,int j)
{
	if(i==0&&j==0)
	{
		return str1[i]==str2[j]?1:0;
	}
	else if(i==0)
	{
		return str1[i]==str2[j]?1:process(str1,str2,i,j-1);
	}
	else if(j==0)
	{
		return str1[i]==str2[j]?1:process(str1,str2,i-1,j);
	}
	//以0到i位置与0到j位置上做匹配
	//以j位置结尾
	else
	{
		int p1=process(str1,str2,i-1,j);
		//以i位置结尾
		int p2=process(str1,str2,i,j-1);
		//以两个都结尾
		int p3=str1[i]==str2[j]?1+process(str1,str2,i-1,j-1):0;
	
		return max(max(p1,p2),p3);
	}
}
int longestCommonSubsequence(string text1, string text2) 
{
	if(text1.length()==0&&text2.length()!=0||text2.length()==0&&text1.length()!=0)
	{
		return 0;
	}
	
	return process(text1,text2,text1.length()-1,text2.length()-1);
}

//动态规划版本
int longestCommonSubsequence2(string text1, string text2)
{
	if(text1.length()==0&&text2.length()!=0||text2.length()==0&&text1.length()!=0)
	{
		return 0;
	}
	int N=text1.length();
	int M=text2.length();
	vector<vector<int>>dp(N,vector<int>(M,0));
	dp[0][0]=text1[0]==text2[0]?1:0;
	for(int j=1;j<M;j++)
	{
		dp[0][j]=text1[0]==text2[j]?1:dp[0][j-1];
	}
	for(int i=1;i<N;i++)
	{
		dp[i][0]=text1[i]==text2[0]?1:dp[i-1][0];
	}
	
	for(int i=1;i<N;i++)
	{
		for(int j=1;j<M;j++)
		{
			int p1=dp[i][j-1];
			int p2=dp[i-1][j];
			int p3=text1[i]==text2[j]?1+dp[i-1][j-1]:0;
			dp[i][j]=max(max(p1,p2),p3);
		}
	}
	return dp[N-1][M-1];
}