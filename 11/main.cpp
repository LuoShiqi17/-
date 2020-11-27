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
typedef struct{  //˳���˳��ṹ���Ķ���
      ElemType * elem;
      int length;
      int listsize;
     }SqList;
typedef struct{  //���Ա�ļ������Ͷ���
     struct { char name[30];
               SqList L;
      } elem[10];
      int length;
 }LISTS;
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
int main(void)
{
    SqList L;
    LISTS Lists;
    Lists.elem[10]={0};
    Lists.length=0;
    L.elem=NULL;
    int op=1,ip=0,i=0,ss=0;
    ElemType e=0,pre=0,next=0;
    char name[30];
    char ListName[30];
    char FileName[30];
    while(op){
        system("cls");
        printf("\n\n");
        printf("      ����˳��ṹ�����Ա����������ʾϵͳ \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. ��ʾȫ�����Ա�\n");
        printf("    	  2. ����һ�����Ա�\n");
        printf("    	  3. ɾ��һ�����Ա� \n");
        printf("    	  4. ѡ�����Ա�\n");
        printf("    	  5. �ļ�����\n");
        printf("    	  0. �˳�ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~5]:");
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            if(Lists.length==0) printf("�����Ա�\n");
            else{
                for(int j=0;j<Lists.length;j++){
                    printf("%s\n",Lists.elem[j].name);
                    ListTraverse(Lists.elem[j].L);
                    putchar('\n');
                }
                printf("����Ϊȫ�����Ա�\n");
            }
            getchar();getchar();
            break;
        case 2:
            printf("���������ӵ����Ա�����֣�");
            scanf("%s",ListName);
            if(AddList(Lists,ListName)==OK){
                        printf("���������Ա����ݣ�");
                        int e=0;
                        scanf("%d",&e);
                        while (e) {
                            Lists.elem[Lists.length-1].L.elem[Lists.elem[Lists.length-1].L.length++]=e;
                            scanf("%d",&e);
                    }
                    printf("ִ�гɹ�\n");
            }
            else printf("ִ��ʧ��\n");
            getchar();getchar();
            break;
        case 3:
            printf("������ɾ�������Ա�����֣�");
            scanf("%s",ListName);
            if(RemoveList(Lists,ListName)==OK) printf("ִ�гɹ�\n");
            else printf("ִ��ʧ��\n");
            getchar();getchar();
            break;
        case 4:
            printf("������ѡ������Ա�����֣�");
            scanf("%s",ListName);
            ss=LocateList(Lists,ListName);
            if(LocateList(Lists,ListName)>0){
                    printf("ִ�гɹ�\n");
                    ip=1;
                    while(ip){
                        L=Lists.elem[ss-1].L;
                        system("cls");
                        printf("\n\n");
                        printf("      Menu for Linear Table On Sequence Structure \n");
                        printf("-------------------------------------------------\n");
                        printf("    	  1. InitList(����Ҫ��       7. LocateElem\n");
                        printf("    	  2. DestroyList    8. PriorElem\n");
                        printf("    	  3. ClearList      9. NextElem \n");
                        printf("    	  4. ListEmpty     10. ListInsert\n");
                        printf("    	  5. ListLength    11. ListDelete\n");
                        printf("    	  6. GetElem       12. ListTrabverse\n");
                        printf("    	  0. Exit\n");
                        printf("-------------------------------------------------\n");
                        printf("    ��ѡ����Ĳ���[0~12]:");
                        scanf("%d",&ip);
                        switch(ip)
                        {
                        case 1:
                            if(InitList(Lists.elem[ss-1].L)==OK) printf("���Ա����ɹ�\n");
                            else printf("���Ա���ʧ��\n");
                            getchar();getchar();
                            break;
                        case 2:
                            if(DestroyList(Lists.elem[ss-1].L)==OK) printf("DestroyListִ�гɹ�\n");
                            else printf("DestroyListִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 3:
                            if(ClearList(Lists.elem[ss-1].L)==OK) printf("ClearListִ�гɹ�\n");
                            else printf("ClearListִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 4:
                            if(ListEmpty(Lists.elem[ss-1].L)==OK) printf("ListEmptyִ�гɹ�\n");
                            else printf("ListEmptyִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 5:
                            if(ListLength(Lists.elem[ss-1].L)>0){
                                printf("%d\n",ListLength(Lists.elem[ss-1].L));
                                printf("ListLengthִ�гɹ�\n");
                            }
                            else printf("ListLengthִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 6:
                            printf("��ȡ��i��Ԫ�أ�������i��");
                            scanf("%d",&i);
                            if(GetElem(Lists.elem[ss-1].L,i,e)==OK){
                                printf("%d\n",e);
                                printf("GetElemִ�гɹ�\n");
                            }
                            else printf("GetElemִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 7:
                            printf("������Ԫ��e��");
                            scanf("%d",&e);
                            i=LocateElem(L,e);
                            if(LocateElem(Lists.elem[ss-1].L,e)>0) printf("LocateElemִ�гɹ���λ��Ϊ%d\n",i);
                            else printf("LocateElemִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 8:
                            printf("����Ԫ��e��");
                            scanf("%d",&e);
                            if(PriorElem(Lists.elem[ss-1].L,e,pre)==OK) printf("PriorElemִ�гɹ�,Ԫ��Ϊ��%d\n",pre);
                            else printf("PriorElemִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 9:
                            printf("����Ԫ��e��");
                            scanf("%d",&e);
                            if(NextElem(Lists.elem[ss-1].L,e,next)==OK) printf("NextElemִ�гɹ�,Ԫ��Ϊ��%d\n",next);
                            else printf("NextElemִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 10:
                            printf("������Ҫ�����Ԫ��e��λ��i��");
                            scanf("%d %d",&e,&i);
                            if(ListInsert(Lists.elem[ss-1].L,i,e)==OK) printf("ListInsertִ�гɹ�\n");
                            else printf("ListInsertִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 11:
                            printf("������Ҫɾ��Ԫ�ص�λ��i��");
                            scanf("%d",&i);
                            if(ListDelete(Lists.elem[ss-1].L,i,e)==OK) printf("ListDeleteִ�гɹ�\n");
                            else printf("ListDeleteִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 12:
                            if(ListTraverse(Lists.elem[ss-1].L)==OK) printf("ListTraverseִ�гɹ�\n");
                            else printf("ListTraverseִ��ʧ��\n");
                            getchar();getchar();
                            break;
                        case 0:
                            break;
                        }
                    }
                    break;
            }
            else printf("ִ��ʧ��\n");
            getchar();getchar();
            break;
        case 5:
            printf("���FileName��ֵ��");
            scanf("%s",FileName);
            printf("������Ҫ��ȡ�����Ա�");
            scanf("%s",name);
            if(SaveList(Lists.elem[LocateList(Lists,name)-1].L,FileName)==OK) printf("SaveListִ�гɹ�\n");
            else printf("SaveListִ��ʧ��\n");
            free(Lists.elem[LocateList(Lists,name)-1].L.elem);
            Lists.elem[LocateList(Lists,name)-1].L.elem=NULL;
            if(LoadList(Lists.elem[LocateList(Lists,name)-1].L,FileName)==OK) printf("LoadListִ�гɹ�\n");
            else printf("LoadListִ��ʧ��\n");
            getchar();getchar();
            break;
        case 0:
            break;
        }
    }
    printf("    ��ӭ�´�ʹ�ñ�ϵͳ\n");
    return 0;
}
status InitList(SqList& L)
{
    if(L.elem==NULL){
        int a[100]={NULL};
        L.elem=&a[0];
        L.length=0;
        L.listsize=100;
        return OK;
    }
    else return INFEASIBLE;
}
status DestroyList(SqList& L)
{
    if(L.elem==NULL)
        return INFEASIBLE;
    else{
        free(L.elem);
        L.elem=NULL;
        L.length=0;
        L.listsize=0;
        return OK;
    }
}
status ClearList(SqList& L)
{
    if(L.elem==NULL)
        return INFEASIBLE;
    else{
        L.length=0;
        return OK;
    }
}
status ListEmpty(SqList L)
{
    if(L.elem==NULL)
        return INFEASIBLE;
    else if(L.length==0)
        return TRUE;
    else
        return FALSE;
}
status ListLength(SqList L)
{
    if(L.elem==NULL)
        return INFEASIBLE;
    else
        return L.length;
}
status GetElem(SqList L,int i,ElemType &e)
{
    if(L.elem==NULL)
        return INFEASIBLE;
    else if(i<=0||i>L.length)
        return ERROR;
    else{
        e=L.elem[i-1];
        return OK;
    }
}
status LocateElem(SqList L,ElemType e)
{
    int i=0;
    if(L.elem==NULL)
        return INFEASIBLE;
    else{
        for(i;L.elem[i]!=e&&i<=L.length;i++) ;
        i++;
        if(i>L.length)
            return ERROR;
        else
            return i;
    }
}
status PriorElem(SqList L,ElemType e,ElemType &pre)
{
    int i=0;
    if(L.elem==NULL)
        return INFEASIBLE;
    else{
        if(e==L.elem[0])
            return ERROR;
        else{
            for(i;e!=L.elem[i]&&i<L.length;i++) ;
            if(i==L.length)
                return ERROR;
            else{
                pre=L.elem[i-1];
                return OK;
            }
        }
    }
}
status NextElem(SqList L,ElemType e,ElemType &next)
{
    int i=0;
    if(L.elem==NULL)
        return INFEASIBLE;
    else{
        for(i;e!=L.elem[i]&&i<L.length;i++) ;
        if(i==L.length||e==L.elem[L.length-1])
            return ERROR;
        else{
            next=L.elem[i+1];
            return OK;
        }
    }
}
status ListInsert(SqList &L,int i,ElemType e)
{
    int j;
    ElemType *p;
    if(L.elem==NULL)
        return INFEASIBLE;
    else{
        if(L.length==0&&i==1){
            L.elem[0]=e;
            L.length++;
            return OK;
        }
        else if(i<=0||i>L.length+1)
            return ERROR;
        else{
            L.elem=(ElemType *)realloc(L.elem,(L.listsize+1)*sizeof(ElemType));
            if(i==L.length+1){
                L.elem[L.length++]=e;
                return OK;
            }
            for(j=L.length;j>=i;j--)
                L.elem[j]=L.elem[j-1];
            L.length++;
            L.elem[j]=e;
            return OK;
        }
    }
}
status ListDelete(SqList &L,int i,ElemType &e)
{
    if(L.elem==NULL)
        return INFEASIBLE;
    else{
        if(i<=0||i>L.length)
            return ERROR;
        else{
            int j=0;
            e=L.elem[i-1];
            for(j=i-1;j<L.length-1;j++)
                L.elem[j]=L.elem[j+1];
            L.elem[L.length-1]=0;
            L.length--;
            return OK;
        }
    }
}
status ListTraverse(SqList L)
{
    int i=0;
    if(L.elem==NULL)
        return INFEASIBLE;
    else{
        if(L.length==0)
            return OK;
        for(i;i<L.length-1;i++)
            printf("%d ",L.elem[i]);
        printf("%d\n",L.elem[i]);
        return OK;
    }
}
status  SaveList(SqList L,char FileName[])
{
    if(L.elem==NULL) return INFEASIBLE;
    FILE *fp;
    fp=fopen(FileName,"w");
    int i=0;
    for(i;i<L.length;i++) fprintf(fp,"%d ",L.elem[i]);
    fclose(fp);
    return OK;
}
status  LoadList(SqList &L,char FileName[])
{
    if(L.elem!=NULL) return INFEASIBLE;
    L.elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    FILE *fp;
    fp=fopen(FileName,"r");
    int i=0,s;
    while(fscanf(fp,"%d",&s)!=EOF)
        L.elem[i++]=s;
    fclose(fp);
    return OK;
}
status AddList(LISTS &Lists,char ListName[])
{
    Lists.elem[Lists.length].L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    Lists.elem[Lists.length].L.length=0;
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.length++;
    return OK;
}
status RemoveList(LISTS &Lists,char ListName[])
{
    int i=0,j=0;
    for(i;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){
            j=i;
            free(Lists.elem[i].L.elem);
            for(j;j<Lists.length-1;j++){
                strcpy(Lists.elem[j].name,Lists.elem[j+1].name);
                Lists.elem[j].L.elem=Lists.elem[j+1].L.elem;
                Lists.elem[j].L.length=Lists.elem[j+1].L.length;
            }
            Lists.elem[Lists.length-1].L.elem=NULL;
            Lists.elem[Lists.length-1].name[30]={0};
            Lists.length=Lists.length-1;
            return OK;
        }
    }
    return ERROR;
}
int LocateList(LISTS Lists,char ListName[])
{
    int i=0;
    for(i;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){
            return (i+1);
        }
    }
    return 0;
}
