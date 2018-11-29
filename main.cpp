#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include "string.h"
#define MAX 100
//图操作相关数据结构和函数声明
//边结点
typedef struct Linknode
{
 int adjvex; //邻接顶点索引，存放在数组的下标，下标从1开始
 Linknode *next;
}LinkNode;
//顶点结点
typedef struct Vexnode
{
 char vexdata; //顶点数据，仅一个字符
 Linknode *first;
}VexNode;
//图结构
typedef struct {
 int vexnum,arcnum;
 VexNode adjlist[MAX];
}ALGraph;
ALGraph G;
int visited[MAX]; //顶点访问标志
void CreateGraph(); //创建图
void PrintGraph(); //输出图邻接表
void DFS(int u); //深度优先搜索

//////////////////////////////////////////////////////////////////////////
//队列操作函数声明，用于广度优先搜索的辅助队列
typedef int Qdata[MAX];
//队列
typedef struct{
 Qdata data;
 //队列(数组型式)
 int front, tail;
 //队头队尾
}Queue;
typedef Queue *Q;
void BFS(int v,Q que); //广度优先搜索
Q InitQ(); //队列初始化
int EnQ(); //入队列
int *DeQ(); //出队列
int *ExamQ(); //访问队列首元素，但不删除该元素
bool FullQ(); //队列是否满
bool EmptyQ(); //队列是否为空
//初始化队列
Q InitQ(Queue *a){
 Q p;
 p=a;
 p->front=MAX-1;
 p->tail=MAX-1;
 return p;
}
//入队操作
int EnQ(Q pa,int* interm)
{
 //队满
 if(pa->tail+1%MAX==pa->front)
 {
  return 1;
 }
 else
 {
  pa->tail=(pa->tail+1)%MAX;
  pa->data[pa->tail]=*interm;
  return 0;
 }
}
//出队列操作
int* DeQ(Q pa)
{
 int* interm;
 //队不空
 if(pa->tail!=pa->front)
 {
  pa->front=(pa->front+1)%MAX;
  interm=&(pa->data[pa->front]);
  return interm;
 }
 else
 {
  return NULL;
 }
}
//访问队首元素，但不删除该元素
int* ExamQ(Q pa)
{
 int *interm;
 if(pa->tail!=pa->front)
 {
  interm=&pa->data[((pa->front+1)%MAX)];
  return interm;
 }
 return NULL;
}
//是否队满
bool FullQ(Q pa)
{
 if((pa->tail+1)%MAX==pa->front)
  return true;
 else
  return false;
}
//是否队空
bool EmptyQ(Q pa)
{
 if(pa->tail==pa->front)
  return true;
 else
  return false;
}
//创建图的结构
void CreateGraph()
{
 int i,temp;
 LinkNode *p,*r;
 printf("请输入顶点的数量:");
 scanf("%d",&G.vexnum);
 for(i=1;i<=G.vexnum;i++)
 {
  printf("输入第%d个顶点数据:",(i));
  fflush(stdin);
  G.adjlist[i].vexdata=getchar();
  G.adjlist[i].first=NULL;
 }
 cout<<endl;
 for(i=1;i<=G.vexnum;i++)
 {
  printf("构造第个%d顶点的边表\n",i);
  //构造边表
  printf("输入与该边邻接的顶点序号:");
  scanf("%d",&temp);
  //如果为-1则转到下一个顶点
  while(temp!=-1)
  {
   //创建一个边结点
   p=new LinkNode;
   p->next=NULL;
   //为该边ID赋值
   p->adjvex=temp;
   //找到顶点的第一条边
   r=G.adjlist[i].first;
   if(r!=NULL)
   {
    while (r->next!=NULL)
     r=r->next;
    r->next=p;
   }
   else
   {
    G.adjlist[i].first=p;
   }
   
   //G.adjlist[i].first=p;
   //p=G.adjlist [i].first ;
   printf("输入与该边邻接的顶点序号:");
   scanf("%d",&temp);
  }
  cout<<endl;
 }
}
void PrintGraph()
{
 cout<<"打印图信息:"<<endl;
 int i;
 LinkNode *p;
 for(i=1;i<=G.vexnum;i++)
 {
  cout<<"顶点 : "<<G.adjlist[i].vexdata<< " 边表 : ";
  p=G.adjlist[i].first;
  while(p!=NULL)
  {
   if (p->next!=NULL)
    cout<<p->adjvex<<"->";
   else
    cout<<p->adjvex;
   p=p->next;
  }
  cout<<endl;
 }
}
//深度优先遍历(递归)
void DFS(int u)
{
 int intemp;
 LinkNode *p;
 //更改顶点的状态为访问状态
 visited[u]=1;
 //取得第u个顶点的第一条边
 p=G.adjlist [u].first ;
 while(p)
 {
  //取得边的另一端顶点
  intemp=p->adjvex ;
  //该顶点没有被访问
  //…;
  if(!visited[intemp])
  {
   cout<<G.adjlist [u].vexdata <<"->"<<G.adjlist [intemp].vexdata <<endl;
   DFS(intemp);
  } //选择下一条边
 //…;
 p=p->next ;
 }
}
//广度优先
void BFS(int v,Q que)
{
 cout<<"广度优先遍历:"<<endl;
 int *intemp;
 // 将顶点存入队列
 EnQ(que,&v);
 //记录已遍历过
 visited[v]=1;
 //保存边结点
 LinkNode *pintr;
 // 队列是否是空的
 while (!EmptyQ(que))
 {
  //将顶点从对列取出
  intemp=DeQ(que);
  //取出第一条边
  pintr=G.adjlist [*intemp].first ;
  //遍历至链表尾
  while (pintr!=NULL)
  {
   //如果没遍历过进行遍历并进队
   if (!visited[pintr->adjvex])
   {
    EnQ(que,&(pintr->adjvex) );
    //记录已遍历
    visited[pintr->adjvex]=1;;
    cout<<G.adjlist[*intemp].vexdata<<"->"
     <<G.adjlist[pintr->adjvex].vexdata<<endl;
   }
   //下一个顶点
   pintr=pintr->next ;
  }
 }
}
//主函数
void main()
{
 int i;
 //队列模型
 Q q=new Queue;
 int flag=1;
 while(flag)
 {
  cout<<endl;
  cout<<"==============================="<<endl;
  cout<<"图的深度优先搜索和广度优先搜索"<<endl;
  cout<<"==============================="<<endl;
  cout<<" 1.创建图的邻接表"<<endl;
  cout<<" 2.进行图的深度优先搜索"<<endl;
  cout<<" 3.进行图的广度优先搜索"<<endl;
  cout<<" 请选择：1~3："<<endl;
  cout<<endl;
  for(int j=0; j<MAX; j++)
   visited[j]=0;
  fflush(stdin);
  cin>>i;
  switch(i){
  case 1:
   CreateGraph();
   PrintGraph();
   break;
  case 2:
   DFS(1);//深度优先
   break;
  case 3:
   InitQ(q);
   BFS(1,q);//广度优先
   break;
  default:
   return;
  }
 }
}