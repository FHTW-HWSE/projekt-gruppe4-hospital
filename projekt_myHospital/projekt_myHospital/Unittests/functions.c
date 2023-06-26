//
// Created by Favour on 05.06.2023.
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

void load_patient_data(Patient patients[MAX_PAT], int patient_record){

    for (int i = 0; i < MAX_PAT; ++i) {
        strcpy(patients[i].svNr,"");
    }

    FILE *fpointer_ambulance= fopen("patients/patients_ambulance.txt", "r");
    int read;
    char date_of_arrival_str[20];
    patient_record=0;

    if (fpointer_ambulance==NULL){
        printf("ambulance.txt not found!");
        return;
    }

    do {
        read = fscanf(fpointer_ambulance, "%50[^,],%50[^,],%50[^,],%20[^,],%50[^,],%50[^,],%50[^,],%50[^,],%50[^;\n]%*[^\r\n]%*[\r\n]",
                      patients[patient_record].svNr, patients[patient_record].vorname, patients[patient_record].nachname,
                      patients[patient_record].gebdat, patients[patient_record].telefon, patients[patient_record].email,
                      patients[patient_record].arrival_method, date_of_arrival_str, patients[patient_record].status);

        if(read==9) {
            patients[patient_record].date_of_arrival = strtoll(date_of_arrival_str, NULL, 10);
            patient_record++;
        }
        else{
            printf("Formatting error! (patients_ambulance.txt) read=%d\n",read);
            break;
        }

    } while (!feof(fpointer_ambulance)&&patient_record<MAX_PAT);
    fclose(fpointer_ambulance);


    FILE *fpointer_other= fopen("patients/patients_other.txt", "r");

    if (fpointer_other==NULL){
        printf("patients_other.txt not found!");
        return;
    }

    do {
        read = fscanf(fpointer_ambulance, "%50[^,],%50[^,],%50[^,],%20[^,],%50[^,],%50[^,],%50[^,],%50[^,],%50[^;\n]%*[^\r\n]%*[\r\n]",
                      patients[patient_record].svNr, patients[patient_record].vorname, patients[patient_record].nachname,
                      patients[patient_record].gebdat, patients[patient_record].telefon, patients[patient_record].email,
                      patients[patient_record].arrival_method, date_of_arrival_str, patients[patient_record].status);

        if(read==9) {
            patients[patient_record].date_of_arrival = strtoll(date_of_arrival_str, NULL, 10);
            patient_record++;
        }
        else{
            printf("Formatting error! (patients_other.txt) read=%d\n",read);
            break;
        }

    } while (!feof(fpointer_other) && patient_record<=MAX_PAT);
    fclose(fpointer_other);

    printf("Patient data loaded! (record: %i)\n",patient_record);
}

void assign_patient_to_seat(Seat seats[MAX_SEAT], Register reg[MAX_REG], Patient patients[MAX_PAT], int record){

    //load_register(reg, seats, record);
    int occupied_counter=0;
    int seat_flag=0;
    int fail_counter=0;
    char input;

    for (int i = 0; i < MAX_SEAT; ++i) {
        if(strcmp(seats[i].status,"Free")==0) {                  //check for seat that isn't occupied

            char temp[11];

            for (int j = 0; j < MAX_PAT; ++j) {
                if (strcmp(patients[j].status, "-") == 0 && strcmp(patients[j].arrival_method, "Other") == 0) {
                    strcpy(temp, patients[j].svNr);
                    strcpy(patients[j].status,"Seating");
                    strcpy(reg[record].pID,patients[j].svNr);
                    break;
                } else fail_counter++;
            }
            if(fail_counter>=MAX_PAT){
                printf("No eligible patients found for seating!\n");
                return;
            }


            strcpy(seats[i].status,temp);

            reg[record].start_time = time(NULL);
            reg[record].end_time = time(NULL);

            FILE *fpointer_reg;
            //char *string_start= ctime(&reg[record].start_time);
            //char *string_end= ctime(&reg[record].end_time);

            fpointer_reg= fopen("register.txt", "w");

            if (fpointer_reg == NULL){
                printf("Datei nicht gefunden (test_register.txt)!");
            }

            fprintf(fpointer_reg, "%s,%d,%d,%lld,%lld;\n",
                    reg[record].pID, seats[i].row, seats[i].spot, reg[record].start_time, reg[record].end_time);


            fclose(fpointer_reg);
            break;
        } else occupied_counter++;
    }
    if (occupied_counter>=MAX_SEAT)
        printf("All seats are currently occupied!");
}

void send_patient_to_er(Seat seats[MAX_SEAT], Register reg[MAX_REG], Patient patients[MAX_PAT], ER er[MAX_ER]){

    int record =0;
    int seat_flag=0;
    int fail_counter=0;
    //load_register(reg, seats, record);

    char input[11], menu_input;
    long long start;

    fail_counter=0;
    for (int i = 0; i < MAX_PAT; ++i) {
        if (strcmp(patients[i].status,"Seating")==0 || (strcmp(patients[i].arrival_method,"Ambulance")==0 && strcmp(patients[i].status,"in ER")!=0)){
            strcpy(input,patients[i].svNr);
            break;
        }else fail_counter++;
    }
    if (fail_counter>=MAX_PAT){
        printf("No eligible Patients found!\n");
        return;
    } else{
        fail_counter=0;
        for (int j = 0; j < MAX_PAT; ++j) {
            if (strcmp(patients[j].svNr, input) == 0) {
                if (strcmp(patients[j].status, "in ER") == 0) {
                    printf("Patient is already in the ER!\n");
                    return;
                } else {
                    strcpy(patients[j].status, "in ER");
                }
            } else fail_counter++;
        }
        if (fail_counter>=MAX_PAT){
            printf("There is no patient with this social security number!\n");
            return;
        }
    }

    fail_counter=0;
    for (int i = 0; i < MAX_ER; ++i) {
        if (strcmp(er[i].status,"Free")==0){
            strcpy(er[i].status,input);
            //printf("Patient %s has been sent to ER %d\n",input,er[i].room);
            break;
        } else fail_counter++;
    }

    if (fail_counter>=MAX_ER){
        printf("All ER's are currently occupied!");
        return;
    }

    for (int i = 0; i < MAX_SEAT; ++i) {
        if (strcmp(seats[i].status,input)==0){
            strcpy(seats[i].status,"Free");
            break;
        }
    }

    for (int i = 0; i < MAX_REG; ++i) {
        if(strcmp(reg[i].pID,input)==0 && reg[i].start_time==reg[i].end_time){
            start=reg[i].start_time;
            reg[i].end_time= time(NULL);
            reg[i].start_time=start;
        }
    }

}
