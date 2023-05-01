#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
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
	int max,min,cnt,n;
	long long int sum=0;
	if(fscanf(fp,"%d",&n)!=EOF){
		max=n;
	}
	min=max,
  rewind(fp);
	while (fscanf(fp,"%d",&n) != EOF){
		if(max<n) max=n;
		if(min>n) min=n;
		sum+=n;
		cnt++;
	}
  FILE *fw;
	fw = fopen("output.txt","w");
	fprintf(fw,"%d\n%d\n%d\n%lld\n%0.2f\n",cnt,min,max,sum,sum*1.0/cnt);
	return 0;
}
