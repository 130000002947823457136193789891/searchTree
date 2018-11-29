#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include "string.h"
#define MAX 100
//ͼ����������ݽṹ�ͺ�������
//�߽��
typedef struct Linknode
{
 int adjvex; //�ڽӶ��������������������±꣬�±��1��ʼ
 Linknode *next;
}LinkNode;
//������
typedef struct Vexnode
{
 char vexdata; //�������ݣ���һ���ַ�
 Linknode *first;
}VexNode;
//ͼ�ṹ
typedef struct {
 int vexnum,arcnum;
 VexNode adjlist[MAX];
}ALGraph;
ALGraph G;
int visited[MAX]; //������ʱ�־
void CreateGraph(); //����ͼ
void PrintGraph(); //���ͼ�ڽӱ�
void DFS(int u); //�����������

//////////////////////////////////////////////////////////////////////////
//���в����������������ڹ�����������ĸ�������
typedef int Qdata[MAX];
//����
typedef struct{
 Qdata data;
 //����(������ʽ)
 int front, tail;
 //��ͷ��β
}Queue;
typedef Queue *Q;
void BFS(int v,Q que); //�����������
Q InitQ(); //���г�ʼ��
int EnQ(); //�����
int *DeQ(); //������
int *ExamQ(); //���ʶ�����Ԫ�أ�����ɾ����Ԫ��
bool FullQ(); //�����Ƿ���
bool EmptyQ(); //�����Ƿ�Ϊ��
//��ʼ������
Q InitQ(Queue *a){
 Q p;
 p=a;
 p->front=MAX-1;
 p->tail=MAX-1;
 return p;
}
//��Ӳ���
int EnQ(Q pa,int* interm)
{
 //����
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
//�����в���
int* DeQ(Q pa)
{
 int* interm;
 //�Ӳ���
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
//���ʶ���Ԫ�أ�����ɾ����Ԫ��
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
//�Ƿ����
bool FullQ(Q pa)
{
 if((pa->tail+1)%MAX==pa->front)
  return true;
 else
  return false;
}
//�Ƿ�ӿ�
bool EmptyQ(Q pa)
{
 if(pa->tail==pa->front)
  return true;
 else
  return false;
}
//����ͼ�Ľṹ
void CreateGraph()
{
 int i,temp;
 LinkNode *p,*r;
 printf("�����붥�������:");
 scanf("%d",&G.vexnum);
 for(i=1;i<=G.vexnum;i++)
 {
  printf("�����%d����������:",(i));
  fflush(stdin);
  G.adjlist[i].vexdata=getchar();
  G.adjlist[i].first=NULL;
 }
 cout<<endl;
 for(i=1;i<=G.vexnum;i++)
 {
  printf("����ڸ�%d����ı߱�\n",i);
  //����߱�
  printf("������ñ��ڽӵĶ������:");
  scanf("%d",&temp);
  //���Ϊ-1��ת����һ������
  while(temp!=-1)
  {
   //����һ���߽��
   p=new LinkNode;
   p->next=NULL;
   //Ϊ�ñ�ID��ֵ
   p->adjvex=temp;
   //�ҵ�����ĵ�һ����
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
   printf("������ñ��ڽӵĶ������:");
   scanf("%d",&temp);
  }
  cout<<endl;
 }
}
void PrintGraph()
{
 cout<<"��ӡͼ��Ϣ:"<<endl;
 int i;
 LinkNode *p;
 for(i=1;i<=G.vexnum;i++)
 {
  cout<<"���� : "<<G.adjlist[i].vexdata<< " �߱� : ";
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
//������ȱ���(�ݹ�)
void DFS(int u)
{
 int intemp;
 LinkNode *p;
 //���Ķ����״̬Ϊ����״̬
 visited[u]=1;
 //ȡ�õ�u������ĵ�һ����
 p=G.adjlist [u].first ;
 while(p)
 {
  //ȡ�ñߵ���һ�˶���
  intemp=p->adjvex ;
  //�ö���û�б�����
  //��;
  if(!visited[intemp])
  {
   cout<<G.adjlist [u].vexdata <<"->"<<G.adjlist [intemp].vexdata <<endl;
   DFS(intemp);
  } //ѡ����һ����
 //��;
 p=p->next ;
 }
}
//�������
void BFS(int v,Q que)
{
 cout<<"������ȱ���:"<<endl;
 int *intemp;
 // ������������
 EnQ(que,&v);
 //��¼�ѱ�����
 visited[v]=1;
 //����߽��
 LinkNode *pintr;
 // �����Ƿ��ǿյ�
 while (!EmptyQ(que))
 {
  //������Ӷ���ȡ��
  intemp=DeQ(que);
  //ȡ����һ����
  pintr=G.adjlist [*intemp].first ;
  //����������β
  while (pintr!=NULL)
  {
   //���û���������б���������
   if (!visited[pintr->adjvex])
   {
    EnQ(que,&(pintr->adjvex) );
    //��¼�ѱ���
    visited[pintr->adjvex]=1;;
    cout<<G.adjlist[*intemp].vexdata<<"->"
     <<G.adjlist[pintr->adjvex].vexdata<<endl;
   }
   //��һ������
   pintr=pintr->next ;
  }
 }
}
//������
void main()
{
 int i;
 //����ģ��
 Q q=new Queue;
 int flag=1;
 while(flag)
 {
  cout<<endl;
  cout<<"==============================="<<endl;
  cout<<"ͼ��������������͹����������"<<endl;
  cout<<"==============================="<<endl;
  cout<<" 1.����ͼ���ڽӱ�"<<endl;
  cout<<" 2.����ͼ�������������"<<endl;
  cout<<" 3.����ͼ�Ĺ����������"<<endl;
  cout<<" ��ѡ��1~3��"<<endl;
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
   DFS(1);//�������
   break;
  case 3:
   InitQ(q);
   BFS(1,q);//�������
   break;
  default:
   return;
  }
 }
}