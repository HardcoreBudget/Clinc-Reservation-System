#include <stdio.h>
#include <conio.h>

#include "menus.h"
#include "config.h"
#include "LinkedList.h"

node_t *ptr = NULL;
node_t *patientsListHead = NULL;
reservationsList *reservedTimesPointer = NULL;
reservationsList *reservedTimesHead = NULL;
u32 timeListSize = 0;

void main(){
	u32 mainMenuChoice;
	u32 AdminMenuChoice;
	u32 UserMenuChoice;
	u32 currentMenu = 0;
	u8 menuErrorFlag = 0;
	u8 restartFlag = 0;
	
	for(int i = 1; i < 6;i++) {	AddReservationTime(i); reservedTimesPointer -> position = i; }
	
	do{
		if(currentMenu == 0){
			mainMenuChoice = MainMenu(menuErrorFlag);
		}
		menuErrorFlag = 0;
		switch(mainMenuChoice){
			case ADMIN_MODE:
				if(currentMenu== 1 ||CheckPassword(0)){
					currentMenu = 1;
					do{
						AdminMenuChoice = AdminModeMenu(menuErrorFlag);
						menuErrorFlag = 0;
						switch(AdminMenuChoice){
							case 1: AddPatientRecord(); break;
							case 2: EditPatientRecord(); break;
							case 3: ReserveSlot(); break;
							case 4: CancelReservation(); break;
							case 5: restartFlag = 1; break;
							default: menuErrorFlag = 1; continue;
						}		
					}while(menuErrorFlag);
					
					if(restartFlag) { currentMenu = 0; restartFlag = 0; continue; }
					break;
				}
				else{ return; }
			case USER_MODE:
				currentMenu = 2;
				do{
					UserMenuChoice = UserModeMenu(menuErrorFlag);
					menuErrorFlag = 0;
					switch(UserMenuChoice){
						case 1: DisplayPatientRecord(); break;
						case 2: 
							if(DisplayReservation()){ 
								printf("Enter any key to continue ...");
								getch();
							}
							break;
						case 3: restartFlag = 1; break;
						default: menuErrorFlag = 1; continue;
					}		
				}while(menuErrorFlag);	
				
				if(restartFlag) { currentMenu = 0; restartFlag = 0; continue; }
				break;
				
			case MAIN_MENU_EXIT: return;
			
			default: menuErrorFlag = 1; continue;
		}
	}while(1);
}