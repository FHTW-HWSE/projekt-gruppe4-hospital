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
#include "catch2/catch.hpp"

void reset_seats(Seat seats[MAX_SEAT],Patient patients[MAX_PAT]){
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            int index = i * 5 + j;
            seats[index].row = i+1;
            seats[index].spot = j+1;
        }
    }
    FILE *fpointer_seat=fopen("seats.txt","w");
    for (int i = 0; i < MAX_SEAT; ++i) {
        fprintf(fpointer_seat,"%d,%d,Free;\n",
                seats[i].row,seats[i].spot);
    }
    fclose(fpointer_seat);
}
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
void load_seat_data(Seat seats[MAX_SEAT]){
    FILE *fpointer_seat;
    fpointer_seat= fopen("seats.txt","r");

    if (fpointer_seat == NULL) {
        printf("Failed to open the file (seats.txt).\n");
        //reset_seats(seats,patients);
        return;
    }

    int read;
    int record=0;

    do{
        char row_buffer=0;
        char spot_buffer=0;

        read = fscanf(fpointer_seat, "%c,%c,%29[^;\n]%*[^\r\n]%*[\r\n]",
                      &row_buffer, &spot_buffer, seats[record].status);

        //printf("row_buffer=%c, spot_buffer=%c, status=%s\n", row_buffer, spot_buffer, seats[record].status);


        int row_value =row_buffer - '0';
        int spot_value =spot_buffer - '0';
        seats[record].row = row_value;
        seats[record].spot = spot_value;

        //printf("row_value=%d, spot_value=%d\n", row_value, spot_value);

        if (read==3) record++;
        else{
            printf("Formatting error! (seats.txt)\n");
            printf("read = %d\n", read);
            printf("R%dS%d - %s\n",row_value,spot_value,seats[record].status);
            break;
        }

    } while (!feof(fpointer_seat));

    fclose(fpointer_seat);

    /*for (int i = 0; i < MAX_SEAT; ++i) {
        printf("%d,%d,%s;\n",seats[i].row,seats[i].spot,seats[i].status);
    }*/


    if(record==25)
        printf("\nSeat data loaded!\n\n");
    else
        printf("Seat data could not be loaded!");
}
void reset_er(ER er[MAX_ER]){
    for (int i = 0; i < MAX_ER; ++i) {
        er[i].room=i+1;
    }
    FILE *fpointer_er = fopen("er.txt","w");
    for (int i = 0; i < MAX_ER; ++i) {
        fprintf(fpointer_er,"%d,Free;\n",
                er[i].room);
    }
    fclose(fpointer_er);
}
void load_er_data(ER er[MAX_ER]){

    FILE *fpointer_er = fopen("er.txt", "r");

    if (fpointer_er == NULL) {
        printf("Failed to open the file. (er.txt)\n");
        reset_er(er);
        return;
    }

    int read;
    int record=0;

    do{
        char room_buffer[3];

        read= fscanf(fpointer_er, "%3[^,],%29[^;\n]%*[^\r\n]%*[\r\n]",
                     room_buffer, er[record].status);


        int room_value = strtol(room_buffer, NULL, 10);
        er[record].room = room_value;

        //printf("row_value=%d, spot_value=%d\n", row_value, spot_value);

        if (read==2) record++;
        else{
            printf("Formatting error! (er.txt)\n");
            printf("read = %d\n", read);
            printf("R%d - %s\n",room_value,er[record].status);
            break;
        }

    } while (!feof(fpointer_er));

    fclose(fpointer_er);

    if(record==10)
        printf("\nER data loaded! (record: %i)\n\n",record);
    else
        printf("ER data could not be loaded! \nrecord");
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
void add_patient(Patient patients[MAX_PAT], int patient_record){

    FILE *fpointer_patient;
    FILE *fpointer_ambulance;
    FILE *fpointer_other;



    strcpy(patients[patient_record].svNr,"0000000001");
    strcpy(patients[patient_record].vorname,"John");
    strcpy(patients[patient_record].nachname,"Doe");
    strcpy(patients[patient_record].gebdat,"01.01.1997");
    strcpy(patients[patient_record].telefon,"+4366464448");
    strcpy(patients[patient_record].email,"johndoe@gmail.com");
    strcpy(patients[patient_record].arrival_method,"Other");
    strcpy(patients[patient_record].status,"-");

    fpointer_patient = fopen("patients/patients.txt","w");

    if(fpointer_patient==NULL){
        printf("Couldn't find file ---> creating new file\n");
    }

    patients[patient_record].date_of_arrival= time(NULL);

    fprintf(fpointer_patient,"%s,%s,%s,%s,%s,%s,%s,%lld,%s;\n",
            patients[patient_record].svNr,patients[patient_record].vorname,patients[patient_record].nachname,patients[patient_record].gebdat,
            patients[patient_record].telefon,patients[patient_record].email, patients[patient_record].arrival_method,
            patients[patient_record].date_of_arrival, patients[patient_record].status);

    fclose(fpointer_patient);

}
void check_file(Patient patients[MAX_PAT], int patient_record){

    for (int i = 0; i < MAX_PAT; ++i) {
        strcpy(patients[i].svNr,"");
    }

    FILE *fpointer_ambulance= fopen("patients/patients.txt", "r");
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
void load_archive(Archive archives[MAX_ARCHIVE]){

    for (int i = 0; i < MAX_PAT; ++i) {
        strcpy(archives[i].svNr, "");
    }

    FILE *fpointer_treated= fopen("patients/treated.txt", "r");
    int read;
    char date_of_arrival_str[20];
    int patient_record=0;

    if (fpointer_treated == NULL){
        printf("treated.txt not found!");
        return;
    }

    do {
        read = fscanf(fpointer_treated, "%50[^,],%50[^,],%50[^,],%20[^,],%50[^,],%50[^,],%50[^,],%50[^,],%50[^;\n]%*[^\r\n]%*[\r\n]",
                      archives[patient_record].svNr, archives[patient_record].vorname, archives[patient_record].nachname,
                      archives[patient_record].gebdat, archives[patient_record].telefon, archives[patient_record].email,
                      archives[patient_record].arrival_method, date_of_arrival_str, archives[patient_record].status);

        if(read==9) {
            archives[patient_record].date_of_arrival = strtoll(date_of_arrival_str, NULL, 10);
            patient_record++;
        }
        else{
            printf("No records! (treated.txt) read=%d\n",read);
            break;
        }

    } while (!feof(fpointer_treated) && patient_record <= MAX_ARCHIVE);
    fclose(fpointer_treated);

    printf("Archives loaded!");
}
int load_register(Register reg[MAX_REG],int record) {
    for (int i = 0; i < MAX_REG; ++i) {
        strcpy(reg[i].pID, "");
    }

    FILE* fpointer_register;
    fpointer_register = fopen("test_register.txt", "r");

    if (fpointer_register == NULL) {
        printf("register.txt not found!\n");
        return -1;
    }

    int read;
    record = 0;
    int flag = 0;

    do {
        char row_buffer, spot_buffer, start_buffer[20], end_buffer[20];

        read = fscanf(fpointer_register, "%29[^,],%c,%c,%29[^,],%29[^;\n]%*[;\n]",
                      reg[record].pID, &row_buffer, &spot_buffer, start_buffer, end_buffer);


        reg[record].seat_row = row_buffer - '0';
        reg[record].seat_spot = spot_buffer - '0';
        reg[record].start_time = strtoll(start_buffer, NULL, 10);
        reg[record].end_time = strtoll(end_buffer, NULL, 10);

        /*printf("Read: %d\n", read);
        printf("pID: %s\n", reg[record].pID);
        printf("row_buffer: %c\n", row_buffer);
        printf("spot_buffer: %c\n", spot_buffer);
        printf("start_buffer: %s\n", start_buffer);
        printf("end_buffer: %s\n", end_buffer);*/

        if (read == 5) {
            record++;
        } else {
            printf("Error loading register.txt! read:%i\n", read);
            flag = 1;
            break;
        }

        if (ferror(fpointer_register)) {
            printf("Error opening file!");
            return 1;
        }
    } while (!feof(fpointer_register) && record <= MAX_REG);

    if (flag == 0) {
        printf("register.txt opened successfully!\n\n");
    }

    fclose(fpointer_register);

    return 0;
}
void successful_treatment(Patient patients[MAX_PAT], ER er[MAX_ER]){

    char input[11]="5110300701";
    int flag=1;


    while(flag==1) {
        int fail_counter=0;

        for (int i = 0; i < MAX_ER; ++i) {
            if (strcmp(er[i].status, input) == 0) {
                printf("Match found!\n");
                strcpy(er[i].status, "Free");
                printf("%d - %s\n",er[i].room,er[i].status);
                flag=0;
                break;
            } else fail_counter++;
        }
        if (fail_counter++ >= MAX_ER) {
            printf("Patient isn't in the ER!\n");
            flag = 1;
        } else flag=0;
    }

    for (int i = 0; i < MAX_PAT; ++i) {
        if (strcmp(patients[i].svNr, input) == 0){
            strcpy(patients[i].status, "treated");
            FILE *fpointer_treated = fopen("successful_treatment/treated.txt","w");
            fprintf(fpointer_treated,"%s,%s,%s,%s,%s,%s,%s,%lld,%s;\n",
                    patients[i].svNr, patients[i].vorname, patients[i].nachname,
                    patients[i].gebdat,patients[i].telefon, patients[i].email,
                    patients[i].arrival_method,patients[i].date_of_arrival, patients[i].status);
            fclose(fpointer_treated);
            break;
        }
    }


    FILE *fpointer_er= fopen("er.txt","w");

    for (int i = 0; i < MAX_ER; ++i) {
        fprintf(fpointer_er,"%d,%s;\n",
                er[i].room, er[i].status);
    }
    fclose(fpointer_er);
}