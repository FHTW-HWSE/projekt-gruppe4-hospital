#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../include/functions.h"

int main() {

    Register reg[MAX_REG];
    Seat seats[MAX_SEAT];
    Patient patients[MAX_PAT];
    ER er[MAX_ER];
    Neighbour neigh[MAX_NEIGH];

    int read;
    int reg_record=0;
    int patient_record=0;
    char input='d';

    while (input!=0){

        load_er_data(er);
        load_seat_data(seats);
        load_patient_data(patients,patient_record);
        load_register(reg, seats, reg_record);


        printf("[1] Patients\n"
               "[2] Seats\n"
               "[3] Show ER's\n"
               "[4] Assign Patient a seat\n"
               "[5] Send Patient to the ER\n"
               "[6] Discharge Patient\n"
               "[7] Contact trace\n\n"
               "[0] End Program\n");
        scanf("%c",&input);

        int i=0;
        char svnr[11];

        switch (input) {
            case '1':
                input = '0';
                printf("[1] Show Patient records \n[2] Add new Patient \n[3] Search for Patient\n");
                scanf(" %c", &input); // Notice the space before %c to consume the newline character
                switch (input) {
                    case '1':
                        while (strcmp(patients[i].svNr, "") != 0) {
                            // Print patient information
                            printf("Social security number: %s\n"
                                   "First Name: %s\n"
                                   "Last Name: %s\n"
                                   "Date of Birth: %s\n"
                                   "Telephone Number: %s\n"
                                   "Email address: %s\n"
                                   "Method of Arrival: %s\n"
                                   "Date of arrival: %s"
                                   "Status: %s\n",
                                   patients[i].svNr, patients[i].vorname, patients[i].nachname, patients[i].gebdat,
                                   patients[i].telefon, patients[i].email, patients[i].arrival_method,
                                   ctime(&patients[i].date_of_arrival), patients[i].status);
                            printf("-----------------------------\n");
                            i++;
                        }
                        break;
                    case '2':
                        add_patient(patients, patient_record);
                        load_patient_data(patients,patient_record);
                        load_seat_data(seats);
                        assign_patient_to_seat(seats, reg, patients, reg_record);
                        //send_patient_to_er(seats, reg, patients, er);
                        //query_seat_neighbour(neigh, reg, seats);

                        break;
                    case '3':
                        printf("Social Security Number of Patient: ");
                        scanf("%11s",svnr);
                        int fail=0;
                        for (int j = 0; j < MAX_PAT; ++j) {
                            if (strcmp(svnr,patients[j].svNr)==0){
                                printf("Social security number: %s\n"
                                       "First Name: %s\n"
                                       "Last Name: %s\n"
                                       "Date of Birth: %s\n"
                                       "Telephone Number: %s\n"
                                       "Email address: %s\n"
                                       "Method of Arrival: %s\n"
                                       "Date of arrival: %s"
                                       "Status: %s\n",
                                       patients[j].svNr, patients[j].vorname, patients[j].nachname, patients[j].gebdat,
                                       patients[j].telefon, patients[j].email, patients[j].arrival_method,
                                       ctime(&patients[j].date_of_arrival), patients[j].status);
                                break;
                            } else fail++;
                        }
                        if (fail>=MAX_PAT){
                            printf("No matches found!\n");
                        }
                        break;
                    default:
                        printf("Invalid input!\n");
                        break;
                }
                sleep(2);
                getchar();
                break;

            case '2':
                input = '0';
                printf("[1] Show seats \n[2] Free all seats\n");
                scanf(" %c", &input); // Notice the space before %c to consume the newline character
                switch (input) {
                    case '1':
                        for (int j = 0; j < MAX_SEAT; ++j) {
                            // Print seat information
                            printf("Row: %d - Seat: %d - Occupied by : %s\n",
                                   seats[j].row, seats[j].spot, seats[j].status);
                        }
                        break;
                    case '2':
                        reset_seats(seats,patients);
                        break;

                    default:
                        printf("Invalid input!\n");
                        break;
                }
                sleep(2);
                getchar();
                break;

            case '3':
                for (int j = 0; j < MAX_ER; ++j) {
                    // Print seat information
                    printf("ER: %d - occupied by: %s\n",
                           er[j].room,er[j].status);
                }
                sleep(2);
                getchar();
                break;

            case '4':
                assign_patient_to_seat(seats, reg, patients, reg_record);
                sleep(2);
                getchar();
                break;

            case '5':
                send_patient_to_er(seats,reg,patients,er);
                assign_patient_to_seat(seats,reg,patients,reg_record);
                sleep(2);
                getchar();
                break;

            case '6':
                successful_treatment(patients, er);
                sleep(2);
                getchar();
                break;

            case '7':
                query_seat_neighbour(neigh,reg,seats);
                contact_trace(neigh,reg,seats);
                sleep(2);
                getchar();
                break;

            case '0':
                return -1;

            default:
                printf("Invalid input!\n");
                break;
        }

    }
    return 0;
}
