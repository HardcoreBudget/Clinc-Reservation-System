#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "STD_TYPES.h"
#include "LinkedList.h"

extern node_t *ptr;
extern node_t *patientsListHead;
extern u32 timeListSize;
extern reservationsList *reservedTimesPointer;
extern reservationsList *reservedTimesHead;


u32 CheckID(u32 ID){
	u32 foundFlag = 0;
	while(ptr != NULL){
		if(ID == ptr -> ID){
			foundFlag = 1;	
			break;
		}
		ptr = ptr -> next;
	}
	
	return foundFlag;			
}

void AddPatientRecord(){
	ptr = patientsListHead;
	u32 counter =1;
	u32 ID = 0;
	node_t *node =NULL;
	printf("Please enter Patient ID: ");
	scanf("%d",&ID);
	if(!CheckID(ID)){
		node = (node_t*) malloc(1 * sizeof(node_t));
		node -> next = NULL;
		node -> ID = ID;
	}
	else{
		printf("\n-----------------------------------------\n");
		printf("Patient with the same ID already exists");
		printf("\n-----------------------------------------\n");
		printf("Enter any key to continue ...");
		getch();
		return;
	}
	printf("Please enter patient's name: ");
	scanf(" %[^\n]s",&(node -> name));
	printf("Please enter patient's gender: ");
	scanf(" %[^\n]s",&(node -> gender));
	printf("Please enter patient's age: ");
	scanf("%d",&(node -> age));
	node -> reservedTime = NULL;
	
	if(patientsListHead == NULL){
		patientsListHead = node;
	}
	else{
		ptr = patientsListHead;
		while(1){
			if(ptr -> next == NULL){
				ptr  -> next = node;
				break;
			}
			/*Move the pointer to the next node*/
			ptr = ptr -> next;
		}
	}
	printf("\n-----------------------------------------\n");
	printf("Patient record added. Thank you");
	printf("\n-----------------------------------------\n");
	printf("Enter any key to continue ...");
	getch();
}

void EditPatientRecord(){
	if(patientsListHead == NULL){
		printf("\n---------------------------\n");
		printf("Patients' List is empty\n");
		printf("---------------------------\n");
		printf("Enter any key to continue ...");
		getch();
		return;
	}
	ptr = patientsListHead;
	u32 ID;

	printf("Please enter the patient's ID you want to edit his/her record: ");
	scanf("%d",&ID);
		
	if(!CheckID(ID)){
		printf("\n-------------------------------------------\n");
		printf("\tID not found");
		printf("\n-------------------------------------------\n");
		printf("Enter any key to continue ...");
		getch();
		return;
	}
	else{
		node_t* temp = ptr;
		u32 foundFlag = 0;
		ptr = patientsListHead;
		printf("Please enter the new patient's ID: ");
		scanf("%d",&ID);
		while(ptr != NULL){
			if(ptr -> ID == ID && ptr != temp){
				printf("\n-----------------------------------------\n");
				printf("Another patient with the same ID already exists");
				printf("\n-----------------------------------------\n");
				foundFlag = 1;
				break;
			}
			ptr = ptr -> next;
		}
		if(!foundFlag){
			temp -> ID = ID;
			printf("Please enter the new patient's name: ");
			scanf(" %[^\n]s",&(temp -> name));
			printf("Please enter the new patient's gender: ");
			scanf(" %[^\n]s",&(temp -> gender));
			printf("Please enter the new patient's age: ");
			scanf("%d",&(temp -> age));	
			printf("\n-------------------------------------------\n");
			printf("Patient with ID %d was updated successfully",ID);
			printf("\n-------------------------------------------\n");
		}
		printf("Enter any key to continue ...");
		getch();
	}
}

u32 ReservationAvailable(){
	u32 ID = 0;
	printf("Please enter the patient's ID: ");
	scanf("%d",&ID);
	if(!CheckID(ID)){
		printf("\n-------------------------------------------\n");
		printf("\tID not found");
		printf("\n-------------------------------------------\n");
		return 0;
	}
	else{
		if(ptr -> reservedTime != NULL) {
			printf("ID %d has another reservation already\n",ID);
			return 0;
		}
		else{ return 1;}	
	}
}

void ReserveSlot(){
	system("cls");
	if(reservedTimesHead == NULL){
		printf("\n---------------------------\n");
		printf("No available times left\n");
		printf("---------------------------\n");
		printf("Enter any key to continue ...");
		getch();
		return;
	}
	
	reservedTimesPointer = reservedTimesHead;
	ptr = patientsListHead;
	u32 counter = 1;
	printf("\n*******************************************************\n");
	printf("Please choose an available reservation time");
	printf("\n*******************************************************\n");
	printf("\n-------------------------------------------\n");
	while(reservedTimesPointer != NULL){
		printf("%d- %s\n", counter, reservedTimesPointer -> time);
		reservedTimesPointer = reservedTimesPointer -> next;
		counter++;
	}
	printf("-------------------------------------------\n");
	
	reservedTimesPointer = reservedTimesHead;
	counter = 1;
	u32 choice = 0;
	printf("Your choice: ");
	scanf("%d",&choice);
	
	if(choice > timeListSize || choice <=0 ) { 
		printf("\n************************************\n");
		printf("\tIncorrect choice"); 
		printf("\n************************************\n");
	}
	else if(choice == 1){
		if(ReservationAvailable()){
			reservedTimesHead = reservedTimesHead -> next;
			ptr -> reservedTime = reservedTimesPointer;
			timeListSize--;	
		}
	}
	else{
		reservationsList *temp = reservedTimesPointer;	
		while(1){
			if(choice == counter){
				if(ReservationAvailable()){
					temp -> next = reservedTimesPointer -> next;
					ptr -> reservedTime = reservedTimesPointer;
					timeListSize--;	
				}
				
				break;
			}
			counter++;
			temp = reservedTimesPointer;
			reservedTimesPointer = reservedTimesPointer -> next;
		}
	}
	
	printf("Enter any key to continue ...");
	getch();
}

void AddReservationTime(u32 position){
	u8 reservationTimes[5][20] = {"2 p.m. -> 2:30 p.m.", 
								  "2:30 p.m. -> 3 p.m.",
								  "3 p.m. -> 3:30 p.m.",
								  "4 p.m. -> 4:30 p.m.",
								  "4:30 p.m. -> 5 p.m."};
								  
	reservedTimesPointer = reservedTimesHead;
	reservationsList *temp = reservedTimesPointer;
	reservationsList *node = (reservationsList*) malloc(1 * sizeof(reservationsList));
	u32 stringLength = 0; 
	while(reservationTimes[position - 1][stringLength] != '\0'){
		node -> time[stringLength] = reservationTimes[position - 1][stringLength];
		stringLength++;
	}
	node -> time[stringLength] = '\0';
	node -> position = position;
	
	if(reservedTimesHead == NULL || reservedTimesHead -> position > position){
		reservedTimesHead = node;
		reservedTimesHead -> next = reservedTimesPointer;
	}
	else{		
		while(reservedTimesPointer != NULL){
			if(reservedTimesPointer -> position > position){
				temp -> next = node;
				node -> next = reservedTimesPointer;
				break;
			}
			temp = reservedTimesPointer;
			reservedTimesPointer = reservedTimesPointer -> next;
		}
		if(position >= timeListSize + 1){
			temp -> next = node;
			node -> next = reservedTimesPointer;
		}
	}
	reservedTimesPointer = node;
	timeListSize++;
}

u8 DisplayReservation(){
	system("cls");
	ptr = patientsListHead;
	reservedTimesPointer = reservedTimesHead;
	if(patientsListHead == NULL){
		printf("\n---------------------------\n");
		printf("No available patients\n");
		printf("---------------------------\n");
		printf("Enter any key to continue ...");
		getch();
		return 0;
	}
	u32 foundFlag = 0;
	printf("\n-----------------------------------------------\n");
	while(ptr != NULL){
		if(ptr -> reservedTime != NULL){
			foundFlag =1;
			printf("ID %d has reserved time: %s\n", ptr -> ID, ptr -> reservedTime -> time);
		}
		ptr = ptr -> next;
	}
	if(!foundFlag){
		printf("No reserved times yet.\n");
		printf("-----------------------------------------------\n");
		printf("Enter any key to continue ...");
		getch();
		return 0;
	}
	printf("-----------------------------------------------\n");
	
	return 1;
}

void CancelReservation(){
	if(DisplayReservation()){
		ptr = patientsListHead;
		reservedTimesPointer = reservedTimesHead;
		u32 ID = 0;
		printf("Please enter patient's ID to cancel his/her reservation: ");
		scanf("%d",&ID);
		
		printf("\n-----------------------------------------------\n");
		if(CheckID(ID)){
			if(ptr -> reservedTime != NULL){
				AddReservationTime(ptr -> reservedTime -> position);
				ptr -> reservedTime = NULL;
				printf("Reservation cancelled successfully.");
			}
			else{
				printf("No available reservations for the ID: %d",ID);
			}
			printf("\n-----------------------------------------------\n");
		}
		else{
			printf("\tWrong ID");
			printf("\n-----------------------------------------------\n");
		}
		printf("Enter any key to continue ...");
		getch();
	}
}

void DisplayPatientRecord(){
	u32 ID = 0;
	system("cls");
	if(patientsListHead == NULL){
		printf("\n---------------------------\n");
		printf("No available patients\n");
		printf("---------------------------\n");
		printf("Enter any key to continue ...");
		getch();
		return;
	}
	printf("\n-----------------------------------------------\n");
	printf("\tView Patients");
	printf("\n-----------------------------------------------\n");
	printf("Please enter patient's ID to display: ");
	scanf("%d",&ID);
	ptr = patientsListHead;
	if(CheckID(ID)){
		printf("\n---------------ID %d-----------------\n",ID);
		printf("Patient's name is: %s\n",ptr -> name);
		printf("Patient's gender is: %s\n",ptr -> gender);
		printf("Patient's age is: %d",ptr -> age);
		printf("\n------------------------------------\n",ID);
	}
	else{
		printf("\n-----------------------------------------------\n");
		printf("\tWrong ID");
		printf("\n-----------------------------------------------\n");
	}
	
	printf("Enter any key to continue ...");
	getch();
}