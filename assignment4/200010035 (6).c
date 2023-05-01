#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE* fo=NULL;
FILE* fw=NULL;
struct Node{
	int data;
	struct Node* next;
};
struct lkls{
	struct Node* head;
};
struct Queue{
	struct Node* head;
};
struct mp_col{
	int col;
};
struct Node* create(int data){
	struct Node* nw=(struct Node*)malloc(sizeof(struct Node));
	nw->data=data;
	nw->next=NULL;
	return nw;
} 
void Enqueue(struct Node** head,int data)
{
	struct Node* nw=create(data);
	struct Node* temp=*head;
	if(*head==NULL){
		*head=nw;
		return;
	}
	while(temp->next!=NULL)
	{
		temp=temp->next;
	}
	temp->next=nw;
}
int Dequeue(struct Node** head)
{
	struct Node* temp=*head;
	if(*head==NULL){
		return -1;
	}
	int k=temp->data;
	*head=temp->next;
	return k;
}
int isQempty(struct Node* head){
	if(head==NULL){
		return 1;
	}
	return 0;
}

void bfs(int vtx,int edg) //adgencylist
{
	struct lkls* lk=(struct lkls *)malloc(vtx*sizeof(struct lkls));
	struct mp_col vtc[vtx];
	int dstore[vtx];
	fw=fopen("sd.txt","w");
	for(int i=0;i<vtx;i++){
		lk[i].head=NULL;
		dstore[i]=-1;
		vtc[i].col=0;
	}
	int x=-2,y=-2,cnt=0;
	while( cnt<edg && fscanf(fo,"%d %d",&x,&y)){
		Enqueue(&lk[x].head,y);
		Enqueue(&lk[y].head,x);
		cnt++;
	}
	struct Queue q;
	q.head=NULL;
	Enqueue(&q.head,0);
	vtc[0].col=1;
	dstore[0]=0;
	while(!isQempty(q.head))
	{
		int k=Dequeue(&q.head);
		struct Node * temp=lk[k].head;
		while(temp!=NULL && vtc[k].col!=2){
			if(vtc[temp->data].col==0){
				Enqueue(&q.head,temp->data);
				vtc[temp->data].col=1;
				dstore[temp->data]=dstore[k]+1;
			}
			temp=temp->next;
		}
		vtc[k].col=2;
	}
	for(int i=0;i<vtx;i++){
	//	printf("%d -> %d\t",i,dstore[i]);
		fprintf(fw,"%d\n",dstore[i]);
	}
	fclose(fw);
}
void bfs2(int vtx,int edg) //matrix
{
	int** map_nd=(int **)malloc(vtx*sizeof(int*));
	int dstore[vtx];
	struct mp_col vtc[vtx];
	fw=fopen("sd.txt","w");
	for(int i=0;i<vtx;i++){
		vtc[i].col=0;
		dstore[i]=-1;
		map_nd[i]=(int *)malloc(vtx*sizeof(int));
		for(int j=0;j<vtx;j++){
			map_nd[i][j]=0;
		}
	}
	int x=-2,y=-2,cnt=0;
	while( cnt<edg && fscanf(fo,"%d %d",&x,&y)){
		map_nd[x][y]=1;
		map_nd[y][x]=1;
		cnt++;
	}
	struct Queue q;
	q.head=NULL;
	Enqueue(&q.head,0);
	vtc[0].col=1;
	dstore[0]=0;
	while(!isQempty(q.head))
	{
		int k=Dequeue(&q.head);
		for(int i=0;i<vtx && vtc[k].col!=2;i++){
			if(map_nd[k][i]==1 && vtc[i].col==0){
				Enqueue(&q.head,i);
				vtc[i].col=1;
				dstore[i]=dstore[k]+1;
			}
		}
		vtc[k].col=2;
	}
	for(int i=0;i<vtx;i++){
	//	printf("%d -> %d\t",i,dstore[i]);
		fprintf(fw,"%d\n",dstore[i]);
	}
	fclose(fw);
}

int main(int argc,char* argv[])
{
	if(argc!=2){
		printf("incorrect Number of arguments");
		exit(0);
	}
	fo=fopen(argv[1],"r");
	if(!fo){
		printf("file do not exist or error reading it");
		exit(0);
	}
	char ch[100];
	int vtx=0,edg=0;
	if(fscanf(fo,"%d %d",&vtx,&edg)){
	}else{
		printf("unable to read");
		exit(0);
	}
	bfs(vtx,edg);
	fclose(fo);
	return 0;
}


