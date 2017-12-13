#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
int BooksNum = 0;


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

void CreateBook() {

    Book B; int I = 0;

    printf("Enter Book Title:");
    B.Title = GetField();
    printf("\nEnter Book Author:");
    B.Author = GetField();
    printf("\nEnter Publisher:");
    B.Publisher = GetField();
    //////////Check ISBN////////////
    printf("\nEnter Unique ISBN:");
    B.ISBN = GetField();
    while (Search(B.ISBN) > 0)
    {
        printf("\nRe-Enter Unique ISBN:");
        B.ISBN = GetField();
    }
    ///////////////////////////////
    printf("\nEnter Date Of Publication (dd/mm/yy):");
    B.DOP = GetField();
    printf("\nEnter Category:");
    B.Ca = GetField();

    B.AC = 1;
    B.NOC = 1;

    BooksNum++;
    MyBooks = (Book*) realloc(MyBooks,BooksNum * sizeof(Book));


    MyBooks[BooksNum - 1].Title = B.Title;
    MyBooks[BooksNum - 1].Author = B.Author;
    MyBooks[BooksNum - 1].Publisher = B.Publisher;
    MyBooks[BooksNum - 1].ISBN = B.ISBN;
    MyBooks[BooksNum - 1].DOP = B.DOP;
    MyBooks[BooksNum - 1].Ca = B.Ca;
    MyBooks[BooksNum - 1].AC = B.AC;
    MyBooks[BooksNum - 1].NOC = B.NOC;


    GotoBook();
}

void AddCpy(){

    char *ISBN; int Results = false,I,NOC,K = -1;

    printf("Enter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");


    for (I = 0; I < BooksNum; I++)
    {
        if (strcmp(MyBooks[I].ISBN,ISBN) == 0) // Not strcasestr
        {  K = I; Results = true; break; }
    }

    if (Results)
    {
        printf("\nEnter number of copies:");
        // scan Noc

        if()

        //validate number
    }
    else
    {

    }

    free(ISBN);
}

int Search(char *InPut){

    int I; int Found = 0;

    for (I = 0; I < BooksNum; I++) {

        if (strcasestr(MyBooks[I].Title, InPut) != NULL ||
            strcasestr(MyBooks[I].Author, InPut) != NULL ||
            strcasestr(MyBooks[I].Publisher, InPut) != NULL ||
            strcasestr(MyBooks[I].ISBN, InPut) != NULL ||
            strcasestr(MyBooks[I].DOP, InPut) != NULL ||
            strcasestr(MyBooks[I].Ca, InPut) != NULL)
        {
            Found++;
            printf("%s, %s, %s, %s, %s, %d, %d, %s",MyBooks[I].Title, MyBooks[I].Author, MyBooks[I].Publisher,
                   MyBooks[I].ISBN, MyBooks[I].DOP, MyBooks[I].NOC, MyBooks[I].AC, MyBooks[I].Ca);
        }

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


// fix choices
// validate any thing the user enters
//comments
// Before Save Check presence of Temp_NB.txt
// And when the program close delete Temp_NB.txt all Temps and in create book method
// Check ISBN Before add
// handle all files errors
// free all pointers

void Load_Books(){

    int I = 0 ,DataRowCount = FileCounter("Books.txt");
    char Line[512], *Value = NULL;
    FILE *BookFile = fopen("Books.txt","r");

    BooksNum = DataRowCount;
    MyBooks  = malloc(sizeof(Book)*(DataRowCount));

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

    int I;
    FILE *BookFile;

    BookFile = fopen("Books.txt","a+");

    for (I = 0; I < BooksNum; ++I)
    {
        fprintf(BookFile, "%s, %s, %s, %s, %s, %d, %d, %s", MyBooks[I].Title, MyBooks[I].Author, MyBooks[I].Publisher, MyBooks[I].ISBN, MyBooks[I].DOP, MyBooks[I].NOC, MyBooks[I].AC, MyBooks[I].Ca);
    }

    fclose(BookFile);
}






