#include <stdio.h>
#include <time.h>

int main() {

    /*wandelt int time in lesbaren String um */
    time_t current_time = time(NULL); //wenn NULL = aktuelle Zeit am PC;
    printf("Current time (as an int): %ld\n", (long)current_time);

    struct tm* local_time = localtime(&current_time);

    char formatted_time[100];
    const char* format = "%A %d.%m.%Y %H:%M:%S";

    strftime(formatted_time, sizeof(formatted_time), format, local_time);
    printf("Current time as a readable String: %s\n", formatted_time);


    /*wandelt lesbaren String in time_t int um */
    const char* time_str = "10.05.2023";
    const char* format_2 = "%d.%m.%Y";

    struct tm tm_val;
    strptime(time_str, format_2, &tm_val);

    time_t time_val = mktime(&tm_val);
    printf("Output as an int (time_t value): %ld\n", (long)time_val);
}



