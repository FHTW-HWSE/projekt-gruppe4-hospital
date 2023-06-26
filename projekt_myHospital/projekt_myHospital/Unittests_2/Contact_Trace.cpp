#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <stdio.h>
#include <string.h>

#define MAX_NEIGH 100
#define MAX_REG 100
#define MAX_SEAT 100

typedef struct {
    char ID[12];
    char n1[50];
    char n2[50];
    char n3[50];
    char n4[50];
} Neighbour;

typedef struct {
    // Register structure definition goes here
} Register;

typedef struct {
    // Seat structure definition goes here
} Seat;

void contact_trace(Neighbour neigh[MAX_NEIGH], Register reg[MAX_REG], Seat seats[MAX_SEAT], const char* patientID, char* output) {
    int flag = 1;
    int fail_counter = 0;

    while (flag == 1) {
        flag = 0;

        for (int i = 0; i < MAX_NEIGH; ++i) {
            if (strcmp(neigh[i].ID, patientID) == 0) {
                sprintf(output, "%s had contact with following people:\n%s\n%s\n%s\n%s",
                        neigh[i].ID, neigh[i].n1, neigh[i].n2, neigh[i].n3, neigh[i].n4);
                flag = 0;
                break;
            } else {
                fail_counter++;
            }
        }

        if (fail_counter >= MAX_NEIGH) {
            sprintf(output, "Error!\n");
            flag = 1;
        }
    }
}

TEST_CASE("Contact Trace") {
    Neighbour neigh[MAX_NEIGH];
    Register reg[MAX_REG];
    Seat seats[MAX_SEAT];

    SECTION("Valid patient ID") {
        // Initialize the test data
        strcpy(neigh[0].ID, "Patient1");
        strcpy(neigh[0].n1, "Contact1");
        strcpy(neigh[0].n2, "Contact2");
        strcpy(neigh[0].n3, "Contact3");
        strcpy(neigh[0].n4, "Contact4");
        strcpy(neigh[1].ID, "Patient2");
        strcpy(neigh[1].n1, "Contact5");
        strcpy(neigh[1].n2, "Contact6");
        strcpy(neigh[1].n3, "Contact7");
        strcpy(neigh[1].n4, "Contact8");

        char output[1000];

        contact_trace(neigh, reg, seats, "Patient1", output);

        std::string expected_output = "Patient1 had contact with following people:\nContact1\nContact2\nContact3\nContact4";
        REQUIRE(strcmp(output, expected_output.c_str()) == 0);
    }
    SECTION("Invalid patient ID") {
        // Initialize the test data
        strcpy(neigh[0].ID, "Patient1");
        strcpy(neigh[0].n1, "Contact1");
        strcpy(neigh[0].n2, "Contact2");
        strcpy(neigh[0].n3, "Contact3");
        strcpy(neigh[0].n4, "Contact4");
        strcpy(neigh[1].ID, "Patient2");
        strcpy(neigh[1].n1, "Contact5");
        strcpy(neigh[1].n2, "Contact6");
        strcpy(neigh[1].n3, "Contact7");
        strcpy(neigh[1].n4, "Contact8");

        char output[1000];

        contact_trace(neigh, reg, seats, "UnknownPatient", output);

        std::string expected_output = "Error!\n";
        REQUIRE(strcmp(output, expected_output.c_str()) == 0);
    }
    SECTION("Empty Neighbour array") {
        // Initialize the test data
        Neighbour neigh[MAX_NEIGH];
        Register reg[MAX_REG];
        Seat seats[MAX_SEAT];

        char output[1000];

        contact_trace(neigh, reg, seats, "Patient1", output);

        std::string expected_output = "Error!\n";
        REQUIRE(strcmp(output, expected_output.c_str()) == 0);
    }
    SECTION("Neighbour with no contacts") {
        // Initialize the test data
        Neighbour neigh[MAX_NEIGH];
        Register reg[MAX_REG];
        Seat seats[MAX_SEAT];

        strcpy(neigh[0].ID, "Patient1");
        strcpy(neigh[0].n1, "");
        strcpy(neigh[0].n2, "");
        strcpy(neigh[0].n3, "");
        strcpy(neigh[0].n4, "");

        char output[1000];

        contact_trace(neigh, reg, seats, "Patient1", output);

        std::string expected_output = "Patient1 had contact with following people:\n\n\n\n";
        REQUIRE(strcmp(output, expected_output.c_str()) == 0);
    }
    SECTION("Neighbour with multiple contacts") {
        // Initialize the test data
        Neighbour neigh[MAX_NEIGH];
        Register reg[MAX_REG];
        Seat seats[MAX_SEAT];

        strcpy(neigh[0].ID, "Patient1");
        strcpy(neigh[0].n1, "Contact1");
        strcpy(neigh[0].n2, "Contact2");
        strcpy(neigh[0].n3, "");
        strcpy(neigh[0].n4, "");

        char output[1000];

        contact_trace(neigh, reg, seats, "Patient1", output);

        std::string expected_output = "Patient1 had contact with following people:\nContact1\nContact2\n\n";
        REQUIRE(strcmp(output, expected_output.c_str()) == 0);
    }

}