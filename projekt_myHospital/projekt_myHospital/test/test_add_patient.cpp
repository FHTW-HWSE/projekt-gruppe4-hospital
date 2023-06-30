#include "functions.h"

TEST_CASE("Test add_patient") {
    // Create a test case using a specific set of inputs

    // Example input
    Patient patients1[MAX_PAT];
    Patient patients2[MAX_PAT];
    int patient_record1=0,patient_record2 = 0;

    add_patient(patients1, patient_record1);
    check_file(patients2, patient_record2);

    //Check if struct matches file output
    REQUIRE(strcmp(patients1[0].svNr, patients2[0].svNr) == 0);
    REQUIRE(strcmp(patients1[0].vorname, patients2[0].vorname) == 0);
    REQUIRE(strcmp(patients1[0].nachname, patients2[0].nachname) == 0);
    REQUIRE(strcmp(patients1[0].gebdat, patients2[0].gebdat) == 0);
    REQUIRE(strcmp(patients1[0].email, patients2[0].email) == 0);
    REQUIRE(strcmp(patients1[0].arrival_method, patients2[0].arrival_method) == 0);
    REQUIRE(strcmp(patients1[0].status, patients2[0].status) == 0);
}