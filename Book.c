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
    int NOC,AC; // Num of copies and Available copies
    char *DOP;
    char *Ca;
}Book;

Book *MyBooks;


void GotoBook() {

    int Select = 0;

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
    if (Select == 4) main();
    if (Select == 5) main();
    if (Select == 6) main();
}

void CreateBook(){

    Book B; int I = 0;

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




    //p1 = (Product*)realloc(p1, tam * sizeof(Product));



    GotoBook();
}

int Search(char *InPut){

    int I = 0; int Found = false;

    while (!(MyBooks[I].Title)){

        if (strstr(MyBooks[I].Title, InPut) != NULL ||
                strstr(MyBooks[I].Author, InPut) != NULL ||
                strstr(MyBooks[I].Publisher, InPut) != NULL ||
                strstr(MyBooks[I].ISBN, InPut) != NULL ||
                strstr(MyBooks[I].DOP, InPut) != NULL ||
                strstr(MyBooks[I].Ca, InPut) != NULL)
        {
            Found = true;
            printf("%s, %s, %s, %s, %s, %d, %d, %s",MyBooks[I].Title, MyBooks[I].Author, MyBooks[I].Publisher,
                   MyBooks[I].ISBN, MyBooks[I].DOP, MyBooks[I].NOC, MyBooks[I].AC, MyBooks[I].Ca);
        }

        I++;
    }

    return Found;
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

void Load_Books(){

    int I = 0 ,DataRowCount = FileCounter("Books.txt");
    char Line[512], *Value = NULL;
    FILE *BookFile = fopen("Books.txt","r");
    MyBooks  = malloc(sizeof(Book)*DataRowCount);

    while (fgets(Line,512, BookFile)){

        //Title
        Value = strtok(Line, ",");
        MyBooks[I].Title = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Title, Value);

        //Author
        Value = strtok(NULL, ",");
        MyBooks[I].Author = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Author, Value);

        //Publisher
        Value = strtok(NULL, ",");
        MyBooks[I].Publisher = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Publisher, Value);

        //ISBN
        Value = strtok(NULL, ",");
        MyBooks[I].ISBN = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].ISBN, Value);

        //DOP
        Value = strtok(NULL, ",");
        MyBooks[I].DOP = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].DOP, Value);

        //NOC
        sscanf(strtok(NULL, ","), "%d", &MyBooks[I].NOC);

        //AC
        sscanf(strtok(NULL, ","), "%d", &MyBooks[I].AC);

        //Ca
        Value = strtok(NULL, ",");
        MyBooks[I].Ca = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Ca, Value);

        I++;
    }

    free(Value);
    fclose(BookFile);
}

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






