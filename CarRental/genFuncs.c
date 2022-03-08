#include <stdio.h>
#include "genFuncs.h"
#include "common.h"

/*Insertion of a new node onto a binary search tree of a specific node type - The order of the tree will be kept by passing the type's comparing function*/
Node* treeInsert(Node* root, Node* newNode, int(*cmp)(void*,void*)){
    if (!root) { /*Root in this case displays the current node we're passing through, if it is not initalized - we got to the end of this branch in our binary search tree*/
        return newNode; /*And we will return the node we have ment to insert in the first place*/
    }
    /*We will now compare the key of our new node (the str) with the one we check*/
    if (cmp(root->data,newNode->data) >= 0) {
        /*If the new node's str is 'smaller' than the root's str - we will go down right in the tree*/
        root->right = treeInsert(root->right, newNode,cmp);
    }
    else {  /*Else -  the new node's str is 'bigger' or equal (=0) than the root's str - we will go down left in the tree*/
        root->left = treeInsert(root->left, newNode, cmp);
        /*In both the if and the else cases - we will pass the right/left (accordingly) node as our root*/
    }
    return root;
}

/*Will create and initalize a new tree with the relevant functions of it's type*/
Tree* createTree(void*(*getData)(void*),int(*checkData)(void*),int(*cmp)(void*,void*),int(*fre)(Node*)){
    Tree *newTree = ALLOC(Tree,1);
    newTree->root = NULL;
    newTree->elementCount = 0;
    newTree->getData = getData;
    newTree->checkData = checkData;
    newTree->cmp = cmp;
    newTree->fre = fre;
    return newTree;

}

/*Entry of a new element into the tree - This is a binary search tree, so the new element's location matters */
void* addNewNode(Tree* tree){
    Node* newNode;
    newNode = ALLOC(Node,1);
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->data = tree->getData(newNode->data);

    if(tree->checkData(newNode->data) == 1){
        tree->root = treeInsert(tree->root,newNode,tree->cmp); /*Will define the root by the return value of the insertion of our new node onto the binary search tree*/
        printf("added successfully.\n");
        tree->elementCount++;
        return tree;
    }
    printf("details will not be saved.\n");
    return NULL;
}


/*Will find a node based on a specific input (depends of the type of the binary tree) and with the assistance of an associated comparing function of the type
The result will be sent in the format of a linked list - Just a head if there's only one result, and a linked list if otherwise.*/
linkedList *findNode(Node *root, int(*findCmp)(void*,void*) ,void *user_input,linkedList **head) {
    if (!root) {
        return NULL;
    }
    findNode(root->left,findCmp,user_input, head);
    if (findCmp(root->data,user_input) == 0) {
        linkedList *new = ALLOC(linkedList, 1);
        new->data = root->data;
        new->next = NULL;
        if (head != NULL) {
            new->next = *head;
        }
        *head = new;
    }
    findNode(root->right,findCmp, user_input, head);
    return *head;
}

/*Will remove and "reconnect" the tree without the deleted node generically. The function will receive an input according to which a node will be deleted*/
Node* removeNode(Node* root,Tree* tree, const char* user_input,int(*cmpForDelete)(Node*,const char*)){
    if(!root){
        return NULL;
    }

    if(cmpForDelete(root,user_input) != 0) {
            root->left = removeNode(root->left,tree,user_input,cmpForDelete);
            root->right = removeNode(root->right,tree,user_input,cmpForDelete);
            return root;
    }

    if(!(root->left) && !(root->right)) {
        tree->fre(root);
        tree->elementCount--;
        return NULL;
    }
/* Option 2: node has only one child*/
    else if(!(root->left)) {
        Node* temp = root->right;
        tree->fre(root);
        tree->elementCount--;
        return temp;
    }
    else if(!(root->right)) {
        Node* temp = root->left;
        tree->fre(root);
        tree->elementCount--;
        return temp;
    }
    if(!(root->left) && !(root->right)) {
        tree->fre(root);
        tree->elementCount--;
        return NULL;
    }
/* Option 2: node has only one child*/
    else if(!(root->left)) {
        Node* temp = root->right;
        tree->fre(root);
        tree->elementCount--;
        return temp;
    }
    else if(!(root->right)) {
        Node* temp = root->left;
        tree->fre(root);
        tree->elementCount--;
        return temp;
    }

        /* Option 3: node has 2 children*/
    else {
        Node* x = root->right;
        void* temp = root->data;
        Node** xparent = &(root->right);
        /*finding the successor*/
        while(x->left){
            xparent = &(x->left);
            x = x->left;

        }
        root->data = x->data;
        x->data = temp;
        *xparent = (removeNode(x,tree,user_input,cmpForDelete));
    }
    return root;
}

/*Will go over the tree in an inorder manner and will enter all of it's nodes'data onto an input array*/
void treeToArray_helper(Node* root,int* index,void** array){
    if(!root){
        return;
    }
    treeToArray_helper(root->left,index,array);
    array[(*index)++] = root->data;
    treeToArray_helper(root->right,index,array);
}

/*Will call a function that will go over an entire tree and will enter it's values onto an array*/
void* treeToArray(Tree* tree, void** array){
    int i = 0;
    if(!tree){
        printf("no data in tree.\n");
        return NULL;
    }
    treeToArray_helper(tree->root,&i,array);

    return array;

}


/*will print all the suppliers' details in the suppliers list*/
void rec_printAll(Node* root,void(*treePrint)(Node* root) ) {
    if(!root){
        return;
    }
    rec_printAll(root->left,treePrint);
    treePrint(root);
    rec_printAll(root->right,treePrint);
}

/*will print all the tree node's details by calling the type's print method (input of the function) in an inorder manner*/
void printTree(Tree* tree, void(*treePrint)(Node* root)) {
    if(tree->elementCount == 0){
        printf("Nothing to print.\n");
        return;
    }
    rec_printAll(tree->root,treePrint);
}
unsigned long averageKey_rec(Node* root,unsigned long(*averageFunc)(Node*),unsigned long* sum){
    if(!root){
        return 0;
    }
    averageKey_rec(root->left,averageFunc,sum);
    (*sum)+=averageFunc(root);
    averageKey_rec(root->right,averageFunc,sum);
    return *sum;



}
/*Will calculate the average of a type's certain field between all of the tree's nodes*/
unsigned long averageKey(Tree* tree,unsigned long(*averageFunc)(Node*)){
    unsigned long sum = 0;
    if(tree->elementCount == 0){
        printf("no elements to check\n");
        return 0;
    }
    return averageKey_rec(tree-> root,averageFunc,&sum)/tree->elementCount;
}

/*Will go over and free the tree node by node in a post order manner*/
void deleteTree(Tree* tree,Node* root){
    if(!root){
        return;
    }
    deleteTree(tree,root->left);
    deleteTree(tree,root->right);
    tree->fre(root);
    tree->elementCount--;

}

/*Will delete and free a tree by calling a recrusive function*/
void freeTree(Tree* tree){
    if(tree->elementCount == 0){
        printf("nothing to delete.\n");
    }
    else{
        deleteTree(tree,tree->root);
        if(tree->elementCount == 0){
            printf("deleted successfully\n");
        }
        else{
            printf("something went wrong\n");
            }
    }

}



