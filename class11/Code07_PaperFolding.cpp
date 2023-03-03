/*
折纸问题
请把一段纸条竖着放在桌子上，然后从纸条的下边向上方对折1次，压出折痕后展开
此时折痕是凹下去的，即折痕突起的方向指向纸条的背面
如果从纸条的下边向上方连续对折2次，压出折痕后展开
此时有三条折痕，从上到下依次是下折痕、下折痕和上折痕。 
给定一个输入参数N，代表纸条都从下边向上方连续对折N次
请从上到下打印所有折痕的方向。 
N=1时，打印: down 
N=2时，打印: down down up 
*/
#include<iostream>
using namespace std;

//多几次，找规律，可得是二叉树的中序遍历
//1.头节点是凹，2.所有左子树的头节点是凹，3.所有右子树的节点是凸
//所以规定凹为true，凸为false


void process(int i,bool down,int N)
{
  if(i>N)
  {
    return ;
  }
  process(i+1,true,N);
  cout<<(down?"凹":"凸")<<" ";
  process(i+1,false,N);
}
  

void printAllFolds(int N)
{
  process(1,true,N);
  cout<<endl;
}

int main()
{
  int N=4;
  printAllFolds(N);
  return 0;
}
