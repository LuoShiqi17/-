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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct LISTS{  //���������������ʽ�ṹ�����Ķ���
      char name[30];
        LNode* LL;
      struct LISTS *next;
      int length;
}LISTS;

status InitList(LinkList &L);//���Ա�Ĵ���
status DestroyList(LinkList &L);//�������Ա�
status ClearList(LinkList &L);//������Ա�
status ListEmpty(LinkList L);//���Ա���п�
int ListLength(LinkList L);//���Ա�ĳ��ȣ����س��ȣ�
status GetElem(LinkList L,int i,ElemType &e);//��ȡԪ��
status LocateElem(LinkList L,ElemType e);//����Ԫ�أ����ز��ҵ�Ԫ�ص�λ�ã�
status PriorElem(LinkList L,ElemType e,ElemType &pre);//��ȡǰ��Ԫ��
status NextElem(LinkList L,ElemType e,ElemType &next);//��ȡ���Ԫ��
status ListInsert(LinkList &L,int i,ElemType e);//����Ԫ��
status ListDelete(LinkList &L,int i,ElemType &e);//ɾ��Ԫ��
status ListTraverse(LinkList L);//�������Ա�
status SaveList(LinkList L,char FileName[]);//���Ա���ļ�
status LoadList(LinkList &L,char FileName[]);//���Ա�д�ļ�
status AddList(LISTS *Lists,char ListName[]);//�½����Ա�
status RemoveList(LISTS *&Lists,char ListName[]);//ɾ�����Ա�


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
        printf("      ������ʽ�ṹ�����Ա����������ʾϵͳ \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. ��ʾȫ�����Ա�\n");
        printf("    	  2. ����һ�����Ա�\n");
        printf("    	  3. ɾ��һ�����Ա� \n");
        printf("    	  4. ѡ�����Ա�\n");
        printf("    	  0. �˳�ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~4]:");
        scanf("%d",&ip);
        switch(ip)
        {
        case 1:
            //p=Lists;
            if(head==NULL||head->LL==NULL){
                    printf("�����Ա�\n");
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
                printf("������ȫ�����Ա�\n");
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
            printf("������Ҫ���ӵ����Ա�����֣�");
            scanf("%s",ListName);
            if(AddList(p,ListName)!=OK) printf("�������Ա�ʧ�ܣ�\n");
            else{
                p->next=NULL;
                printf("���������Ա����ݣ�");
                scanf("%d",&e);
                q=(LNode *)malloc(sizeof(LNode));
                p->LL=q;
                if(e==0){
                    p->LL->next=NULL;
                    printf("���Ա����ӳɹ���\n");
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
                printf("���Ա����ӳɹ���\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("������Ҫɾ�������Ա�����֣�");
            scanf("%s",ListName);
            if(RemoveList(head,ListName)!=OK) printf("ɾ�����Ա�ʧ�ܣ�\n");
            else printf("ɾ�����Ա�ɹ���\n");
            getchar();getchar();
            break;
        case 4:
            printf("������Ҫѡ������Ա����֣�");
            scanf("%s",ListName);
            p=head;
            while(p&&(strcmp(p->name,ListName)!=0)) p=p->next;
            if(p==NULL){
                printf("δ�ҵ�ѡ������Ա�\n");
                getchar();getchar();
                break;
            }
            else printf("���ҵ�ѡ������Ա������������\n");
            getchar();getchar();
            op=1;
            while(op){
                system("cls");	printf("\n\n");
                printf("      ������ʽ�ṹ�����Ա����������ʾϵͳ \n");
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
                printf("    ��ѡ����Ĳ���[0~14]:");
                scanf("%d",&op);
                switch(op){
                case 1:
                    if(InitList(p->LL)==OK) printf("���Ա����ɹ���\n");
                    else printf("���Ա���ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 2:
                    printf("\n----DestroyList���ܴ�ʵ�֣�\n");
                    if(DestroyList(p->LL)==OK) printf("���Ա����ٳɹ���\n");
                    else printf("���Ա�����ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 3:
                    printf("\n----ClearList���ܴ�ʵ�֣�\n");
                    if(ClearList(p->LL)==OK) printf("���Ա���ճɹ���\n");
                    else printf("���Ա����ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 4:
                    printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
                    if(ListEmpty(p->LL)==TRUE) printf("���Ա��пճɹ���\n");
                    else printf("���Ա��п�ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 5:
                    printf("\n----ListLength���ܴ�ʵ�֣�\n");
                    if(ListLength(p->LL)!=INFEASIBLE) printf("ִ�гɹ������Ա���Ϊ��%d\n",ListLength(p->LL));
                    else printf("���Ա����ڣ��޳��ȣ�");
                    getchar();getchar();
                    break;
                case 6:
                    printf("\n----GetElem���ܴ�ʵ�֣�\n");
                    printf("��������Ҫ��ȡ��Ԫ�ص�λ�ã�");
                    scanf("%d",&i);
                    if(GetElem(p->LL,i,e)==OK) printf("ִ�гɹ���Ԫ��Ϊ��%d\n",e);
                    else printf("ִ��ʧ�ܣ��޷���ȡԪ�أ�\n");
                    getchar();getchar();
                    break;
                case 7:
                    printf("\n----LocateElem���ܴ�ʵ�֣�\n");
                    printf("��������Ҫ���ҵ�Ԫ�أ�");
                    scanf("%d",&e);
                    if((LocateElem(p->LL,e)==INFEASIBLE)||(LocateElem(p->LL,e)==ERROR)) printf("����Ԫ��ʧ�ܣ�\n");
                    else printf("����Ԫ�سɹ���Ԫ�ص�λ��Ϊ��%d\n",LocateElem(p->LL,e));
                    getchar();getchar();
                    break;
                case 8:
                    printf("\n----PriorElem���ܴ�ʵ�֣�\n");
                    printf("��������Ҫ��ȡǰ����Ԫ�أ�");
                    scanf("%d",&e);
                    if(PriorElem(p->LL,e,pre)==OK) printf("��ȡ�ɹ�����Ԫ�ص�ǰ��Ԫ��Ϊ��%d\n",pre);
                    else printf("��ȡʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 9:
                    printf("\n----NextElem���ܴ�ʵ�֣�\n");
                    printf("��������Ҫ��ȡ��̵�Ԫ�أ�");
                    scanf("%d",&e);
                    if(NextElem(p->LL,e,next)==OK) printf("��ȡ�ɹ�����Ԫ�صĺ��Ԫ��Ϊ��%d\n",next);
                    else printf("��ȡʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 10:
                    printf("\n----ListInsert���ܴ�ʵ�֣�\n");
                    printf("������Ҫ�����Ԫ�غ�λ�ã�");
                    scanf("%d %d",&e,&i);
                    if(ListInsert(p->LL,i,e)==OK) printf("����ɹ���\n");
                    else printf("����ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 11:
                    printf("\n----ListDelete���ܴ�ʵ�֣�\n");
                    printf("������Ҫɾ����Ԫ��λ�ã�");
                    scanf("%d",&i);
                    if(ListDelete(p->LL,i,e)==OK) printf("ɾ���ɹ���ɾ����Ԫ��Ϊ��%d\n",e);
                    else printf("ɾ��ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 12:
                    if(ListTraverse(p->LL)==INFEASIBLE) printf("�����Ա�\n");
                    else printf("\n���������Ա�����Ԫ�أ�\n");
                    getchar();getchar();
                    break;
                case 13:
                    printf("���FileName��ֵ��");
                    scanf("%s",FileName);
                    if(SaveList(p->LL,FileName)==OK) printf("д�ļ��ɹ���\n");
                    else printf("д�ļ�ʧ�ܣ�\n");
                    getchar();getchar();
                    break;
                case 14:
                    p->LL=NULL;
                    printf("���FileName��ֵ��");
                    scanf("%s",FileName);
                    if(LoadList(p->LL,FileName)==OK) printf("���ļ��ɹ���\n");
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

status InitList(LinkList &L)//���Ա�Ĵ���
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    if(L!=NULL) return INFEASIBLE;
    L=(LNode *)malloc(sizeof(LNode));
    L->next=NULL;
    return OK;
}
status DestroyList(LinkList &L)//�������Ա�
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
status ClearList(LinkList &L)//������Ա�
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
status ListEmpty(LinkList L)//���Ա���п�
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L==NULL) return INFEASIBLE;
    else if(L->next==NULL) return TRUE;
    else return FALSE;
}
int ListLength(LinkList L)//���Ա�ĳ��ȣ����س��ȣ�
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
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
status GetElem(LinkList L,int i,ElemType &e)//��ȡԪ��
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
status LocateElem(LinkList L,ElemType e)//����Ԫ�أ����ز��ҵ�Ԫ�ص�λ�ã�
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    if(L==NULL) return INFEASIBLE;
    int i=1;
    LinkList p=L->next;
    if(p==NULL) return ERROR;
    while(p->data!=e&&p->next!=NULL){
        if(p->next->next==NULL){//�ж��ǲ��ǳ������ȶ��˳�ѭ��
            if(p->next->data!=e) return ERROR;
            else return (i+1);
        }
        p=p->next;
        i++;
    }
    return i;
}
status PriorElem(LinkList L,ElemType e,ElemType &pre)//��ȡǰ��Ԫ��
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
status NextElem(LinkList L,ElemType e,ElemType &next)//��ȡ���Ԫ��
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
status ListInsert(LinkList &L,int i,ElemType e)//����Ԫ��
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
status ListDelete(LinkList &L,int i,ElemType &e)//ɾ��Ԫ��
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
status ListTraverse(LinkList L)//�������Ա�
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L==NULL) return INFEASIBLE;
    LinkList p=L->next;
    while(p){
        printf("%d ",p->data);
        p=p->next;
    }
    return OK;
}
status SaveList(LinkList L,char FileName[])//���Ա�д�ļ�
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    if(L==NULL) return INFEASIBLE;
    else{
        LinkList p=L->next;
        FILE *fp;
        fp=fopen(FileName,"r");//�ж��ļ��Ƿ����
        if(!fp){
            fclose(fp);
            return ERROR;
        }
        fp=fopen(FileName,"w");//��w���ļ������ڻ�ֱ�Ӵ���
        while(p){
            fprintf(fp,"%d ",p->data);
            p=p->next;
        }
        fclose(fp);
    }
    return OK;
}

status LoadList(LinkList &L,char FileName[])//���Ա���ļ�
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
status AddList(LISTS *Lists,char ListName[])//�½�һ�����Ա�
{
    LNode *p=(LNode*)malloc(sizeof(LNode));
    Lists->LL=p;
    Lists->LL->next=NULL;
    Lists->next=NULL;
    strcpy(Lists->name,ListName);
    Lists->length++;
    return OK;
}

status RemoveList(LISTS *&Lists,char ListName[])//ɾ��һ�����Ա�
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

