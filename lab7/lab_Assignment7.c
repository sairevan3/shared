/*Sai Revan Vemuri
blazerid: vemuris
To compile & Run : using make file
OR
To compile : gcc -Wall -o lab7 lab_Assignment7.c
To run : ./lab7 sample.t
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 256
#define OUTPUT_FILE "output.log"

double gettime(void) {
    struct timeval tval;
    gettimeofday(&tval, NULL);
    return (double)tval.tv_sec + (double)tval.tv_usec / 1000000.0;
}

void log_execution(const char *command, time_t start_time, time_t end_time) {
    FILE *output_file = fopen(OUTPUT_FILE, "a");
    if (output_file == NULL) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }
    setenv("TZ", "America/Chicago", 1);//setting time zone to central time
    tzset();
    
    // Convert time_t to string using ctime
    char *start_time_str = ctime(&start_time);
    char *end_time_str = ctime(&end_time);

    // Remove newline character from ctime output
    start_time_str[strcspn(start_time_str, "\n")] = '\0';
    end_time_str[strcspn(end_time_str, "\n")] = '\0';

    fprintf(output_file, "%s\t%s\t%s\n", command, start_time_str, end_time_str);
    fclose(output_file);
}

void execute_commands(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    char command[MAX_COMMAND_LENGTH];
    while (fgets(command, sizeof(command), file) != NULL) {
        command[strcspn(command, "\n")] = '\0';  // removing newline

        pid_t pid;
        pid = fork();
        if (pid < 0) {
            perror("Fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {// this is child process
            char *args[] = {"/bin/sh", "-c", command, NULL};
            execvp(args[0], args);
            perror("Exec");
            exit(EXIT_FAILURE);
        } 
        else {// this is parent process
            time_t start_time = time(NULL);
            int status;
            waitpid(pid, &status, 0);
            time_t end_time = time(NULL);

            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {//the child process terminates normally
                log_execution(command, start_time, end_time);// function call
            } 
            else {
                fprintf(stderr, "Command '%s' failed with status %d\n", command, WEXITSTATUS(status));
            }
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    execute_commands(argv[1]);
    return EXIT_SUCCESS;
}

