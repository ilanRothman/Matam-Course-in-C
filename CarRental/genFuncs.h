#ifndef PROJECT7_GENFUNCS_H
#define PROJECT7_GENFUNCS_H


typedef struct genNode {
    void* data; /*supplier/car/client*/
    struct genNode* right;
    struct genNode* left;
}Node;

typedef struct Tree {
    Node* root; /*tree root*/
    int elementCount;
    void*(*getData)(void*);
    int(*checkData)(void*);
    int(*cmp)(void*,void*);
    int(*fre)(Node*);

}Tree;

typedef struct nodeList{
    void* data;
    struct nodeList* next;
}linkedList;




/*Will find a node based on a specific input (depends of the type of the binary tree) and with the assistance of an associated comparing function of the type
The result will be sent in the format of a linked list - Just a head if there's only one result, and a linked list if otherwise.*/
linkedList *findNode(Node *root, int(*findCmp)(void*,void*) ,void *user_input,linkedList **head);

/*Insertion of a new node onto a binary search tree of a specific node type - The order of the tree will be kept by passing the type's comparing function*/
Node* treeInsert(Node* root, Node* newNode, int(*cmp)(void*,void*));

/*Will create and initalize a new tree with the relevant functions of it's type*/
Tree* createTree(void*(*getData)(void*),int(*checkData)(void*),int(*cmp)(void*,void*),int(*fre)(Node*));

/*Entry of a new element into the tree - This is a binary search tree, so the new element's location matters */
void* addNewNode(Tree* tree);

/*Will remove and "reconnect" the tree without the deleted node generically. The function will receive an input according to which a node will be deleted*/
Node* removeNode(Node* root,Tree* tree, const char* user_input,int(*cmpForDelete)(Node*,const char*));

/*Will calculate the average of a type's certain field between all of the tree's nodes*/
unsigned long averageKey(Tree* tree,unsigned long(*averageFunc)(Node*));

/*Will call a function that will go over an entire tree and will enter it's values onto an array*/
void* treeToArray(Tree* tree, void** array);

/*will print all the tree node's details by calling the type's print method (input of the function) in an inorder manner*/
void printTree(Tree* tree, void(*treePrint)(Node* root));

/*Will delete and free a tree by calling a recrusive function*/
void freeTree(Tree* tree);

#endif
