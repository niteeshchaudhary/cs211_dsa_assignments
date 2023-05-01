#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *fq=NULL,*fwd=NULL;
struct Node{
	char ch[100];
	struct Node * next;
};
struct link{
	struct Node* head;
};
struct hex{
	struct link lk;	
};

struct Node* create(char data[])
{
	struct Node* n=(struct Node*)malloc(sizeof(struct Node));
	strcpy(n->ch,data);
	n->next=NULL;
	return n;
}
struct Node* insert_b(struct Node* head,char data[])
{
	struct Node* n=create(data);
	if(head==NULL){
		return n;
	}
	n->next=head;
	return n;
}

void data_hex(struct hex  tb[],int size){
	char chr[100];
	while (fgets(chr,99,fwd)!=NULL){
		int sm=0;
		char store[100];
		chr[strlen(chr)-1]='\0';
		strcpy(store,chr);
		for(int i=0;i<strlen(store);i++)
		{
			sm+=(int)chr[i];
		}
		tb[sm%size].lk.head=insert_b(tb[sm%size].lk.head,store);
	}
}
int checkhex(char w1[],char w2[])
{
	int ln1=strlen(w1);
	int ln2=strlen(w2);
	int wr1[256],wr2[256];
	for(int i=0;i<256;i++){
		wr1[i]=0;
		wr2[i]=0;
	}
	if(ln1!=ln2){
		return 0;
	}
	for(int i=0; i<ln1;i++){
		wr1[w1[i]]++;
		wr2[w2[i]]++;
	}
	for (int i = 0; i < 256; i++)
    {
        if (wr1[i] != wr2[i])
            return 0;
    }
    return 1;
}
void printhex(struct hex tb[],int size)
{
	char inpq[100];
	FILE* fw=fopen("anagrams.txt","w");
	while (fgets(inpq,99,fq)!=NULL){
		inpq[strlen(inpq)-1]='\0';
		int sm=0;
		for(int i=0;i<strlen(inpq);i++)
		{
			sm+=(int)inpq[i];
		}
		struct Node* temp=tb[sm%size].lk.head;
		int prt=0;
		if(temp!=NULL){
			while(temp->next!=NULL){
				if(checkhex(inpq,temp->ch)){
					if(prt==0){
						fprintf(fw,"%s",temp->ch);
						prt=1;
					}
					else{
						fprintf(fw," %s",temp->ch);
					}
				}
				temp=temp->next;
			}
			if(checkhex(inpq,temp->ch))
				if(prt==0){
						fprintf(fw,"%s",temp->ch);
						prt=1;
					}
					else{
						fprintf(fw," %s",temp->ch);
					}
			fprintf(fw,"\n");
		}
		else{
				fprintf(fw,"\n");
		}
	}
}
int main(int argc,char *argv[])
{
	int hex_size;
	if(argc==4){
		hex_size=atoi(argv[2]);
	}
	else if(4>argc>=1){
		printf("NOT VALID. PLEASE ENTER THE Query FILE, size of the hash table AND words file name");
	}
	else{
		printf("NOT VALID. PLEASE ENTER THE FILE NAME AND DIGITS COUNT");
		exit(1);
	}
	
	fq = fopen(argv[3],"r");
	fwd = fopen(argv[1],"r");
	if(fq == NULL ||fwd==NULL ){
		printf("FILE are Missing");
		exit(2);
	}	
	struct hex tb[hex_size];
	for(int i=0;i<hex_size;i++)
	{
		tb[i].lk.head=NULL;
	}
	data_hex(tb,hex_size);
	printhex(tb,hex_size);
	//while (fgets(ch,99,reader)!=NULL){
	return 0;
}
