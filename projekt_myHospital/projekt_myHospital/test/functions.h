//
// Created by Favour on 05.06.2023.
//

#ifndef PROJEKT_FUNCTIONS_H
#define PROJEKT_FUNCTIONS_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_REG 100
#define MAX_SEAT 25
#define MAX_PAT 100
#define MAX_ER 10
#define MAX_NEIGH 100

typedef struct{
    char svNr[11];
    char vorname[20];
    char nachname[20];
    char gebdat[20];
    char telefon[20];
    char email[40];
    char arrival_method[20];
    time_t date_of_arrival;
    char status[20];
}Patient;

typedef struct{
    //char id[5];
    int row;
    int spot;
    char status[20];
}Seat;

typedef struct {
    int room;
    char status[20];
}ER;

typedef struct {
    char pID[11];
    int seat_row;
    int seat_spot;
    time_t start_time;
    time_t end_time;
}Register;

typedef struct{
    char ID[11];
    char n1[11];
    char n2[11];
    char n3[11];
    char n4[11];

}Neighbour;

void reset_seats(Seat seats[MAX_SEAT],Patient patients[MAX_PAT]);
void reset_er(ER er[MAX_ER]);
int load_register(Register reg[MAX_REG], Seat seats[MAX_SEAT], int record);
void load_patient_data(Patient patients[MAX_PAT], int patient_record);
void load_seat_data(Seat seats[MAX_SEAT]);
void load_er_data(ER er[MAX_ER]);
void assign_patient_to_seat(Seat seats[MAX_SEAT], Register reg[MAX_REG], Patient patients[MAX_PAT], int record);
void send_patient_to_er(Seat seats[MAX_SEAT], Register reg[MAX_REG], Patient patients[MAX_PAT], ER er[MAX_ER]);
void add_patient(Patient patients[MAX_PAT], int patient_record);
void successful_treatment(Patient patients[MAX_PAT], ER er[MAX_ER]);
void query_seat_neighbour(Neighbour neigh[MAX_NEIGH], Register reg[MAX_REG], Seat seats[MAX_SEAT]);
void contact_trace(Neighbour neigh[MAX_NEIGH], Register reg[MAX_REG], Seat seats[MAX_SEAT]);

#endif //PROJEKT_FUNCTIONS_H
