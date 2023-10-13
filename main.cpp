// ACADEMIC INTEGRITY PLEDGE
//
// - I have not used source code obtained from another student nor
//   any other unauthorized source, either modified or unmodified.
//
// - All source code and documentation used in my program is either
//   my original work or was derived by me from the source code
//   published in the textbook for this course or presented in
//   class.
//
// - I have not discussed coding details about this project with
//   anyone other than my instructor. I understand that I may discuss
//   the concepts of this program with other students and that another
//   student may help me debug my program so long as neither of us
//   writes anything during the discussion or modifies any computer
//   file during the discussion.
//
// - I have violated neither the spirit nor letter of these restrictions.
//
//
//
// Signed:Mark P. Earl                                   Date:10/17/2023

// 3460:426 Lab 1 - Basic C shell rev. 9/10/2020

/* Basic shell */

/*
 * This is a very minimal shell. It finds an executable in the
 * PATH, then loads it and executes it (using execv). Since
 * it uses "." (dot) as a separator, it cannot handle file
 * names like "minishell.h"
 *
 * The focus on this exercise is to use fork, PATH variables,
 * and execv.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_ARG_LEN 16
#define MAX_LINE_LEN 80
#define WHITESPACE " ,\t\n"

struct command_t
{
   char *name;
   int argc;
   char *argv[MAX_ARGS];
};

/* Function prototypes */
int parseCommand(char *, struct command_t *);
void printPrompt();
void readCommand(char *);

int main(int argc, char *argv[])
{
   int pid;
   int status;
   char cmdLine[MAX_LINE_LEN];
   struct command_t command;

   bool done = false;
   while (!done)
   {
      printPrompt();
      /* Read the command line and parse it */
      readCommand(cmdLine);
      parseCommand(cmdLine, &command);
      command.argv[command.argc] = NULL;

      // If you are not passing any command line arguments, you should define an empty array of strings and pass
      // that as args.
      if (command.argc == 1)
      {
         char *args[] = {NULL};
         for (int i = 0; i < MAX_ARGS; ++i)
         {
            command.argv[i] = args[i];
         }
      }

      /*
         This shell directly supports the following internal commands:

         • C file1 file2 Copy; create file2, copy all bytes of file1 to file2 without deleting file1.
         • D file Delete the named file.
         • E comment Echo; display comment on screen followed by a new line (multiple
             spaces/tabs may be reduced to a single space); if no argument simply
             issue a new prompt.
         • H Help; display the user manual.
         • L List the contents of the current directory.
         • M file Make; create the named text file by launching a text editor.
         • P file Print; display the contents of the named file on screen.
         • Q Quit the shell.
         • S Surf the web by launching a browser as a background process.
         • W Wipe; clear the screen.
         • X program Execute the named program.

         All commands are case sensitive. Any command not part of this list should just be passed to execvp() and
         normal execution attempted.
      */

      switch (*command.name)
      {

      // C file1 file2 Copy; create file2, copy all bytes of file1 to file2 without deleting file1.
      case 'C':
         strcpy(command.name, "cp");
         break;

      // D file Delete the named file.
      case 'D':
         strcpy(command.name, "rm");
         break;

      // E comment Echo; display comment on screen followed by a new line (multiple
      // spaces/tabs may be reduced to a single space); if no argument simply
      // issue a new prompt.
      case 'E':
         strcpy(command.name, "echo");
         break;

      // H Help; display the user manual
      case 'H':
         strcpy(command.name, "man");
         command.argv[0] = (char *)"man";
         command.argv[1] = (char *)"./manpage.1";
         command.argv[2] = NULL;
         break;

      // L List the contents of the current directory.
      case 'L':

      {
         printf("\n");

         // Create a child process for 'pwd'
         int pid_pwd = fork();
         if (pid_pwd == 0)
         {
            // Child process for 'pwd'
            strcpy(command.name, "pwd");
            status = execvp(command.name, command.argv);
            if (status == -1)
            {
               perror("Error");
               exit(EXIT_FAILURE);
            }
         }
         else if (pid_pwd < 0)
         {
            perror("Fork error");
         }
         else
         {
            // Parent process
            waitpid(pid_pwd, NULL, 0); // Wait for the 'pwd' command to finish
         }

         printf("\n");

         // Create another child process for 'ls -l'
         int pid_ls = fork();
         if (pid_ls == 0)
         {
            // Child process for 'ls -l'
            strcpy(command.name, "ls");
            command.argv[0] = (char *)"ls";
            command.argv[1] = (char *)"-l";
            command.argv[2] = NULL;
            status = execvp(command.name, command.argv);
            if (status == -1)
            {
               perror("Error");
               exit(EXIT_FAILURE);
            }
         }
         else if (pid_ls < 0)
         {
            perror("Fork error");
         }
         else
         {
            // Parent process
            waitpid(pid_ls, NULL, 0); // Wait for the 'ls -l' command to finish
         }
         continue;
      }

      // M file Make; create the named text file by launching a text editor.
      case 'M':
         strcpy(command.name, "nano");
         break;

      // P file Print; display the contents of the named file on screen.
      case 'P':
         strcpy(command.name, "more");
         break;

      // Q Quit the shell.
      case 'Q':
         done = true;
         break;

      // S Surf the web by launching a browser as a background process.
      case 'S':
         strcpy(command.name, "firefox");
         break;

      // W Wipe; clear the screen.
      case 'W':
         strcpy(command.name, "clear");
         break;

      // X program Execute the named program.
      case 'X':
         strcpy(command.name, command.argv[1]);
         break;

      // Any command not part of this list should just be passed to execvp() and
      // normal execution attempted. So no default case needed
      default:
         break;
      }

      // If the user did not request to quit the shell, attempt execution
      if (!done)
      {
         /* Create a child process to execute the command */
         if ((pid = fork()) == 0)
         {
            /* Child executing command */

            // Check if the command name is not empty and is valid
            if (strlen(command.name) > 0)
            {
               status = execvp(command.name, command.argv);
               if (status == -1)
               {
                  perror("Error");
                  exit(EXIT_FAILURE); // Exit the child process with an error code
               }
            }

            // If the command name is empty (just pressing 'Enter') or an unknown command, exit the child process with success
            else
            {
               exit(EXIT_SUCCESS);
            }

            return 0;
         }
      }

      /* Wait for the child to terminate, with one exception, allow Firefox to run in background */
      if (strcmp(command.name, "firefox") != 0)
      {
         wait(NULL);
      }
   }

   /* Shell termination */
   printf("\n\n shell: Terminating successfully\n");
   return 0;
}

/* End basic shell */

/* Parse Command function */

/* Determine command name and construct the parameter list.
 * This function will build argv[] and set the argc value.
 * argc is the number of "tokens" or words on the command line
 * argv[] is an array of strings (pointers to char *). The last
 * element in argv[] must be NULL. As we scan the command line
 * from the left, the first token goes in argv[0], the second in
 * argv[1], and so on. Each time we add a token to argv[],
 * we increment argc.
 */
int parseCommand(char *cLine, struct command_t *cmd)
{
   int argc;
   char **clPtr;
   /* Initialization */
   clPtr = &cLine; /* cLine is the command line */
   argc = 0;
   cmd->argv[argc] = (char *)malloc(MAX_ARG_LEN);
   /* Fill argv[] */
   while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL)
   {
      cmd->argv[++argc] = (char *)malloc(MAX_ARG_LEN);
   }

   /* Set the command name and argc */
   cmd->argc = argc - 1;
   cmd->name = (char *)malloc(sizeof(cmd->argv[0]));
   strcpy(cmd->name, cmd->argv[0]);
   return 1;
}

/* End parseCommand function */

/* Print prompt and read command functions - Nutt pp. 79-80 */

void printPrompt()
{
   /* Build the prompt string to have the machine name,
    * current directory, or other desired information
    */
   char promptString[] = "linux(mpe12)|>";
   printf("%s ", promptString);
}

void readCommand(char *buffer)
{
   /* This code uses any set of I/O functions, such as those in
    * the stdio library to read the entire command line into
    * the buffer. This implementation is greatly simplified,
    * but it does the job.
    */
   fgets(buffer, 80, stdin);
}

/* End printPrompt and readCommand */
