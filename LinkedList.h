#include "STD_TYPES.h"

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct node{
	u32 ID;
	u8 name[20];
	u32 age;
	u8 gender[20];
	struct times *reservedTime;
	struct node *next;
}node_t;

typedef struct times{
	u8 time[20];
	u8 position;
	struct times *next;
}reservationsList;

void AddPatientRecord();
void ReserveSlot();
void EditPatientRecord();
u8 DisplayReservation();
void CancelReservation();

void AddReservationTime();
void DisplayPatientRecord();
#endif