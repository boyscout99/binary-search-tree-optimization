/*
Algorithms and Programming
Laboratory number 10
--------------------

Exercise 01
-----------
Considerations
--------------
There are applications in which it may be useful to have
records (i.e., data fields) associated to more than one key.
For example, it may be useful to associate every student's
information to the student last name and first name pair, and to
his/her register number value as well.
In this way, it will be possible to search for a student using
both these keys, obtaining the same performance.

Specifications
--------------
Re-using (and freely modifying) the library
lab09-BSTLibrary
solve the following problem.

A file includes information about students.
For each student the file stores 6 fields (space separated)
on the same row:

- register-number (long integer value or string on 6 digits)
- last-name (30 chars, at most, for each one)
- first-name (30 chars, at most, for each one)
- birth-date (format dd/mm/yyyy)
- program (string of 5 chars)
- enrollment-year (integer value)

File lab10-input.txt shows a correct example of such a file.

Write a program able to execute the following set of commands:

- load name
  reads the file *name* and stores its content in a
  proper data structure.

- searchS last first
  searches in the data structure all data fields related to the
  student with last and first name equal to *last* and *first*,
  respectively.

- searchN integer
  searches in the data structure all data related to the student
  with register number equal to the *integer* value.

- save name
  stores into the file *name* all students information (with the same
  format of the input file).

- quit
  stops the program.

Complexity constraint
---------------------
The data structure has to allow searches (for both the searchS
and the searchN commands) with a logarithmic cost in term of number
of students.

Suggestion
----------
The core idea is to use a BST to store the data and to allow for
searches with a logarithmic cost.
As the specification requires 2 different searching keys, this would
imply two different BSTs, one organized using the first key the other
organized using the second one.
To avoid data duplication it is however possible to merge two "physically"
separated BSTs into a single BSTs.
This BST will have in each node:
- all required data fields
- two set of pointers.
  The first set of pointers will be used to order data following the
  last and first name pair.
  The second one will be used to order data following the register number.

In other words the ADT used for the BST should have more or less the
following definition:

typedef struct elem_t {
  char *name;
  char *date;
  char *course;
  int year;
  int code;
  struct elem_t *left_1;
  struct elem_t *right_1;
  struct elem_t *left_2;
  struct elem_t *right_2;
} elem_s;
*/
#include "binaryTreePublic.h"

int main(void)
{

  int command, saved, end;
  long int id;
  char f_name[MAX_NAME+1];
  char last_n[MAX_NAME+1], first_n[MAX_NAME+1], name[2*MAX_NAME+3];
  FILE *fp;
  node_t *head_N, *head_ID;

  saved = end = 0;
  head_N = head_ID = NULL;

  while(!end)
  {
    fprintf(stdout, "\nCommands:\n\t1) Load file\n\t2) Save data\n");
    fprintf(stdout, "\t3) Search name\n\t4) Search ID\n\t5) Exit\n");
    fprintf(stdout, "\nYour selection: ");
    fscanf(stdin, "%d", &command);

    switch(command)
    {
      case 1://load file
        fprintf(stdout, "Enter file name: ");
        fscanf(stdin, "%s", f_name);
        if(load_file(f_name, "r", &head_N, &head_ID))
          fprintf(stdout, "File loaded correctly.\n");
        else
          fprintf(stdout, "Could not load the file.\n");
        break;

      case 2://save data into a file
        fprintf(stdout, "Enter output file name: ");
        fscanf(stdin, "%s", f_name);
        fp = util_fopen(f_name, "w");
        save_tree_ID(fp, head_N);
        fclose(fp);
        break;

      case 3://search name into BST
        fprintf(stdout, "Enter <last name> <first name> : ");
        fscanf(stdin, "%s %s", last_n, first_n);
        sprintf(name, "%s %s", last_n, first_n);
        search_name(name, head_N);
        break;

      case 4://search ID into BST
        fprintf(stdout, "Enter <student ID>: ");
        fscanf(stdin, "%ld", &id);
        search_ID(id, head_ID);
        break;

      case 5:
        end = 1;
        fprintf(stdout, "Exiting...\n");
        break;

      default:
        fprintf(stdout, "Unknown option.\n");
        break;
    }
  }

  return EXIT_SUCCESS;
}
