//==============================================================================
// Author      : Zhenia Steger
// Purpose     : Demonstrate the collatz conjecture using threads.
// =============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Prototype functions
void ParentProcess(void);
void ChildProcess(int input);

// Main function, runs the program, takes one argument (integer)
int main(int argc, char *argv[])
{
  // Check for correct number of arguments
  if (argc != 2) {
    fprintf(stderr, "Error. Incorrect number of arguments (Needed 1).\n");
    return -1;
  }

  int inputInt;               // Store the integer for computation
  if (atoi(argv[1]) == 0) {
    fprintf(stderr, "Number is not an integer.\n");
    return -1;
  }
  inputInt = atoi(argv[1]);   // Assigns the value to integer from the prog argument
  if (inputInt < 0) {
    fprintf(stderr, "Number cannot be negative.\n");
    return -1;
  }

  pid_t pid = fork();         // fork the process

  // Run the child process if PID is 0; otherwise run the parent
  if (pid == 0) { ChildProcess(inputInt); }
  else { ParentProcess(); }
}

// Parent process - waits for the child process to complete
void ParentProcess(void) {
  printf("=== Parent Process Entered ===\n");
  wait(NULL); // Waits for child process to end.
  printf("=== Parent Process Ended ===\n");
}

// Child process - Performs the Collatz conjecture on the input integer
void ChildProcess(int input) {
  printf("=== Child Process Entered ===\n");
  int integer = input;
  printf("%d, ", integer);
    while (integer != 1) {
      if ((integer & 1) == 0) {
        integer /= 2;
        printf("%d, ", integer);
      }
      else {
        integer = (3 * integer) + 1;
        printf("%d, ", integer);
      }
    }
  printf("\n=== Child Process Ended ===\n");
} // END OF PROGRAM
