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
	else
	{	
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
			p2=arr[index]+next;
		}
		return max(p1,p2);
	}
	
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
	if((arr.size()&1)==0)
	{
		return process(arr,0,arr.size()/2,sum/2);
	}
	else
	{
		return max(process(arr,0,arr.size()/2,sum/2),process(arr,0,arr.size()/2+1,sum/2));
	}
}
		
int ways2(vector<int>&arr)
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
	sum/=2;
	int N=arr.size();
	int M=(N+1)/2;
	vector<vector<vector<int>>>dp(N+1,vector<vector<int>>(M+1,vector<int>(sum+1,-1)));
	for (int rest = 0; rest <= sum; rest++) 
	{
		dp[N][0][rest] = 0;
	}
	for(int index=N-1;index>=0;index--)
	{
		for(int picks=0;picks<=M;picks++)
		{
			for(int rest=0;rest<=sum;rest++)
			{
				//不要当前位置
				int p1=dp[index+1][picks][rest];
				//要当前位置的值
				int p2=-1;
				int next=-1;
				if(picks-1>=0&&arr[index]<=rest)
				{
					next=dp[index+1][picks-1][rest-arr[index]];
				}
				if(next!=-1)
				{
					p2=next+arr[index];
				}
				dp[index][picks][rest]=max(p1,p2);
			}
		}
	}
	if ((arr.size() & 1) == 0) 
	{
		return dp[0][arr.size() / 2][sum];
	} else 
	{
		return max(dp[0][arr.size() / 2][sum], dp[0][(arr.size() / 2) + 1][sum]);
	}
}

vector<int> randomArray(int len, int value) {
		vector<int>arr(len);
		for (int i = 0; i < arr.size(); i++) {
			arr[i] = rand()% value;
		}
		return arr;
	}

	// for test
 void printArray(vector<int>arr) {
		for (int num : arr) {
			cout<<num << " ";
		}
		cout<<endl;
	}

	// for test
int main() {
		int maxLen = 10;
		int maxValue = 50;
		int testTime = 10000;
		cout<<"测试开始"<<endl;;
		for (int i = 0; i < testTime; i++) {
			int len = rand()%maxLen;
			vector<int>arr = randomArray(len, maxValue);
			int ans1 = ways1(arr);
			int ans2 = ways2(arr);
			if (ans1 != ans2 ) {
				printArray(arr);
				cout<<ans1<<endl;
				cout<<ans2<<endl;
				cout<<"Oops!"<<endl;
				break;
			}
		}
		cout<<"测试结束"<<endl;
		return 0;
	}