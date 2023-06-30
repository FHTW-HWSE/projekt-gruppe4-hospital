#include "functions.h"

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
TEST_CASE("Test load_seat_data"){
    Seat expected_value[MAX_SEAT]={1,1,"Free"};
    Seat seats[MAX_SEAT];
    Patient patients[MAX_PAT];

    reset_seats(seats,patients);
    load_seat_data(seats);

    REQUIRE(seats[0].row == expected_value[0].row);
    REQUIRE(seats[0].spot == expected_value[0].spot);
    REQUIRE(strcmp(expected_value[0].status,seats[0].status)==0);
}
TEST_CASE("Test load_er_data"){
    ER expected_value[MAX_ER]={1,"Free"};
    ER er[MAX_ER];

    reset_er(er);
    load_er_data(er);

    REQUIRE(er[0].room == expected_value[0].room);
    REQUIRE(strcmp(expected_value[0].status,er[0].status)==0);
}
TEST_CASE("Test load_archive") {
    Archive archive[MAX_ARCHIVE];
    Archive expected_value[MAX_ARCHIVE] = {
            "5110300701", "Favour", "Reuben", "30.07.2001",
            "06646404406", "favour@gmail.com", "Other", 0, "treated"
    };

    load_archive(archive);

    REQUIRE(strcmp(archive[0].svNr, expected_value[0].svNr) == 0);
    REQUIRE(strcmp(archive[0].vorname, expected_value[0].vorname) == 0);
    REQUIRE(strcmp(archive[0].nachname, expected_value[0].nachname) == 0);
    REQUIRE(strcmp(archive[0].gebdat, expected_value[0].gebdat) == 0);
    REQUIRE(strcmp(archive[0].email, expected_value[0].email) == 0);
    REQUIRE(strcmp(archive[0].arrival_method, expected_value[0].arrival_method) == 0);
    REQUIRE(strcmp(archive[0].status, expected_value[0].status) == 0);
}
TEST_CASE("Test load_register"){
    Register expected_Value[MAX_REG]={
            "5110300701",1,1,1688132571,1688132571
    };

    Register reg[MAX_REG];
    Seat seats[MAX_SEAT];
    int record=0;
    load_register(reg,record);

    REQUIRE(strcmp(reg[0].pID,expected_Value[0].pID)==0);
    REQUIRE(reg[0].seat_row==expected_Value[0].seat_row);
    REQUIRE(reg[0].seat_spot==expected_Value[0].seat_spot);
    REQUIRE(reg[0].start_time==expected_Value[0].start_time);
    REQUIRE(reg[0].end_time==expected_Value[0].end_time);
}