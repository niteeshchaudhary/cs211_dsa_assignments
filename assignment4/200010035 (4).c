#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
struct btnode
{
    int value;
    struct btnode *l;
    struct btnode *r;
}*root = NULL, *temp = NULL, *t2, *t1;
 
void delete1();
void insert(int num);
void delete();
void inorder(struct btnode *t,int min);
struct btnode* findSuccess(struct btnode *t,int key);
struct btnode* predecessor(struct btnode *t,int key);
void create(int num);
void search(struct btnode *t);
void preorder(struct btnode *t);
void postorder(struct btnode *t);
void search1(struct btnode *t,int data);
int find(struct btnode *t,int data);
int smallest(struct btnode *t);
struct btnode * findMinimum(struct btnode *t);
struct btnode * findMaximum(struct btnode *t);
int largest(struct btnode *t);
 
int flag = 1;
int post=1;
FILE *fp;
void main(int argc,char *argv[])
{
    int ch;
 	if (argc > 2){
      printf("Error : Multiple files were inputed . Please input only one file ");
    }
    else if(argc == 0){
      printf("Error : File name was not inputed");
      exit(0);
    }
    FILE *inp;
    fp= fopen("bst.txt","w");
    inp = fopen(argv[1],"r");
    if(inp == NULL){
        printf("File name doesn't exist .");
        exit(0);
    }
    char chr[100];
    char com[100];
	while (fgets(chr,99,inp)!=NULL){
		chr[strlen(chr)-1]='\0';
        strcpy(com,chr);
        char *token = strtok(com, " ");
        char cmd[100];
        strcpy(cmd,token);
        int ch=0;
        if(strcmp(cmd, "insert")==0){ch=1;}
        else if(strcmp(cmd, "inorder")==0){ch=3;}
        else if(strcmp(cmd, "preorder")==0){ch=4;}
        else if(strcmp(cmd, "postorder")==0){ch=5;}
		else if(strcmp(cmd, "successor")==0){ch=6;}
        else if(strcmp(cmd, "predecessor")==0){ch=7;}
        else if(strcmp(cmd, "minimum")==0){ch=8;}
        else if(strcmp(cmd, "maximum")==0){ch=9;}
        else if(strcmp(cmd, "search")==0){ch=10;}
        switch (ch)
        {
        case 1:    
            insert(atoi(strtok(NULL, " ")));
            break;
        case 3:    
            inorder(root,smallest(root));
            fprintf(fp,"\n");
            break;
        case 4:    
            preorder(root);
            fprintf(fp,"\n");
            break;
        case 5:    
        	post=1;
            postorder(root);
            fprintf(fp,"\n");
            break;
        case 6:{
        		int key=atoi(strtok(NULL, " "));
	        	struct btnode*  prec = findSuccess(root, key);
		        if (prec != NULL) {
		            fprintf(fp,"%d\n",prec->value);
		        }
		        break;
		    }
		case 7:{
        		int key=atoi(strtok(NULL, " "));
	        	struct btnode*  prec = predecessor(root, key);
		        if (prec != NULL) {
		            fprintf(fp,"%d\n",prec->value);
		        }
		        break;
		    }
         case 8:    
         {
         	int s=smallest(root);
         	if(s!=-404){
            	fprintf(fp,"%d\n",smallest(root));
        	}
        	else{
        		fprintf(fp,"\n");
			}
            break;
        }
        case 9:    {
        	int l=smallest(root);
         	if(l!=-404){
            	fprintf(fp,"%d\n",largest(root));
            }
            else{
        		fprintf(fp,"\n");
			}
            break;
        }
        case 10:{
        	int k=atoi(strtok(NULL, " "));
        	int r=find(root,k);
        	if(r==1){
        		 fprintf(fp,"%d found\n",k);
			}
			else{
				fprintf(fp,"%d not found\n",k);
			}
			break;
		}    
        case 0:    
            exit(0);
        default :     
            printf("Wrong choice, Please enter correct choice  ");
            break;    
        }   
    }
    fclose(inp);
    fclose(fp);
}
 
 
struct btnode* findSuccess(struct btnode *t, int key)
{
    struct btnode* succ = NULL;
 	 if (!t) {
        	fprintf(fp,"%d does not exist\n",key);
            return NULL;
        }
    while (1)
    {
        if (key < t->value)
        {
            succ = t;
            t = t->l;
        }
        else if (key > t->value) {
            t = t->r;
        }
        else {
            if (t->r) {
                succ = findMinimum(t->r);
            }
            break;
        }
        if (!t) {
        	fprintf(fp,"%d does not exist\n",key);
            return NULL;
        }
    }
    if(!succ){
        		fprintf(fp,"successor of %d does not exist\n",key);
			}
    return succ;
}

/* To insert a node in the tree */
struct btnode* predecessor(struct btnode *t,int key) {
   struct btnode* pred = NULL;
    if (!t) {
        	fprintf(fp,"%d does not exist\n",key);
            return NULL;
        }
    while (1)
    {
        // if the given key is less than the root node, visit the left subtree
        if (key < t->value)
        {
            t = t->l;
        }
        // if the given key is more than the root node, visit the right subtree
        else if (key > t->value) {
        	pred = t;
            t = t->r;
        }
 
        // if a node with the desired value is found, the successor is the minimum
        // value node in its right subtree (if any)
        else {
        	
            if (t->l) {
                pred = findMaximum(t->l);
            }
            break;
        }
 
        // if the key doesn't exist in the binary tree
        if (!t) {
        	fprintf(fp,"%d does not exist\n",key);
            return NULL;
        }
    }
    if(!pred){
        		fprintf(fp,"predecessor of %d does not exist\n",key);
			}
    return pred;
}

void insert(int num)
{
    create(num);
    if (root == NULL) {
        root = temp;
        fprintf(fp,"%d inserted\n",num);
    }
    else    
        search(root);    
}
 
/* To create a node */
void create(int num)
{
    temp = (struct btnode *)malloc(1*sizeof(struct btnode));
    temp->value = num;
    temp->l = temp->r = NULL;
}
 
/* Function to search the appropriate position to insert the new node */
void search(struct btnode *t)
{
    if ((temp->value > t->value) && (t->r != NULL))      /* value more than root node value insert at right */
        search(t->r);
    else if ((temp->value > t->value) && (t->r == NULL)){
        t->r = temp;
        fprintf(fp,"%d inserted\n",temp->value);
    }
    else if ((temp->value < t->value) && (t->l != NULL))    /* value less than root node value insert at left */
        search(t->l);
    else if ((temp->value < t->value) && (t->l == NULL))
      {
		  t->l = temp;
		  fprintf(fp,"%d inserted\n",temp->value);
		}
}
 
/* recursive function to perform inorder traversal of tree */
void inorder(struct btnode *t,int min)
{
    if (root == NULL)
    {
        
        return;
    }
    if (t->l != NULL)    
        inorder(t->l,min);
    if(t->value==min){
    	fprintf(fp,"%d", t->value);
	}else
   		fprintf(fp," %d", t->value);
    if (t->r != NULL)    
        inorder(t->r,min);
}
 
/* To find the preorder traversal */
void preorder(struct btnode *t)
{
    if (root == NULL)
    {
       
        return;
    }
    if(t==root){
    	fprintf(fp,"%d", t->value);
	}else
   		fprintf(fp," %d", t->value);
    if (t->l != NULL)    
        preorder(t->l);
    if (t->r != NULL)    
        preorder(t->r);
}
 
/* To find the postorder traversal */

void postorder(struct btnode *t)
{
    if (root == NULL)
    {
       
        return;
    }
    if (t->l != NULL) 
        postorder(t->l);
    if (t->r != NULL) 
        postorder(t->r);
    if(post==1){
    	fprintf(fp,"%d", t->value);
    	post=0;
	}else
   		fprintf(fp," %d", t->value);
}
int find(struct btnode *t, int data)
{
    // Base Cases: root is null or key is present at root
    if(t == NULL){
    	return 0;
	}
    if ( t->value == data)
       return 1;
    
    // Key is greater than root's key
    if (t->value < data)
       return find(t->r, data);
 
    // Key is smaller than root's key
    return find(t->l, data);
}
/* Search for the appropriate position to insert the new node */
void search1(struct btnode *t, int data)
{
	if (t==NULL){
		return;
	}
    if ((data>t->value))
    {
        t1 = t;
        search1(t->r, data);
    }
    else if ((data < t->value))
    {
        t1 = t;
        search1(t->l, data);
    }
    else if ((data==t->value))
    {
     //   delete1(t);
    }
}

 
/* To find the smallest element in the right sub tree */
struct btnode * findMinimum(struct btnode *t)
{
    while (t->l) {
        t = t->l;
    }
	return t;
}
struct btnode * findMaximum(struct btnode *t)
{
    while (t->r) {
        t = t->r;
    }
	return t;
}

int smallest(struct btnode *t)
{
	if(t==NULL){
		return -404;
	}
    t2 = t;
    if (t->l != NULL)
    {
        t2 = t;
        return(smallest(t->l));
    }
    else    {
        return (t->value);
    }
}
 
int largest(struct btnode *t)
{
	if(t==NULL){
		return -404;
	}
    if (t->r != NULL)
    {
        t2 = t;
        return(largest(t->r));
    }
    else  {
        return(t->value);
    }
}
