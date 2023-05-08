#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unitTests.h"


#define INPUT_SIZE 50

FILE * open_read_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file: %s\n", filename);
        return NULL;
    }
    return file;
}

typedef struct {
    char date[11];
} Birthdate;

typedef struct {
    char firstName[INPUT_SIZE];
    char lastName[INPUT_SIZE];
    Birthdate birthDate;
    int insurance;
    char email[INPUT_SIZE];
    int phone;
    char arrival_mode[INPUT_SIZE/10];
} Patient;

int read_patient_data(FILE *file, Patient *patient) {
    char line[INPUT_SIZE*8];
    if (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        //if (token == NULL)
          //  return 0;       //wenn .csv file nicht richtig formatiert;
        snprintf(patient->firstName, sizeof(patient->firstName), "%s", token);

        token = strtok(NULL, ",");
        snprintf(patient->lastName, sizeof(patient->lastName), "%s", token);
       
        token = strtok(NULL, ",");
        snprintf(patient->birthDate.date, sizeof(patient->birthDate.date), "%s", token);

        token = strtok(NULL, ",");
        patient->insurance = atoi(token);

        token = strtok(NULL, ",");
        snprintf(patient->email, sizeof(patient->email), "%s", token);

        token = strtok(NULL, ",");
        patient->phone = atoi(token);

        token = strtok(NULL, "\n");
        snprintf(patient->arrival_mode, sizeof(patient->arrival_mode), "%s", token);

        return 1;
    }
    return 0;
}

FILE * open_open_write_csv(const char *filename) {
        FILE *file = fopen(filename, "a");
        if (file == NULL) {
            printf("Error finding the file: %s\n", filename);
            return NULL;
        }
        return file;
    }
    
    
void input_data_patient(Patient *patient){
    printf("First name of patient: ");
    scanf("%49s", patient->firstName);
    printf("\n");
    printf("Last name of patient: ");
    scanf("%s", patient->lastName);
    printf("\n");
    
    //birthdate
    printf("Date of birth of patient (TAG.MONAT.YEAR: ");
    scanf("%49s,", patient->birthDate.date);
    printf("\n");
    
    printf("Insurance number of patient: ");
    scanf("%d", &patient->insurance);
    printf("\n");
    
    printf("E-Mail of patient: ");
    scanf("%49s", patient->email);
    printf("\n");
    
    printf("Phone number of patient: ");
    scanf("%d", &patient->phone);
    printf("\n");
    
    printf("Arrival of patient: ");
    scanf("%9s", patient->arrival_mode);
    printf("\n");
}


void write_to_csv(FILE *file, Patient *patient) {
    fprintf(file, "%s,%s,%s,%d,%s,%d,%s\n",
                patient->firstName,
                patient->lastName,
                patient->birthDate.date,
                patient->insurance,
                patient->email,
                patient->phone,
                patient->arrival_mode);
    }


int main(int argc, const char *argv[]) {
    while(1) {
        
        printf("Do you want to READ [press r] or WRITE [press w] to a .csv file or exit [press e]?\n");
        char user_choice = ' ';
        scanf(" %c", &user_choice);
        
        const char *filename = "patient_data.csv";
        FILE *file = open_read_csv(filename);
        Patient patient;
        
        // READ
        if(user_choice == 'r') {
            
            if (file != NULL) {
                
                char header_line[INPUT_SIZE*2];                           // nur damit erste Überschrift Line in .csv übersprungen wird;
                fgets(header_line, sizeof(header_line), file);  // 1. line wird eingelesen, aber nix damit gemacht;
                
                while (read_patient_data(file, &patient)) {
	

                    printf("%s, %s, %s, %d, %s, %d, %s\n",
                           patient.firstName,
                           patient.lastName,
                           patient.birthDate.date,
                           patient.insurance,
                           patient.email,
                           patient.phone,
                           patient.arrival_mode);
unitTest_firstLetterBig(patient.firstName);
unitTest_validEmail(patient.email); 
                }
                fclose(file);
            }
        }
        
        // WRITE
        else if(user_choice == 'w') {
            printf("How many patients do you want to add to the .csv file?\n");
            int num_patients = 0;
            scanf(" %d", &num_patients);
            
            if(num_patients > 0) {
                Patient *new_patients = malloc(num_patients * sizeof(Patient));
                FILE *file = open_open_write_csv(filename);
                             if (file != NULL) {
                                 for (int i = 0; i < num_patients; i++) {
                                     input_data_patient(&new_patients[i]);
                                     write_to_csv(file, &new_patients[i]);
                                 }
                                 fclose(file);
                             }
                        free(new_patients); // Moved outside the loop
                          }
                      }

                      // EXIT
                      else if (user_choice == 'e') {
                          return 0;
                      }

                      else {
                          printf("Please enter r for READ or w for WRITE or e for EXIT\n");
                      }
                }
                  return 0;
        }
            

