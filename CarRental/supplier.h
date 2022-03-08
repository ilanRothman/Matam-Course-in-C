#ifndef PROJECT7_SUPPLIER_H
#define PROJECT7_SUPPLIER_H

#define SUPPLIER_NUM 10
#define SUPPLIER_PHONE_NUM 10
#include "genFuncs.h"


typedef struct{
    char* supName;
    char supNum[SUPPLIER_NUM+1];
    char supPhone[SUPPLIER_PHONE_NUM+1];
    int dealsAmount; /*upto 5 digits*/
    unsigned long sumOfDeals; /*10 digits*/

}supplier;

/*creating a generic tree for a supplier by calling the create tree function with the suitable functions for supplier.*/
Tree* createSupTree();

/*calling the generic function for adding a new Node.*/
supplier addNewSupplier(Tree* supTree);

/*Will receive the input from the user for all the struct fields*/
void* getSupplierDetails(void *currentSup);

/*Will check the input gotten from the user based on it's format and it's length
Once a wrong/invalid input is being detected, the user will be notified and the function will return*/
int checkSupplierDetails(void *check);

/*Will compare a two client's sum (existing and new supplier to order the binary tree) of deals and will return 
 1 if the new client's sum is bigger than the existing one's
 0 if they are equal
 -1  if the new client's sum is smaller than the existing one's */
int supCmp(void* sup1, void* newSupplier);

/*freeing memory of a supplier node.*/
int fre_sup(Node* supNode);

/*Will compare the value of a given and a supplier's business number in order to delete it by the given input*/
int cmpForDelete_supplier(Node* root,const char* user_input);

/*Will print the entire suppliers tree by using the generic printTree function*/
void printSupplier(Node* root);

/*Will compare a client's and a given sum of deals and will return 
 1 if the given sum is bigger than the client's
 0 if they are equal
 -1 if the given sum is smaller than the client's */
int findCmp_supplier(void* data,void* sum);

/*Will return a node's sum of deals to be used in the average calculation function*/
unsigned long averageFunc_Sup(Node* root);

/*Will calculate and return the average of all the supplier's sum of deals*/
unsigned long averageOfSupplierMoney(Tree* supTree);

/*will call the free tree function with the tree of suppliers and delete all of it.*/
void deleteAllSuppliers(Tree* supplierTree);

/*Will delete a supplier lient from the supplier binary tree based on the given ID by operating the generic remove function.*/
void deleteSupplier(Tree* supTree);

/*Will return an array of the supplier's number of the three suppliers with largest sum of deals by operating a recursive function*/
int threeGreatestSuppliers(Tree* supTree, char emptyHelper[3][SUPPLIER_NUM+1]);

/*will print a supplier's details.*/
void printSuppliers(Tree* supTree);

#endif
