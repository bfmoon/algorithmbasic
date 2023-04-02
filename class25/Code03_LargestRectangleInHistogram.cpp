//给定一个非负数组arr，代表直方图，返回直方图的最大长方形面积
//https://leetcode.cn/problems/largest-rectangle-in-histogram/

int largestRectangleArea(vector<int>& heights)
{
	if(heights.size()==0)
	{
		return 0;
	}
	int N=heights.size();
	stack<int>sta;
	int ans=0;
	for(int i=0;i<N;i++)
	{
		while(!sta.empty()&&heights[sta.top()]>=heights[i])
		{
			int j=sta.top();
			sta.pop();
			int k=sta.empty()?-1:sta.top();
			ans=max(ans,(i-k-1)*heights[j];
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
