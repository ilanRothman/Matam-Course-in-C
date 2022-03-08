#include <assert.h>
#include "common.h"
#include "car.h"
#include <string.h>
#include <ctype.h>
#include "genFuncs.h"

/*creating a generic tree for a car by calling the create tree function with the suitable functions for car.*/
Tree* createCarTree(){
    return createTree(getCarDetails,checkCarDetails,carCmp,fre_car);

}
/*calling the generic function for adding a new Node.*/
car addNewCar(Tree* carTree){
    return *(car*)addNewNode(carTree);
}

/*Will delete a car from the car binary tree based on the given license number by operating the generic remove function.*/
void deleteCar(Tree* carTree) {
    int checker = carTree->elementCount;
    char user_input[LICENSE_NUM_LEN + 1];
    if (carTree->elementCount == 0) {
        printf("Nothing to delete\n");
        return;
    }
    flusher();
    printf("enter the license of the car you want to delete:\n");
    scanf("%s", user_input);
    user_input[LICENSE_NUM_LEN] = '\0';
    carTree->root = removeNode(carTree->root,carTree, user_input,&cmpForDelete_car);
    if(checker != carTree->elementCount){
        printf("car with license number: %s deleted successfully\n",user_input);
    }
}

/*Will count recursively the number of cars with the given engine volume.*/
int carNumberWithGivenCapacity_helper(Node* root,int engineVol) {
    car* car1;
    if (!root) {
        return 0;
    }
    car1 = (car*)root->data;

    if (car1->engineVol == engineVol) {
        return  1 + carNumberWithGivenCapacity_helper(root->right, engineVol)+carNumberWithGivenCapacity_helper(root->left, engineVol);

    }
    return carNumberWithGivenCapacity_helper(root->right, engineVol)+ carNumberWithGivenCapacity_helper(root->left, engineVol);
}

/*Will get as an input a car's engine volume and the binary tree of cars, and will return the number of cars with the given engine volume after calculating so, using a recursive function*/
unsigned int carNumberWithGivenCapacity(Tree* tree) {
    int counter = 0;
    int engineVol;
    if(tree->elementCount == 0){
        printf("No cars in system\n.");
        return 0;
    }
    flusher();
    printf("Please enter engine vol to count how many cars have the same:\n");
    scanf("%d", &engineVol);
    counter = carNumberWithGivenCapacity_helper(tree->root,engineVol);
    return counter;
}


/*Will receive the input from the user for all the struct fields.*/
void* getCarDetails(void* currentCar) {
    char inputString[300];

    car* newCar = (car*)currentCar;
    newCar = ALLOC(car,1);
    /*flusher();*/
    printf("Enter the license number, 7 digits:\n");
    scanf(" %s", inputString);
    if (strlen(inputString) > LICENSE_NUM_LEN) {
        strcpy(newCar->licenseNum, "long");
    } else {
        inputString[LICENSE_NUM_LEN] = '\0';
        strcpy(newCar->licenseNum, inputString);
    }
    flusher();
    printf("Enter the shield number of the car, 5 digits:\n");
    scanf(" %s", inputString);
    if (strlen(inputString) > CAR_SHIELD_LEN) {
        strcpy(newCar->shieldNum, "long");
    } else {
        inputString[CAR_SHIELD_LEN] = '\0';
        strcpy(newCar->shieldNum, inputString);
    }
    flusher();
    printf("Enter the make name:\n");
    scanf(" %s", inputString);
    newCar->makeName = (char*)checked_malloc(strlen(inputString));
    strcpy(newCar->makeName, inputString);

    flusher();
    printf("Enter the model name of the car:\n");
    scanf(" %s", inputString);
    newCar->modelName = (char*)checked_malloc(strlen(inputString));
    strcpy(newCar->modelName, inputString);

    flusher();
    printf("Enter the car color:\n");
    scanf(" %s", inputString);
    newCar->carColor = (char*)checked_malloc(strlen(inputString));
    strcpy(newCar->carColor, inputString);

    flusher();
    printf("Enter the make year:\n");
    scanf("%d", &newCar->makeYear);

    flusher();
    printf("Enter year the car went on the road:\n");
    scanf("%d", &newCar->yearOnRoad);

    flusher();
    printf("Enter the car engine volume:\n");
    scanf("%d", &newCar->engineVol);

    flusher();
    printf("Enter how much was paid to supplier:\n");
    scanf("%d", &newCar->paidToSupplier);

    flusher();
    printf("Enter the current price of the car:\n");
    scanf("%d", &newCar->currentPrice);

    return newCar;
}


/*Will check the input gotten from the user based on it's format and it's length
Once a wrong/invalid input is being detected, the user will be notified and the function will return*/
int checkCarDetails(void* check) {
    car* carCheck = (car*)check;
    int i = 0;
    if (strcmp(carCheck->licenseNum, "long") == 0) {
        printf("License number to long.");
        return 0;
    }
    while (carCheck->licenseNum[i] != '\0') {

        if (!isdigit(carCheck->licenseNum[i])) {
            printf("License number not in correct format.\n");
            return 0;

        }
        i++;
    }
    if (strlen(carCheck->licenseNum) != LICENSE_NUM_LEN) {
        printf("license number not in correct format.\n");
        return 0;
    }


    if (strcmp(carCheck->shieldNum, "long") == 0) {
        printf("shield number too long.\n");
        return 0;
    }

    if (strlen(carCheck->shieldNum) != CAR_SHIELD_LEN) {
        printf("shield number not in correct format.\n");
        return 0;
    }
    i = 0;
    while (carCheck->shieldNum[i] != '\0') {
        if (!isdigit(carCheck->shieldNum[i])) {
            printf("shield number not in correct format.\n");
            return 0;
        }
        i++;
    }
    i = 0;
    while (carCheck->makeName[i] != '\0') {
        if (!isalpha(carCheck->makeName[i])) {
            printf("Car make name not in correct format.\n");
            return 0;
        }
        i++;
    }
    if (strcmp(carCheck->carColor, "long") == 0) {
        printf("car color name too long.\n");
        return 0;
    }

    i = 0;
    while (carCheck->carColor[i] != '\0') {
        if (!isalpha(carCheck->carColor[i])) {
            printf("car color should only be with letters.\n");
            return 0;
        }
        i++;
    }
    if (carCheck->makeYear > 9999 || carCheck->makeYear < 999) {
        printf("car make year should be with 4 digits\n");
        return 0;
    }
    if (carCheck->yearOnRoad > 9999 || carCheck->yearOnRoad < 999) {
        printf("car year on road should be with 4 digits\n");
        return 0;
    }
    if (carCheck->yearOnRoad < carCheck->makeYear) {
        printf("year on road cannot be lower than make year \n");
        return 0;
    }

    if (carCheck->engineVol > 9999 || carCheck->engineVol < 999) {
        printf("car engine vol should be with 4 digits\n");
        return 0;
    }
    if (carCheck->paidToSupplier > 9999999) {
        printf("pay amount to supplier not allowed above 7 digits\n");
        return 0;
    }
    if (carCheck->currentPrice > 9999999) {
        printf("current price of car cannot bo above 7 digits\n");
        return 0;
    }
    return 1;
}

/*the car compare alogorythem for finding a car in the tree based on the car's license number.*/
int findCmp_car(void* data, void* license){
    car* car1 = (car*)data;
    return strcmp(car1->licenseNum,(char*)license);
}

/*the car compare alogorythem for adding a car to the tree.*/
int carCmp(void* car1, void* newCar){
    car* n_car1 = (car*)car1;
    car* n_newCar = (car*)newCar;
    return strncmp(n_car1->licenseNum, n_newCar->licenseNum,LICENSE_NUM_LEN);
}

/*freeing memory of a car node.*/
int fre_car(Node* carNode){
    car* car1 = (car*)carNode->data;
    FREE(car1->modelName);
    FREE(car1->makeName);
    FREE(car1->carColor);
    FREE(car1);
    FREE(carNode);
    return 1;
}

/*the car compare alogorythem for deleting a car. */
int cmpForDelete_car(Node* root, const char* user_input){
    car* car1 = (car*)root->data;
    return strcmp(car1->licenseNum,user_input);
}

/*will print a car's details.*/
void printCar(Node* root){
    car car1 = *(car*)root->data;
    printf("car license : %s\n",car1.licenseNum);
    printf("shield number : %s\n",car1.shieldNum);
    printf("car color name: %s\n",car1.carColor);
    printf("car model length: %s\n",car1.modelName);
    printf("car make name length: %s\n",car1.makeName);
    printf("the car was made on the year: %d \n",car1.makeYear);
    printf("year it went on the road: %d \n",car1.yearOnRoad);
    printf("engine volume: %d \n",car1.engineVol);
    printf("paid to supplier - %d, current price - %d \n\n",car1.paidToSupplier,car1.currentPrice);
}

/*will call the free tree function with the tree of cars and delete all of it.*/
void deleteAllCars(Tree* carTree){
    freeTree(carTree);
}




