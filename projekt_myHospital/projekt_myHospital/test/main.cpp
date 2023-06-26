#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <iostream>
#include "functions.h"


void reset_seats(Seat seats[MAX_SEAT]){
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

TEST_CASE("Test load_patient_data function") {
    // Create an array of Patient objects to hold the loaded data
    Patient patients[MAX_PAT];
    int patient_record = 0;

    // Call the load_patient_data function
    load_patient_data(patients, patient_record);

    // assertion: Check the first patient's social security number
    REQUIRE(strcmp(patients[0].svNr, "0000000002") == 0);
    REQUIRE(strcmp(patients[0].vorname, "Mohanad") == 0);
    REQUIRE(strcmp(patients[0].nachname, "Alrachid") == 0);
    REQUIRE(strcmp(patients[0].arrival_method, "Ambulance") == 0);
}
TEST_CASE("Test assign_patient_to_seat function") {
    // Create test data (seats, register, patients, record) as needed
    Seat seats[MAX_SEAT]={
            1,1,"Free"
    };
    Register reg[MAX_REG];
    Patient patients[MAX_PAT]={
            "5110300701","Favour","Reuben","30.07.2001",
            "06646404406","favourreub@gmail.com","Other",0,"-"
    };
    int record = 0;
    // Call the assign_patient_to_seat function
    reset_seats(seats);
    //load_patient_data(patients,record);
    //load_seat_data(seats);
    assign_patient_to_seat(seats, reg, patients, record);

    // Add assertions to verify the expected behavior of the function

    // Example assertion: Check if a seat has been assigned to a patient
    REQUIRE(strcmp(seats[0].status, "5110300701") == 0);

    // Example assertion: Check if the patient's status has been updated
    REQUIRE(strcmp(patients[0].status, "Seating") == 0);

    // Add more assertions as needed to cover different aspects of the function's behavior
}
TEST_CASE("Test send_patient_to_er"){
    Register reg[MAX_REG];
    Seat seats[MAX_SEAT]={
            1,1,"5110300701"
    };
    ER er[MAX_ER]={
      1,"Free"
    };
    Patient patients[MAX_PAT]={
            "5110300701","Favour","Reuben","30.07.2001",
            "06646404406","favourreub@gmail.com","Other",0,"Seating"
    };

    send_patient_to_er(seats,reg,patients,er);

    REQUIRE(strcmp(patients[0].status,"in ER")==0);
    REQUIRE(strcmp(seats[0].status,"Free")==0);
    REQUIRE(strcmp(er[0].status,"5110300701")==0);


}