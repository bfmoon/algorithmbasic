//打印n层汉诺塔从最左边移动到最右边的全部过程（递归+非递归实现）
#include<iostream>
#include<stack>
using namespace std;


void leftToRight(int n);
void leftToMid(int n);
void midToRight(int n);
void midToLeft(int n);
void rightToLeft(int n);
void rightToMid(int n);

void hanoi1(int n)
{
	leftToRight(n);
}
//左->右
void leftToRight(int n)
{
	if(n==1)
	{
		cout<<"move 1 from left to right"<<endl;
		return ;
	}
	leftToMid(n-1);
	cout<<"move "<<n<<" from left to right"<<endl;
	midToRight(n-1);
}
	
//左->中
void leftToMid(int n)
{
	if(n==1)
	{
		cout<<"move 1 from left to mid"<<endl;
		return ;
	}
	leftToRight(n-1);
	cout<<"move "<<n<<" from left to mid"<<endl;
	rightToMid(n-1);
}
//中->右
void midToRight(int n)
{
	if(n==1)
	{
		cout<<"move 1 from mid to right"<<endl;
		return ;
	}
	midToLeft(n-1);
	cout<<"move "<<n<<" from mid to right"<<endl;
	leftToRight(n-1);
}
//中->左
void midToLeft(int n)
{
	if(n==1)
	{
		cout<<"move 1 from mid to left"<<endl;
		return ;
	}
	midToRight(n-1);
	cout<<"move "<<n<<" from mid ro left"<<endl;
	rightToLeft(n-1);
}
//右->左
void rightToLeft(int n)
{
	if(n==1)
	{
		cout<<"move 1 from right to left"<<endl;
		return ;
	}
	rightToMid(n-1);
	cout<<"move "<<n<<" from right to left"<<endl;
	midToLeft(n-1);
}
//右->中
void rightToMid(int n)
{
	if(n==1)
	{
		cout<<"move 1 from right to mid"<<endl;
		return ;
	}
	rightToLeft(n-1);
	cout<<"move "<<n<<" from right to mid"<<endl;
	leftToMid(n-1);
}

//方法二：利用参数变化实现一个递归
void process(int n,string from,string to,string other)
{
	if(n==1)
	{
		cout<<"move 1 "<<" from "<<from<<" to "<<to<<endl;
		return ;
	}
	process(n-1,from,other,to);
	cout<<"move "<<n<<" from "<<from<<" to "<<to<<endl;
	process(n-1,other,to,from);
}
	
	
void hanoi2(int n)
{
	if(n>0)
	{
		process(n,"left","right","mid");
	}
}

int main()
{
	int n=3;
	hanoi1(n);
	cout<<"=================="<<endl;
	hanoi2(n);
	return 0;
}
	
