#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/functions.h"

void test_add_patient(Patient patients[MAX_PAT], int patient_record, char* svNr, char* vorname, char* nachname, char* gebdat, char* telefon, char* email, char* arrival_method) {
    strcpy(patients[patient_record].svNr, svNr);
    strcpy(patients[patient_record].vorname, vorname);
    strcpy(patients[patient_record].nachname, nachname);
    strcpy(patients[patient_record].gebdat, gebdat);
    strcpy(patients[patient_record].telefon, telefon);
    strcpy(patients[patient_record].email, email);
    strcpy(patients[patient_record].arrival_method, arrival_method);
    
    
}

TEST_CASE("Patient data is stored in array", "[add_patient]") {
    Patient patients[MAX_PAT];
    memset(patients, 0, sizeof(patients));  // Initialize the array to zeros
    
    test_add_patient(patients, 0, "1234567890", "Max", "Muster", "01.01.2000", "123456789", "user@gmail.com", "Ambulance");  // You will have to manually input data here when the test runs
    test_add_patient(patients, 1, "2035190192", "Phil", "Hort", "05.02.2002", "06643610101", "phil34@gmail.com", "Other");

    REQUIRE(strcmp(patients[0].svNr, "1234567890") == 0);  
    REQUIRE(strcmp(patients[0].vorname, "Max") == 0); 
    REQUIRE(strcmp(patients[0].nachname, "Muster") == 0); 
    REQUIRE(strcmp(patients[0].gebdat, "01.01.2000") == 0); 
    REQUIRE(strcmp(patients[0].telefon, "123456789") == 0); 
    REQUIRE(strcmp(patients[0].email, "user@gmail.com") == 0); 
    REQUIRE(strcmp(patients[0].arrival_method, "Ambulance") == 0); 
    
    
    REQUIRE(strcmp(patients[1].svNr, "2035190192") == 0);  
    REQUIRE(strcmp(patients[1].vorname, "Phil") == 0); 
    REQUIRE(strcmp(patients[1].nachname, "Hort") == 0); 
    REQUIRE(strcmp(patients[1].gebdat, "05.02.2002") == 0); 
    REQUIRE(strcmp(patients[1].telefon, "06643610101") == 0); 
    REQUIRE(strcmp(patients[1].email, "phil34@gmail.com") == 0); 
    REQUIRE(strcmp(patients[1].arrival_method, "Other") == 0); 
   
}
