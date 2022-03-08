#include "client.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "common.h"
#include "genFuncs.h"


/*creating a generic tree for a client by calling the create tree function with the suitable functions for client.*/
Tree* createClientTree(){
    return createTree(getClientDetails,checkClientDetails,clientCmp,fre_client);
}

/*calling the generic function for adding a new Node.*/
client addNewClient(Tree* clientTree){
    return *(client*)addNewNode(clientTree);
}


/*Will operate the recursion over the clients binary tree in order to get the number of clients with the given car year*/
int clientNumberWithGivenCarYear_helper_client(const char *licenseNum, Node *clientRoot) {
    client* client1;
    if (!clientRoot) {
        return 0;
    }
    client1 = (client*)clientRoot->data;
    if (strcmp(licenseNum, client1->licenseNum) == 0) {
        return 1 + clientNumberWithGivenCarYear_helper_client(licenseNum, clientRoot->left) +
               clientNumberWithGivenCarYear_helper_client(licenseNum, clientRoot->right);
    }
    return clientNumberWithGivenCarYear_helper_client(licenseNum, clientRoot->left) +
           clientNumberWithGivenCarYear_helper_client(licenseNum, clientRoot->right);

}

/*Will operate the recursion over the cars binary tree in order to get the number of clients with the given car year*/
unsigned int clientNumberWithGivenCarYear_helper_car(Node *carRoot, Node *clientRoot, int year) {
    car* car1;
    if (!carRoot) {
        return 0;
    }
     car1 = (car*)carRoot->data;

    if (car1->makeYear == year) {
        return clientNumberWithGivenCarYear_helper_client(car1->licenseNum, clientRoot)+
               clientNumberWithGivenCarYear_helper_car(carRoot->left, clientRoot, year)+
               clientNumberWithGivenCarYear_helper_car(carRoot->right, clientRoot, year);

    }
    return clientNumberWithGivenCarYear_helper_car(carRoot->left, clientRoot, year)+
           clientNumberWithGivenCarYear_helper_car(carRoot->right, clientRoot, year);

}

/*Will operate the generic find function to search for a specific client based on the requested input - ID or rental date.
If there will be more than one client found with the input field - a linked list of the found clients will be returned */
linkedList* findClient(Tree* clientTree){
    date input_date;
    linkedList *clientListHead = NULL;
    int user_input;
    char user_input_id[ID_LEN + 1];
    if (clientTree->elementCount ==0) {
        printf("No clients to find.");
        return NULL;
    }
    printf("To find client with id number enter 1, with rental date enter 2: \n ");
    flusher();
    scanf("%d", &user_input);
    switch (user_input) {
        case 1:
            printf("enter client id: \n");
            scanf("%s", user_input_id);
            user_input_id[ID_LEN] = '\0';
            findNode(clientTree->root, findCmp_id,user_input_id, &clientListHead);
            if (!clientListHead) {
                printf("No client with the entered ID was found");
                return NULL;
            }
            break;
        case 2:
            printf("Enter the year of the clients year rental\n");
            scanf("%d", &input_date.year);
            flusher();
            printf("Enter the month of the clients year rental\n");
            scanf("%d", &input_date.month);
            flusher();
            printf("Enter the day of the clients year rental\n");
            scanf("%d", &input_date.day);
            if (!valid_date(input_date.day, input_date.month, input_date.year)) {
                printf("Not a valid date");
                return NULL;
            }
            findNode(clientTree->root, findCmp_date,&input_date,&clientListHead);
            if (!clientListHead) {
                printf("No client with the entered date was found");
                return NULL;
            }
            break;
        default:
            printf("invalid input.\n");
            return NULL;
    }
    return clientListHead;

}

/* prints the clients with a car rented on a given date recursively.*/
void printClientCarsForGivenRentDate_helper(Node *root, date inputDate) {
    if (!root) {
        return;
    }
    if (!findCmp_date(root->data,&inputDate)) {
        printClient(root);
    }
    printClientCarsForGivenRentDate_helper(root->left, inputDate);
    printClientCarsForGivenRentDate_helper(root->right, inputDate);
}

/* Will get an input date out of the user and will operate the recursive function that will locate and print all client care for the given rent date.*/
void printClientCarsForGivenRentDate(Tree *clientTree) {
    date inputDate;
    if(clientTree->elementCount == 0){
        printf("No cars in system. \n");
        return;
    }
    flusher();
    printf("Enter the year of the clients rental date\n");
    scanf("%d", &inputDate.year);
    flusher();
    printf("Enter the month of the clients rental date\n");
    scanf("%d", &inputDate.month);
    flusher();
    printf("Enter the day of the clients rental date\n");
    scanf("%d", &inputDate.day);
    if (!valid_date(inputDate.day, inputDate.month, inputDate.year)) {
        printf("Not a valid date");
        return;
    }
    printClientCarsForGivenRentDate_helper(clientTree->root, inputDate);

}


/*Will delete a client from the client binary tree based on the given ID by operating the generic remove function.*/
void deleteClient(Tree *clientTree) {
    int checker = clientTree->elementCount;
    char user_input[ID_LEN + 1];
    if (clientTree->elementCount == 0) {
        printf("Nothing to delete\n");
        return;
    }
    flusher();
    printf("enter the id of the client you want to delete:\n");
    scanf("%s", user_input);
    user_input[ID_LEN] = '\0';
    removeNode(clientTree->root,clientTree, user_input,&cmpForDelete_client);
    if (checker!= clientTree->elementCount){
        printf("client with id number: %s deleted successfully\n", user_input);
    }
    return;
}


/*Will get as an input the Binary trees of both the cars and the clients and the year of making of a car, and will return the number of client which rent a car of that year,
 based on crossing the license numbers given on the found cars and the existing clients.*/
unsigned int clientNumberWithGivenCarYear(Tree *carTree, Tree *clientTree) {
    int year;
    unsigned int counter = 0;
    if(carTree->elementCount == 0 || clientTree->elementCount == 0){
        return 0;
    }
    flusher();
    printf("Enter the year of the car to be checked\n");
    scanf("%d", &year);
    counter = clientNumberWithGivenCarYear_helper_car(carTree->root, clientTree->root, year);
    return counter;
}


/*Will check the input gotten from the user based on it's format and it's length
Once a wrong/invalid input is being detected, the user will be notified and the function will return*/
int checkClientDetails(void *newClient) {
    client* clientCheck = (client*)newClient;
    int i = 0;
    for (; i < strlen(clientCheck->firstName); i++) {
        if (!isalpha(clientCheck->firstName[i]) && clientCheck->firstName[i] != '\0') {
            printf("client name can only have letters\n");
            return 0;
        }
    }

    if (strcmp(clientCheck->licenseNum, "long") == 0) {
        printf("license number to long.");
        return 0;
    }


    for (; i < strlen(clientCheck->lastName); i++) {
        if (!isalpha(clientCheck->lastName[i]) && clientCheck->lastName[i] != '\0') {
            printf("client last name can only have letters\n");
            return 0;
        }
    }

    if (strlen(clientCheck->id) != (ID_LEN)) {
        printf("client id number not 9 digits\n");
        return 0;
    }

    if (clientCheck->pricePerDay < 100 || clientCheck->pricePerDay > 999) {
        printf("The entered price is not as requested\n");
        return 0;
    }


    i = 0;
    while (clientCheck->id[i] != '\0') {

        if (!(isdigit(clientCheck->id[i]))) {
            printf("client id has non digits\n");
            return 0;
        }

        i++;
    }
    if (!valid_date(clientCheck->dateOfRental.day, clientCheck->dateOfRental.month, clientCheck->dateOfRental.year)) {
        printf("wrong date format entered\n");
        return 0;

    }
    if (clientCheck->hourOfRental.hour > 24 || clientCheck->hourOfRental.hour < 0
        || clientCheck->hourOfRental.minute > 59 || clientCheck->hourOfRental.minute < 0) {
        printf("wrong time format entered\n");
        return 0;
    }

    return 1;

}

/*Will receive the input from the user for all the struct fields*/
void* getClientDetails(void* tempClient) {
    date clientDate;
    time rentalTime;
    char inputString[300];
    client* newClient = ALLOC(client,1);
    tempClient = (client*)tempClient;
    flusher();
    printf("Enter clients first name:\n");
    scanf(" %s", inputString);
    newClient->firstName = (char *) checked_malloc(strlen(inputString));
    strcpy(newClient->firstName, inputString);

    flusher();
    printf("Enter clients last name:\n");
    scanf(" %s", inputString);
    newClient->lastName = (char *) checked_malloc(strlen(inputString));
    strcpy(newClient->lastName, inputString);

    flusher();
    printf("Enter clients id number: 9 digits\n");
    scanf(" %s", inputString);
    if (strlen(inputString) > ID_LEN) {
        strcpy(newClient->id, "long");
    } else {
        inputString[ID_LEN] = '\0';
        strcpy(newClient->id, inputString);
    }

    flusher();
    printf("Enter clients license number: 7 digits\n");
    scanf(" %s", inputString);
    if (strlen(inputString) > LICENSE_NUM_LEN) {
        strcpy(newClient->licenseNum, "long");
    } else {
        inputString[LICENSE_NUM_LEN] = '\0';
        strcpy(newClient->licenseNum, inputString);
    }
    flusher();
    printf("Enter rental date: (dd/mm/yy) \n");
    printf("day:\n");
    scanf(" %d", &clientDate.day);
    flusher();
    printf("month:\n");
    scanf(" %d", &clientDate.month);
    flusher();
    printf("year:\n");
    scanf(" %d", &clientDate.year);

    newClient->dateOfRental = clientDate;
    flusher();
    printf("Enter rental time: hh:mm \n");
    printf("hour:\n");
    if (!(scanf(" %d", &rentalTime.hour) == 1)) {
        rentalTime.hour = 25;
    }

    flusher();
    printf("minute:\n");
    if (!(scanf(" %d", &rentalTime.minute) == 1)) {
        rentalTime.minute = 61;
    }
    newClient->hourOfRental = rentalTime;
    flusher();
    printf("Enter client price per day: 3 digits long \n");
    scanf("%d", &newClient->pricePerDay);
    tempClient = newClient;
    return tempClient;


}

/*Will compare an input id with an id of an input client, in order to locate client with the given id*/
int findCmp_id(void* data, void* id){
    client* client1 = (client*)data;
    return strcmp(client1->id,(char*)id);
}

/*Will compare an input date with a date of an input client, in order to locate client with the given rental date*/
int findCmp_date(void* data, void* clientDate){
    client* client1 = (client*)data;
    date* date1 = (date*)clientDate;
    return (!(client1->dateOfRental.day == date1->day && client1->dateOfRental.month == date1->month &&
                client1->dateOfRental.year == date1->year) );
}

/*Will compare two given clients based on their ID numbers.*/
int clientCmp(void* client1, void* newClient){
    client* n_client1 = (client*)client1;
    client* n_newClient = (client*)newClient;
    return strncmp(n_client1->id, n_newClient->id,ID_LEN);
}

/*Will compare a given client's ID and an input ID number in order to locate a client to delete*/
int cmpForDelete_client(Node* root, const char* user_input){
    client* client1 = (client*)root->data;
    return strcmp(client1->id, user_input);
}


int fre_client(Node* clientNode){
    client* client1 = (client*)clientNode->data;
    FREE(client1->id);
    FREE(client1);
    FREE(clientNode);
    return 1;

}

/*will print a client's details.*/
void printClient(Node* root){
    client* client1 = (client*)root->data;
    printf("Client's full name - %s %s \n", client1->firstName, client1->lastName);
    printf("ID number : %s\n", client1->id);
    printf("rented car's license number: %s \n", client1->licenseNum);
    printf("rental date: %d / %d / %d \n", client1->dateOfRental.day, client1->dateOfRental.month,
           client1->dateOfRental.year);
    printf("rental hour: %d:%d\n", client1->hourOfRental.hour, client1->hourOfRental.minute);
    printf("price per day: %d\n\n", client1->pricePerDay);

}

/*will call the free tree function with the tree of clients and delete all of it.*/
void deleteAllClients(Tree* clientsTree){
    freeTree(clientsTree);
}

