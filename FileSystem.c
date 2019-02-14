//
// Created by Janik Buecher on 2019-01-31.
//
//based on:
/* ************************************** */
/* file:   sample_menu.c                  */
/* author: Arne Heimeshoff                */
/* date:   24.01.2019                     */
/* ************************************** */

#define LINES 35 /* lines to be cleared for clearscreen */
#define MAXCHAR 1000
#define SAVEFILE_HEADER "janik_savefile"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>


struct student{

    char name[20+1];
    unsigned int id;
    char course[20+1];
    struct student * next;
    struct student * prev;
};



/* prototype for local defined functions */
void print_menu (void);
void clearscreen (int lines);
struct student * add(char name [], int id, char course[], struct student * ptr);
bool checkID(int id, struct student * ptr );
struct student * load(char filename[],struct student *start, struct student *ptr);
int showData(struct student *start);
void delete (struct student * ptr, int id,struct student ** start);
int saveFile(struct student *ptr,char filename[]);
bool checkString(char string[]);
int bubbleSort(struct student *start);
int list_files(int output);
void clearData(struct student *start);

int main (void)
{
    struct student * start;
    struct student * ptr;


    start =  NULL;
    ptr =  NULL;
    ptr = (struct student *) malloc(sizeof(struct student));

    char name[21];
    int id;
    char courses [21];


    char choice;
    clearscreen (LINES);
    print_menu ();

    choice = getchar ();
    getchar ();
    while (choice!='0')
    {
        switch (choice)
        {
            case '1' :;

                bool a = false;

                while(a ==false) {
                    printf("Name:\t");
                    // scanf("%s", name);
                    fgets(name, 100, stdin); // liest maximal 100 character ein und speichert den string in name
                    name[strlen(name) - 1] = '\0'; //da fgets das \n speichert muss dieses gelöscht werden werden
                    if(checkString(name)== true){
                        a =true;
                    }else{
                        clearscreen(LINES);
                        printf("Pls reenter a Name without a ',' this is not allowed \n");


                    }
                }


                 a = false;
                while(a == false) {

                    printf("ID:");
                    scanf("%d", &id);
                    if(checkID(id,start)== true){
                        a =true;
                    }else{
                        clearscreen(LINES);
                        printf("Pls reenter a different ID this one is already used \n");


                    }

                }

                a = false;

                while(a ==false) {
                    printf("Course:\t");
                    getchar();
                    fgets(courses, 100, stdin); // liest maximal 100 character ein und speichert den string in courses
                    courses[strlen(courses)-1]='\0'; //da fgets das \n speichert muss dieses gelöscht werden
                    if(checkString(courses)== true){
                        a =true;
                    }else{
                        clearscreen(LINES);
                        printf("Pls reenter a Course without a ',' this is not allowed \n");


                    }
                }

                if(start == NULL){

                   start= ptr = add(name, id, courses, start);

                }else {

                    ptr = add(name, id, courses, start);
                }


            break;
            case '2' : ;
                        showData(start);

                break;
            case '3' :;
                 int id2 ;
                printf("ID:\t");
                scanf("%d",&id2);


                delete(start,id2,&start);


                break;
            case '4' :;
                char filename[150] ; // /Users/janikbuecher/Box Sync/Privat/MyFileSystem/FileData insert.txt

                printf("Enter thr file name, where you want to store your data without '.txt'\n(If you file doesn't exist a new one wille be created) :\n\n");
                fgets(filename, 145, stdin); // liest maximal 150 character ein und speichert den string in filename

                filename[strlen(filename)-1]='.'; //da fgets das \n speichert muss dieses ersetzt werden
                filename[strlen(filename)]='t';
                filename[strlen(filename)]='x';
                filename[strlen(filename)]='t';
                filename[strlen(filename)]='\0';
                printf("%s\n",filename);

                saveFile(start,filename);

                break;
            case '5' :;

                printf("If you load a file your local data will be lost if you didn't save it.\nDo you want to continue? [y/n]\n");
                char choice = getchar ();
                getchar ();

                switch (choice)
                {
                    case 'y':;

                        char filename1[150] ; // /Users/janikbuecher/Box Sync/Privat/MyFileSystem/FileData small.txt

                        printf("Filepath:\t");
                        fgets(filename1, 150, stdin); // liest maximal 150 character ein und speichert den string in filename

                        filename1[strlen(filename1)-1]='\0'; //da fgets das \n speichert muss dieses ersetzt werden

                        if(start != NULL) {
                            clearData(start);
                        }

                        start = load(filename1,start,ptr);
                        break;
                    case 'n':
                    {
                        printf("Loading aborted! Returning to menu...\n");
                        break;
                    }
                    default:
                        printf("Invalid choice Returning to menu...\n");
                        break;
                }




                break;
            case '6' :;
                bubbleSort(start);
                printf("Bubblesort war erfolgreich");
                break;
            case '0' : break;
            default  : printf ("\n-> Please use a valid input.\n\n");
                break;
        } /* end of switch */

        printf ("Press ENTER to continue.\n");
        getchar ();
        clearscreen (LINES);
        print_menu ();
        choice = getchar ();
        getchar ();
    } /* end of while */
    printf ("\n-> Thanks for using My Filecard System.\n\n");
    getchar ();

    return (0);
}

/* The function print_menue only prints a menu text on the screen */
void print_menu (void)
{
    printf ("\tMy Filecard System\n");
    printf ("\t------------------\n\n");
    printf ("\t1. Input record\n");
    printf ("\t2. Show records\n");
    printf ("\t3. Delete record\n");
    printf ("\t4. File records\n");
    printf ("\t5. Load records\n");
    printf ("\t6. Sort records\n");
    printf ("\t0. End Program\n\n");
    printf ("Your choice is: ");
}

/* The function clearscreen does multiple LF to move the text from the screen.       */
void clearscreen (int lines) {
    char i;
    for (i = 0; i < lines; i++) printf("\n");
}

struct student * add(char name [], int id, char course[], struct student * ptr){
    struct student * help;   //help pointer that remembers the prev pointer
    if(ptr) {

        while (ptr->next != NULL) {

            ptr = ptr->next;
        }
        help = ptr;
        ptr->next = (struct student *) malloc(sizeof(struct student));
        ptr = ptr->next;
        ptr->next = NULL;
        strcpy(ptr->name, name);
        strcpy(ptr->course, course);
        ptr->id = id;
        ptr->prev= help;
    }
    else{               //end of if-case ptr!=NULL

        ptr = (struct student *) malloc(sizeof(struct student));
        ptr->next=NULL;
        strcpy(ptr->name, name);
        strcpy(ptr->course, course);
        ptr->id = id;
        ptr->prev=NULL;




    }                   //end of else-case ptr==NULL
    return ptr;

}

bool checkID(int id, struct student * ptr ){

    if(ptr) {

        while (ptr->next != NULL){
            if(ptr->id == id){

                return false;
            }

            ptr = ptr->next;
        }
        if(ptr->id == id){   //checks the last element of the list

            return false;
        }

        return true;
    }
    else{               //end of if-case ptr!=NULL

        return true;
    }                   //end of else-case ptr==NULL

}

struct student * load(char filename[],struct student *start, struct student *ptr){

    FILE *fp;
    char * line = NULL;
    ssize_t read;
    size_t len = 0;
    char delimiter[] = ",";
    char *p;
    char *student[3];
    int count = 0;
    int i;
    int headerCount = 0;


    fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Could not open file %s. Please Enter a valid Filepath",filename);
        return 1;
    }

    while ((read = getline(&line, &len, fp)) != -1) {

        if(count == 0){
            line[strlen(line)-1]='\0'; //da fgets das \n speichert muss dieses ersetzt werden
            if(strcmp(line,SAVEFILE_HEADER)!=0){

                break;
            }


        }

        p = strtok(line, delimiter);

        i = 0;

        while(p != NULL) {


            student[i++] = p;

            // naechsten Abschnitt erstellen
            p = strtok(NULL, delimiter);

        }

        student[2][strlen(student[2])-1]='\0'; //da fgets das \n speichert muss dieses ersetzt werden





        if(count == 1){

            start = ptr = add(student[0],atoi(student[1]),student[2],start);

        }else {

            ptr = add(student[0],atoi(student[1]),student[2],start);

        }

        count++;


    }

    fclose(fp);
    if (line)
        free(line);
    if(count != 0){
        printf("Successfully loaded!\n");
    }
    else{
        printf("Document is not a savefile! Please try again!\n");
    }
    return start;

}

int showData(struct student *start) {

    do{


        printf("Name: %20s  ", start->name);
        printf("%s: %20d  ", "ID", start->id);
        printf("%s: %20s\n", "Course", start->course);
        start = start->next;
    }while (start != NULL);

    return 0;
}

void delete (struct student * ptr, int id,struct student ** start){
    struct student * prev = NULL;


    while (ptr->next != NULL && ptr->id != id){
        prev = ptr;
        ptr = ptr->next;

    }
    if(prev==NULL){
        *start= ptr->next;
        free(ptr);
    }
    else {
        if(ptr->id ==id) {
            prev->next = ptr->next;
            ptr->next->prev = prev;
            free(ptr);
        }
    }

}


int saveFile(struct student *ptr,char filename[]){

    printf("There are two different ways to save a file:\n-Type 'o' to overwrite\n-Type 'a' to append your data to the existing data\n");
    char choice = getchar ();
    getchar ();

    switch (choice)
    {
        case 'o':;
            FILE *f = fopen(filename, "w");
            if (f == NULL)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            fprintf(f,"%s\n",SAVEFILE_HEADER);

            while (ptr->next != NULL){
                fprintf(f, "%s,", ptr->name);
                fprintf(f, "%d,", ptr->id);
                fprintf(f, "%s\n", ptr->course);

                ptr = ptr->next;
            }

            fprintf(f, "%s,", ptr->name);
            fprintf(f, "%d,", ptr->id);
            fprintf(f, "%s\n", ptr->course);

            fclose(filename);
            printf("Saved Successfully!");
            break;
        case 'a':
        {
            printf("Run program 2\n");
            printf("Please Wait\n");
            break;
        }
        default:
            printf("Invalid choice\n");
            break;
    }


}


bool checkString(char string[]){

    for(int i = 0; i<strlen(string);i++){
        if(string[i]==','){

            return false;

        }

    }

    return true;



}

void swap(struct student *A, struct student *B){
    struct student temp;
    strcpy(temp.name, A->name);
    strcpy(temp.course,A->course);
    temp.id = A->id;

    strcpy(A->name, B->name);
    strcpy(A->course,B->course);
    A->id = B->id;

    strcpy(B->name, temp.name);
    strcpy(B->course,temp.course);
    B->id = temp.id;
}


int bubbleSort(struct student *start){

    int swapped, i;
    struct student *ptr1;
    struct student *lptr = NULL;

    printf("Which way do you want to sort your data?\n1. By Name\n2. By ID\n3. By Course\n");
    char choice = getchar ();
    getchar ();
    switch (choice)
    {
        case '1':;
            /* Checking for empty list */
            if (start == NULL)
                return 1;

            do
            {
                swapped = 0;
                ptr1 = start;

                while (ptr1->next != lptr)
                {
                    if (strcmp(ptr1->name, ptr1->next->name)> 0)
                    {
                        swap(ptr1,ptr1->next);

                        swapped = 1;
                    }
                    ptr1 = ptr1->next;
                }
                lptr = ptr1;
            }
            while (swapped);

            break;
        case '2':
            /* Checking for empty list */
            if (start == NULL)
                return 1;

            do
            {
                swapped = 0;
                ptr1 = start;

                while (ptr1->next != lptr)
                {
                    if (ptr1->id >ptr1->next->id)
                    {
                        swap(ptr1,ptr1->next);

                        swapped = 1;
                    }
                    ptr1 = ptr1->next;
                }
                lptr = ptr1;
            }
            while (swapped);

            break;

        case '3':
            /* Checking for empty list */
            if (start == NULL)
                return 1;

            do
            {
                swapped = 0;
                ptr1 = start;

                while (ptr1->next != lptr)
                {
                    if (strcmp(ptr1->course, ptr1->next->course)> 0)
                    {
                        swap(ptr1,ptr1->next);

                        swapped = 1;
                    }
                    ptr1 = ptr1->next;
                }
                lptr = ptr1;
            }
            while (swapped);

            break;

        default:
            printf("Invalid choice\n");
            break;
    }
    return  0;

}

void clearData(struct student *start){
    struct student * help;
    do{

        help = start;
        free(start);

        start = help->next;
    }while (start != NULL);





}

//Method list_files created by Theo Remmert
// reads the given directory and lists containing save files (only)
/*
int list_files(int output){

    int count;
    char filename[100], buff[50];
    struct dirent *dirpointer;
    FILE *fp;
    DIR *dp = "./"; //"./" für Mac und ".\\" für Windows
    count = 0;
    // reads directory
    while((dirpointer = readdir(dp))){
        strcpy(filename, (*dirpointer).d_name);
        // excludes the hidden directories
        if(strcmp(filename, ".") && strcmp(filename, "..")){
            // makes sure to only list .txt files
            if(strlen(filename) >= 4){
                buff[3] = filename[strlen(filename) - 1];
                buff[2] = filename[strlen(filename) - 2];
                buff[1] = filename[strlen(filename) - 3];
                buff[0] = filename[strlen(filename) - 4];
                buff[4] = '\0';
                if(!strcmp(buff, ".txt")){
                    // opens the given file and checks whether it has the defined SAVEFILE_HEADER
                    fp = fopen(filename, "r");
                    fgets(buff, 50, fp);
                    buff[strlen(buff) - 1] = '\0';
                    fclose(fp);
                    // only counts possible save files (cheks the header)
                    if(!strcmp(buff, SAVEFILE_HEADER)){
                        if(output){
                            printf("\t%d.\t%s\n", count + 1, filename);
                        }
                        count++;
                    }
                }
            }
        }
    }
    if(output){
        printf("\n");
    }
    rewinddir(dp);
    return count;

*/