//
// Created by chris on 11/22/2021.
//

#ifndef CODEWARS_FUNCTIONS_H
#define CODEWARS_FUNCTIONS_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define Length(x) sizeof(x)/sizeof(x[0])

struct TreeNode{

    int key;
    struct TreeNode *left,*right;

};

typedef struct {
    int x;
    int y;
}point;

void Insert(struct TreeNode **root,int key);
void InOrder(struct TreeNode *root);
double distance(point a, point b);


#endif //CODEWARS_FUNCTIONS_H
