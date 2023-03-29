// 测试链接：https://leetcode.com/problems/gas-station

//思路：将两个数组合到一起，用gas-cost，只要中途累加和小于0
//则说明不能走通

vector<int>goodArray(vector<int>&gas,vector<int>&cost)
{
	int N=gas.size();
	int M=N<<1;
	vector<int>arr(M);
	for(int i=0;i<N;i++)
	{
		arr[i]=gas[i]-cost[i];
		arr[i+N]=gas[i]-cost[i];
	}
	//前缀和
	for(int i=1;i<M;i++)
	{
		arr[i]=arr[i]+arr[i-1];
	}
	deque<int>w;//最小值窗口,存放的是下标
	//将前缀和数组的前N个进入
	for(int i=0;i<N;i++)
	{
		while(!w.empty()&&arr[w.back()]>=arr[i])
		{
			w.pop_back();
		}
		w.push_back(i);
	}
	//标记每个位置是否可以是出发的位置
	vector<bool>ans(N);
	for(int offest=0,i=0,j=N;j<M;offest=arr[i++],j++)
	{
		if(arr[w.front()]-offest>=0)
		{
			ans[i]=true;
		}
		//说明当前值过期了，弹出
		if(w.front()==i)
		{
			w.pop_front();
		}
		//将N以后的进入
		while(!w.empty()&&arr[w.back()]>=arr[j])
		{
			w.pop_back();
		}
		w.push_back(j);
	}
	return ans;
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
{
	if(gas.size()!=cost.size())
	{
		return -1;
	}
	vector<int>good=goodArray(gas,cost);
	for(int i=0;i<good.size();i++)
	{
		if(good[i])
		{
			return i;
		}
	}
	return -1;
}