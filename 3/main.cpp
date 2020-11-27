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
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef int status;
typedef int KeyType;
typedef struct {//二叉树结点类型定义
    KeyType  key;
    char others[20];
}TElemType;

typedef struct BiTNode{ //二叉链表结点的定义
    TElemType  data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct LISTS{  //单链表管理二叉树结点的定义
      char name[30];
        BiTree LL;
      struct LISTS *next;
      int length;
}LISTS;

status CreateBiTree(BiTree &T,TElemType definition[]);//二叉树的创建
status ClearBiTree(BiTree &T);//二叉树的清空
int BiTreeDepth(BiTree T);//二叉树深度
BiTNode* LocateNode(BiTree T,KeyType e);//查找结点
status Assign(BiTree &T,KeyType e,TElemType value);//结点赋值
BiTNode* GetSibling(BiTree T,KeyType e);//获得兄弟结点
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);//插入结点
status DeleteNode(BiTree &T,KeyType e);//删除结点
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));//先序遍历
status InOrderTraverse(BiTree T,void (*visit)(BiTree));//中序遍历
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));//后序遍历
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));//按层遍历
status SaveBiTree(BiTree T, char FileName[]);//写文件
status LoadBiTree(BiTree &T, char FileName[]);//读文件
status AddTree(LISTS *Lists,char ListName[]);//增加一个二叉树
status RemoveTree(LISTS *&Lists,char TreeName[]);//删除一个二叉树
status DestoryBiTree(BiTree &T);//二叉树的销毁
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

int main()
{
    //LISTS ll=NULL;
    BiTNode *q/*,*s=NULL,*ss=NULL*/;
    LISTS *p=NULL,*tail=NULL,*head=NULL,*Lists=NULL;//*pp=NULL
    Lists=(LISTS *)malloc(sizeof(LISTS));
    head=Lists;
    tail=head;
    BiTree b=NULL;
    Lists->LL=b;
    int op=1,i=0,ip=1,ans,LR,key=0;
    KeyType e=0;
    TElemType c;
    TElemType definition[100]={NULL};
    //BiTree b=(BiNode *)malloc(sizeof(BiNode));
    char FileName[100],TreeName[100];
    while(ip){
        system("cls");
        printf("\n\n");
        printf("         二叉树的基本操作演示系统 \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. 显示全部二叉树\n");
        printf("    	  2. 增加一个二叉树\n");
        printf("    	  3. 删除一个二叉树 \n");
        printf("    	  4. 选择二叉树\n");
        printf("    	  0. 退出系统\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~4]:");
        scanf("%d",&ip);
        switch(ip)
        {
        case 1:
            if(head==NULL||head->LL==NULL){
                    printf("无二叉树！\n");
                    tail=head;
            }
            else{
                Lists=head;
                while(Lists){
                        tail=Lists;
                        printf("%s\n",Lists->name);
                        PreOrderTraverse(Lists->LL,visit);
                        printf("\n");
                        InOrderTraverse(Lists->LL,visit);
                        printf("\n");
                        Lists=Lists->next;
                }
                printf("以上是全部二叉树！（先序、中序遍历显示）\n");
            }
            getchar();getchar();
            break;
        case 2:
            i=0;
            if(head==NULL){
                Lists=(LISTS *)malloc(sizeof(LISTS));
                head=Lists;
                head->LL=NULL;
                tail=head;
            }
            if(head->LL==NULL) p=Lists;
            else{
                p=(LISTS *)malloc(sizeof(LISTS));
                tail->next=p;
                tail=tail->next;
            }
            printf("请输入要增加的二叉树的名字：");
            scanf("%s",TreeName);
            if(AddTree(p,TreeName)!=OK) printf("增加二叉树失败！\n");
            else{
                p->next=NULL;
                printf("请输入二叉树内容：（按先序遍历输入）");
                do {
                    scanf("%d%s",&definition[i].key,definition[i].others);
                } while (definition[i++].key!=-1);
                ans=CreateBiTree(p->LL,definition);
                printf("二叉树增加成功！\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("请输入要删除的二叉树的名字：");
            scanf("%s",TreeName);
            if(RemoveTree(head,TreeName)!=OK) printf("删除二叉树失败！\n");
            else printf("删除二叉树成功！\n");
            getchar();getchar();
            break;
        case 4:
            printf("请输入要选择的二叉树名字：");
            scanf("%s",TreeName);
            p=head;
            while(p&&(strcmp(p->name,TreeName)!=0)) p=p->next;
            if(p==NULL){
                printf("未找到选择的二叉树！\n");
                getchar();getchar();
                break;
            }
            else printf("已找到选择的二叉树！请继续操作！\n");
            getchar();getchar();
            op=1;
            while(op){
                system("cls");	printf("\n\n");
                printf("               二叉树的基本操作演示系统 \n");
                printf("-------------------------------------------------\n");
                printf("    	  1. 二叉树的创建       7. 删除结点\n");
                printf("    	  2. 二叉树的清空       8. 先序遍历\n");
                printf("    	  3. 查找结点           9. 中序遍历 \n");
                printf("    	  4. 结点赋值           10. 后序遍历\n");
                printf("    	  5. 获得兄弟结点       11. 按层遍历\n");
                printf("    	  6. 插入结点           12. 写文件\n");
                printf("    	  13. 读文件            14. 求二叉树深度\n");
                printf("    	  15.二叉树的销毁       0.退出\n");
                printf("-------------------------------------------------\n");
                printf("    请选择你的操作[0~15]:");
                scanf("%d",&op);
                switch(op){
                case 1:
                    definition[100]={NULL};
                    definition[0].key=-1;
                    if(CreateBiTree(p->LL,definition)==OK) printf("二叉树创建成功！\n");
                    else printf("二叉树创建失败！\n");
                    getchar();getchar();
                    break;
                case 2:
                    if(ClearBiTree(p->LL)==OK) printf("二叉树清空成功！\n");
                    else printf("二叉树清空失败！\n");
                    getchar();getchar();
                    break;
                case 3:
                    printf("请输入要查找的结点关键字：");
                    scanf("%d",&e);
                    q=LocateNode(p->LL,e);
                    if(q) printf("查找结点成功！%d,%s",q->data.key,q->data.others);
                    else printf("查找结点失败！\n");
                    getchar();getchar();
                    break;
                case 4:
                    printf("请输入要赋值的关键字和修改后的关键字及内容：");
                    scanf("%d%d%s",&key,&c.key,c.others);
                    ans=Assign(p->LL,key,c);
                    if (ans==OK)
                    {
                        printf("结点赋值成功！\n");
                        PreOrderTraverse(p->LL,visit);
                        printf("\n");
                        InOrderTraverse(p->LL,visit);
                    }
                    else printf("结点赋值失败！\n");
                    getchar();getchar();
                    break;
                case 5:
                    printf("请输入要获得兄弟结点的结点的关键字：");
                    scanf("%d",&e);
                    q=GetSibling(p->LL,e);
                    if(q) printf("获得兄弟结点成功！ %d,%s",q->data.key,q->data.others);
                    else printf("获得兄弟结点失败！\n");
                    getchar();getchar();
                    break;
                case 6:
                    printf("请输入要插入结点的结点的关键字、左或右孩子、插入的结点的关键字和内容：");
                    scanf("%d%d%d%s",&e,&LR,&c.key,c.others);
                    ans=InsertNode(p->LL,e,LR,c);
                    if (ans==OK)
                    {
                        printf("插入结点成功！\n");
                        PreOrderTraverse(p->LL,visit);
                        printf("\n");
                        InOrderTraverse(p->LL,visit);
                    }
                    else printf("插入结点失败！\n");
                    getchar();getchar();
                    break;
                case 7:
                    printf("请输入要删除结点的结点的关键字：");
                    scanf("%d",&e);
                    ans=DeleteNode(p->LL,e);
                    if (ans==OK)
                    {
                        printf("删除结点成功！\n");
                        PreOrderTraverse(p->LL,visit);
                        printf("\n");
                        InOrderTraverse(p->LL,visit);
                    }
                    else printf("删除结点失败！\n");
                    getchar();getchar();
                    break;
                case 8:
                    if(PreOrderTraverse(p->LL,visit)==-3) printf("无二叉树！\n");
                    else printf("\n以上为先序遍历\n");
                    getchar();getchar();
                    break;
                case 9:
                    InOrderTraverse(p->LL,visit);
                    printf("\n以上为中序遍历\n");
                    getchar();getchar();
                    break;
                case 10:
                    PostOrderTraverse(p->LL,visit);
                    printf("\n以上为后序遍历\n");
                    getchar();getchar();
                    break;
                case 11:
                    LevelOrderTraverse(p->LL,visit);
                    printf("\n以上为按层遍历\n");
                    getchar();getchar();
                    break;
                case 12:
                    printf("请给FileName赋值：");
                    scanf("%s",FileName);
                    if(SaveBiTree(p->LL,FileName)==OK) printf("写文件成功！\n");
                    else printf("写文件失败！\n");
                    getchar();getchar();
                    break;
                case 13:
                    p->LL=NULL;
                    printf("请给FileName赋值：");
                    scanf("%s",FileName);
                    if(LoadBiTree(p->LL,FileName)==OK) printf("读文件成功！\n");
                    else printf("读文件失败！\n");
                    getchar();getchar();
                    break;
                case 14:
                    if(BiTreeDepth(p->LL)!=INFEASIBLE) printf("执行成功！二叉树深度为：%d\n",BiTreeDepth(p->LL));
                    else printf("二叉树不存在，无深度！");
                    getchar();getchar();
                    break;
                case 15:
                    if(DestoryBiTree(p->LL)==OK) printf("二叉树销毁成功！\n");
                    else printf("二叉树销毁失败！\n");
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

status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    BiTNode *p,*q,*s[10]={NULL};
    int i=1,j=1,x=0,yy=0;
    for(x=0;definition[x].key!=-1;x++){
            for(yy=0;yy<x;yy++)
                if(definition[yy].key==definition[x].key&&definition[x].key!=0) return ERROR;
    }
    x=0;
    q=(BiTNode *)malloc(sizeof(BiTNode));
    T=q;
    p=T;
    s[0]=T;
    p->lchild=NULL;
    p->rchild=NULL;
    if(definition[0].key!=-1){
        p->data.key=definition[0].key;
        strcpy(p->data.others,definition[0].others);
    }
    else{
        T->data.key=0;
        strcpy(T->data.others,"NULL");
        return OK;
    }
    while(definition[i].key!=-1){
        q=(BiTNode *)malloc(sizeof(BiTNode));
        if(p->lchild==NULL){
            if(definition[i].key==0){
                    p->lchild=q;
                    p->lchild->data.key=-2;
                    j--;
                }
                else{
                    p->lchild=q;
                    p=p->lchild;
                    s[j]=p;
                    p->data.key=definition[i].key;
                    strcpy(p->data.others,definition[i].others);
                    p->lchild=NULL;
                    p->rchild=NULL;
                    j++;
                }
        }
        else if(p->rchild==NULL){
            if(s[j]->lchild->data.key==-2){
                free(s[j]->lchild);
                s[j]->lchild=NULL;
                if(definition[i].key==0){
                    s[j]->rchild=NULL;
                    while(s[--j]->lchild==NULL) {
                        s[j]=NULL;
                    }
                    p=s[j];
                }
                else{
                    s[j]->rchild=q;
                    p=s[j]->rchild;
                    p->data.key=definition[i].key;
                    strcpy(p->data.others,definition[i].others);
                    p->lchild=NULL;
                    p->rchild=NULL;
                    j++;
                    s[j]=p;
                    j++;
                }
            }
            else{
                if(definition[i].key==0){
                    p->rchild=NULL;
                    while(s[--j]->lchild==NULL) ;
                    p=s[--j];
                }
                else{
                    p->rchild=q;
                    p=p->rchild;
                    s[++j]=p;
                    p->data.key=definition[i].key;
                    strcpy(p->data.others,definition[i].others);
                    p->lchild=NULL;
                    p->rchild=NULL;
                    j++;
                }
            }
        }
        i++;
    }
    return OK;
}

status DestoryBiTree(BiTree &T)
//销毁二叉树
{
    if(T->lchild!=NULL){
        DestoryBiTree(T->lchild);
    }
    if(T->rchild!=NULL){
        DestoryBiTree(T->rchild);
    }
    if(T->lchild==NULL&&T->rchild==NULL){
        free(T);
        T=NULL;
    }
    return OK;
}

status ClearBiTree(BiTree &T)
//清空二叉树
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    T->data.key=0;
    strcpy(T->data.others,"NULL");
    if(T->lchild!=NULL) DestoryBiTree(T->lchild);
    if(T->rchild!=NULL) DestoryBiTree(T->rchild);
    return OK;
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    int id=1,rd=1,i=0;//id为每次更新时获取的深度，rd为真实的深度
    BiTree s[20],p=T;
    int ss[20]={0};
    if(!p) return 0;
    s[i]=p;
    while(s[0]){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
            }
            if((id=(i--)+1)>rd) rd=id;//如果当前深度比真实深度大，则更新真实的深度
        }
        if((id=i+1)>rd) rd=id;//如果当前深度比真实深度大，则更新真实的深度
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
        }
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    return rd;
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    int i=0;
    BiTree p=T,s[20];
    int ss[20]={0};
    s[i]=p;
    while(s[0]&&p->data.key!=e){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
                if(p->data.key==e) break;
            }
        }
        if(p->data.key==e) break;
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
        }
        if(p->data.key==e) break;
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    if(s[0]==0) return NULL;
    return p;
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    int i=0;
    BiTree p=T,s[20],th=NULL;
    int ss[20]={0};
    s[i]=p;
    while(s[0]){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
                if(p->data.key!=e&&p->data.key==value.key) return ERROR;
                if(p->data.key==e) th=p;
            }
        }
        if(p->data.key!=e&&p->data.key==value.key) return ERROR;
        if(p->data.key==e) th=p;
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
        }
        //if(p->data.key!=e&&p->data.key==value.key) return ERROR;
        //if(p->data.key==e) th=p;
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if(p->data.key!=e&&p->data.key==value.key) return ERROR;
            if(p->data.key==e) th=p;
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    if(th==NULL) return ERROR;
    th->data.key=value.key;
    strcpy(th->data.others,value.others);
    return OK;
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    int i=0,t=0;
    BiTree p=T,s[20]={NULL};
    int ss[20]={0};
    s[i]=p;
    while(s[0]&&p->data.key!=e){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
                if(p->data.key==e){
                    t=i-1;
                    break;
                }
            }
        }
        if(p->data.key==e) break;
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
            if(p->data.key==e){
                t=i-1;
                break;
            }
        }
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    if(s[0]==0) return NULL;
    if(s[t]->lchild==p){
        if(s[t]->rchild==NULL) return NULL;
        return s[t]->rchild;
    }
    if(s[t]->rchild==p){
        if(s[t]->lchild==NULL) return NULL;
        return s[t]->lchild;
    }
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    int i=0;
    BiTree p=T,s[20]={NULL},th=NULL,q=NULL,newq;
    int ss[20]={0};
    s[i]=p;
    if((e==0)&&(LR==-1)){
        newq=(BiTNode *)malloc(sizeof(BiTNode));
        newq->data.key=c.key;
        strcpy(newq->data.others,c.others);
        newq->lchild=p;
        newq->rchild=NULL;
        T=newq;
        return OK;
    }
    while(s[0]){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
                if((p->data.key!=e&&p->data.key==c.key)||(p->data.key==e&&p->data.key==c.key)) return ERROR;
                if(p->data.key==e) th=p;
            }
        }
        if((p->data.key!=e&&p->data.key==c.key)||(p->data.key==e&&p->data.key==c.key)) return ERROR;
        if(p->data.key==e) th=p;
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
        }
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if((p->data.key!=e&&p->data.key==c.key)||(p->data.key==e&&p->data.key==c.key)) return ERROR;
            if(p->data.key==e) th=p;
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    if(th==NULL) return ERROR;
    if(LR==0){
        q=th->lchild;
        newq=(BiTNode *)malloc(sizeof(BiTNode));
        newq->data.key=c.key;
        strcpy(newq->data.others,c.others);
        th->lchild=newq;
        newq->lchild=NULL;
        newq->rchild=q;
    }
    if(LR==1){
        q=th->rchild;
        newq=(BiTNode *)malloc(sizeof(BiTNode));
        newq->data.key=c.key;
        strcpy(newq->data.others,c.others);
        th->rchild=newq;
        newq->lchild=NULL;
        newq->rchild=q;
    }
    /*if(LR==-1){
        p=T;
        newq=(BiTNode *)malloc(sizeof(BiTNode));
        newq->data.key=c.key;
        strcpy(newq->data.others,c.others);
        newq->rchild=p;
        newq->lchild=NULL;
        T=newq;
    }*/
    return OK;
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    int i=0,t=0;
    BiTree p=T,s[20]={NULL},q=NULL,qq=NULL;
    int ss[20]={0};
    s[i]=p;
    while(s[0]&&p->data.key!=e){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
                if(p->data.key==e){
                    t=i-1;
                    break;
                }
            }
        }
        if(p->data.key==e) break;
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
            if(p->data.key==e){
                t=i-1;
                break;
            }
        }
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    if(s[0]==0) return ERROR;
    if(T->data.key==e){
        if(T->lchild!=NULL){
            if(T->rchild==NULL){
                p=T;
                T=T->lchild;
                free(p);
            }
            else{
                p=T->lchild;
                q=T;
                while(p->rchild!=NULL) p=p->rchild;
                p->rchild=T->rchild;
                T=T->lchild;
                free(q);
            }
        }
        else if(T->lchild==NULL&&T->rchild!=NULL){
            p=T;
            T=T->rchild;
            free(p);
        }
    }
    else if(s[t]->lchild==p){
        if(p->lchild==NULL&&p->rchild==NULL){
            s[t]->lchild=NULL;
            free(p);
            p=NULL;
        }
        else if(p->lchild!=NULL&&p->rchild!=NULL){
            q=p->rchild;
            s[t]->lchild=p->lchild;
            qq=p->lchild;
            while(qq->rchild) qq=qq->rchild;
            qq->rchild=q;
            free(p);
            p=NULL;
        }
        else{
            if(p->lchild==NULL){
                s[t]->lchild=p->rchild;
                free(p);
                p=NULL;
            }
             else if(p->rchild==NULL){
                s[t]->lchild=p->lchild;
                free(p);
                p=NULL;
            }
        }
    }
    else if(s[t]->rchild==p){
        if(p->lchild==NULL&&p->rchild==NULL){
            s[t]->rchild=NULL;
            free(p);
            p=NULL;
        }
        else if(p->lchild!=NULL&&p->rchild!=NULL){
            q=p->rchild;
            s[t]->rchild=p->lchild;
            qq=p->lchild;
            while(qq->rchild) qq=qq->rchild;
            qq->rchild=q;
            free(p);
            p=NULL;
        }
        else{
            if(p->lchild==NULL){
                s[t]->rchild=p->rchild;
                free(p);
                p=NULL;
            }
            if(p->rchild==NULL){
                s[t]->rchild=p->lchild;
                free(p);
                p=NULL;
            }
        }
    }
    return OK;
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    if(T==NULL) return -3;
    if(T->lchild==NULL&&T->rchild==NULL) return ERROR;
    int i=0;
    BiTree p=T,s[20]={NULL};
    int ss[20]={0};
    s[i]=p;
    visit(p);
    while(s[0]){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
                visit(p);
            }
        }
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
            visit(p);
        }
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    return OK;
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    if(T==NULL) return OK;
    if(T->lchild) InOrderTraverse(T->lchild,visit);
    visit(T);
    if(T->rchild) InOrderTraverse(T->rchild,visit);
    /*if(T->lchild==NULL&&T->rchild==NULL) return ERROR;
    int i=0;
    BiTree p=T,s[20]={NULL};
    int ss[20]={0};
    s[i]=p;
    while(s[0]){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
            }
        }
        visit(p);
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
        }
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    return OK;*/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    if(T==NULL) return OK;
    if(T->lchild) PostOrderTraverse(T->lchild,visit);
    if(T->rchild) PostOrderTraverse(T->rchild,visit);
    visit(T);
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    int i=1,t=1;
    BiTree p=T,aqueue[50]={NULL},q;
    aqueue[0]=T;
    q=aqueue[0];
    if(p->lchild) aqueue[i++]=p->lchild;
    if(p->rchild) aqueue[i++]=p->rchild;
    q=aqueue[t];
    while(t!=i){
        p=q;
        if(p->lchild) aqueue[i++]=p->lchild;
        if(p->rchild) aqueue[i++]=p->rchild;
        q=aqueue[++t];
    }
    for(i=0;i<t;i++) visit(aqueue[i]);
    return OK;
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
   	if(T==NULL) return INFEASIBLE;
	FILE* fp;
	if((fp=fopen(FileName,"w"))==NULL)
        return ERROR;
	int i=0;
	BiTree p=T,s[20]={NULL};
    int ss[20]={0};
    s[i]=p;
    fprintf(fp,"%d %s ",p->data.key,p->data.others);
    while(s[0]){
        if(ss[i]==0){
            while(p->lchild){
                i++;
                s[i]=p->lchild;
                ss[i-1]=1;
                p=p->lchild;
                fprintf(fp,"%d %s ",p->data.key,p->data.others);
            }
            fprintf(fp,"0 NULL ");
        }
        if(p->rchild){
            i++;
            if((!ss[i])&&(s[i]!=0)) i++;
            s[i]=p->rchild;
            ss[i-1]=2;
            p=p->rchild;
            fprintf(fp,"%d %s ",p->data.key,p->data.others);
        }
        else{
            p=s[i];
            s[i+1]=NULL;
            while(ss[i]==2){
                i--;
                if(i>=0) p=s[i];
                s[i+1]=NULL;
                ss[i+1]=0;
            }
            if(i>=0){
                if(ss[i]==0||(p->lchild!=NULL&&p->rchild==NULL)){
                    fprintf(fp,"0 NULL ");
                    i--;
                    s[i+1]=NULL;
                    ss[i+1]=0;
                }
            }
        }
    }
    fprintf(fp,"-1 null ");
	fclose(fp);
	return OK;
}
status LoadBiTree(BiTree &T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    if(T!=NULL) return INFEASIBLE;
	FILE* fp;
	if((fp=fopen(FileName,"r"))==NULL)
        return ERROR;
	TElemType x[100]={{0,NULL}};
	int i=0;
	while(fscanf(fp,"%d",&x[i].key)!=EOF&&(fscanf(fp,"%s",x[i].others)!=EOF))
        i++;
	x[i].key=-1;
	CreateBiTree(T,x);
	fclose(fp);
	return OK;
}

status AddTree(LISTS *Lists,char TreeName[])//新建一个二叉树
{
    BiTNode *p=(BiTNode*)malloc(sizeof(BiTNode));
    Lists->LL=p;
    Lists->LL->lchild=NULL;
    Lists->LL->rchild=NULL;
    Lists->next=NULL;
    strcpy(Lists->name,TreeName);
    Lists->length++;
    return OK;
}
status RemoveTree(LISTS *&Lists,char TreeName[])//删除一个二叉树
{

    LISTS *p=NULL,*pp=NULL;
    p=Lists;
    pp=Lists->next;
    if(!strcmp(p->name,TreeName)){
        Lists=pp;
        ClearBiTree(p->LL);
        free(p);
        p=NULL;
        return OK;
    }
    else{
        while(pp!=NULL&&(strcmp(pp->name,TreeName))){
            pp=pp->next;
            p=p->next;
        }
        if(pp){
            p->next=pp->next;
            ClearBiTree(pp->LL);
            free(pp);
            pp=NULL;
            return OK;
        }
        else return ERROR;
    }
}
/*status DestroyBiTree(BiTree &T)
{
   if (T)
   {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T=NULL;
   }
   return OK;
}*/
