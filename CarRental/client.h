#ifndef PROJECT7_CLIENT_H
#define PROJECT7_CLIENT_H

#include "car.h"
#include "genFuncs.h"

# define ID_LEN 9
#define LICENSE_NUM_LEN 7

typedef struct{
    int day;
    int month;
    int year;
}date;

typedef struct{
    int hour;
    int minute;
}time;

typedef struct {
    char* firstName;
    char* lastName;
    char id[ID_LEN + 1];
    char licenseNum[LICENSE_NUM_LEN + 1];
    date dateOfRental;
    time hourOfRental;
    int pricePerDay;


} client;

/*creating a generic tree for a client by calling the create tree function with the suitable functions for client.*/
Tree* createClientTree();

/*will call the free tree function with the tree of clients and delete all of it.*/
void deleteAllClients(Tree* clientsTree);

/* Will get an input date out of the user and will operate the recursive function that will locate and print all client care for the given rent date.*/
void printClientCarsForGivenRentDate(Tree *clientTree);

/*Will delete a client from the client binary tree based on the given ID by operating the generic remove function.*/
void deleteClient(Tree *clientTree);

/*calling the generic function for adding a new Node.*/
client addNewClient(Tree* clientTree);

/*Will get as an input the Binary trees of both the cars and the clients and the year of making of a car, and will return the number of client which rent a car of that year,
 based on crossing the license numbers given on the found cars and the existing clients.*/
unsigned int clientNumberWithGivenCarYear(Tree *carTree, Tree *clientTree);

/*Will receive the input from the user for all the struct fields*/
void* getClientDetails(void* tempClient) ;

/*Will check the input gotten from the user based on it's format and it's length
Once a wrong/invalid input is being detected, the user will be notified and the function will return*/
int checkClientDetails(void *newClient);

/*Will compare two given clients based on their ID numbers.*/
int clientCmp(void* client1, void* newClient);

/*freeing memory of a client node.*/
int fre_client(Node* clientNode);

/*will print a client's details.*/
void printClient(Node* root);

/*Will compare a given client's ID and an input ID number in order to locate a client to delete*/
int cmpForDelete_client(Node* root, const char* user_input);

/*Will compare an input date with a date of an input client, in order to locate client with the given rental date*/
int findCmp_date(void* data, void* clientDate);

/*Will compare an input id with an id of an input client, in order to locate client with the given id*/
int findCmp_id(void* data, void* id);

/*Will operate the generic find function to search for a specific client based on the requested input - ID or rental date.
If there will be more than one client found with the input field - a linked list of the found clients will be returned */
linkedList* findClient(Tree* clientTree);

#endif
