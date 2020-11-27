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
}VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
    int adjvex;              //����λ�ñ��
    struct ArcNode  *nextarc;	   //��һ������ָ��
}ArcNode;
typedef struct VNode{				//ͷ��㼰���������Ͷ���
    VertexType data;       	//������Ϣ
    ArcNode *firstarc;      	 //ָ���һ����
}VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
    AdjList vertices;     	 //ͷ�������
    int vexnum,arcnum;   	  //������������
    GraphKind  kind;        //ͼ������
}ALGraph;
typedef struct LISTS{  //����������ڽӱ�Ķ���
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
    if ((Q.rear + 1) % MAXSIZE == Q.front) return ERROR;//������
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

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);//��������ͼ
status DestroyGraph(ALGraph &G);//��������ͼ
int LocateVex(ALGraph G,KeyType u);//���Ҷ���
status KeyRepet(ALGraph G, KeyType u, VertexType value);//KeyRepet����������(��һ�ֺ���)
status PutVex(ALGraph &G,KeyType u,VertexType value);//���㸳ֵ
int FirstAdjVex(ALGraph G,KeyType u);//��õ�һ�ڽӵ�
int NextAdjVex(ALGraph G,KeyType v,KeyType w);//�����һ�ڽӵ�
status InsertVex(ALGraph &G,VertexType v);//���붥��
status DeleteVex(ALGraph &G,KeyType v);//ɾ������
status InsertArc(ALGraph &G,KeyType v,KeyType w);//���뻡
status DeleteArc(ALGraph &G,KeyType v,KeyType w);//ɾ����
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));//���������������
void DFS(ALGraph G, int v, int visited[], void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));//���������������
status SaveGraph(ALGraph G, char FileName[]);//д�ļ�
status LoadGraph(ALGraph &G, char FileName[]);//���ļ�
status AddGraph(LISTS *Lists,char GraphName[]);//����һ��ͼ
status RemoveGraph(LISTS *&Lists,char GraphName[]);//ɾ��һ��ͼ
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
        printf("         ͼ�Ļ���������ʾϵͳ \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. ��ʾȫ��ͼ\n");
        printf("    	  2. ����һ��ͼ\n");
        printf("    	  3. ɾ��һ��ͼ \n");
        printf("    	  4. ѡ��ͼ\n");
        printf("    	  0. �˳�ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~4]:");
        scanf("%d",&ip);
        switch(ip)
        {
        case 1:
            if(head==NULL/*||head->AG.vexnum==0*/){
                    printf("��ͼ��\n");
                    tail=head;
            }
            else{
                Lists=head;
                while(Lists){
                        tail=Lists;
                        printf("%s\n",Lists->name);
                        /*DFSTraverse(Lists->AG,visit);//���������������
                        printf("\n");
                        BFSTraverse(Lists->AG,visit);//���������������
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
                printf("������ȫ��ͼ��\n");
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
            printf("������Ҫ���ӵ�ͼ�����֣�");
            scanf("%s",GraphName);
            if(AddGraph(p,GraphName)!=OK) printf("����ͼʧ�ܣ�\n");
            else{
                p->next=NULL;
                printf("������ͼ���ݣ�");
                do {
                    scanf("%d%s",&V[i].key,V[i].others);
                } while(V[i++].key!=-1);
                i=0;
                do {
                    scanf("%d%d",&VR[i][0],&VR[i][1]);
                } while(VR[i++][0]!=-1);
                if (CreateCraph(p->AG,V,VR)==OK) printf("ͼ���ӳɹ���\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("������Ҫɾ����ͼ�����֣�");
            scanf("%s",GraphName);
            if(RemoveGraph(head,GraphName)!=OK) printf("ɾ��ͼʧ�ܣ�\n");
            else printf("ɾ��ͼ�ɹ���\n");
            getchar();getchar();
            break;
        case 4:
            printf("������Ҫѡ���ͼ���֣�");
            scanf("%s",GraphName);
            p=head;
            while(p&&(strcmp(p->name,GraphName)!=0)) p=p->next;
            if(p==NULL){
                printf("δ�ҵ�ѡ���ͼ��\n");
                getchar();getchar();
                break;
            }
            else printf("���ҵ�ѡ���ͼ�������������\n");
            getchar();getchar();
            op=1;
            while(op){
                system("cls");	printf("\n\n");
                printf("               ͼ�Ļ���������ʾϵͳ \n");
                printf("-------------------------------------------------\n");
                printf("    	  1. ��������ͼ         8. ɾ������\n");
                printf("    	  2. ��������ͼ         9. ���뻡\n");
                printf("    	  3. ���Ҷ���           10. ɾ���� \n");
                printf("    	  4. ���㸳ֵ           11. ���������������\n");
                printf("    	  5. ��õ�һ�ڽӵ�     12. ���������������\n");
                printf("    	  6. �����һ�ڽӵ�     13. д�ļ�\n");
                printf("    	  7. ���붥��           14. ���ļ�\n");
                printf("    	  15.                   0.�˳�\n");
                printf("-------------------------------------------------\n");
                printf("    ��ѡ����Ĳ���[0~14]:");
                scanf("%d",&op);
                switch(op){
                case 1:
                    V[0].key=-1;
                    strcpy(V[0].others,"nil");
                    VR[0][0]=-1;VR[0][1]=-1;
                    if(CreateCraph(p->AG,V,VR)==OK) printf("ͼ�����ɹ���\n");
                    else printf("ͼ����ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 2:
                    if(DestroyGraph(p->AG)==OK) printf("ͼ���ٳɹ���\n");
                    else printf("����������ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 3:
                    printf("������Ҫ���ҵĶ���ؼ��֣�");
                    scanf("%d",&e);
                    x=LocateVex(p->AG,e);
                    if(x!=-1) printf("���Ҷ���ɹ���%d",x);
                    else printf("���Ҷ���ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 4:
                    printf("������Ҫ��ֵ�Ĺؼ��ֺ��޸ĺ�Ĺؼ��ּ����ݣ�");
                    scanf("%d %d %s",&key,&v.key,v.others);
                    ans=PutVex(p->AG,key,v);
                    if (ans==OK)
                    {
                        printf("���㸳ֵ�ɹ���\n");
                        /*DFSTraverse(p->AG,visit);//���������������
                        printf("\n");
                        BFSTraverse(p->AG,visit);//���������������
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
                    else printf("���㸳ֵʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 5:
                    printf("������Ҫ��õ�һ�ڽӵ�Ľ��Ĺؼ��֣�");
                    scanf("%d",&e);
                    x=FirstAdjVex(p->AG,e);
                    if(x!=-1) printf("��óɹ�����һ�ڽӵ��λ��Ϊ%d\n",x);
                    else printf("���ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 6:
                    printf("������Ҫ��õ�һ����һ�ڽӵ�Ľ��Ĺؼ��֣�");
                    scanf("%d %d",&e,&key);
                    x=NextAdjVex(p->AG,e,key);
                    if(x!=-1) printf("��óɹ�����һ�ڽӵ��λ��Ϊ%d\n",x);
                    else printf("���ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 7:
                    printf("������Ҫ���붥��Ĺؼ��ֺ����ݣ�");
                    scanf("%d %s",&v.key,v.others);
                    ans=InsertVex(p->AG,v);
                    if (ans==OK)
                    {
                        printf("���붥��ɹ���\n");
                        /*DFSTraverse(p->AG,visit);//���������������
                        printf("\n");
                        BFSTraverse(p->AG,visit);//���������������
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
                    else printf("���붥��ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 8:
                    printf("������Ҫɾ������Ľ��Ĺؼ��֣�");
                    scanf("%d",&e);
                    ans=DeleteVex(p->AG,e);
                    if (ans==OK)
                    {
                        printf("ɾ������ɹ���\n");
                        /*DFSTraverse(p->AG,visit);//���������������
                        printf("\n");
                        BFSTraverse(p->AG,visit);//���������������
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
                    else printf("ɾ������ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 9:
                    printf("������Ҫ���뻡�Ľ��Ĺؼ��֣�");
                    scanf("%d %d",&key,&e);
                    ans=InsertArc(p->AG,key,e);
                    if (ans==OK)
                    {
                        printf("���뻡�ɹ���\n");
                        /*DFSTraverse(p->AG,visit);//���������������
                        printf("\n");
                        BFSTraverse(p->AG,visit);//���������������
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
                    else printf("���뻡ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 10:
                    printf("������Ҫɾ�����Ľ��Ĺؼ��֣�");
                    scanf("%d %d",&key,&e);
                    ans=DeleteArc(p->AG,key,e);
                    if (ans==OK)
                    {
                        printf("ɾ�����ɹ���\n");
                        /*DFSTraverse(p->AG,visit);//���������������
                        printf("\n");
                        BFSTraverse(p->AG,visit);//���������������
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
                    else printf("ɾ����ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 11:
                    DFSTraverse(p->AG,visit);
                    printf("\n����Ϊ���������������\n");
                    getchar();getchar();
                    break;
                case 12:
                    BFSTraverse(p->AG,visit);
                    printf("\n����Ϊ���������������\n");
                    getchar();getchar();
                    break;
                case 13:
                    printf("���FileName��ֵ��");
                    scanf("%s",FileName);
                    if(SaveGraph(p->AG,FileName)==OK) printf("д�ļ��ɹ���\n");
                    else printf("д�ļ�ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 14:
                    p->AG.vexnum=0;
                    printf("���FileName��ֵ��");
                    scanf("%s",FileName);
                    if(LoadGraph(p->AG,FileName)==OK) printf("���ļ��ɹ���\n");
                    else printf("���ļ�ʧ�ܣ�\n");
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
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    int i=0,t=0,one=0,two=0;
    ArcNode *q=NULL;
    //G.kind={UDG};
    for(i;V[i].key!=-1;i++){//�ж��Ƿ��йؼ����ظ���������Χ
        int j=0;
        for(j;V[j].key!=-1;j++){
            if(i!=j&&V[i].key==V[j].key) return ERROR;
        }
        if((j-1)==MAX_VERTEX_NUM) return ERROR;
    }
    for(i=0;VR[i][0]!=-1;i++){//�жϻ��еĹؼ����Ƿ����
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
/*��������ͼG*/
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    int i=0;
    for(i;i<G.vexnum;i++)
        if(G.vertices[i].data.key==u) return i;
    return -1;
}
status KeyRepet(ALGraph G, KeyType u, VertexType value)//KeyRepet����������(��һ�ֺ���)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == value.key && G.vertices[i].data.key != u)
            return ERROR;
    }
    return OK;
}
status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    int i=0;
    for(i;i<G.vexnum;i++)
        if(G.vertices[i].data.key==u&&G.vertices[i].firstarc) return G.vertices[i].firstarc->adjvex;
    return -1;
}
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
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
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
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
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
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
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
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
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
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
        visit(G.vertices[v].data);//δ�����ʣ����з���
    }
    if(G.vertices[v].firstarc){
        p=G.vertices[v].firstarc;//pָ��ý��ĵ�һ������
        while (p){
            if(!visited[p->adjvex]) DFS(G, p->adjvex, visited, visit);
            p=p->nextarc;
        }
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    int visited[MAX_VERTEX_NUM]={-1};
    for(int i=0;i<G.vexnum;i++) visited[i]=0;//���财ֵ��1��ʾ���ʹ���0��ʾδ����
    for(int i=0;i<G.vexnum;i++)
        if(!visited[i]) DFS(G,i,visited,visit);//��ʱ����Ϊi�Ľ��δ������
    return OK;
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    int* visited;
    visited = (int*)malloc(G.vexnum * sizeof(int));//�������飬��СΪ G.vexnum
    for (int i = 0; i < G.vexnum; i++) visited[i] = 0;//��ʼ��visited

    BFSQueue Q; InitQueue(Q);//�������в���ʼ��
    int i, j;
    ArcNode* p;
    for (i = 0; i < G.vexnum; i++)
    {
        if (visited[i] == 0)//i��δ����
        {
            visited[i] = 1;
            visit(G.vertices[i].data);//visited i;
            EnQueue(Q, i);
            while (Q.front != Q.rear)
            {
                DeQueue(Q, j);
                if (G.vertices[i].firstarc != NULL)
                {
                    p = G.vertices[i].firstarc;//pָ���һ������
                    while (p)
                    {
                        if (visited[p->adjvex] == 0)
                        {
                            visited[p->adjvex] = 1;//��Ϊ�ѷ���
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
//��ͼ������д�뵽�ļ�FileName��
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
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
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
status AddGraph(LISTS *Lists,char GraphName[])//����һ��ͼ
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
status RemoveGraph(LISTS *&Lists,char GraphName[])//ɾ��һ��ͼ
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
