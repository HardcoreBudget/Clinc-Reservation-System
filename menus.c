#include <stdio.h>
#include <stdlib.h>

#include "STD_types.h"
#include "config.h"

u32 MainMenu(u8 errorFlag){
	system("cls");
	if(errorFlag){
		printf("\n*****************************************\n");
		printf("Wrong choice.Please try again.");
		printf("\n*****************************************\n");
	}
	u32 choice = 0;
	printf("\n-----------------------\n");
	printf("\tMain Menu");
	printf("\n-----------------------\n");
	printf("%d- Admin mode\n",ADMIN_MODE);
	printf("%d- User mode\n",USER_MODE);
	printf("%d- Exit",MAIN_MENU_EXIT);
	printf("\n***********************\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}

u32 CheckPassword(u8 errorFlag){
	u32 pass = 0;
	static u32 tries = 0;
	system("cls");
	if(errorFlag){
		printf("\n*****************************************\n");
		printf("Wrong password. Please try again");
		printf("\n*****************************************\n");
	}
	printf("\n------------------------------\n");
	printf("\tValidation Menu");
	printf("\n------------------------------\n");
	printf("Enter your password: ");
	scanf("%d",&pass);
	switch(pass){
		case 1234:
			tries = 0;
			return 1;
		default:
			if(tries < 2){
				tries++;
				errorFlag = 1;
				return CheckPassword(errorFlag);
			}
			else{
				return 0;
			}
	}
}

u32 AdminModeMenu(u8 errorFlag){
	system("cls");
	if(errorFlag){
		printf("\n*****************************************\n");
		printf("Wrong choice.Please try again.");
		printf("\n*****************************************\n");
	}
	u32 choice = 0;
	printf("\n-----------------------\n");
	printf("\tAdmin Mode");
	printf("\n-----------------------\n");
	printf("1- Add new patient record\n");
	printf("2- Edit patient record\n");
	printf("3- Reserve a slot with the doctor\n");
	printf("4- Cancel reservation\n");
	printf("5- Return to MainMenu");
	printf("\n***********************\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}
u32 UserModeMenu(u8 errorFlag){
	system("cls");
	if(errorFlag){
		printf("\n*****************************************\n");
		printf("Wrong choice.Please try again.");
		printf("\n*****************************************\n");
	}
	u32 choice = 0;
	printf("\n-----------------------\n");
	printf("\tUser Mode");
	printf("\n-----------------------\n");
	printf("1- View patient's record\n");
	printf("2- View today's reservations\n");
	printf("3- Return to MainMenu");
	printf("\n***********************\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}