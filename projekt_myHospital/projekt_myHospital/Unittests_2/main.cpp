// Created by Mohanad Alrachid
// Date: 23/06/2023
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#define MAX_ER 10
// Define the structure representing an ER room
typedef struct {
    int room;
    char status[10];
} ER;
// Function to reset the ER rooms and write the initial status to a file
void reset_er(ER er[MAX_ER]) {
    for (int i = 0; i < MAX_ER; ++i) {
        er[i].room = i + 1;
    }
    // Open the file for writing
    FILE* fpointer_er = fopen("er.txt", "w");
    // Write the initial status of each room to the file
    for (int i = 0; i < MAX_ER; ++i) {
        fprintf(fpointer_er, "%d,Free;\n", er[i].room);
    }
    fclose(fpointer_er);
}

TEST_CASE("Reset ER") {
    ER er[MAX_ER];
    // Section to test the reset_er function and check file content
    SECTION("Reset ER and check file content") {
        reset_er(er);

        FILE *fpointer_er = fopen("er.txt", "r");
        // Iterate over each ER room
        for (int i = 0; i < MAX_ER; ++i) {
            int room;
            char status[10];
            // Read the room number and status from the file
            int read = fscanf(fpointer_er, "%d,%[^;];\n", &room, status);

            // Check if the read was successful and the values match the expected values
            // Expecting two values to be read successfully
            REQUIRE(read == 2);
            // The room number expected to be i + 1
            REQUIRE(room == i + 1);
            // The status should be Free
            REQUIRE(strcmp(status, "Free") == 0);
        }
        fclose(fpointer_er);
    }
}
