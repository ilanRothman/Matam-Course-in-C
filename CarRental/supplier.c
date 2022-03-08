#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "supplier.h"
#include "common.h"


/*creating a generic tree for a supplier by calling the create tree function with the suitable functions for supplier.*/
Tree* createSupTree(){
    return createTree(&getSupplierDetails,&checkSupplierDetails,&supCmp,&fre_sup);
}

/*Will calculate and return the average of all the suppliers' sum of deals*/
unsigned long averageOfSupplierMoney(Tree* supTree){
    return averageKey(supTree,&averageFunc_Sup);
}

/*calling the generic function for adding a new Node.*/
supplier addNewSupplier(Tree* supTree){
    return *(supplier*)addNewNode(supTree);
}


/*calling the generic function for adding a new Node.*/
/*Will return an array of the supplier's number of the three suppliers with largest sum of deals by operating a recursive function*/
int threeGreatestSuppliers(Tree* supTree, char emptyHelper[3][SUPPLIER_NUM+1]){
    supplier** supArray;
    supArray = ALLOC(supplier*,supTree->elementCount);
    treeToArray(supTree, (void **) supArray);
    strcpy(emptyHelper[2], supArray[2]->supNum);
    strcpy(emptyHelper[0], supArray[0]->supNum);
    strcpy(emptyHelper[1], supArray[1]->supNum);
    FREE(supArray);
    return 1;
}


/*Will receive the input from the user for all the struct fields*/
void* getSupplierDetails(void *currentSup) {
    char inputString[300];
    supplier* newSupplier = (supplier*)currentSup;
    newSupplier = ALLOC(supplier,1);
    flusher();

    printf("Enter the supplier number, 10 digits:\n");
    scanf(" %s", inputString);
    if (strlen(inputString) > SUPPLIER_NUM) {
        strcpy(newSupplier->supNum, "long");
    } else {
        inputString[SUPPLIER_NUM] = '\0';
        strcpy(newSupplier->supNum, inputString);
    }

    flusher();

    printf("Enter the supplier name:\n");
    scanf(" %s", inputString);
    newSupplier->supName = (char *) checked_malloc(strlen(inputString));
    strcpy(newSupplier->supName, inputString);

    flusher();

    printf("Enter the supplier phone number: 10 digits\n");
    scanf(" %s", inputString);
    if (strlen(inputString) > SUPPLIER_PHONE_NUM + 1) {
        strcpy(newSupplier->supPhone, "long");
    } else {
        inputString[SUPPLIER_PHONE_NUM] = '\0';
        strcpy(newSupplier->supPhone, inputString);
    }
    flusher();
    printf("Enter the supplier's amount of deals: 5 digits\n");
    scanf(" %d", &newSupplier->dealsAmount);

    flusher();
    printf("Enter the supplier's sum of deals: 10 digits\n");
    scanf(" %lu", &newSupplier->sumOfDeals);
    currentSup = newSupplier;
    return currentSup;
}

/*Will check the input gotten from the user based on it's format and it's length
Once a wrong/invalid input is being detected, the user will be notified and the function will return*/
int checkSupplierDetails(void *check) {
    int i = 0;
    supplier* newSupplier = (supplier*)check;
    while (newSupplier->supName[i] != '\0') {
        if ((isdigit(newSupplier->supName[i])) != 0) {
            printf("supplier name can't have numbers\n");
            return 0;
        }
        i++;
    }

    if (strcmp(newSupplier->supNum, "long") == 0) {
        printf("supplier number to long.");
        return 0;
    }

    if (strlen(newSupplier->supNum) == (SUPPLIER_NUM + 1)) {
        printf("supplier number not 10 digits\n");
        return 0;
    }

    i = 0;

    while (newSupplier->supNum[i] != '\0') {
        if (!((newSupplier->supNum[i]) >= '0' && (newSupplier->supNum[i]) <= '9')) {
            printf("supplier number must be only with digits\n");
            return 0;
        }
        i++;
    }

    if (strcmp(newSupplier->supPhone, "long") == 0) {
        printf("supplier phone number to long.");
        return 0;
    }
    if (strlen(newSupplier->supPhone) != (SUPPLIER_PHONE_NUM)) {
        printf("supplier phone number not 10 digits\n");
        return 0;
    }
    i = 0;

    while (newSupplier->supPhone[i] != '\0') {
        if ((newSupplier->supPhone[i]) < 48 || (newSupplier->supPhone[i]) > 57) {
            printf("supplier phone number must be only with digits\n");
            return 0;
        }
        i++;
    }
    if ((newSupplier->sumOfDeals > 9999999999.0) || (newSupplier->sumOfDeals < 1000000000.0)) {
        printf("sum of deals should be 10 digits\n");
        return 0;
    }
    if (newSupplier->dealsAmount > 99999 || newSupplier->dealsAmount < 10000) {
        printf("deals amount should be 5 digits\n");
        return 0;
    }


    return 1;

}

/*Will return a node's sum of deals to be used in the average calculation function*/
unsigned long averageFunc_Sup(Node* root){
    supplier * supplier1 = (supplier*)root->data;
    return  supplier1->sumOfDeals;


}

/*Will compare a client's and a given sum of deals and will return 
 1 if the given sum is bigger than the client's
 0 if they are equal
 -1 if the given sum is smaller than the client's */
int findCmp_supplier(void* data,void* sum){
    supplier * supplier1 = (supplier*)data;
    if (supplier1->sumOfDeals < *(unsigned long*)sum){
        return -1;
    } else if (supplier1->sumOfDeals > *(unsigned long*)sum){
        return 1;
    }
    return 0; /*in case they have the same value*/
}

/*Will compare a two client's sum (existing and new supplier to order the binary tree) of deals and will return 
 1 if the new client's sum is bigger than the existing one's
 0 if they are equal
 -1  if the new client's sum is smaller than the existing one's */
int supCmp(void* sup1, void* newSupplier){
    supplier* n_sup1 = (supplier*)sup1;
    supplier* n_newSup = (supplier*)newSupplier;
    if (n_sup1->sumOfDeals < n_newSup->sumOfDeals){
        return -1;
    } else if (n_sup1->sumOfDeals > n_newSup->sumOfDeals){
        return 1;
    }
    return 0; /*in case they have the same value*/
}

/*freeing memory of a supplier node.*/
int fre_sup(Node* supNode){
    supplier* sup1 = (supplier*)supNode->data;
    FREE(sup1->supName);
    FREE(sup1);
    FREE(supNode);
    return 1;
}

/*Will compare the value of a given and a supplier's business number in order to delete it by the given input*/
int cmpForDelete_supplier(Node* root,const char* user_input){
    supplier* sup = (supplier*)root->data;
    return (strcmp(sup->supNum,user_input));
}

/*Will print the entire suppliers tree by using the generic printTree function*/
void printSuppliers(Tree* supTree){
    printTree(supTree,&printSupplier);
}


/*Will delete a supplier lient from the supplier binary tree based on the given ID by operating the generic remove function.*/
void deleteSupplier(Tree* supTree) {
    int checker = supTree->elementCount;
    char user_input[SUPPLIER_NUM + 1];
    if (supTree->elementCount == 0) {
        printf("Nothing to delete\n");
        return;
    }
    flusher();
    printf("enter the supplier number of the supplier you want to delete:\n");
    scanf("%s", user_input);
    user_input[SUPPLIER_NUM] = '\0';
    supTree->root = removeNode(supTree->root, supTree,user_input,cmpForDelete_supplier);
    if(checker != supTree->elementCount){
        printf("Supplier with the number: %s deleted successfully\n",user_input);
    }
}
/*will print a supplier's details.*/
void printSupplier(Node* root) {
    supplier *sup = ((supplier *) root->data);
    printf("supplier's name - %s \n", sup->supName);
    printf("supplier's business number : %s\n", sup->supNum);
    printf("supplier's phone number: %s\n", sup->supPhone);
    printf("number of deals = %d\n", sup->dealsAmount);
    printf("sum of all deals made by supplier: %lu\n\n", sup->sumOfDeals);

}

/*will call the free tree function with the tree of suppliers and delete all of it.*/
void deleteAllSuppliers(Tree* supplierTree){
    freeTree(supplierTree);
}


