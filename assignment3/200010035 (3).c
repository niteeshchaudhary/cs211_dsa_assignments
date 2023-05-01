#include <stdio.h>
#include<stdlib.h>
void cntS(int arr[], int n, int tpr)
{
    int outarr[n]; 
    int i=0, count[10] = { 0 };
    for (i = 0; i < n; i++)
        count[(arr[i] / tpr) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        outarr[count[(arr[i] / tpr) % 10] - 1] = arr[i];
        count[(arr[i] / tpr) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = outarr[i];
}
 
void radixsort(int arr[], int n,int d)
{
    for (int ex=1,p = 1; p <= d; ex *= 10,p++)
        cntS(arr, n, ex);
}
 
int main(int argc,char* argv[])
{
	int d;
	if(argc==3){
		d=atoi(argv[2]);
	}
	else if(argc==2){
		printf("NOT VALID. PLEASE ENTER THE FILE NAME AND DIGITS COUNT(output : cosidering 10)");
		d=10;
	}
	else{
		printf("NOT VALID. PLEASE ENTER THE FILE NAME AND DIGITS COUNT");
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
    radixsort(arr, n,d);
    fclose(fp);
	FILE *fw;
	fw = fopen("radix.txt","w");
    for (int i = 0; i < n-1; i++)
        fprintf(fw,"%d\n",arr[i]);
    fprintf(fw,"%d",arr[n-1]);
    fclose(fw);
    
    return 0;
}
