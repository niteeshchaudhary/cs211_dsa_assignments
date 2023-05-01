#include<stdio.h>
#include<stdlib.h>
void merge(int arr[],int st,int m,int end){
	int i, j, k,n1 = m - st + 1,n2 = end - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[st + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    for(i = 0,j = 0,k = st;i < n1 && j < n2;k++) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
    }
    for(;i < n1;i++,k++) 
        arr[k] = L[i];      
    for (;j < n2;j++,k++) 
        arr[k] = R[j];
}
void mergesrt(int arr[],int st, int end){
	if(st<end){
		int m=(st+end)/2;
		mergesrt(arr,st,m);
		mergesrt(arr,m+1,end);
		merge(arr,st,m,end);
	}
}

int main(int argc,char *argv[]){
	
	if(argc!=2){
	if(argc>2)
		printf("NOT VALID. PLEASE ENTER ONLY ONE FILE NAME");
	else
		printf("NOT VALID. PLEASE ENTER THE FILE NAME");
		exit(1);
	}
	FILE *fp;
	fp = fopen(argv[1],"r");
	if( fp == NULL){
		printf("FILE NOT FOUND");
		exit(2);
	}	
	int n=0,cnt=0,m=0;
	while (fscanf(fp,"%d",&m) != EOF){cnt++;}
	n=cnt;
	int arr[n];
	int i=0;
	rewind(fp);
	while (fscanf(fp,"%d",&m) != EOF){
		arr[i]=m;
		i++;
	}
	mergesrt(arr,0,n-1);
	i=0;
	FILE *fw=fopen("mergesort.txt","w");
	while(i<n-1){
		fprintf(fw,"%d\n",arr[i]);
		i++;
	}
	fprintf(fw,"%d",arr[n-1]);
	fclose(fp);
	fclose(fw);
}
