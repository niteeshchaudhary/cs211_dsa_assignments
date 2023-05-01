#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
struct Node{
    int des,wt;
    struct Node* next;
};

struct lkls{
	struct Node* head;
	int d;
	int pi;
	int vis;
}; 
struct Alist{    
   struct Node *head;
};
struct Graph{
    int Vtx;
    struct Alist* arr;
};
struct MinNode{
    int  v,dist;
};

struct vertex{
	struct Node* next;
	int info;
	int w;
	struct Node* prev;
};
struct MinHeap{
    int sz,cap,*pos;   
    struct MinNode **arr;
};
struct mp_col{
	int col;
};

typedef struct Node Node;
typedef struct Alist Alist;
typedef struct Graph Graph;
typedef struct MinNode MinNode;
typedef struct MinHeap MinHeap;

void swapMinHeapNode(MinNode** a,MinNode** b);
void minHeapify(int idx,MinHeap* minHeap);
int isEmpty(MinHeap* minHeap);
MinNode* extractMin(MinHeap* minHeap);
void decreaseKey( int v, int dist,MinHeap* minHeap);
int isInMinHeap(MinHeap *minHeap, int v);
void printArr(int dist[], int n);
void dijkstra(Graph* graph, int src);
void process(int dist[],Graph* graph,MinHeap* minHeap);
void Node_initialise(int dist[],int V,MinHeap* minHeap);

void swapMinHeapNode(MinNode** a,MinNode** b){
    MinNode* t = *a;
    *a = *b;
    *b = t;
}

struct Node* create(int data)
{
	struct Node* n=(struct Node*)malloc(sizeof(struct Node));
	n->des=data;
	n->next=NULL;
	return n;
}

Node* createNode(int des, int wt){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->des = des;
    newNode->wt = wt;
    return newNode;
}
void fillgraph(Graph* graph){
	int i=0;
    while(i < graph->Vtx){
        graph->arr[i].head = NULL;
        i++;
    }
}
Graph* createGraph(int V){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->arr = (Alist*)malloc(V * sizeof(Alist));
    graph->Vtx = V;
    fillgraph(graph);
    return graph;
}
struct Node* insert_b(struct Node* head,int data)
{
	struct Node* n=create(data);
	if(head==NULL){
		return n;
	}
	n->next=head;
	return n;
}

MinHeap* createMinHeap(int capacity){
    MinHeap* minHeap =(MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->sz = 0;
    minHeap->cap = capacity;
    minHeap->arr =(MinNode**)malloc(capacity*sizeof(MinNode*));
    return minHeap;
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

void Edge(int src, int des, int wt,Graph* graph){
    Node* newNode = createNode(des, wt);
    newNode->next = graph->arr[src].head;
    graph->arr[src].head = newNode;
}
struct Node* insert_etail(struct Node* tail,int data)
{
	struct Node* n=create(data);
	tail->next=n;
	return n;
}
struct Node* insert_e(struct Node* head,int data)
{
	struct Node* n=create(data);
	struct Node* temp=head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=n;
	return n;
}

MinNode* MinHeapNode(int v, int dist){
    MinNode* minHeapNode = (MinNode*)malloc(sizeof(MinNode));
    minHeapNode->dist = dist;
	minHeapNode->v = v;
    return minHeapNode;
}
struct Node* insert_p(struct Node* head,int pos,int data)
{
	struct Node* n=create(data);
	struct Node* temp=head;
	for(int i=1;i<pos && temp->next!=NULL;i++){
		temp=temp->next;
	}
	n->next=temp->next;
	temp->next=n;
	return head;
}

void dijkstra(Graph* graph, int src){
    int V = graph->Vtx;
    int dist[V];    
    MinHeap* minHeap = createMinHeap(V);
    Node_initialise(dist,V,minHeap);
    minHeap->arr[src] = MinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(src, dist[src],minHeap);
    minHeap->sz = V;
   	process(dist,graph,minHeap);
    printArr(dist, V);
}

int del_b(struct Node** head)
{
	struct Node* temp=*head;
	if(temp==NULL){
		printf("\nunderflow..\n");
		return -1;
	}
	int pv= temp->des;
	*head=temp->next;
	return pv;
}

void solve(char arg1[],int sr){
	int x,y,z,mx=-INT_MAX,cnt=0;
	FILE* fo=fopen(arg1,"r");
	int source=sr;
	if(!fo){printf("file do not exist or error reading it");exit(0);}
    while(fscanf(fo,"%d %d %d",&x,&y,&z)!=EOF){
		if(mx<y){mx=y;}
		if(mx<x){mx=x;}
		cnt++;
	}
	int V = mx+1;
    Graph* graph = createGraph(V);
    rewind(fo); 
	while(fscanf(fo,"%d %d %d",&x,&y,&z)!=EOF){Edge(x, y, z,graph);}
    dijkstra(graph, source);
	fclose(fo);
}
int main(int argc,char *argv[]){
	if(argc!=3){ printf("incorrect Number of arguments");exit(0);}
	solve(argv[1],atoi(argv[2]));
    return 0;
}
void minHeapify(int idx,MinHeap* minHeap){
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 	
	 if (right < minHeap->sz && minHeap->arr[right]->dist < minHeap->arr[smallest]->dist )
      smallest = right;
    if (left < minHeap->sz && minHeap->arr[left]->dist < minHeap->arr[smallest]->dist)
		smallest = left;
    if (smallest != idx)
    {
        MinNode *smallestNode = minHeap->arr[smallest];
        MinNode *idxNode = minHeap->arr[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&minHeap->arr[smallest],&minHeap->arr[idx]); 
        minHeapify(smallest,minHeap);
    }
}
int isEmpty(MinHeap* minHeap){
    if(minHeap->sz == 0){
    	return 1;
	}
	return 0;
}
MinNode* extractMin(MinHeap* minHeap){
    if (isEmpty(minHeap))
        return NULL;
    MinNode* root = minHeap->arr[0];
    MinNode* lastNode = minHeap->arr[minHeap->sz - 1];
    minHeap->pos[root->v] = minHeap->sz-1;
    minHeap->arr[0] = lastNode;
    minHeap->pos[lastNode->v] = 0;
    (minHeap->sz)--;
    minHeapify(0,minHeap);
    return root;
}
void decreaseKey(int v, int dist, MinHeap* minHeap){
    int i = minHeap->pos[v];
    minHeap->arr[i]->dist = dist;
    while (i && minHeap->arr[i]->dist < minHeap->arr[(i - 1) / 2]->dist){
        minHeap->pos[minHeap->arr[i]->v] =(i-1)/2;
        minHeap->pos[minHeap->arr[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int isInMinHeap(MinHeap *minHeap, int v){
   if (minHeap->pos[v] < minHeap->sz)
     return 1;
   return 0;
}

void toposort(int vtx,int edg) //matrix
{
	int** map_nd=(int **)malloc(vtx*sizeof(int*));
	int dprev[vtx];
	struct mp_col vtc[vtx];
	FILE* fw=fopen("ts.txt","w");
	for(int i=0;i<vtx;i++){
		vtc[i].col=0;
		dprev[i]=0;
		map_nd[i]=(int *)malloc(vtx*sizeof(int));
		for(int j=0;j<vtx;j++){
			map_nd[i][j]=-1;
		}
	}
	FILE* fo=fw=fopen("dijkstra.txt","r");
	int x=-2,y=-2,cnt=0,z=-2;
	while( cnt<edg && fscanf(fo,"%d %d %d",&x,&y,&z)){
			map_nd[x][y]=1;
			dprev[y]+=1;
		cnt++;
	}
	
	for(int nk=vtx-1;nk>=0;nk--){
		int fls=0;
		for(int ck=0;ck<vtx;ck++){
			if(map_nd[ck][nk]==1){
				fls=1;
				break;
			}
		}
		if(fls==1){continue;}
		
		if(vtc[nk].col!=2 && dprev[nk]<2){
			vtc[nk].col=1;
		}
	}
	fclose(fw);
}

void dfs2(int vtx,int edg) //adgencylist Not Working just to see all adjency list
{
	struct lkls* lk=(struct lkls *)malloc(vtx*sizeof(struct lkls));
	struct mp_col vtc[vtx];
	int dprev[vtx];
	FILE *fw=fopen("sd2.txt","w");
	for(int i=0;i<vtx;i++){
		lk[i].head=NULL;
		dprev[i]=0;
		vtc[i].col=0;
	}
	int x=-2,y=-2,z=-2,cnt=0;
	FILE *fo=fopen("sd2.txt","r");
	while( cnt<edg && fscanf(fo,"%d %d %d",&x,&y,&z)!=EOF){
			Enqueue(&lk[x].head,y);
			dprev[y]+=1;
		cnt++;
	}
	for(int k=0;k<vtx;k++){
	    struct Node * temp=lk[k].head;
	    fprintf(fw,"%d ",k);
		while(temp!=NULL){
			fprintf(fw," %d ",temp->des);
			temp=temp->next;
		}
		fprintf(fw,"\n");	
	}
	fclose(fw);
}

void printArr(int dist[], int n){
	int vis[n];
	FILE* fw=fopen("dijkstra.txt","w");
	for (int i = 0; i < n; ++i){
		vis[i]=0;
	}
    for (int i = 0; i < n; ++i){
    	if(dist[i]==INT_MAX){
    		dist[i]=-1;
    		fprintf(fw,"%d %d\n", i, dist[i]);
    		vis[i]=1;
		}
    }
    for (int i = 0; i < n; ++i){
		if(vis[i]==0){
			fprintf(fw,"%d %d\n", i, dist[i]);
			vis[i]=1;
		}
	}
	fclose(fw);
}
void Node_initialise(int dist[],int V,MinHeap* minHeap){
	for (int v = 0; v < V; ++v){
        dist[v] = INT_MAX;
        minHeap->arr[v] = MinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
}
void process(int dist[], Graph* graph, MinHeap* minHeap){
	 while (!isEmpty(minHeap)){
        MinNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        struct Node* pCrawl = graph->arr[u].head;
        while (pCrawl != NULL){
            int v = pCrawl->des;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->wt + dist[u] < dist[v]){
                dist[v] = dist[u] + pCrawl->wt;
                decreaseKey(v, dist[v],minHeap);
            }
            pCrawl = pCrawl->next;
        }
    }
}
