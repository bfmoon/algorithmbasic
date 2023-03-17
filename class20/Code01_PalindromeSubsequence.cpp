//给定一个字符串str，返回这个字符串的最长回文子序列长度
//比如 ： str = “a12b3c43def2ghi1kpm”
//最长回文子序列是“1234321”或者“123c321”，返回长度7


// 测试链接：https://leetcode.cn/problems/longest-palindromic-subsequence/


//暴力尝试
int process(string s,int L,int R)
{
	if(L==R)
	{
		return s[L]==s[R]?1:0;
	}
	else if(L==R-1)
	{
		return s[L]==s[R]?2:1;
	}
	else
	{
		
		//情况一：不以L为开始
		int p1=process(s,L+1,R);
		//情况二：不以R为结尾
		int p2=process(s,L,R-1);
		//情况三：不以L开头，也不以R结尾
		int p3=process(s,L+1,R-1);
		//情况四：以L开头，以R结尾
		int p4=s[L]==s[R]?process(s,L+1,R-1)+2:0;
		return max(max(max(p1,p2),p3),p4);
	}
}

int longestPalindromeSubseq(string s) 
{
	if(s.length()==0||s=="")
	{
		return 0;
	}
	return process(s,0,s.length()-1);
}

//动态规划
int longestPalindromeSubseq(string s) 
{
	if(s.length()==0||s=="")
	{
		return 0;
	}
	int N=s.length();
	vector<vector<int>>dp(N,vector<int>(N,0));
	dp[N-1][N-1]=1;
	//主对角线
	for(int i=0;i<N-1;i++)
	{
		dp[i][i]=1;
		dp[i][i+1]=s[i]==s[i+1]?2:1;
	}
	//处理剩下的
	for(int L=N-3;L>=0;L--)
	{
		for(int R=L+2;R<N;R++)
		{
			dp[L][R]=max(dp[L][R-1],dp[L+1][R]);
			if(s[L]==s[R])
			{
				dp[L][R]=max(dp[L][R],dp[L+1][R-1]+2);
			}
			
		}
	}
	return dp[0][N-1];
}
	
	
	
	
}
