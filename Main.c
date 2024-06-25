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
  
}

//Function to add student details
void addStuDet(){
  int i,n;
  FILE* stufile;
  FILE* gfile;

  input input;
  ginput ginput;
  
  stufile = fopen ("studentdetails.txt","a");
  gfile = fopen ("gradefile.txt","a");

  if (stufile == NULL)
     {
      printf("\nError: Cannot open file.\n\n");
      exit(1);
     }
  if (gfile == NULL)
     {
      printf("\nError: Cannot open file.\n\n");
      exit(1);
     }

  printf("\n##############################\n");
  printf("STUDENT DETAILS\n");
  printf("______________________________\n");

  //Prompt user for inputs
  printf("Index No : ");
  scanf ("%d", &input.index_no);
  ginput.studentid = input.index_no;

  fflush(stdin);
  printf("Full Name : ");
  gets(input.name);
     
  printf("Department : ");
  scanf ("%s",&input.dept);

  fwrite (&input, sizeof(struct student), 1, stufile);

  //insert gradefile saving

  printf ("Enter number of subjects : ");
  scanf ("%d", &n);

  for(i=1; i<=n; i++){

    printf("Course %d ID : ", i);
    scanf ("%d", &ginput.courseid);

    fflush(stdin);
    printf("Course %d Grade : ",i);
    scanf ("%s", ginput.grade);

    fwrite (&ginput, sizeof(struct grades), 1, gfile);
  }

  fclose(stufile);
  fclose(gfile);

}


//Function to add course details
void coursedet(){
    FILE *coursefile;

    cinput cinput;
    coursefile = fopen ("coursedetails.txt","a+");

    if (coursefile == NULL)
     {
      printf("\nError: Cannot open file.\n\n");
      exit(1);
     }

    printf("\n###############################\n");
    printf("COURSE DETAILS\n");
    printf("_______________________________\n");

    while (fread(&cinput, sizeof(struct course), 1, coursefile))
    {
        printf ("%d | %-20s | %d\n", cinput.courseid, cinput.coursename, cinput.creditvalue);
    }

      //Prompt user for inputs
      printf("\nCourse ID : ");
      scanf ("%d", &cinput.courseid);

      fflush(stdin);
      printf("Course Name : ");
      gets(cinput.coursename);
      
      printf("Credit Value : ");
      scanf ("%d", &cinput.creditvalue);

  fwrite (&cinput, sizeof (struct course), 1, coursefile);

  fclose(coursefile);
}

//Function to generate report
void report(){

  int search_index,i,edit;
  float crtot=0,crgpv,crgpvtot=0,gpa;

  input input;
  cinput cinput;
  ginput ginput;

  FILE *stufile;
  FILE *coursefile;
  FILE *gfile;

  stufile = fopen ("studentdetails.txt","r");
  coursefile = fopen ("coursedetails.txt","r");
  gfile = fopen ("gradefile.txt","r");

  if (stufile == NULL || coursefile == NULL || gfile == NULL)
     {
      printf("\nError: Cannot open file.\n\n");
      exit(1);
     }
  
  printf("Enter Student Index No: ");
  scanf("%d",&search_index);
  

while(fread (&input, sizeof(struct student),1, stufile))
{
  if (input.index_no==search_index)
  {
    printf ("\n\nName: %s\nIndex No: %d\nDepartment: %s\n\n",input.name,input.index_no,input.dept);
    printf("_________________________________________\n");
    printf(" COURSE ID | COURSE NAME         | GRADE \n");
    printf("=========================================\n");
    while(fread (&ginput, sizeof(struct grades),1, gfile))
    {
      if (ginput.studentid == search_index)
      {
        fseek(coursefile,0,SEEK_SET);
        while (fread (&cinput, sizeof(struct course),1, coursefile))
        {
          if (cinput.courseid == ginput.courseid)
          {
            printf(" %-10d| %-20s| %s\n",cinput.courseid, cinput.coursename, ginput.grade);
          
            crtot += cinput.creditvalue;
            if (strcmp(ginput.grade,"A")==0 || strcmp(ginput.grade,"a")==0){
              crgpv=cinput.creditvalue*4.0;
            }
            if (strcmp(ginput.grade,"B")==0 || strcmp(ginput.grade,"b")==0){
              crgpv=cinput.creditvalue*3.0;
            }
            if (strcmp(ginput.grade,"C")==0 || strcmp(ginput.grade,"c")==0){
              crgpv=cinput.creditvalue*2.5;
            }
            if (strcmp(ginput.grade,"D")==0 || strcmp(ginput.grade,"d")==0){
              crgpv=cinput.creditvalue*1.5;
            }
            if (strcmp(ginput.grade,"E")==0 || strcmp(ginput.grade,"e")==0){
              crgpv=cinput.creditvalue*0;
            }
            if (strcmp(ginput.grade,"AB")==0 || strcmp(ginput.grade,"ab")==0){
              crgpv=cinput.creditvalue*0;
            }
            crgpvtot += crgpv;
          }
        }
      }
    }
  }
}
printf("_________________________________________\n");
gpa = crgpvtot / crtot;
printf ("\nGPA : %.4f\n", gpa);

printf ("\n1. Edit Student Details");
printf ("\n2. Edit Course Details");
printf ("\n0. Exit to Main Menu");

printf ("\nEnter Option : ");
scanf ("%d", &edit);

FILE *tempfile;

switch (edit){
case 1:
  fclose(coursefile);
  tempfile = fopen ("tempfile.txt", "w");
  fseek(stufile,0,SEEK_SET);
  while (fread(&input, sizeof(struct student), 1, stufile)){
    if (input.index_no != search_index){
      fwrite (&input, sizeof(struct student), 1, tempfile);
    }
  }
  fclose (stufile);
  fclose (tempfile);
  remove ("studentdetails.txt");
  rename ("tempfile.txt", "studentdetails.txt");

  tempfile = fopen ("tempfile.txt", "w");
  fseek(gfile,0,SEEK_SET);
  while (fread(&ginput, sizeof(struct grades), 1, gfile)){
    if (ginput.studentid != search_index){
      fwrite (&ginput, sizeof(struct grades), 1, tempfile);
    }
  }
  fclose (stufile);
  fclose(gfile);
  fclose (tempfile);
  remove ("gradefile.txt");
  rename ("tempfile.txt", "gradefile.txt");
  addStuDet();
  break;

case 2:
  fclose(stufile);
  fclose(gfile);
  tempfile = fopen ("tempfile.txt", "w");

  printf ("\n\nEnter Course ID : ");
  scanf("%d", &search_index);

  fseek(coursefile,0,SEEK_SET);
  while (fread (&cinput, sizeof(struct course),1, coursefile))
  {
    if (cinput.courseid != search_index){
      fwrite (&cinput, sizeof(struct course), 1, tempfile);
    }
  }
    
  fclose (coursefile);
  fclose (tempfile);
  remove ("coursedetails.txt");
  rename ("tempfile.txt", "coursedetails.txt");
  coursedet();
  break;

default:
  fclose(stufile);
  fclose(coursefile);
  fclose(gfile);
  break;
}

}
