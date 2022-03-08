#include <stdio.h>
#include "genFuncs.h"
#include "car.h"
#include "client.h"
#include "supplier.h"
#include "common.h"

int main() {
    int i;
    char suppliersSumHelper[3][SUPPLIER_NUM+1]; /*Will be needed as an output the the ThreeGreatestSuppliers function*/
    int userChoice= -1; /*Will store the menu choice of the user*/
    Tree * carTree;
    Tree* clientTree;
    Tree* supTree;
    linkedList* head;


    /*initalization of all the trees*/
    clientTree = createClientTree();
    supTree = createSupTree();
    carTree = createCarTree();


    /*Running the program with a multiple choice menu based on the choice of the user*/
    printf("welcome to our car rental service: what would you like to do? \n");
    while (userChoice != 0)
    {
        printf("\n Enter your choice:\n\n");
        printf("\t\t To add a car, enter 1:\n");
        printf("\t\t To add a Supplier, enter 2:\n");
        printf("\t\t To add a Client, enter 3:\n");
        printf("\t\t To delete a Car, enter 4:\n");
        printf("\t\t To delete a Client, enter 5:\n");
        printf("\t\t To delete a supplier, enter 6:\n");
        printf("\t\t To delete all the Cars, enter 7:\n");
        printf("\t\t To delete all the Clients, enter 8:\n");
        printf("\t\t To delete all the suppliers, enter 9:\n");
        printf("\t\t To find a client, enter 10: \n");
        printf("\t\t To get a clients number with a given Car year, enter 11:\n");
        printf("\t\t To get number of cars with given engine vol, enter 12:\n");
        printf("\t\t To get three suppliers with the highest sum of deals, enter 13: \n");
        printf("\t\t To print all the existing suppliers, enter 14: \n");
        printf("\t\t To print client cars for given rental date, enter 15:\n");
        printf("\t\t To get the average of the existing suppliers' sum of deals, enter 16:\n");
        printf("\t\t To exit enter 0:\n");
        if(!(scanf(" %d", &userChoice) == 1)){
            userChoice = 16;
        }
        switch (userChoice)
        {
            case 1:
                addNewCar(carTree);
                flusher();
                break;
            case 2:
                addNewSupplier(supTree);
                flusher();
                break;
            case 3:
                addNewClient(clientTree);
                flusher();
                break;
            case 4:
                deleteCar(carTree);
                flusher();
                break;
            case 5:
                deleteClient(clientTree);
                flusher();
                break;
            case 6:
                deleteSupplier(supTree);
                flusher();
                break;
            case 7:
                deleteAllCars(carTree);
                flusher();
                break;
            case 8:
                deleteAllClients(clientTree);
                flusher();
                break;
            case 9:
                deleteAllSuppliers(supTree);
                flusher();
                break;
            case 10:
                head = findClient(clientTree);
                if (head){
                    printf("found client(s) added to the list successfully\n");
                }
                break;
            case 11:
                printf("Amount of clients with given car year: %d\n",clientNumberWithGivenCarYear(carTree,clientTree));
                flusher();
                break;
            case 12:
                printf("Amount of cars with given capacity: %d\n",carNumberWithGivenCapacity(carTree));
                break;
            case 13:
                if(supTree->elementCount < 3){
                    printf("not enough suppliers.\n");
                    break;
                }
                threeGreatestSuppliers(supTree,suppliersSumHelper);

                printf("three greatest suppliers' business numbers - \n\n");
                for (i=0; i < 3; i++){
                    printf("%s\n\n",suppliersSumHelper[i]);
                }
                flusher();
                break;
            case 14:
                printSuppliers(supTree);
                break;
            case 15:
                printClientCarsForGivenRentDate(clientTree);
                flusher();
                break;

            case 16:
                printf("the average amount of all suppliers sum of deals is: %lu \n",averageOfSupplierMoney(supTree));
                break;

            case 0:
                printf("Goodbye...\n");
                break;

            default:
                printf("invalid input, try again:\n");
                flusher();
                break;
        }



    }

    return 0;
}

