//https://leetcode.cn/problems/maximal-rectangle/
//给定一个二维数组matrix，其中的值不是0就是1，
//返回全部由1组成的最大子矩形内部有多少个1（面积）

int maxRecFromBottom(vector<int>&heights)
{
	if(heights.size()==0)
	{
		return 0;
	}
	int ans=0;
	stack<int>sta;
	int N=heights.size();
	for(int i=0;i<N;i++)
	{
		while(!sta.empty()&&heights[sta.top()]>=heights[i])
		{
			int j=sta.top();
			sta.pop();
			int k=sta.empty()?-1:sta.top();
			ans=max(ans,(i-k-1)*heights[j]);
		}
		sta.push(i);
	}
	while(!sta.empty())
	{
		int j=sta.top();
		sta.pop();
		int k=sta.empty()?-1:sta.top();
		int cur=(heights.size()-k-1)*heights[j];
		ans=max(ans,cur);
	}
	return ans;
}

int maximalRectangle(vector<vector<char>>& matrix)
{
	if(matrix.size()==0||matrix[0].size()==0)
	{
		return 0;
	}
	int row=matrix.size();//行数
	int col=matrix[0].size();//列数
	int ans=0;
	vector<int>heights(col);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			heights[j]=matrix[i][j]=='0'?0:heights[j]+1;
		}
		ans=max(ans,maxRecFromBottom(heights));
	}
	return ans;
        
}