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
typedef struct {//������������Ͷ���
    KeyType  key;
    char others[20];
}TElemType;

typedef struct BiTNode{ //����������Ķ���
    TElemType  data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct LISTS{  //�����������������Ķ���
      char name[30];
        BiTree LL;
      struct LISTS *next;
      int length;
}LISTS;

status CreateBiTree(BiTree &T,TElemType definition[]);//�������Ĵ���
status ClearBiTree(BiTree &T);//�����������
int BiTreeDepth(BiTree T);//���������
BiTNode* LocateNode(BiTree T,KeyType e);//���ҽ��
status Assign(BiTree &T,KeyType e,TElemType value);//��㸳ֵ
BiTNode* GetSibling(BiTree T,KeyType e);//����ֵܽ��
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);//������
status DeleteNode(BiTree &T,KeyType e);//ɾ�����
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));//�������
status InOrderTraverse(BiTree T,void (*visit)(BiTree));//�������
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));//�������
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));//�������
status SaveBiTree(BiTree T, char FileName[]);//д�ļ�
status LoadBiTree(BiTree &T, char FileName[]);//���ļ�
status AddTree(LISTS *Lists,char ListName[]);//����һ��������
status RemoveTree(LISTS *&Lists,char TreeName[]);//ɾ��һ��������
status DestoryBiTree(BiTree &T);//������������
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
        printf("         �������Ļ���������ʾϵͳ \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. ��ʾȫ��������\n");
        printf("    	  2. ����һ��������\n");
        printf("    	  3. ɾ��һ�������� \n");
        printf("    	  4. ѡ�������\n");
        printf("    	  0. �˳�ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~4]:");
        scanf("%d",&ip);
        switch(ip)
        {
        case 1:
            if(head==NULL||head->LL==NULL){
                    printf("�޶�������\n");
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
                printf("������ȫ�������������������������ʾ��\n");
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
            printf("������Ҫ���ӵĶ����������֣�");
            scanf("%s",TreeName);
            if(AddTree(p,TreeName)!=OK) printf("���Ӷ�����ʧ�ܣ�\n");
            else{
                p->next=NULL;
                printf("��������������ݣ���������������룩");
                do {
                    scanf("%d%s",&definition[i].key,definition[i].others);
                } while (definition[i++].key!=-1);
                ans=CreateBiTree(p->LL,definition);
                printf("���������ӳɹ���\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("������Ҫɾ���Ķ����������֣�");
            scanf("%s",TreeName);
            if(RemoveTree(head,TreeName)!=OK) printf("ɾ��������ʧ�ܣ�\n");
            else printf("ɾ���������ɹ���\n");
            getchar();getchar();
            break;
        case 4:
            printf("������Ҫѡ��Ķ��������֣�");
            scanf("%s",TreeName);
            p=head;
            while(p&&(strcmp(p->name,TreeName)!=0)) p=p->next;
            if(p==NULL){
                printf("δ�ҵ�ѡ��Ķ�������\n");
                getchar();getchar();
                break;
            }
            else printf("���ҵ�ѡ��Ķ������������������\n");
            getchar();getchar();
            op=1;
            while(op){
                system("cls");	printf("\n\n");
                printf("               �������Ļ���������ʾϵͳ \n");
                printf("-------------------------------------------------\n");
                printf("    	  1. �������Ĵ���       7. ɾ�����\n");
                printf("    	  2. �����������       8. �������\n");
                printf("    	  3. ���ҽ��           9. ������� \n");
                printf("    	  4. ��㸳ֵ           10. �������\n");
                printf("    	  5. ����ֵܽ��       11. �������\n");
                printf("    	  6. ������           12. д�ļ�\n");
                printf("    	  13. ���ļ�            14. ����������\n");
                printf("    	  15.������������       0.�˳�\n");
                printf("-------------------------------------------------\n");
                printf("    ��ѡ����Ĳ���[0~15]:");
                scanf("%d",&op);
                switch(op){
                case 1:
                    definition[100]={NULL};
                    definition[0].key=-1;
                    if(CreateBiTree(p->LL,definition)==OK) printf("�����������ɹ���\n");
                    else printf("����������ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 2:
                    if(ClearBiTree(p->LL)==OK) printf("��������ճɹ���\n");
                    else printf("���������ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 3:
                    printf("������Ҫ���ҵĽ��ؼ��֣�");
                    scanf("%d",&e);
                    q=LocateNode(p->LL,e);
                    if(q) printf("���ҽ��ɹ���%d,%s",q->data.key,q->data.others);
                    else printf("���ҽ��ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 4:
                    printf("������Ҫ��ֵ�Ĺؼ��ֺ��޸ĺ�Ĺؼ��ּ����ݣ�");
                    scanf("%d%d%s",&key,&c.key,c.others);
                    ans=Assign(p->LL,key,c);
                    if (ans==OK)
                    {
                        printf("��㸳ֵ�ɹ���\n");
                        PreOrderTraverse(p->LL,visit);
                        printf("\n");
                        InOrderTraverse(p->LL,visit);
                    }
                    else printf("��㸳ֵʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 5:
                    printf("������Ҫ����ֵܽ��Ľ��Ĺؼ��֣�");
                    scanf("%d",&e);
                    q=GetSibling(p->LL,e);
                    if(q) printf("����ֵܽ��ɹ��� %d,%s",q->data.key,q->data.others);
                    else printf("����ֵܽ��ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 6:
                    printf("������Ҫ������Ľ��Ĺؼ��֡�����Һ��ӡ�����Ľ��Ĺؼ��ֺ����ݣ�");
                    scanf("%d%d%d%s",&e,&LR,&c.key,c.others);
                    ans=InsertNode(p->LL,e,LR,c);
                    if (ans==OK)
                    {
                        printf("������ɹ���\n");
                        PreOrderTraverse(p->LL,visit);
                        printf("\n");
                        InOrderTraverse(p->LL,visit);
                    }
                    else printf("������ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 7:
                    printf("������Ҫɾ�����Ľ��Ĺؼ��֣�");
                    scanf("%d",&e);
                    ans=DeleteNode(p->LL,e);
                    if (ans==OK)
                    {
                        printf("ɾ�����ɹ���\n");
                        PreOrderTraverse(p->LL,visit);
                        printf("\n");
                        InOrderTraverse(p->LL,visit);
                    }
                    else printf("ɾ�����ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 8:
                    if(PreOrderTraverse(p->LL,visit)==-3) printf("�޶�������\n");
                    else printf("\n����Ϊ�������\n");
                    getchar();getchar();
                    break;
                case 9:
                    InOrderTraverse(p->LL,visit);
                    printf("\n����Ϊ�������\n");
                    getchar();getchar();
                    break;
                case 10:
                    PostOrderTraverse(p->LL,visit);
                    printf("\n����Ϊ�������\n");
                    getchar();getchar();
                    break;
                case 11:
                    LevelOrderTraverse(p->LL,visit);
                    printf("\n����Ϊ�������\n");
                    getchar();getchar();
                    break;
                case 12:
                    printf("���FileName��ֵ��");
                    scanf("%s",FileName);
                    if(SaveBiTree(p->LL,FileName)==OK) printf("д�ļ��ɹ���\n");
                    else printf("д�ļ�ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 13:
                    p->LL=NULL;
                    printf("���FileName��ֵ��");
                    scanf("%s",FileName);
                    if(LoadBiTree(p->LL,FileName)==OK) printf("���ļ��ɹ���\n");
                    else printf("���ļ�ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 14:
                    if(BiTreeDepth(p->LL)!=INFEASIBLE) printf("ִ�гɹ������������Ϊ��%d\n",BiTreeDepth(p->LL));
                    else printf("�����������ڣ�����ȣ�");
                    getchar();getchar();
                    break;
                case 15:
                    if(DestoryBiTree(p->LL)==OK) printf("���������ٳɹ���\n");
                    else printf("����������ʧ�ܣ�\n");
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

status CreateBiTree(BiTree &T,TElemType definition[])
/*���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
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
//���ٶ�����
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
//��ն�����
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
    T->data.key=0;
    strcpy(T->data.others,"NULL");
    if(T->lchild!=NULL) DestoryBiTree(T->lchild);
    if(T->rchild!=NULL) DestoryBiTree(T->rchild);
    return OK;
}

int BiTreeDepth(BiTree T)
//�������T�����
{
    int id=1,rd=1,i=0;//idΪÿ�θ���ʱ��ȡ����ȣ�rdΪ��ʵ�����
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
            if((id=(i--)+1)>rd) rd=id;//�����ǰ��ȱ���ʵ��ȴ��������ʵ�����
        }
        if((id=i+1)>rd) rd=id;//�����ǰ��ȱ���ʵ��ȴ��������ʵ�����
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
//���ҽ��
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
//ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
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
//ʵ�ֻ���ֵܽ��
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
//�����㡣��������ͨ������������������ʵ�ֱ�������
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
//ɾ����㡣��������ͨ������������������ʵ�ֱ�������
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
//�������������T
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
//�������������T
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
//�������������T
{
    if(T==NULL) return OK;
    if(T->lchild) PostOrderTraverse(T->lchild,visit);
    if(T->rchild) PostOrderTraverse(T->rchild,visit);
    visit(T);
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
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
//���������Ľ������д�뵽�ļ�FileName��
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
//�����ļ�FileName�Ľ�����ݣ�����������
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

status AddTree(LISTS *Lists,char TreeName[])//�½�һ��������
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
status RemoveTree(LISTS *&Lists,char TreeName[])//ɾ��һ��������
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
