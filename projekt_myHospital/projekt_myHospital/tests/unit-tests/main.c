#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cmake-build-debug//functions.h"


void reset(Seat seats[MAX_SEAT]){
    FILE *fpointer_patients= fopen("files/test_patients_other.txt","w");
    fprintf(fpointer_patients,"5110300701,Favour,Reuben,30.07.2001,06646404406,favourreuben2001@gmail.com,Other,0,-;\n"
            "000000001,Max,Mustermann,01.01.2000,32148585,max@gmail.com,Other,0,-;\n");
    fclose(fpointer_patients);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            int index = i * 5 + j;
            seats[index].row = i+1;
            seats[index].spot = j+1;
        }
    }
    FILE *fpointer_seat=fopen("files/test_seats.txt","w");
    for (int i = 0; i < MAX_SEAT; ++i) {
        fprintf(fpointer_seat,"%d,%d,Free;\n",
                seats[i].row,seats[i].spot);
    }
    fclose(fpointer_seat);
}

// Define a test case
void load_patient_data(Patient patients[MAX_PAT], int patient_record){

    for (int i = 0; i < MAX_PAT; ++i) {
        strcpy(patients[i].svNr,"");
    }

    int read;
    char date_of_arrival_str[20];
    patient_record=0;

    FILE *fpointer_other= fopen("files/test_patients_other.txt", "r");

    for (int i = 0; i < 2; ++i) {

        read = fscanf(fpointer_other,
                      "%50[^,],%50[^,],%50[^,],%20[^,],%50[^,],%50[^,],%50[^,],%50[^,],%50[^;\n]%*[\n;]",
                      patients[i].svNr, patients[i].vorname, patients[i].nachname,
                      patients[i].gebdat, patients[i].telefon, patients[i].email,
                      patients[i].arrival_method, date_of_arrival_str, patients[i].status);

        if (read == 9) {
            patients[patient_record].date_of_arrival = strtoll(date_of_arrival_str, NULL, 10);
            patient_record++;
        } else {
            printf("Formatting error! (patients_other.txt) read=%d\n", read);
            break;
        }

    }
    fclose(fpointer_other);

    //printf("Patient data loaded! (record: %i)\n",patient_record);
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

            fpointer_reg= fopen("files/test_register.txt", "w");

            if (fpointer_reg == NULL){
                printf("Datei nicht gefunden (test_register.txt)!");
            }

            fprintf(fpointer_reg, "%s,%d,%d,%lld,%lld;\n",
                    reg[record].pID, seats[i].row, seats[i].spot, reg[record].start_time, reg[record].end_time);

            /*printf("Patient: %s has been asssigned seat R%dS%d at %s\n",reg[record].pID,seats[i].row,seats[i].spot,
                   ctime(&reg[record].start_time));*/

            fclose(fpointer_reg);
            break;
        } else occupied_counter++;
    }
    if (occupied_counter>=MAX_SEAT)
        printf("All seats are currently occupied!");

    //Overwriting existing seats.txt file with new data
    FILE *fpointer_seats;
    fpointer_seats= fopen("files/test_seats.txt","w");

    for (int i = 0; i < MAX_SEAT; ++i) {
        fprintf(fpointer_seats,"%d,%d,%s;\n",seats[i].row,seats[i].spot,seats[i].status);
    }

    fclose(fpointer_seats);

    //Overwriting existing patient.txt file with new data
    FILE *fpointer_patient= fopen("files/test_patients_other.txt","w");

    int patient_record=0;

    while (strcmp(patients[patient_record].svNr,"")!=0){
        fprintf(fpointer_patient,"%s,%s,%s,%s,%s,%s,%s,%lld,%s;\n",
                patients[patient_record].svNr,patients[patient_record].vorname,patients[patient_record].nachname,patients[patient_record].gebdat,
                patients[patient_record].telefon,patients[patient_record].email, patients[patient_record].arrival_method,
                patients[patient_record].date_of_arrival, patients[patient_record].status);
        patient_record++;
    }
    fclose(fpointer_patient);

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
            printf("Patient %s has been sent to ER %d\n",input,er[i].room);
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

    //Overwrite existing register.txt file with new data
    FILE *fpointer_reg= fopen("files/test_register.txt","w");

    for (int i = 0; i < MAX_REG; ++i) {
        if(strcmp(reg[i].pID,"")!=0) {
            fprintf(fpointer_reg, "%s,%d,%d,%lld,%lld;\n",
                    reg[i].pID, reg[i].seat_row, reg[i].seat_spot, reg[i].start_time, reg[i].end_time);
        }
    }
    fclose(fpointer_reg);

    FILE *fpointer_seats;
    fpointer_seats= fopen("files/test_seats.txt","w");

    for (int i = 0; i < MAX_SEAT; ++i) {
        fprintf(fpointer_seats,"%d,%d,%s;\n",seats[i].row,seats[i].spot,seats[i].status);
    }

    fclose(fpointer_seats);

    //Overwriting existing patient.txt file with new data
    FILE *fpointer_patient= fopen("files/test_patients.txt","w");

    int patient_record=0;

    while (strcmp(patients[patient_record].svNr,"")!=0){
        fprintf(fpointer_patient,"%s,%s,%s,%s,%s,%s,%s,%lld,%s;\n",
                patients[patient_record].svNr,patients[patient_record].vorname,patients[patient_record].nachname,patients[patient_record].gebdat,
                patients[patient_record].telefon,patients[patient_record].email, patients[patient_record].arrival_method,
                patients[patient_record].date_of_arrival, patients[patient_record].status);
        patient_record++;
    }
    fclose(fpointer_patient);

    FILE *fpointer_other= fopen("files/test_patients_other.txt","w");

    int other_record=0;

    while (strcmp(patients[other_record].svNr,"")!=0){
        if(strcmp(patients[other_record].arrival_method,"Other")==0) {
            fprintf(fpointer_other, "%s,%s,%s,%s,%s,%s,%s,%lld,%s;\n",
                    patients[other_record].svNr, patients[other_record].vorname, patients[other_record].nachname,
                    patients[other_record].gebdat,patients[other_record].telefon, patients[other_record].email,
                    patients[other_record].arrival_method,patients[patient_record].date_of_arrival, patients[other_record].status);
        }
        other_record++;
    }
    fclose(fpointer_other);

    //Overwrite existing er.txt file
    FILE *fpointer_er= fopen("files/test_er.txt","w");

    for (int i = 0; i < MAX_ER; ++i) {
        fprintf(fpointer_er,"%d,%s;\n",
                er[i].room, er[i].status);
    }
    fclose(fpointer_er);
    printf("Success!");
}

void test_load_patient_data() {
    // Define the expected patient data
    Patient expectedPatients[MAX_PAT] = {
            { "5110300701", "Favour", "Reuben", "30.07.2001", "06646404406", "favourreuben2001@gmail.com", "Other", 0, "-" },
            { "000000001", "Max", "Mustermann", "01.01.2000", "32148585", "max@gmail.com", "Other", 0, "-" },
            // Add more expected patient data here
    };

    // Create an array to hold the loaded patient data
    Patient loadedPatients[MAX_PAT];

    // Call the load_patient_data function to load the data from the test file
    load_patient_data(loadedPatients, MAX_PAT);

    // Compare the loaded patient data with the expected patient data
    bool testPassed = true;
    for (int i = 0; i < MAX_PAT; i++) {
        if (strcmp(loadedPatients[i].svNr, expectedPatients[i].svNr) != 0 ||
            strcmp(loadedPatients[i].vorname, expectedPatients[i].vorname) != 0 ||
            strcmp(loadedPatients[i].nachname, expectedPatients[i].nachname) != 0 ||
            strcmp(loadedPatients[i].gebdat, expectedPatients[i].gebdat) != 0 ||
            strcmp(loadedPatients[i].telefon, expectedPatients[i].telefon) != 0 ||
            strcmp(loadedPatients[i].email, expectedPatients[i].email) != 0 ||
            strcmp(loadedPatients[i].arrival_method, expectedPatients[i].arrival_method) != 0 ||
            loadedPatients[i].date_of_arrival != expectedPatients[i].date_of_arrival ||
            strcmp(loadedPatients[i].status, expectedPatients[i].status) != 0) {
            testPassed = false;
            break;
        }
    }

    // Check if the test passed or failed
    if (testPassed) {
        printf("load_patient_data test passed!\n");
    } else {
        printf("load_patient_data test failed!\n");
    }
}
void test_assign_patient_to_seat() {
    // Define test data
    Seat seats[MAX_SEAT] = {
            { 1, 1, "Free" },
            { 1, 2, "Free" },
            // Add more seats here
    };

    Register reg[MAX_REG] = {
            { "5110300701", 1, 1 },
            { "000000001", 1, 2 },
            // Add more registers here
    };

    Patient patients[MAX_PAT] = {
            { "5110300701", "Favour", "Reuben", "30.07.2001", "06646404406", "favourreuben2001@gmail.com", "Other", 0, "Seating" },
            { "000000001", "Max", "Mustermann", "01.01.2000", "32148585", "max@gmail.com", "Other", 0, "Seating" },
            // Add more patients here
    };

    int record = 0;

    // Call the assign_patient_to_seat function to assign a patient to a seat
    load_patient_data(patients,MAX_PAT);
    assign_patient_to_seat(seats, reg, patients, record);

    // Perform assertions to check if the function behaved as expected

    if (strcmp(seats[0].status, patients[0].svNr) == 0 && strcmp(patients[0].status,"Seating")==0) {
        printf("Seat status correctly updated.\n");
    } else {
        printf("Seat status update failed.\n");
    }
}
void test_send_patient_to_er() {
    // Define test data
    Seat seats[MAX_SEAT] = {
            { 1, 1, "Free" },
            { 1, 2, "Free" },
            // Add more seats here
    };

    Register reg[MAX_REG] = {
            { "5110300701", 1, 1 },
            { "000000001", 1, 2 },
            // Add more registers here
    };

    Patient patients[MAX_PAT] = {
            { "5110300701", "Favour", "Reuben", "30.07.2001", "06646404406", "favourreuben2001@gmail.com", "Other", 0, "Seating" },
            { "000000001", "Max", "Mustermann", "01.01.2000", "32148585", "max@gmail.com", "Other", 0, "Seating" },
            // Add more patients here
    };

    ER er[MAX_ER] = {
            { 1, "Free" },
            { 2, "Free" },
            // Add more ERs here
    };

    // Call the send_patient_to_er function to send a patient to the ER
    send_patient_to_er(seats, reg, patients, er);

    // Perform assertions to check if the function behaved as expected
    // ...

    // Example assertions
    if (strcmp(patients[0].status, "in ER") == 0 && strcmp(er[0].status,patients[0].svNr)==0) {
        printf("send_patient_to_er test passed!\n");
    } else {
        printf("send_patient_to_er test failed!\n");
    }
}


int main() {
    // Run the test for load_patient_data function
    Seat seats[MAX_SEAT];
    reset(seats);
    test_load_patient_data();
    test_assign_patient_to_seat();
    test_send_patient_to_er();

    return 0;
}
