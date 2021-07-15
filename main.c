#include <stdio.h>
#include <stdlib.h>
#include <String.h>
typedef struct{

    char x[50];
    struct Node *left,*right;

}Node;

Node * newNode(char y[]){
    Node *n=malloc(sizeof(Node));
    strcpy(n->x,y);
    n->left=NULL;
    n->right=NULL;
    return n;

}

Node * insert(Node *root,char y[]){
    if(root==NULL)
     root= newNode(y);
    else if(strcasecmp(root,y)<0)
        root->right=insert(root->right,y);
    else if(strcasecmp(root,y)>0)
        root->left=insert(root->left,y);

        return root;
}

int max(int x, int y){
if(x>y) return x;
return y;
}
int height(Node *root){
if(root==NULL)
    return -1;
else
    return 1+max(height(root->left),height(root->right));
}
int count(Node*root){
    if(root==NULL)
        return 0;
    else
        return 1+ count(root->left)+count(root->right);
}
Node* findMin(Node*root)
{
    if(root==NULL)
        return NULL;
    if(root->left!=NULL)
        return findMin(root->left);
    else
        return root;
}
Node* findMax(Node*root)
{
    if(root==NULL)
        return NULL;
    if(root->right!=NULL)
        return findMax(root->right);
    else
        return root;
}

void getSuggestions(Node *root,char y[]){
Node*temp=root;
Node*target=NULL;
Node*succ=NULL;
Node*pre=NULL;
while(temp!=NULL){
        target=temp;
          if(strcasecmp(y,temp->x)>0)
          temp=temp->right;
        else if(strcasecmp(y,temp->x)<0)
            temp=temp->left;
}
temp=root;

if(target->right !=NULL)
    succ=findMin(target->right);
else if(target->right ==NULL){
    while(temp!=target){
      if(strcasecmp(target,temp->x)<0){
      succ=temp;
      temp=temp->left;
      }
      else if(strcasecmp(target,temp->x)>0)
        temp=temp->right;

    }
}
temp=root;

if(target->left !=NULL)
    pre=findMax(target->left);
else if(target->left ==NULL){
    while(temp!=target){
      if(strcasecmp(target,temp->x)>0){
      pre=temp;
      temp=temp->right;
      }
      else if(strcasecmp(target,temp->x)<0)
        temp=temp->left;

    }
}



printf("%s - Incorrect, Suggestions: %s %s %s\n",y,target->x,succ->x,pre->x);




}





Node* searchRec(Node* root,char y[])
{

    if(root==NULL)
        return NULL;
    else if(strcasecmp(y,root->x)==0)
        printf("%s - Correct\n",y);
    else if(strcasecmp(y,root->x)<0)
        return searchRec(root->left,y);
    else
        return searchRec(root->right,y);

}




Node * readFile(char *filename)
{

    int fileSize;
      Node *root=NULL;

    FILE *f=fopen(filename,"r");
    if(f==NULL) return ;


        fseek(f,0,SEEK_END);
        fileSize=ftell(f);
        rewind(f);

    char read[fileSize];



    while(!feof(f))
    {
         fscanf(f, "%s",read);
        root=insert(root,read);
    }
    fclose(f);


return root;

}


void inOrder(Node* root)
{
    if(root)
    {
        inOrder(root->left);
        printf("%s\n",root->x);
        inOrder(root->right);
    }
}






int main()
{
    char x[100];
    char *tok;
    Node*check;
    Node *root=readFile("EN-US-Dictionary.txt");
    printf("Dictionary Loaded Successfully\n");
    printf("...................................\n");
    printf("count=%d\n",count(root));
    printf("...................................\n");
    printf("Height=%d\n",height(root));
    printf("...................................\n");
    printf("Enter a sentence :\n");
    gets(x);
    tok = strtok(x," ");
  while(tok !=NULL)
  {

    check=searchRec(root,tok);
    if(check==NULL)
        getSuggestions(root,tok);
    tok= strtok(NULL," ");
  }


    return 0;
}
