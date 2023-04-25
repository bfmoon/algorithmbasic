//给定一个二维数组matrix，其中的值不是0就是1，返回全部由1组成的子矩形数量
//https://leetcode.cn/problems/count-submatrices-with-all-ones/

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat)
{
	if(mat.size()==0||mat[0].size()==0)
	{
		return 0;
	}
	int row=mat.size();
	int col=mat[0].size();
	int ans=0;
	vector<int>heights(col);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			heights[j]=mat[i][j]==0?0:heights[j]+1;
		}
		ans+=countFromBottom(heights);
	}
	return ans;
}

int countFromBottom(vector<int>&heights)
{
	if(heights.size()==0)
	{
		return 0;
	}
	int N=heights.size();
	stack<int>sta;
   
	int sum=0;
	for(int i=0;i<N;i++)
	{
		while(!sta.empty()&&heights[sta.top()]>=heights[i])
		{
			int cur=sta.top();
			sta.pop();
			//最后处理相等的元素
			if(heights[cur]>heights[i])
			{
				int left=sta.empty()?-1:sta.top();
				int n=i-left-1;
				int down=max((left==-1?0:heights[left]),heights[i]);
				sum+=(heights[cur]-down)*num(n);
			}
		}
        sta.push(i);
	}
    while(!sta.empty())
	{
		int cur=sta.top();
		sta.pop();
		int left=sta.empty()?-1:sta.top();
		int n=heights.size()-left-1;
		int down=left==-1?0:heights[left];
		sum+=(heights[cur]-down)*num(n);
	}
	return sum;
}

int num(int n)
{
	return (n*(n+1))/2;
}
};
			
