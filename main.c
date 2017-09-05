#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "string.h"


struct Account{
	char name[30];
	char password[30];
	char type;
	char path[100];
	char restName[150];
}active;

struct Food{
	char name[50];
	char type[50];
	float price;
};

void createAcc();
void openFile(char path[150],char mode[3]);
void closeFile(FILE *Ptr);
int nameCheck(char name [50]);
void login();
void viewMenu(char path[100]);
void custMenu();
void displayRest();
void purchaseFood(char path[100]);
void restMenu();
char createRest(char restName[100]);
void createMenu(int choice);

FILE *Ptr = NULL;


void main(){

	int choice = 0;

	while(1){

		printf("Welcome to EatGalway.ie\n");
		printf("------------------------\n");
		printf("1 - To log in\n2 - To create an account\n");
		printf("------------------------\n");
		printf("Choice: ");
		scanf("%d",&choice);

		switch(choice){
		case 1:
			system("cls");
			login();
			break;
		case 2:
			system("cls");
			createAcc();
			break;

		default : 
			system("cls");
			continue;
		}
	}
}
void custMenu(){

	int choice = 0;
	char restaurant[100];
	char path[100] = "Galway/";
	int rest = 0;
	int i;
	int j;
	char c;

	printf("--------------------------\n");
	while(choice < 3){
		//display all the restaurants
		displayRest();
		printf("------------------------\n");

		//gets the restaurant
		printf("Enter the number of the desired restaurant (e.g. 2): ");
		scanf("%d", &rest);

		//opens the file
		openFile("restaurants.txt","r");

		//gets the chosen restaurant
		for(i = 0; i < rest; i++){
			fgets(restaurant, 100, Ptr);
		}

		//formats the string
		for(j = 0; j <100; j++){
			if (restaurant[j] == '\n'){
				restaurant[j] = ' ';
			}
		}

		closeFile(Ptr);

		//sets up the path
		strcat(path, restaurant);


		//displays the menu of desired restaurant
		viewMenu(path);

		//lets the user choose weather to go back and choose another restaurant
		printf("------------------------\n");
		printf("1 - choose a meal\n");
		printf("2 - go back\n");
		printf("------------------------\n");
		printf("Choice:");
		scanf("%d", &choice);

		//clears the path and the screen
		if (choice == 2){
			system("cls");
			strcpy(path,"Galway/");
		}
		else{
			purchaseFood(path);
		}
	}
}
void purchaseFood(char path[100]){

	int choice;
	int num;
	float price;
	char meal[256];
	int i,j = 0;
	int z = 0;
	char *token;
	struct Food order[31];
	float total = 0;
	int purchase;

	//clears the screen
	system("cls");

	//gets the amount of meals + error checking
	printf("How many meals do you want (system can't handle more than 30): ");
	scanf("%d", &num);
	while(num > 30){
		printf("How many meals do you want (system can't handle more than 30): ");
		scanf("%d", &num);
	}

	//clears the screen
	system("cls");
	//displays the menu
	viewMenu(path);
	printf("--------------------------\n");


	while(num > 0){
		//gets the meal
		printf("Enter the number of the desired meal (e.g. 2): ");
		scanf("%d", &choice);
		//opens the file
		openFile(path,"r");

		//gets the chosen meal
		for(i = 0; i < choice; i++){
			fgets(meal, 256, Ptr);
		}

		//gets the details of the meal
		token = strtok (meal,"\t");
		strcpy(order[j].name,token);
		token = strtok (NULL, "\t");
		strcpy(order[j].type,token);
		token = strtok (NULL, "\t");
		order[j].price = atof(token);

		closeFile(Ptr);
		num--;
		j++;
	}

	//clears the screen
	system("cls");
	printf("--------------------------\n");

	//displays the selected meals
	while(j > z){
		printf("%s\t%s\t%.2f\n",order[z].name,order[z].type,order[z].price);
		z++;
	}

	//gets the total price
	while(z > 0){
		total = total + order[z-1].price;
		z--;
	}

	//displays the total price
	printf("--------------------------\n");
	printf("Total: %.2f\n", total);
	printf("--------------------------\n");
	//prompts to comfirm the purchase
	printf("Do you wish to purchase this?\n");
	printf("--------------------------\n");
	printf("1 - Yes\n2 - No\n");
	printf("--------------------------\n");
	printf("Choice: ");
	scanf("%d", &purchase);

	//lets the user know that purchase has been comfirem
	if(purchase == 1){
		printf("\nThank you for your purchase, we have your IP address and we will deliver to your door If you want to change the address please get in contanct with the restaurant\n");
	}
	exit(0);
}
void displayRest(){

	int num = 1;
	char restaurants[256];

	//opens the resturant file
	openFile("restaurants.txt","r");

	//displays all the restaurants
	while(fgets(restaurants, 256, Ptr) != NULL){
		printf("%d. %s\n",num,restaurants);
		num++;
	}

	//closes the file
	closeFile(Ptr);

}
void createAcc(){

	//the structure in which the data will be entered
	struct Account creat = {" "," ",' ',"None","None"};
	//the type of account, either customer or restaurant
	int type;

	//if the file doesn't exists, it is created
	openFile("accounts.txt","a+");
	closeFile(Ptr);

	//gets the user's name
	printf("Account name - ");
	scanf("%s", creat.name);

	//checks if the name has been taken, if so keeps asking for other one
	while(nameCheck(creat.name)){
		printf("this name has been used, please choose another one\n");
		printf("Account name - ");
		scanf("%s", creat.name);
	}

	//gets the user's password
	printf("Password - ");
	scanf("%s", creat.password);

	//gets the user's type
	printf("------------------------\n");
	printf("1 - Customer\n");
	printf("2 - Restaurant\n");
	printf("------------------------\n");
	printf("Choice: ");
	scanf("%d", &type);

	//makes sure that the user has entered the right values
	while(!(type == 1 || type == 2)){
		printf("Error!!! enter '1' or '2'\n");
		printf("Choice: ");
		scanf("%d", &type);
	}

	//decides which type the user is
	if(type == 1){
		//c = customer
		creat.type = 'c';
	}
	else if (type == 2){
		//r = restaurant
		creat.type = 'r';
	}

	//gets the name of the restaurant and sets up the path
	if(creat.type == 'r'){
		printf("The name of the restaurant - ");
		fflush(stdin);
		gets(creat.restName);
		strcpy(creat.path, "Galway/");
		strcat(creat.path, creat.restName);

		//adds the restaurant's name to a list
		createRest(creat.restName);

	}

	//writes the data into a file
	openFile("accounts.txt","a");
	fprintf(Ptr, "%s,%s,%c,%s,%s\n", creat.name, creat.password, creat.type, creat.path, creat.restName);
	closeFile(Ptr);

	//clears the screen
	system("cls");

}
void openFile(char path[150],char mode[3]){


	if((Ptr = fopen(path,mode)) == NULL){
		printf("File could not be opened\n");
	}
}
void closeFile(FILE *Ptr){

	fclose(Ptr);
}
int nameCheck(char name[50]){

	char accName[50];
	char line [256];
	char *token;
	int i = 0;

	openFile("accounts.txt", "r");

	//gets the line
	while(fgets(line, 256, Ptr) != NULL)
	{

		token = strtok (line,",");
		//gets name
		strcpy(accName,token);
		while (token != NULL)
		{
			token = NULL;
		}

		//if the name exists set i to 1
		if(strcmp(name, accName) == 0){
			i = 1;
		}
	}
	closeFile(Ptr);
	return i;
}
void login(){

	struct Account acc;
	char name[50];
	char password[50];
	char line [256];
	char *token;
	int found = 0;

	printf("Enter your details (case sensetive)\n");
	printf("----------------------------------\n");
	printf("Account name - ");
	scanf("%s", name);
	printf("Password - ");
	scanf("%s", password);

	openFile("accounts.txt", "r");

	//gets the line
	while(fgets(line, 256, Ptr) != NULL)
	{

		token = strtok (line,",");
		//gets name
		strcpy(acc.name,token);
		while (token != NULL)
		{
			token = strtok (NULL, ",");
			//gets password
			strcpy(acc.password,token);
			//gets type
			token = strtok (NULL, ",");
			acc.type = token[0];
			//gets path
			token = strtok (NULL, ",");
			strcpy(acc.path,token);
			//gets restaurant's name
			token = strtok (NULL, ",");
			strcpy(acc.restName,token);
			//sets the token to NULL
			token = NULL;
		}

		//compares the name and the password
		if(strcmp(acc.name, name) == 0 && strcmp(acc.password, password) == 0){

			system("cls");
			printf("Welcome %s\n", name);

			//sets up the active account
			strcpy(active.name, acc.name);
			strcpy(active.password, acc.password);
			active.type = acc.type;
			strcpy(active.path, acc.path);
			strcpy(active.restName, acc.restName);
			found = 1;
			break;
		}
	}

	if(found == 0){
		printf("Account does not exist\n");
		system("cls");
	}

	if (active.type == 'r'){
		restMenu();
	}
	else if (active.type == 'c'){
		custMenu();
	}

	closeFile(Ptr);
}
void restMenu(){

	int choice = 0;

	while (choice < 4){

		printf("--------------------------\n");
		printf("1 - To view your menu\n");
		printf("2 - To create a new menu\n");
		printf("3 - To update your menu\n");
		printf("4 - To exit\n");
		printf("--------------------------\n");
		printf("Enter your choice - ");
		scanf("%d", &choice);

		switch(choice){
		case 1  :
			viewMenu(active.path);
			break;
		case 2 :
			createMenu(1);
			break;
		case 3  :
			createMenu(2);
			break;
		case 4  :
			exit(0);
			break;
		default :
			;
		}
	}
}
char createRest(char restName[100]){

	char path[100] = "Galway/";

	//adds the restaurant's name to the list
	openFile("restaurants.txt", "a+");
	fprintf(Ptr, "%s\n",restName);
	closeFile(Ptr);

	//sets up the path
	strcat(path, restName);

	//creates the restaurant's file
	openFile(path,"a+");
	closeFile(Ptr);
	system("cls");
}
void createMenu(int choice){

	int menNum;
	struct Food meal;
	int i;
	system("cls");
	//sets up the menu
	printf("Please enter the amount of items in your menu - ");
	scanf("%d", &menNum);

	if (choice == 1){
		openFile(active.path,"w");
	}
	else{
		openFile(active.path,"a+");
	}

	for(i = 0; i < menNum; i++){
		fflush(stdin);
		printf("\nEnter the name of food no.%d - ",i+1);
		gets(meal.name);
		printf("Enter the type of %s (eg. spicy) - ",meal.name);
		gets(meal.type);
		printf("Enter the price of %s (eg. 10.56) - ", meal.name);
		scanf("%f", &meal.price);
		printf("\n");
		fprintf(Ptr, "%s\t%s\t%.2f\n", meal.name, meal.type, meal.price);
	}
	system("cls");
	closeFile(Ptr);
}
void viewMenu(char path[100]){

	int i = 1;
	char menu[256];
	system("cls");
	openFile(path,"r");
	printf("Name\tType\tPrice\n");
	printf("--------------------------\n");



	while(fgets(menu, 256, Ptr) != NULL){
		printf("%d. ",i);
		puts(menu);
		i++;
	}
	closeFile(Ptr);
}
