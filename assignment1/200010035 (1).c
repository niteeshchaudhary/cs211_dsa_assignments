#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *fp=NULL;
struct Stack{
	int *st;
	int top;
	int size;	
	char name;
};
void push(struct Stack *st,int x);
void fillup(struct Stack *st,int n);
int pop(struct Stack *st);
void check(struct Stack *st);

void fillup(struct Stack *st,int n){
	while(n--){
		push(st,n+1);
	}
}
void push(struct Stack *st,int x)
{
    if(st->top>=st->size-1)
    {
        printf("\n   STACK is Over Flow..    "); 
    }
    else
    {
    	fprintf(fp,"Push disk %d to Stack %c\n",x,st->name);
    	//printf("Push disk %d to Stack %c\n",x,st->name);
        st->top++;
        st->st[st->top]=x;
    }
}
int pop(struct Stack *st)
{
    if(st->top<=-1)
    {
        printf("\n   Stack is Under Flow...    ");
    }
    else
    {
    	int temp=st->st[st->top];
		fprintf(fp,"Pop disk %d from Stack %c\n",st->st[st->top],st->name);
		//printf("Pop disk %d from Stack %c\n",st->st[st->top],st->name);
        st->top--;
        return temp;
    }
    return 0;
}
void toh(int n,struct Stack *from_st,struct Stack *dest_st,struct Stack *aux_st){
	if(n>0){	
		toh(n-1,from_st,aux_st,dest_st);
		push(dest_st,pop(from_st));
		toh(n-1,aux_st,dest_st,from_st);
	}
}
int main(int argc,char *argv[])
{
	int n=15;	
	if(argc==2){
		n=atoi(argv[1]);
		if(n<1){
			scanf("%d",&n);
		}
	}
	else{
		scanf("%d",&n);
	}
	struct Stack st_a,st_b,st_c;	
	st_a.st=(int *)malloc(n*sizeof(int));
	st_a.size=n;
	st_a.name='A';
	st_a.top=-1;
	st_b.st=(int *)malloc(n*sizeof(int));
	st_b.size=n;
	st_b.name='B';
	st_b.top=-1;
	st_c.st=(int *)malloc(n*sizeof(int));
	st_c.size=n;
	st_c.name='C';
	st_c.top=-1;
	fp=fopen("toh.txt","w");
	fillup(&st_a,n);
	toh(n,&st_a,&st_c,&st_b);
	return 0;
}





