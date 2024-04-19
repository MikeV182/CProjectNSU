#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

typedef struct BTreeNode {
    int val[MAX + 1], count;
    struct BTreeNode *link[MAX + 1];
} BTreeNode;

struct BTreeNode *root;

struct BTreeNode *addNode(int val, struct BTreeNode *child) {
    struct BTreeNode *newNode;
    newNode = (struct BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child; 

    return newNode;
}

void insertNode(int val, struct BTreeNode *node) {

}

int setValue(int val, int *pval, struct BTreeNode *node, struct BTreeNode **child) {
    if (node == NULL) {
        *pval = val;
        *child = NULL;
        return 1;
    }

    int pos;
    
}

int insert(int val) {
    struct BTreeNode *child;
    int flag, i;
    flag = setValue(val, &i, root, &child);
    if (flag) {
        root = addNode(i, child);
    }
}

int main(void) {
    insert(8);

    return 0;
}