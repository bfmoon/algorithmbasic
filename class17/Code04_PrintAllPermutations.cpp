//打印一个字符串的全部排列
//如abc,则有abc.acb,bac,bca,cab,cba
#include<iostream>
#include<vector>
#include<string>
using namespace std;

void swap(string&str,int i,int j)
{
	char temp=str[i];
	str[i]=str[j];
	str[j]=temp;
}
void process01(string str,int index,vector<string>&ans)
{
	if(index==str.length())
	{
		ans.push_back(str);
	}
	else
	{
		for(int i=index;i<str.length();i++)
		{
			swap(str,index,i);
			process01(str,index+1,ans);
			swap(str,index,i);
		}
	}
}

	
vector<string>permutation1(string str)
{
	vector<string>ans;
	if(str.length()==0)
	{
		ans.push_back("");
		return ans;
	}
	process01(str,0,ans);
	return ans;
}

int main()
{
	string str="ccc";
	vector<string>ans=permutation1(str);
	for(string cur:ans)
	{
		cout<<cur<<endl;
	}
	return 0;
}