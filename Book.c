#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Book.h"
#include "main.h"

typedef struct {
    char *Title;
    char *Author;
    char *Publisher;
    char *ISBN;
    char *DOP;
    char *Ca;
}Book;


void GotoBook() {

    int Select;

    printf("\n:::[Book Menu]:::\n\n");
    printf("1.Add New Book\n");
    printf("2.Add New Copy\n");
    printf("3.Delete Book\n");
    printf("4.Find Book\n");
    printf("5.Edit Book\n");
    printf("6.Main Menu\n");
    printf("------------------------\n");


    while(Select != 1 && Select != 2 && Select != 3 && Select != 4 && Select != 5 && Select != 6)
    {
        printf("Enter your choice: ");
        scanf("%d",&Select);
    }

    system("@cls||clear");


    if (Select == 1) CreateBook();
    if (Select == 2) main();
    if (Select == 3) main();
    if (Select == 4) GotoSearch();
    if (Select == 5) main();
    if (Select == 6) main();
}

void GotoSearch(){


}

void CreateBook(){

    Book B;

    printf("Enter Book Title:");
    B.Title = GetField();
    printf("\nEnter Book Author:");
    B.Author = GetField();
    printf("\nEnter Publisher:");
    B.Publisher = GetField();
    printf("\nEnter ISBN:");
    B.ISBN = GetField();
    printf("\nEnter Date Of Publication:");
    B.DOP = GetField();
    printf("\nEnter Category:");
    B.Ca = GetField();

    FILE *Temp_NB = fopen("Temp_NB.txt","a+");

    fprintf(Temp_NB, "%s,%s,%s,%s,%s,%s\n", B.Title, B.Author, B.Publisher, B.ISBN, B.DOP, B.Ca);
    fclose(Temp_NB);

    free(B.Title);
    free(B.Author);
    free(B.Publisher);
    free(B.ISBN);
    free(B.DOP);
    free(B.Ca);

    GotoBook();
}

void Search(char *InPut, int Field){

    int I = 0, DataRowCount = FileCounter("Books.txt");
    int Data[2]; // 0: n of copies , 1: av copies
    char Line[512], *Value;
    FILE *BookFile;

    /*
     *     char *Title;
    char *Author;
    char *Publisher;
    char *ISBN;
    char *DOP;
    char *Ca;
    */
    BookFile = fopen("Books.txt","r");

    while (fgets(Line,512, BookFile)) {

        if(Field == 1)
        {
            if (strstr(strtok(Line,", "),InPut) != NULL)
            {
                printf("Title: %s\n");
                printf("Author: %s\n");
                printf("Publisher: %s\n");
                printf("ISBN: %s\n");
                printf("DOP: %s\n");
                printf("Number Of Copies: %d\n");
                printf("Available Copies: %d\n");
                printf("Category: %s\n");
                printf("--------------------------\n");
            }
        }
        if(Field == 2)
        {

        }
        if(Field == 3)
        {

        }
        if(Field == 4)
        {

        }
        if(Field == 5)
        {

        }
        if(Field == 6)
        {

        }
    }


    free(Value);
    fclose(BookFile);
}

char *GetField(){

    size_t I = 0; char *P;

    Here:
    P = GetString();
    while (P == NULL) P = GetString();

    bool Accept = false;

    while (P[I] != '\0')
    {
        if (P[I] != ' ')
        {
            Accept = true;
            break;
        }
        I++;
    }

    if (!Accept){ Accept = false; I = 0; free(P); goto Here; }

    return P;
}

// Before Save Check presence of Temp_NB.txt
// And when the program close delete Temp_NB.txt all Temps and in create book method
// Check ISBN Before add
// handle all files errors
// free all pointers

void Save_B(){

    int I = 0, DataRowCount = FileCounter("Temp_NB.txt");
    char Line[512], *Value;
    FILE *Temp_NB, *BookFile;
    Book B[DataRowCount];

    Temp_NB = fopen("Temp_NB.txt","r");

    while (fgets(Line,512, Temp_NB)) {

        Value = strtok(Line, ",");
        B[I].Title = malloc(strlen(Value) + 1);
        strcpy(B[I].Title, Value);

        Value = strtok(NULL, ",");
        B[I].Author = malloc(strlen(Value) + 1);
        strcpy(B[I].Author, Value);

        Value = strtok(NULL, ",");
        B[I].Publisher = malloc(strlen(Value) + 1);
        strcpy(B[I].Publisher, Value);

        Value = strtok(NULL, ",");
        B[I].ISBN = malloc(strlen(Value) + 1);
        strcpy(B[I].ISBN, Value);

        Value = strtok(NULL, ",");
        B[I].DOP = malloc(strlen(Value) + 1);
        strcpy(B[I].DOP, Value);

        Value = strtok(NULL, ",");
        B[I].Ca = malloc(strlen(Value) + 1);
        strcpy(B[I].Ca, Value);

        I++;
    }

    BookFile = fopen("Books.txt","a+");

    for ( I = 0; I < DataRowCount; ++I) {

        fprintf(BookFile, "%s, %s, %s, %s, %s, 1, 1, %s", B[I].Title, B[I].Author, B[I].Publisher, B[I].ISBN, B[I].DOP, B[I].Ca);
    }

    for ( I = 0; I < DataRowCount; ++I) {

        free(B[I].Title);
        free(B[I].Author);
        free(B[I].Publisher);
        free(B[I].ISBN);
        free(B[I].DOP);
        free(B[I].Ca);
    }
    free(Value);

    fclose(BookFile);
    fclose(Temp_NB);
    remove("Temp_NB.txt");
}






