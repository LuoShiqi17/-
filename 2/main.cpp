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
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct LISTS{  //单链表管理单链表（链式结构）结点的定义
      char name[30];
        LNode* LL;
      struct LISTS *next;
      int length;
}LISTS;

status InitList(LinkList &L);//线性表的创建
status DestroyList(LinkList &L);//销毁线性表
status ClearList(LinkList &L);//清空线性表
status ListEmpty(LinkList L);//线性表的判空
int ListLength(LinkList L);//线性表的长度（返回长度）
status GetElem(LinkList L,int i,ElemType &e);//获取元素
status LocateElem(LinkList L,ElemType e);//查找元素（返回查找的元素的位置）
status PriorElem(LinkList L,ElemType e,ElemType &pre);//获取前驱元素
status NextElem(LinkList L,ElemType e,ElemType &next);//获取后继元素
status ListInsert(LinkList &L,int i,ElemType e);//插入元素
status ListDelete(LinkList &L,int i,ElemType &e);//删除元素
status ListTraverse(LinkList L);//遍历线性表
status SaveList(LinkList L,char FileName[]);//线性表读文件
status LoadList(LinkList &L,char FileName[]);//线性表写文件
status AddList(LISTS *Lists,char ListName[]);//新建线性表
status RemoveList(LISTS *&Lists,char ListName[]);//删除线性表


int main()
{
    LinkList L=NULL;
    LISTS *p=NULL,*pp=NULL;
    LISTS *tail=NULL;
    LNode *q,*s=NULL,*ss=NULL;
    LISTS *Lists,*head;
    Lists=(LISTS *)malloc(sizeof(LISTS));
    head=Lists;
    Lists->LL=L;
    Lists->next=NULL;
    Lists->length=0;
    int op=1,i=0,ip=1;
    ElemType e=0,pre=0,next=0;
    char FileName[100],ListName[100];
    while(ip){
        system("cls");
        printf("\n\n");
        printf("      基于链式结构的线性表基本操作演示系统 \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. 显示全部线性表\n");
        printf("    	  2. 增加一个线性表\n");
        printf("    	  3. 删除一个线性表 \n");
        printf("    	  4. 选择线性表\n");
        printf("    	  0. 退出系统\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~4]:");
        scanf("%d",&ip);
        switch(ip)
        {
        case 1:
            //p=Lists;
            if(head==NULL||head->LL==NULL){
                    printf("无线性表！\n");
                    tail=head;
            }
            else{
                Lists=head;
                while(Lists){
                        tail=Lists;
                        printf("%s\n",Lists->name);
                        ListTraverse(Lists->LL);
                        printf("\n");
                        Lists=Lists->next;
                }
                printf("以上是全部线性表！\n");
            }
            getchar();getchar();
            break;
        case 2:
            if(head==NULL){
                Lists=(LISTS *)malloc(sizeof(LISTS));
                head=Lists;
                head->LL=NULL;
            }
            if(head->LL==NULL) p=Lists;
            else{
                p=(LISTS *)malloc(sizeof(LISTS));
                tail->next=p;
                tail=tail->next;
            }
            printf("请输入要增加的线性表的名字：");
            scanf("%s",ListName);
            if(AddList(p,ListName)!=OK) printf("增加线性表失败！\n");
            else{
                p->next=NULL;
                printf("请输入线性表内容：");
                scanf("%d",&e);
                q=(LNode *)malloc(sizeof(LNode));
                p->LL=q;
                if(e==0){
                    p->LL->next=NULL;
                    printf("线性表增加成功！\n");
                    getchar();getchar();
                    break;
                }
                s=p->LL;
                q=(LNode *)malloc(sizeof(LNode));
                s->next=q;
                s=s->next;
                ss=s;
                while(e){
                    s->data=e;
                    q=(LNode *)malloc(sizeof(LNode));
                    s->next=q;
                    ss=s;
                    s=s->next;
                    scanf("%d",&e);
                }
                ss->next=NULL;
                free(s);
                s=NULL;
                printf("线性表增加成功！\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("请输入要删除的线性表的名字：");
            scanf("%s",ListName);
            if(RemoveList(head,ListName)!=OK) printf("删除线性表失败！\n");
            else printf("删除线性表成功！\n");
            getchar();getchar();
            break;
        case 4:
            printf("请输入要选择的线性表名字：");
            scanf("%s",ListName);
            p=head;
            while(p&&(strcmp(p->name,ListName)!=0)) p=p->next;
            if(p==NULL){
                printf("未找到选择的线性表！\n");
                getchar();getchar();
                break;
            }
            else printf("已找到选择的线性表！请继续操作！\n");
            getchar();getchar();
            op=1;
            while(op){
                system("cls");	printf("\n\n");
                printf("      基于链式结构的线性表基本操作演示系统 \n");
                printf("-------------------------------------------------\n");
                printf("    	  1. InitList       7. LocateElem\n");
                printf("    	  2. DestroyList    8. PriorElem\n");
                printf("    	  3. ClearList      9. NextElem \n");
                printf("    	  4. ListEmpty      10. ListInsert\n");
                printf("    	  5. ListLength     11. ListDelete\n");
                printf("    	  6. GetElem        12. ListTraverse\n");
                printf("    	  13. SaveList      14. LoadList\n");
                printf("    	  0. Exit\n");
                printf("-------------------------------------------------\n");
                printf("    请选择你的操作[0~14]:");
                scanf("%d",&op);
                switch(op){
                case 1:
                    if(InitList(p->LL)==OK) printf("线性表创建成功！\n");
                    else printf("线性表创建失败！\n");
                    getchar();getchar();
                    break;
                case 2:
                    printf("\n----DestroyList功能待实现！\n");
                    if(DestroyList(p->LL)==OK) printf("线性表销毁成功！\n");
                    else printf("线性表销毁失败！\n");
                    getchar();getchar();
                    break;
                case 3:
                    printf("\n----ClearList功能待实现！\n");
                    if(ClearList(p->LL)==OK) printf("线性表清空成功！\n");
                    else printf("线性表清空失败！\n");
                    getchar();getchar();
                    break;
                case 4:
                    printf("\n----ListEmpty功能待实现！\n");
                    if(ListEmpty(p->LL)==TRUE) printf("线性表判空成功！\n");
                    else printf("线性表判空失败！\n");
                    getchar();getchar();
                    break;
                case 5:
                    printf("\n----ListLength功能待实现！\n");
                    if(ListLength(p->LL)!=INFEASIBLE) printf("执行成功！线性表长度为：%d\n",ListLength(p->LL));
                    else printf("线性表不存在，无长度！");
                    getchar();getchar();
                    break;
                case 6:
                    printf("\n----GetElem功能待实现！\n");
                    printf("请输入想要获取的元素的位置：");
                    scanf("%d",&i);
                    if(GetElem(p->LL,i,e)==OK) printf("执行成功！元素为：%d\n",e);
                    else printf("执行失败！无法获取元素！\n");
                    getchar();getchar();
                    break;
                case 7:
                    printf("\n----LocateElem功能待实现！\n");
                    printf("请输入想要查找的元素：");
                    scanf("%d",&e);
                    if((LocateElem(p->LL,e)==INFEASIBLE)||(LocateElem(p->LL,e)==ERROR)) printf("查找元素失败！\n");
                    else printf("查找元素成功！元素的位置为：%d\n",LocateElem(p->LL,e));
                    getchar();getchar();
                    break;
                case 8:
                    printf("\n----PriorElem功能待实现！\n");
                    printf("请输入想要获取前驱的元素：");
                    scanf("%d",&e);
                    if(PriorElem(p->LL,e,pre)==OK) printf("获取成功！该元素的前驱元素为：%d\n",pre);
                    else printf("获取失败！\n");
                    getchar();getchar();
                    break;
                case 9:
                    printf("\n----NextElem功能待实现！\n");
                    printf("请输入想要获取后继的元素：");
                    scanf("%d",&e);
                    if(NextElem(p->LL,e,next)==OK) printf("获取成功！该元素的后继元素为：%d\n",next);
                    else printf("获取失败！\n");
                    getchar();getchar();
                    break;
                case 10:
                    printf("\n----ListInsert功能待实现！\n");
                    printf("请输入要插入的元素和位置：");
                    scanf("%d %d",&e,&i);
                    if(ListInsert(p->LL,i,e)==OK) printf("插入成功！\n");
                    else printf("插入失败！\n");
                    getchar();getchar();
                    break;
                case 11:
                    printf("\n----ListDelete功能待实现！\n");
                    printf("请输入要删除的元素位置：");
                    scanf("%d",&i);
                    if(ListDelete(p->LL,i,e)==OK) printf("删除成功！删除的元素为：%d\n",e);
                    else printf("删除失败！\n");
                    getchar();getchar();
                    break;
                case 12:
                    if(ListTraverse(p->LL)==INFEASIBLE) printf("无线性表！\n");
                    else printf("\n以上是线性表所有元素！\n");
                    getchar();getchar();
                    break;
                case 13:
                    printf("请给FileName赋值：");
                    scanf("%s",FileName);
                    if(SaveList(p->LL,FileName)==OK) printf("写文件成功！\n");
                    else printf("写文件失败！\n");
                    getchar();getchar();
                    break;
                case 14:
                    p->LL=NULL;
                    printf("请给FileName赋值：");
                    scanf("%s",FileName);
                    if(LoadList(p->LL,FileName)==OK) printf("读文件成功！\n");
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

status InitList(LinkList &L)//线性表的创建
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L!=NULL) return INFEASIBLE;
    L=(LNode *)malloc(sizeof(LNode));
    L->next=NULL;
    return OK;
}
status DestroyList(LinkList &L)//销毁线性表
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L;
    while(p){
        L=L->next;
        free(p);
        //p=NULL;
        p=L;
    }
    return OK;
}
status ClearList(LinkList &L)//清空线性表
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L->next,q=L->next;
    while(q){
        q=q->next;
        free(p);
        p=q;
    }
    L->next=NULL;
    return OK;
}
status ListEmpty(LinkList L)//线性表的判空
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    else if(L->next==NULL) return TRUE;
    else return FALSE;
}
int ListLength(LinkList L)//线性表的长度（返回长度）
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList q=L->next;
    int i=0;
    while(q){
        q=q->next;
        i++;
    }
    return i;
}
status GetElem(LinkList L,int i,ElemType &e)//获取元素
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L->next;
    int j=0,length=0;
    while(p){
        p=p->next;
        j++;
    }
    length=j;
    p=L->next;
    if(i<1||i>length) return ERROR;
    else{
        for(j=1;j<i;j++) p=p->next;
        e=p->data;
        return OK;
    }
}
status LocateElem(LinkList L,ElemType e)//查找元素（返回查找的元素的位置）
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    int i=1;
    LinkList p=L->next;
    if(p==NULL) return ERROR;
    while(p->data!=e&&p->next!=NULL){
        if(p->next->next==NULL){//判断是不是超出长度而退出循环
            if(p->next->data!=e) return ERROR;
            else return (i+1);
        }
        p=p->next;
        i++;
    }
    return i;
}
status PriorElem(LinkList L,ElemType e,ElemType &pre)//获取前驱元素
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L,q=L->next;
    if(q==NULL) return ERROR;
    while(q->data!=e/*&&q!=NULL*/){
        p=p->next;
        q=q->next;
        if(q->next==NULL){
            if(q->data!=e) return ERROR;
            else{
                pre=p->data;
                return OK;
            }
        }
    }
    if(q==L->next) return ERROR;
    if(p->data==NULL) return ERROR;
    pre=p->data;
    return OK;
}
status NextElem(LinkList L,ElemType e,ElemType &next)//获取后继元素
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L->next;
    if(p==NULL/*||(p->data==e&&p->next==NULL)*/) return ERROR;
    while(p->data!=e){
        if(p->next==NULL) return ERROR;
        p=p->next;
    }
    if(p->next==NULL) return ERROR;
    next=p->next->data;
    return OK;
}
status ListInsert(LinkList &L,int i,ElemType e)//插入元素
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L,q=L->next;
    if(q==NULL&&i==1){
        LNode *pp=(LNode*) malloc(sizeof(LNode));
        pp->data=e;
        p->next=pp;
        pp->next=NULL;
        return OK;
    }
    int length=0;
    while(q){
        q=q->next;
        length++;
    }
    q=L->next;
    if(i<1||i>length+1) return ERROR;
    for(int j=1;j<i;j++){
        p=p->next;
        q=q->next;
    }
    LNode *pp=(LNode*) malloc(sizeof(LNode));
    pp->data=e;
    p->next=pp;
    pp->next=q;
    return OK;
}
status ListDelete(LinkList &L,int i,ElemType &e)//删除元素
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L->next,q=NULL;
    int length=0;
    while(p){
        p=p->next;
        length++;
    }
    p=L->next;
    if(i<1||i>length) return ERROR;
    if(i==1){
        e=p->data;
        L->next=p->next;
        free(p);
        return OK;
    }
    for(int j=1;j<i-1;j++) p=p->next;
    e=p->next->data;
    q=p->next;
    p->next=p->next->next;
    free(q);
    return OK;
}
status ListTraverse(LinkList L)//遍历线性表
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L->next;
    while(p){
        printf("%d ",p->data);
        p=p->next;
    }
    return OK;
}
status SaveList(LinkList L,char FileName[])//线性表写文件
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    else{
        LinkList p=L->next;
        FILE *fp;
        fp=fopen(FileName,"r");//判断文件是否存在
        if(!fp){
            fclose(fp);
            return ERROR;
        }
        fp=fopen(FileName,"w");//“w”文件不存在会直接创建
        while(p){
            fprintf(fp,"%d ",p->data);
            p=p->next;
        }
        fclose(fp);
    }
    return OK;
}

status LoadList(LinkList &L,char FileName[])//线性表读文件
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    int temp;
    if(L!=NULL) return INFEASIBLE;
    else{
        L=(LinkList)malloc(sizeof(LNode));
        L->data=0;
        LinkList p=L, q=NULL;
        FILE *fp;
        fp=fopen(FileName,"r");
        if(!fp){
            fclose(fp);
            return ERROR;
        }
        while(fscanf(fp,"%d ",&temp)!=EOF)
        {
            q=(LinkList)malloc(sizeof(LNode));
            q->data = temp;
            p->next = q;
            p = p->next;
        }
        fclose(fp);
        p->next=NULL;
    }
    return OK;
}
status AddList(LISTS *Lists,char ListName[])//新建一个线性表
{
    LNode *p=(LNode*)malloc(sizeof(LNode));
    Lists->LL=p;
    Lists->LL->next=NULL;
    Lists->next=NULL;
    strcpy(Lists->name,ListName);
    Lists->length++;
    return OK;
}

status RemoveList(LISTS *&Lists,char ListName[])//删除一个线性表
{

    LISTS *p=NULL,*pp=NULL;
    p=Lists;
    pp=Lists->next;
    if(!strcmp(p->name,ListName)){
        Lists=pp;
        DestroyList(p->LL);
        free(p);
        p=NULL;
        return OK;
    }
    else{
        while(pp!=NULL&&(strcmp(pp->name,ListName))){
            pp=pp->next;
            p=p->next;
        }
        if(pp){
            p->next=pp->next;
            DestroyList(pp->LL);
            free(pp);
            pp=NULL;
            return OK;
        }
        else return ERROR;
    }
}

