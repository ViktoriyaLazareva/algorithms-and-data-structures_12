#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
}TreeNode;

TreeNode* treeInsert(TreeNode *t, int data){
    TreeNode* newNode;
    newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    TreeNode *current = t;
    TreeNode *parent = t;
    if (t==NULL){
        t = newNode;
    }else{
        while(current->key != data){
            parent = current;
            if(current->key > data){
                current = current->left;
                if(current == NULL){
                    parent->left = newNode;
                    return t;
                }
            }else{
                current = current->right;
                if (current == NULL){
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}

void printTree(TreeNode* root){
    if (root){
        printf("%d", root->key);
        if(root->left || root->right){
            printf("(");
            if(root->left){
                printTree(root->left);
            }else{
            printf("NULL");
            }
            printf(",");
            if(root->right){
                printTree(root->right);
            }else{
            printf("NULL");
            }
            printf(")");
        }
    }
}

TreeNode* getSuccessor(TreeNode* node){
    TreeNode* current = node->right;
    TreeNode* parent = node;
    TreeNode* s = node;

    while(current != NULL){
        parent = s;
        s = current;
        current = current->left;
    }
    if(s != node->right){
        parent->left = s->right;
        s->right = node->right;
    }
    return s;
}

int delete(TreeNode* root, int key){
    TreeNode* current = root;
    TreeNode* parent = root;
    int isLeftChild = 1;

    while(current->key != key){
        parent = current;
        if(key < current->left){
            current = current->left;
            isLeftChild = 1;
        }else{
        current = current->right;
        isLeftChild = 0;
        }
        if(current == NULL){
            return 0;
        }
    }
    if(current->left == NULL && current->right == NULL){
        if(current == root){
            root = NULL;
        }else if(isLeftChild==1){
        parent->left = NULL;
        }else{
        parent->right = NULL;
        }
    }
    else if(current->right == NULL){
        if(isLeftChild == 1){
            parent->left = current->left;
        }else{
        parent->right = current->left;
        }
    }
    else if(current->left == NULL){
        if(isLeftChild == 1){
            parent->left = current->right;
        }else{
        parent->right = current->right;
        }
    }
    else{
        TreeNode* successor = getSuccessor(current);
    if(current == root){
        root == successor;
    }
    else if(isLeftChild ==1 ){
        parent->left = successor;
    }
    else{
        parent ->right = successor;
    }
    successor->left = current->left;
    }
    return 1;
}

int main()
{
    TreeNode* tree = treeInsert(tree, 10);
    treeInsert(tree, 8);
    treeInsert(tree, 19);
    treeInsert(tree, 5);
    treeInsert(tree, 9);
    treeInsert(tree, 16);
    treeInsert(tree, 21);

    printTree(tree);

    printf("\n");

    return 0;
}

