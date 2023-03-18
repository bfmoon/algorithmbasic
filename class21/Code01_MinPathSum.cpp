//给定一个二维数组matrix，一个人必须从左上角出发，最后到达右下角
//沿途只可以向下或者向右走，沿途的数字都累加就是距离累加和
//返回最小距离累加和
#include<iostream>
#include<vector>
using namespace std;


int process(vector<vector<int>>&m,int x,int y,int N,int M)
{
	if(x==N-1&&y==M-1)
	{
		return m[N-1][M-1];
	}
	if(x==N-1)
	{
		return m[x][y]+process(m,x,y+1,N,M);
	}
	if(y==M-1)
	{
	    return m[x][y]+process(m,x+1,y,N,M);
	}
	return m[x][y]+min(process(m,x+1,y,N,M),process(m,x,y+1,N,M));
	
}
int minPathSum1(vector<vector<int>>m)
{
	if(m.size()==0)
	{
		return 0;
	}
	return process(m,0,0,m.size(),m[0].size());
}

//方法二：动态规划
int minPathSum2(vector<vector<int>>&m)
{
	if(m.size()==0)
	{
		return 0;
	}
	int N=m.size();
	int M=m[0].size();
	vector<vector<int>>dp(N,vector<int>(M,0));
	//先处理第0行
	dp[0][0]=m[0][0];
	for(int i=1;i<M;i++)
	{
		dp[0][i]=dp[0][i-1]+m[0][i];
	}
	//处理第0列
	for(int i=1;i<N;i++)
	{
		dp[i][0]=dp[i-1][0]+m[i][0];
	}
	//处理剩下的
	for(int i=1;i<N;i++)
	{
		for(int j=1;j<M;j++)
		{
			dp[i][j]=min(dp[i-1][j],dp[i][j-1])+m[i][j];
		}
	}
	return dp[N-1][M-1];
}

//空间优化的动态规划
int minPathSum3(vector<vector<int>>&m)
{
	if(m.size()==0)
	{
		return 0;
	}
	int N=m.size();
	int M=m[0].size();
	vector<int>dp(M,0);
	dp[0]=m[0][0];
	//处理第一行
	for(int i=1;i<M;i++)
	{
		dp[i]=dp[i-1]+m[0][i];
	}
	//处理剩下的
	for(int i=1;i<N;i++)
	{
		dp[0]+=m[i][0];
		for(int j=1;j<M;j++)
		{
			dp[j]=min(dp[j-1],dp[j])+m[i][j];
		}
	}
	return dp[M-1];
}

//for test
vector<vector<int>>generateRandomMatrix(int rowSize, int colSize) {
		vector<vector<int>>result(rowSize,vector<int>(colSize,0));
		for (int i = 0; i != result.size(); i++) 
		{
			for (int j = 0; j != result[0].size(); j++) 
			{
				result[i][j] = rand()%100;
			}
		}
		return result;
	}

// for test
void printMatrix(vector<vector<int>>matrix) 
{
	for (int i = 0; i != matrix.size(); i++) 
	{
		for (int j = 0; j != matrix[0].size(); j++) 
		{
			cout<<matrix[i][j] <<" ";
		}
		cout<<endl;
	}
}

vector<vector<int>>copy(vector<vector<int>>&m)
{
	vector<vector<int>>result(m.size(),vector<int>(m[0].size(),0));
	for (int i = 0; i != result.size(); i++) 
		{
			for (int j = 0; j != result[0].size(); j++) 
			{
				result[i][j] = m[i][j];
			}
		}
	return result;
}

int main()
{
	int rowSize = 10;
	int colSize = 10;
	vector<vector<int>>m=generateRandomMatrix(rowSize,colSize);
	vector<vector<int>>m2=copy(m);
	cout<<minPathSum1(m2)<<endl;
	cout<<minPathSum2(m)<<endl;
	cout<<minPathSum3(m)<<endl;
	return 0;
}
	