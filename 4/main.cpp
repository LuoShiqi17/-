#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

typedef int status;
typedef int KeyType;
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
    KeyType  key;
    char others[20];
}VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号
    struct ArcNode  *nextarc;	   //下一个表结点指针
}ArcNode;
typedef struct VNode{				//头结点及其数组类型定义
    VertexType data;       	//顶点信息
    ArcNode *firstarc;      	 //指向第一条弧
}VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
}ALGraph;
typedef struct LISTS{  //单链表管理邻接表的定义
      char name[30];
      ALGraph AG;
      struct LISTS *next;
      int length;
}LISTS;

#define MAXSIZE 100
typedef struct {
    int front;
    int rear;
    KeyType* base;
}BFSQueue;
status InitQueue(BFSQueue& Q)
{
    Q.front = Q.rear = 0;
    Q.base = (int*)malloc(MAXSIZE * sizeof(int));
    return OK;
}
status EnQueue(BFSQueue& Q, KeyType e)
{
    if ((Q.rear + 1) % MAXSIZE == Q.front) return ERROR;//队列满
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXSIZE;
    return OK;
}
status DeQueue(BFSQueue& Q, KeyType& e)
{
    if (Q.front == Q.rear) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;
    return OK;
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);//创建无向图
status DestroyGraph(ALGraph &G);//销毁无向图
int LocateVex(ALGraph G,KeyType u);//查找顶点
status KeyRepet(ALGraph G, KeyType u, VertexType value);//KeyRepet函数的重载(另一种函数)
status PutVex(ALGraph &G,KeyType u,VertexType value);//顶点赋值
int FirstAdjVex(ALGraph G,KeyType u);//获得第一邻接点
int NextAdjVex(ALGraph G,KeyType v,KeyType w);//获得下一邻接点
status InsertVex(ALGraph &G,VertexType v);//插入顶点
status DeleteVex(ALGraph &G,KeyType v);//删除顶点
status InsertArc(ALGraph &G,KeyType v,KeyType w);//插入弧
status DeleteArc(ALGraph &G,KeyType v,KeyType w);//删除弧
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));//深度优先搜索遍历
void DFS(ALGraph G, int v, int visited[], void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));//广度优先搜索遍历
status SaveGraph(ALGraph G, char FileName[]);//写文件
status LoadGraph(ALGraph &G, char FileName[]);//读文件
status AddGraph(LISTS *Lists,char GraphName[]);//增加一个图
status RemoveGraph(LISTS *&Lists,char GraphName[]);//删除一个图
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

int main()
{
    VertexType V[30];
    KeyType VR[100][2];
    VertexType v;
    ArcNode *q;
    LISTS *p=NULL,*tail=NULL,*head=NULL,*Lists=NULL;
    tail=head;
    int op=1,i=0,ip=1,ans,x=0,key=0;
    KeyType e=0;
    char FileName[100],GraphName[100];
    while(ip){
        system("cls");
        printf("\n\n");
        printf("         图的基本操作演示系统 \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. 显示全部图\n");
        printf("    	  2. 增加一个图\n");
        printf("    	  3. 删除一个图 \n");
        printf("    	  4. 选择图\n");
        printf("    	  0. 退出系统\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~4]:");
        scanf("%d",&ip);
        switch(ip)
        {
        case 1:
            if(head==NULL/*||head->AG.vexnum==0*/){
                    printf("无图！\n");
                    tail=head;
            }
            else{
                Lists=head;
                while(Lists){
                        tail=Lists;
                        printf("%s\n",Lists->name);
                        /*DFSTraverse(Lists->AG,visit);//深度优先搜索遍历
                        printf("\n");
                        BFSTraverse(Lists->AG,visit);//广度优先搜索遍历
                        printf("\n");*/
                        for(i=0;i<Lists->AG.vexnum;i++){
                            q=Lists->AG.vertices[i].firstarc;
                            printf("%d %s",Lists->AG.vertices[i].data.key,Lists->AG.vertices[i].data.others);
                            while (q)
                            {
                                printf(" %d",q->adjvex);
                                q=q->nextarc;
                            }
                            printf("\n");
                        }
                        printf("\n");
                        Lists=Lists->next;
                }
                printf("以上是全部图！\n");
            }
            getchar();getchar();
            break;
        case 2:
            i=0;
            if(head==NULL){
                Lists=(LISTS *)malloc(sizeof(LISTS));
                head=Lists;
                head->AG.vexnum=0;
                head->AG.arcnum=0;
                tail=head;
                p=tail;
            }
            //if(head->AG.vexnum==0) p=Lists;
            else{
                p=(LISTS *)malloc(sizeof(LISTS));
                tail->next=p;
                tail=tail->next;
            }
            printf("请输入要增加的图的名字：");
            scanf("%s",GraphName);
            if(AddGraph(p,GraphName)!=OK) printf("增加图失败！\n");
            else{
                p->next=NULL;
                printf("请输入图内容：");
                do {
                    scanf("%d%s",&V[i].key,V[i].others);
                } while(V[i++].key!=-1);
                i=0;
                do {
                    scanf("%d%d",&VR[i][0],&VR[i][1]);
                } while(VR[i++][0]!=-1);
                if (CreateCraph(p->AG,V,VR)==OK) printf("图增加成功！\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("请输入要删除的图的名字：");
            scanf("%s",GraphName);
            if(RemoveGraph(head,GraphName)!=OK) printf("删除图失败！\n");
            else printf("删除图成功！\n");
            getchar();getchar();
            break;
        case 4:
            printf("请输入要选择的图名字：");
            scanf("%s",GraphName);
            p=head;
            while(p&&(strcmp(p->name,GraphName)!=0)) p=p->next;
            if(p==NULL){
                printf("未找到选择的图！\n");
                getchar();getchar();
                break;
            }
            else printf("已找到选择的图！请继续操作！\n");
            getchar();getchar();
            op=1;
            while(op){
                system("cls");	printf("\n\n");
                printf("               图的基本操作演示系统 \n");
                printf("-------------------------------------------------\n");
                printf("    	  1. 创建无向图         8. 删除顶点\n");
                printf("    	  2. 销毁无向图         9. 插入弧\n");
                printf("    	  3. 查找顶点           10. 删除弧 \n");
                printf("    	  4. 顶点赋值           11. 深度优先搜索遍历\n");
                printf("    	  5. 获得第一邻接点     12. 广度优先搜索遍历\n");
                printf("    	  6. 获得下一邻接点     13. 写文件\n");
                printf("    	  7. 插入顶点           14. 读文件\n");
                printf("    	  15.                   0.退出\n");
                printf("-------------------------------------------------\n");
                printf("    请选择你的操作[0~14]:");
                scanf("%d",&op);
                switch(op){
                case 1:
                    V[0].key=-1;
                    strcpy(V[0].others,"nil");
                    VR[0][0]=-1;VR[0][1]=-1;
                    if(CreateCraph(p->AG,V,VR)==OK) printf("图创建成功！\n");
                    else printf("图创建失败！\n");
                    getchar();getchar();
                    break;
                case 2:
                    if(DestroyGraph(p->AG)==OK) printf("图销毁成功！\n");
                    else printf("二叉树销毁失败！\n");
                    getchar();getchar();
                    break;
                case 3:
                    printf("请输入要查找的顶点关键字：");
                    scanf("%d",&e);
                    x=LocateVex(p->AG,e);
                    if(x!=-1) printf("查找顶点成功！%d",x);
                    else printf("查找顶点失败！\n");
                    getchar();getchar();
                    break;
                case 4:
                    printf("请输入要赋值的关键字和修改后的关键字及内容：");
                    scanf("%d %d %s",&key,&v.key,v.others);
                    ans=PutVex(p->AG,key,v);
                    if (ans==OK)
                    {
                        printf("顶点赋值成功！\n");
                        /*DFSTraverse(p->AG,visit);//深度优先搜索遍历
                        printf("\n");
                        BFSTraverse(p->AG,visit);//广度优先搜索遍历
                        printf("\n");*/
                        for(i=0;i<p->AG.vexnum;i++){
                            q=p->AG.vertices[i].firstarc;
                            printf("%d %s",p->AG.vertices[i].data.key,p->AG.vertices[i].data.others);
                            while (q)
                            {
                                printf(" %d",q->adjvex);
                                q=q->nextarc;
                            }
                            printf("\n");
                        }
                        printf("\n");
                    }
                    else printf("顶点赋值失败！\n");
                    getchar();getchar();
                    break;
                case 5:
                    printf("请输入要获得第一邻接点的结点的关键字：");
                    scanf("%d",&e);
                    x=FirstAdjVex(p->AG,e);
                    if(x!=-1) printf("获得成功！第一邻接点的位序为%d\n",x);
                    else printf("获得失败！\n");
                    getchar();getchar();
                    break;
                case 6:
                    printf("请输入要获得第一和下一邻接点的结点的关键字：");
                    scanf("%d %d",&e,&key);
                    x=NextAdjVex(p->AG,e,key);
                    if(x!=-1) printf("获得成功！下一邻接点的位序为%d\n",x);
                    else printf("获得失败！\n");
                    getchar();getchar();
                    break;
                case 7:
                    printf("请输入要插入顶点的关键字和内容：");
                    scanf("%d %s",&v.key,v.others);
                    ans=InsertVex(p->AG,v);
                    if (ans==OK)
                    {
                        printf("插入顶点成功！\n");
                        /*DFSTraverse(p->AG,visit);//深度优先搜索遍历
                        printf("\n");
                        BFSTraverse(p->AG,visit);//广度优先搜索遍历
                        printf("\n");*/
                        for(i=0;i<p->AG.vexnum;i++){
                            q=p->AG.vertices[i].firstarc;
                            printf("%d %s",p->AG.vertices[i].data.key,p->AG.vertices[i].data.others);
                            while (q)
                            {
                                printf(" %d",q->adjvex);
                                q=q->nextarc;
                            }
                            printf("\n");
                        }
                        printf("\n");
                    }
                    else printf("插入顶点失败！\n");
                    getchar();getchar();
                    break;
                case 8:
                    printf("请输入要删除顶点的结点的关键字：");
                    scanf("%d",&e);
                    ans=DeleteVex(p->AG,e);
                    if (ans==OK)
                    {
                        printf("删除顶点成功！\n");
                        /*DFSTraverse(p->AG,visit);//深度优先搜索遍历
                        printf("\n");
                        BFSTraverse(p->AG,visit);//广度优先搜索遍历
                        printf("\n");*/
                        for(i=0;i<p->AG.vexnum;i++){
                            q=p->AG.vertices[i].firstarc;
                            printf("%d %s",p->AG.vertices[i].data.key,p->AG.vertices[i].data.others);
                            while (q)
                            {
                                printf(" %d",q->adjvex);
                                q=q->nextarc;
                            }
                            printf("\n");
                        }
                        printf("\n");
                    }
                    else printf("删除顶点失败！\n");
                    getchar();getchar();
                    break;
                case 9:
                    printf("请输入要插入弧的结点的关键字：");
                    scanf("%d %d",&key,&e);
                    ans=InsertArc(p->AG,key,e);
                    if (ans==OK)
                    {
                        printf("插入弧成功！\n");
                        /*DFSTraverse(p->AG,visit);//深度优先搜索遍历
                        printf("\n");
                        BFSTraverse(p->AG,visit);//广度优先搜索遍历
                        printf("\n");*/
                        for(i=0;i<p->AG.vexnum;i++){
                            q=p->AG.vertices[i].firstarc;
                            printf("%d %s",p->AG.vertices[i].data.key,p->AG.vertices[i].data.others);
                            while (q)
                            {
                                printf(" %d",q->adjvex);
                                q=q->nextarc;
                            }
                            printf("\n");
                        }
                        printf("\n");
                    }
                    else printf("插入弧失败！\n");
                    getchar();getchar();
                    break;
                case 10:
                    printf("请输入要删除弧的结点的关键字：");
                    scanf("%d %d",&key,&e);
                    ans=DeleteArc(p->AG,key,e);
                    if (ans==OK)
                    {
                        printf("删除弧成功！\n");
                        /*DFSTraverse(p->AG,visit);//深度优先搜索遍历
                        printf("\n");
                        BFSTraverse(p->AG,visit);//广度优先搜索遍历
                        printf("\n");*/
                        for(i=0;i<p->AG.vexnum;i++){
                            q=p->AG.vertices[i].firstarc;
                            printf("%d %s",p->AG.vertices[i].data.key,p->AG.vertices[i].data.others);
                            while (q)
                            {
                                printf(" %d",q->adjvex);
                                q=q->nextarc;
                            }
                            printf("\n");
                        }
                        printf("\n");
                    }
                    else printf("删除弧失败！\n");
                    getchar();getchar();
                    break;
                case 11:
                    DFSTraverse(p->AG,visit);
                    printf("\n以上为深度优先搜索遍历\n");
                    getchar();getchar();
                    break;
                case 12:
                    BFSTraverse(p->AG,visit);
                    printf("\n以上为广度优先搜索遍历\n");
                    getchar();getchar();
                    break;
                case 13:
                    printf("请给FileName赋值：");
                    scanf("%s",FileName);
                    if(SaveGraph(p->AG,FileName)==OK) printf("写文件成功！\n");
                    else printf("写文件失败！\n");
                    getchar();getchar();
                    break;
                case 14:
                    p->AG.vexnum=0;
                    printf("请给FileName赋值：");
                    scanf("%s",FileName);
                    if(LoadGraph(p->AG,FileName)==OK) printf("读文件成功！\n");
                    else printf("读文件失败！\n");
                    getchar();getchar();
                    break;
                case 0:
                    break;
                }
            }
            break;
        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    int i=0,t=0,one=0,two=0;
    ArcNode *q=NULL;
    //G.kind={UDG};
    for(i;V[i].key!=-1;i++){//判断是否有关键字重复及超出范围
        int j=0;
        for(j;V[j].key!=-1;j++){
            if(i!=j&&V[i].key==V[j].key) return ERROR;
        }
        if((j-1)==MAX_VERTEX_NUM) return ERROR;
    }
    for(i=0;VR[i][0]!=-1;i++){//判断弧中的关键字是否存在
        int j=0;
        for(j;V[j].key!=-1;j++){
            if(V[j].key==VR[i][0]) break;
        }
        if(V[j].key==-1) return ERROR;
        for(j=0;V[j].key!=-1;j++){
            if(V[j].key==VR[i][1]) break;
        }
        if(V[j].key==-1) return ERROR;
    }
    i=0;
    while(V[i].key!=-1&&i<MAX_VERTEX_NUM){
        t=0;
        G.vertices[i].data.key=V[i].key;
        strcpy(G.vertices[i].data.others,V[i].others);
        G.vertices[i].firstarc=NULL;
        i++;
    }
    G.vexnum=i;
    i=0;
    while(VR[i][0]!=-1){
        for(t=0;t<G.vexnum;t++){
            if (VR[i][0]==G.vertices[t].data.key)
            {
                one=t;
                break;
            }
        }
        for(t=0;t<G.vexnum;t++){
            if (VR[i][1]==G.vertices[t].data.key)
            {
                two=t;
                break;
            }
        }
        q=(ArcNode*)malloc(sizeof(ArcNode));
        q->adjvex=two;
        q->nextarc=G.vertices[one].firstarc;
        G.vertices[one].firstarc=q;
        q=(ArcNode*)malloc(sizeof(ArcNode));
        q->adjvex=one;
        q->nextarc=G.vertices[two].firstarc;
        G.vertices[two].firstarc=q;
        i++;
    }
    return OK;
}
status DestroyGraph(ALGraph &G)
/*销毁无向图G*/
{
    int i=0;
    ArcNode *p=NULL,*q=NULL;
    for(i;i<G.vexnum;i++){
        if(G.vertices[i].firstarc){
            p=G.vertices[i].firstarc;
            while(p){
                q=p;
                p=p->nextarc;
                free(q);
            }
            G.vertices[i].data.key=-1;
            strcpy(G.vertices[i].data.others,"nil");
            G.vertices[i].firstarc=NULL;
        }
    }
    G.vexnum=0;
    return OK;
}
int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    int i=0;
    for(i;i<G.vexnum;i++)
        if(G.vertices[i].data.key==u) return i;
    return -1;
}
status KeyRepet(ALGraph G, KeyType u, VertexType value)//KeyRepet函数的重载(另一种函数)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == value.key && G.vertices[i].data.key != u)
            return ERROR;
    }
    return OK;
}
status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    int i=0;
    for(i;i<G.vexnum;i++){
        if(G.vertices[i].data.key==value.key&&G.vertices[i].data.key!=u) return ERROR;
        if(G.vertices[i].data.key==u) break;
    }
    if(i!=G.vexnum) G.vertices[i].data=value;
    else return ERROR;
    return OK;
}
int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    int i=0;
    for(i;i<G.vexnum;i++)
        if(G.vertices[i].data.key==u&&G.vertices[i].firstarc) return G.vertices[i].firstarc->adjvex;
    return -1;
}
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    ArcNode *p=NULL;
    for(int i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v){
            p=G.vertices[i].firstarc;
            while(p){
                if(G.vertices[p->adjvex].data.key==w&&p->nextarc) return p->nextarc->adjvex;
                p=p->nextarc;
            }
        }
    }
    return -1;
}
status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    int i=0;
    for(i;i<G.vexnum;i++)
        if(G.vertices[i].data.key==v.key) return ERROR;
    if(G.vexnum==MAX_VERTEX_NUM) return ERROR;
    else{
        G.vertices[G.vexnum].data=v;
        G.vertices[G.vexnum++].firstarc=NULL;
    }
    return OK;
}
status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    int i=0,j=0,x=0;
    ArcNode *p=NULL,*pp=NULL,*q=NULL,*qq=NULL;
    if(G.vexnum<=1) return ERROR;
    for(i;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v){
            if(G.vertices[i].firstarc==NULL) ;
            else{
                p=G.vertices[i].firstarc;
                while(p){
                    pp=p;
                    for(j=0;j!=p->adjvex;j++) ;
                    q=G.vertices[j].firstarc;
                    qq=q;
                    for(;q&&q->adjvex!=i;q=q->nextarc) qq=q;
                    if(q&&q!=qq){
                        qq->nextarc=q->nextarc;
                        free(q);q=NULL;
                    }
                    else if(q==qq){
                        G.vertices[j].firstarc=q->nextarc;
                        free(q);q=NULL;
                    }
                    p=p->nextarc;
                    free(pp);pp=NULL;
                }
                x=i;
            }
            for(i;i<G.vexnum;i++){
                G.vertices[i].data=G.vertices[i+1].data;
                G.vertices[i].firstarc=G.vertices[i+1].firstarc;
            }
            G.vexnum--;
            for(j=0;j<G.vexnum;j++){
                p=G.vertices[j].firstarc;
                while(p){
                    if(p->adjvex>x) p->adjvex--;
                    p=p->nextarc;
                }
            }
            return OK;
        }
    }
    return ERROR;
}
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    ArcNode *p;
    int one=-1,two=-1,i=0;
    for(i;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v) one=i;
        if(G.vertices[i].data.key==w) two=i;
        if(one!=-1&&two!=-1) break;
    }
    if(one==-1||two==-1) return ERROR;
    p=G.vertices[one].firstarc;
    while(p){
        if(p->adjvex==two) return ERROR;
        p=p->nextarc;
    }
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=two;p->nextarc=G.vertices[one].firstarc;G.vertices[one].firstarc=p;
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=one;p->nextarc=G.vertices[two].firstarc;G.vertices[two].firstarc=p;
    return OK;
}
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    ArcNode *p,*pp;
    int one=-1,two=-1,i=0;
    for(i;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v) one=i;
        if(G.vertices[i].data.key==w) two=i;
        if(one!=-1&&two!=-1) break;
    }
    if(one==-1||two==-1) return ERROR;
    i=-1;
    p=G.vertices[one].firstarc;
    while(p){
        if(p->adjvex==two&&p!=G.vertices[one].firstarc){
            if(!p->nextarc) pp->nextarc=NULL;
            else pp->nextarc=p->nextarc;
            free(p);p=NULL;
            i=0;
            break;
        }
        if(p->adjvex==two&&p==G.vertices[one].firstarc){
            if(!p->nextarc) G.vertices[one].firstarc=NULL;
            else G.vertices[one].firstarc=p->nextarc;
            free(p);p=NULL;
            i=0;
            break;
        }
        pp=p;
        p=p->nextarc;
    }
    if(i==-1) return ERROR;
    i=-1;
    p=G.vertices[two].firstarc;
    while(p){
        if(p->adjvex==one&&p!=G.vertices[two].firstarc){
            if(!p->nextarc) pp->nextarc=NULL;
            else pp->nextarc=p->nextarc;
            free(p);p=NULL;
            i=0;
            break;
        }
        if(p->adjvex==one&&p==G.vertices[two].firstarc){
            if(!p->nextarc) G.vertices[two].firstarc=NULL;
            else G.vertices[two].firstarc=p->nextarc;
            free(p);p=NULL;
            i=0;
            break;
        }
        pp=p;
        p=p->nextarc;
    }
    if(i==-1) return ERROR;
    return OK;
}
void DFS(ALGraph G, int v, int visited[], void (*visit)(VertexType))
{
    ArcNode *p;
    if(!visited[v]){
        visited[v]=1;
        visit(G.vertices[v].data);//未被访问，进行访问
    }
    if(G.vertices[v].firstarc){
        p=G.vertices[v].firstarc;//p指向该结点的第一个表结点
        while (p){
            if(!visited[p->adjvex]) DFS(G, p->adjvex, visited, visit);
            p=p->nextarc;
        }
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int visited[MAX_VERTEX_NUM]={-1};
    for(int i=0;i<G.vexnum;i++) visited[i]=0;//赋予储值，1表示访问过，0表示未访问
    for(int i=0;i<G.vexnum;i++)
        if(!visited[i]) DFS(G,i,visited,visit);//此时索引为i的结点未被访问
    return OK;
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int* visited;
    visited = (int*)malloc(G.vexnum * sizeof(int));//创建数组，大小为 G.vexnum
    for (int i = 0; i < G.vexnum; i++) visited[i] = 0;//初始化visited

    BFSQueue Q; InitQueue(Q);//创建队列并初始化
    int i, j;
    ArcNode* p;
    for (i = 0; i < G.vexnum; i++)
    {
        if (visited[i] == 0)//i尚未访问
        {
            visited[i] = 1;
            visit(G.vertices[i].data);//visited i;
            EnQueue(Q, i);
            while (Q.front != Q.rear)
            {
                DeQueue(Q, j);
                if (G.vertices[i].firstarc != NULL)
                {
                    p = G.vertices[i].firstarc;//p指向第一个表结点
                    while (p)
                    {
                        if (visited[p->adjvex] == 0)
                        {
                            visited[p->adjvex] = 1;//置为已访问
                            visit(G.vertices[p->adjvex].data);
                            EnQueue(Q, p->adjvex);
                        }
                        p = p->nextarc;
                    }
                }
            }
        }
    }
    return OK;
}
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    int i=0,t=0;
    ArcNode *p=NULL;
    FILE *fp=fopen(FileName,"w");
    while(i<G.vexnum){
        fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
        i++;
    }
    i=-1;
    fprintf(fp,"%d nil ",i);
    i=0;
    for(i;i<G.vexnum;i++){
        p=G.vertices[i].firstarc;
        while(p){
            fprintf(fp,"%d ",G.vertices[i].data.key);
            fprintf(fp,"%d ",p->adjvex);
            p=p->nextarc;
        }
    }
    fprintf(fp,"%d %d",-1,-1);
    fclose(fp);
    return OK;
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    FILE *fp=fopen(FileName,"r");
    int i=0,t=0,x=0,y=0;
    ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
    ArcNode *q;
    VertexType V[21];
    KeyType VR[100][2];
    do{
        fscanf(fp,"%d",&(V[i].key));
        fscanf(fp,"%s",V[i].others);
        i++;
    }while(V[i-1].key!=-1);
    i=0;
    for(i;V[i].key!=-1;i++){
        G.vertices[i].data=V[i];
    }
    G.vexnum=i;
    i=0;
    while((fscanf(fp,"%d",&x))){
        if(x==-1) break;
        VR[i][0]=x;
        fscanf(fp,"%d",&y);
        VR[i][1]=y;
        i++;
    }
    VR[i][0]=VR[i][1]=-1;
    G.vertices[t].firstarc=p;
    for(int j=0;VR[j][0]!=-1;j++){
        if(G.vertices[t].data.key==VR[j][0]){
            p->adjvex=VR[j][1];q=(ArcNode*)malloc(sizeof(ArcNode));p->nextarc=q;q=p;p=p->nextarc;
        }
        else{
            free(p);
            q->nextarc=NULL;
            ++t;
            p=(ArcNode*)malloc(sizeof(ArcNode));
            G.vertices[t].firstarc=p;
            j--;
        }
    }
    free(p);
    q->nextarc=NULL;
    fclose(fp);
    return OK;
}
status AddGraph(LISTS *Lists,char GraphName[])//增加一个图
{
    //ALGraph *p=(ALGraph*)malloc(sizeof(ALGraph));
    //Lists->AG=p;
    //Lists->AG->lchild=NULL;
    //Lists->AG->rchild=NULL;
    Lists->AG.arcnum=0;
    Lists->AG.vexnum=0;
    Lists->next=NULL;
    strcpy(Lists->name,GraphName);
    Lists->length++;
    return OK;
}
status RemoveGraph(LISTS *&Lists,char GraphName[])//删除一个图
{

    LISTS *p=NULL,*pp=NULL;
    p=Lists;
    pp=Lists->next;
    if(!strcmp(p->name,GraphName)){
        Lists=pp;
        DestroyGraph(p->AG);
        p=NULL;
        return OK;
    }
    else{
        while(pp!=NULL&&(strcmp(pp->name,GraphName))){
            pp=pp->next;
            p=p->next;
        }
        if(pp){
            p->next=pp->next;
            DestroyGraph(pp->AG);
            pp=NULL;
            return OK;
        }
        else return ERROR;
    }
}
