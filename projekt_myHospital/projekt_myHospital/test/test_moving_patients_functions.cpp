#include "functions.h"

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
    reset_seats(seats,patients);
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
TEST_CASE("Test successful_treatment"){
    ER er[MAX_ER]={
            1,"5110300701"
    };

    Archive expected_value[MAX_ARCHIVE] = {
            "5110300701", "Favour", "Reuben", "30.07.2001",
            "06646404406", "favour@gmail.com", "Other", 0, "treated"
    };

    Patient patients[MAX_PAT]={
            "5110300701", "Favour", "Reuben", "30.07.2001",
            "06646404406", "favour@gmail.com", "Other", 0, "in Er"
    };
    Archive archive[MAX_ARCHIVE];

    successful_treatment(patients,er);
    //load_archive(archive);


    REQUIRE(strcmp(er[0].status,"Free")==0);
    REQUIRE(strcmp(patients[0].status,"treated")==0);
}
