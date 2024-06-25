#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a structure to read and write
typedef struct student {
  int index_no;
  char  name[50];
  char  dept[20];
}input;

typedef struct grades{
    int studentid;
    int courseid;
    char grade[2];
}ginput;

typedef struct course {
    int courseid;
    char coursename[50];
    int creditvalue;
}cinput;

//Functions
void addStuDet();
void coursedet();
void report();

int main ()
{
