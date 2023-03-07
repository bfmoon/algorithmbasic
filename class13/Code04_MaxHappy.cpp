/*
派对的最大快乐值
 员工信息的定义如下:
class Employee {
    public int happy; // 这名员工可以带来的快乐值
    List<Employee> subordinates; // 这名员工有哪些直接下级
}
公司的每个员工都符合 Employee 类的描述。整个公司的人员结构可以看作是一棵标准的、 没有环的多叉树
树的头节点是公司唯一的老板，除老板之外的每个员工都有唯一的直接上级
叶节点是没有任何下属的基层员工(subordinates列表为空)，除基层员工外每个员工都有一个或多个直接下级
这个公司现在要办party，你可以决定哪些员工来，哪些员工不来，规则：
1.如果某个员工来了，那么这个员工的所有直接下级都不能来
2.派对的整体快乐值是所有到场员工快乐值的累加
3.你的目标是让派对的整体快乐值尽量大
给定一棵多叉树的头节点boss，请返回派对的最大快乐值。
*/
#include<iostream>
#include<vector>
using namespace std;

class Employee
{
public:
  int happy;
  vector<Employee*>subordinates;
  Employee(int h):happy(h){};
};


//利用二叉树的递归套路
class Info
{
public:
  int yes;//当前节点来的最大快乐值
  int no;//当前节点不来时的最大快乐值
  Info(int y,int n):yes(y),no(n){}
};

Info* process01(Employee*head)
{
  if(head==nullptr)
  {
    return new Info(0,0);
  }
  int no=0;
  int yes=head->happy;
  for(Employee*node:head->subordinates)
  {
    Info*nextInfo=process01(node);
    //当前节点不来时，下一节点来时与不来时的最大值
    no+=max(nextInfo->no,nextInfo->yes);
    //当前节点来了，孩子节点不能来
    yes+=nextInfo->no;
  }
  return new Info(yes,no);
}

int maxHappy1(Employee*root)
{
  Info* info=process01(root);
  int ans=max(info->yes,info->no);
  delete info;
  info=nullptr;
  return ans;
}

//当前来到的节点叫做cur
//参数up表示cur的上级是否来
//函数的意义：
//  up为true, 表示cur的上级确定要来的情况，cur 整棵树能提供的最大happy值
//  up为false，表示cur的上级确定不来的情况，cur 整棵树能提供的最大happy值
int process02(Employee*cur,bool up)
{
  if(up)
  {
    int ans=0;
    for(Employee*next:cur->subordinates)
    {
      ans+=process02(next,false);
    }
    return ans;
  }
  else
  {
    int p1=cur->happy;
    //p2表示当前节点的上一节点依旧不来
    int p2=0;
    for(Employee*next:cur->subordinates)
    {
      p1+=process02(next,true);
      p2+=process02(next,false);
    }
    return max(p1,p2);
  }
}

int maxHappy2(Employee*root)
{
  if(root==nullptr)
  {
    return 0;
  }
  return process02(root,false);
}

void generateNexts(Employee *e, int level, int maxLevel, int maxNexts, int maxHappy) {
    if (level > maxLevel) return ;

    int nextsSize = rand() % (maxNexts + 1);

    for (int i = 0; i < nextsSize; i++) {
        Employee *next = new Employee(rand() % (maxHappy + 1));
        e->subordinates.push_back(next);
        generateNexts(next, level + 1, maxLevel, maxNexts, maxHappy);
    }
}

Employee *generateBoss(int maxLevel, int maxNexts, int maxHappy) {
    if ((rand() % 100 / (double)101) < 0.02) return nullptr;

    Employee *boss = new Employee(rand() % (maxHappy + 1));
    generateNexts(boss, 1, maxLevel, maxNexts, maxHappy);
    return boss;
}


int main() {
    srand(time(0));
    int maxLevel = 4;
    int maxNexts = 7;
    int maxHappy = 100;
    int testTimes = 100000;
    for (int i = 0; i < testTimes + 1; i++) {
        Employee *boss = generateBoss(maxLevel, maxNexts, maxHappy);
        if (maxHappy1(boss) != maxHappy2(boss)) {
            cout << "Failed!" << endl;
            return 0;
        }
    }
    cout << "Success！" << endl;
    return 0;
}

