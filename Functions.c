#include "Functions.h"

#include <math.h>

void Insert(struct TreeNode **root,int key){

    if((*root)==NULL){
        *root= (struct TreeNode *) calloc(1,sizeof(struct TreeNode));
        (*root)->key=key;
        (*root)->left=NULL;
        (*root)->right=NULL;
        return;
    }
    if((*root)->key<key){
        Insert(&(*root)->right,key);
    }
    else
        Insert(&(*root)->left,key);
};

void InOrder(struct TreeNode *root){

    if(root==NULL)
        return;
    printf("%d ",root->key);
    InOrder(root->left);
    InOrder(root->right);
};

double distance(point a, point b){

    double xdiff= pow(a.x-b.x,2);
    double ydiff= pow(a.y-b.y,2);
    return sqrt(xdiff+ydiff);

};