#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
using namespace std;

//要与不要问题
void process01(string str,int index,string path,vector<string>&ans)
{
	if(index==str.length())
	{
		ans.push_back(path);
		return ;
	}
	//不要当前位置的字符
	process01(str,index+1,path,ans);
	//要当前字符
	process01(str,index+1,path+str[index],ans);
}
//打印一个字符串的全部子序列
vector<string>subs(string str)
{
	string path="";
	vector<string>ans;
	process01(str,0,path,ans);
	return ans;
}

void process02(string str,int index,string path,unordered_set<string>&ans)
{
	if(index==str.length())
	{
		ans.insert(path);
		return ;
	}
	process02(str,index+1,path,ans);
	process02(str,index+1,path+str[index],ans);
}
//打印一个字符串的全部子序列，要求不要出现重复字面值的子序列
vector<string>subsNoRepeat(string str)
{
	string path="";
	unordered_set<string>_set;
	process02(str,0,path,_set);
	vector<string>ans;
	for(string value:_set)
	{
		ans.push_back(value);
	}
	return ans;
}

//方法一样
void process03(string str,int index,string path,vector<string>&ans)
{
	if(index==str.length())
	{
		ans.push_back(path);
		return ;
	}
	process03(str,index+1,path,ans);
	process03(str,index+1,path+str[index],ans);
}
//打印一个字符串的全部子序列，要求不要出现重复字面值的子序列
unordered_set<string>subsNoRepeat2(string str)
{
	string path="";
	unordered_set<string>_set;
	vector<string>ans;
	process03(str,0,path,ans);
	
	for(string value:ans)
	{
		_set.insert(value);
	}
	return _set;
}

int main()
{
	string str="accc";
	vector<string>ans1=subs(str);
	vector<string>ans2=subsNoRepeat(str);
	unordered_set<string>ans3=subsNoRepeat2(str);
	for(string cur:ans1)
	{
		cout<<cur<<" ";
	}
	cout<<endl<<"=============="<<endl;
	for(string cur:ans2)
	{
		cout<<cur<<" ";
	}
	cout<<endl<<"=============="<<endl;
	for(string cur:ans3)
	{
		cout<<cur<<" ";
	}
	cout<<endl;
	return 0;
}
	