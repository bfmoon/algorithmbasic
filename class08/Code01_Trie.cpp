//前缀树---数组实现
#include<iostream>
#include<vector>
using namespace std;

class Node
{
public:
  Node():pass(0),end(0){}
  int pass;
  int end;
  Node* nexts[26];
};

class Trie
{
private:
  Node* root;
public:
  Trie()
  {
    root=(Node*)malloc(sizeof(Node));
  }

  void insert(string word)
  {
    Node* node=root;
    node->pass++;
    int path=0;
    for(int i=0;i<word.length();i++)
    {
      path=word[i]-'a';
      if(node->nexts[path]==nullptr)
      {
        node->nexts[path]=(Node*)malloc (sizeof(Node));
      }
      node=node->nexts[path];
      node->pass++;
    }
    node->end++;
  }

  //删除
  void erase(string word)
  {
    if(!search(word))
    {
      return ;
    }
    Node* node=root;
    node->pass--;
    int index=0;
    for(int i=0;i<word.length();i++)
    {
      index=word[i]-'a';
      if(--node->nexts[index]->pass==0)
      {
        Node* temp=node->nexts[index];
        for(int j=0;j<26;j++)
        {
          if(temp->nexts[j])
          {
            clean(temp->nexts[j]);
          }
        }
        free temp;
        node->nexts[index]==nullptr;
        return ;
      }
      node=node->nexts[index];
    }
    node->end--;
  }



  //查询字符串出现的次数
  int search(string word)
  {
    Node* node=root;
    int index=0;
    for(int i=0;i<word.length();i++)
    {
      index=word[i]-'a';
      if(node->nexts[index]==nullptr)
      {
        return 0;
      }
      node=node->nexts[index];
    }
    return node.end;
  }

  //查询以pre为前缀的字符个数
  int prefixNumber(string pre)
  {
    Node* node=root;
    int index=0;
    for(int i=0;i<pre.length();i++)
    {
      index=pre[i]-'a';

      if(node->nexts[index]==nullptr)
      {
        return 0;
      }
      node=node->nexts[index];
    }
    return node->pass;
  }

  //清理内存
  void clean(Node* node)
  {
    if(node==nullptr)
    {
      return ;
    }
    for(int i=0;i<26;i++)
    {
      if(node->nexts[i])
      {
        clean(node->next[i]);
      }
    }
    free node;
    node=nullptr;
  }
};




