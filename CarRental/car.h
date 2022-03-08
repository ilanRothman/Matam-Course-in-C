#ifndef PROJECT7_CAR_H
#define PROJECT7_CAR_H
#define LICENSE_NUM_LEN 7
#define CAR_SHIELD_LEN 5
#include "genFuncs.h"

typedef struct car{
    char licenseNum[LICENSE_NUM_LEN+1];
    char shieldNum[CAR_SHIELD_LEN+1];
    char* makeName;
    char* modelName;
    char* carColor;
    int makeYear;/*4 digits*/
    int yearOnRoad;/*4 digits*/
    int engineVol;/*4 digits*/
    int paidToSupplier; /*upto 7 digits*/
    int currentPrice; /*upto 7 digits*/

}car;

/*creating a generic tree for a car by calling the create tree function with the suitable functions for car.*/
Tree* createCarTree();

/*Will get as an input a car's engine volume and the binary tree of cars, and will return the number of cars with the given engine volume after calculating so, using a recursive function*/
unsigned int carNumberWithGivenCapacity(Tree* tree);

/*Will delete a car from the car binary tree based on the given license number by operating the generic remove function.*/
void deleteCar(Tree* carTree);

/*the car compare alogorythem for finding a car in the tree based on the car's license number.*/
int findCmp_car(void* data, void* license);

/*Will receive the input from the user for all the struct fields.*/
void* getCarDetails(void* currentCar);

/*Will check the input gotten from the user based on it's format and it's length
Once a wrong/invalid input is being detected, the user will be notified and the function will return*/
int checkCarDetails(void *carCheck);

/*freeing memory of a car node.*/
int fre_car(Node* carNode);

/*the car compare alogorythem for adding a car to the tree.*/
int carCmp(void* car1, void* newCar);

/*the car compare alogorythem for deleting a car. */
int cmpForDelete_car(Node* root, const char* user_input);


/*will print a car's details.*/
void printCar(Node* root);

/*calling the generic function for adding a new Node.*/
car addNewCar(Tree* carTree);

/*will call the free tree function with the tree of cars and delete all of it.*/
void deleteAllCars(Tree* carTree);


#endif

