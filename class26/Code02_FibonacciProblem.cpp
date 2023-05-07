#include<iostream>
#include<vector>
using namespace std;

//求斐波那契数列的三种方法
//方法一:暴力递归
int f1(int n)
{
  if(n<1)
  {
    return 0;
  }
  if(n==1||n==2)
  {
    return 1;
  }
  return f1(n-1)+f1(n-2);
}

//方法二:递推循环
int f2(int n)
{
  if(n<1)
  {
    return 0;
  }
  if(n<3)
  {
    return 1;
  }
  int res=1;
  int pre=1;
  int temp=0;
  for(int i=3;i<=n;i++)
  {
    temp=res;
    res+=pre;
    pre=temp;
  }
  return res;
}

//方法三:利用矩阵乘法

vector<vector<int>> product(vector<vector<int>>a,vector<vector<int>>b)
{
	int n = a.size(); //a的行数
	int m = b[0].size(); //b的列数
	int k = a[0].size(); // a的列数同时也是b的行数
	vector<vector<int>>ans(n,vector<int>(m,0));
	for(int i = 0 ; i < n; i++) {
		for(int j = 0 ; j < m;j++) {
			for(int c = 0; c < k; c++) {
				ans[i][j] += a[i][c] * b[c][j];
			}
		}
	}
		return ans;
}
void matrixPower(vector<vector<int>>&base,int p,vector<vector<int>>&res)
{
	for(int i=0;i<res.size();i++)
	{
		res[i][i]=1;
	}
	vector<vector<int>>t=base;
	for(;p!=0;p>>=1)
	{
		if((p&1)!=0)
		{
			res=product(res,t);
		}
		t=product(t,t);
	}
}

int f3(int n)
{
  if(n<1)
  {
    return 0;
  }
  if(n==1||n==2)
  {
    return 1;
  }
  vector<vector<int>>base(2,vector<int>(2,0));
  vector<vector<int>>res(2,vector<int>(2,0));
  matrixPower(base,n-2,res);
  return res[0][0]+res[1][0];
}

int main()
{
	int n=19;
	cout<<f1(n)<<endl;
	cout<<f2(n)<<endl;
	cout<<f3(n)<<endl;
	return 0;
}
