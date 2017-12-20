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
    int NOC, AC; // Num of copies and Available copies
    char *DOP;
    char *Ca;
} Book;

typedef struct {
    int dd;
    int mm;
    int yy;
} Date;


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


    while (Select != 1 && Select != 2 && Select != 3 && Select != 4 && Select != 5 && Select != 6) {
        printf("Enter your choice: ");
        scanf("%d", &Select);
    }

    system("@cls||clear");

    if (Select == 1) CreateBook();
    if (Select == 2) AddCpy();
    if (Select == 3) Delete();
    if (Select == 4) Find();
    if (Select == 5) main();
    if (Select == 6) main();
}

void CreateBook() {

    Book B;
    int I = 0;

    printf("Enter Book Title:");
    B.Title = GetField();
    printf("\nEnter Book Author:");
    B.Author = GetField();
    printf("\nEnter Publisher:");
    B.Publisher = GetField();
    //////////Check ISBN////////////
    printf("\nEnter Unique ISBN:");
    B.ISBN = GetField();
    while (Exist(B.ISBN, 'I') == 1) {
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
    MyBooks = (Book *) realloc(MyBooks, BooksNum * sizeof(Book));

    MyBooks[BooksNum - 1].Title = B.Title;
    MyBooks[BooksNum - 1].Author = B.Author;
    MyBooks[BooksNum - 1].Publisher = B.Publisher;
    MyBooks[BooksNum - 1].ISBN = B.ISBN;
    MyBooks[BooksNum - 1].DOP = B.DOP;
    MyBooks[BooksNum - 1].Ca = B.Ca;
    MyBooks[BooksNum - 1].AC = B.AC;
    MyBooks[BooksNum - 1].NOC = B.NOC;

    printf("\n:: Done ::\n\n");
    Redirect();
}

void AddCpy() {

    char *ISBN = NULL, *CNOC = NULL;
    int Results = false, I, NOC;

    printf(":: Add New Copy ::\n");
    printf("------------------\n");

    printf("Enter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");

    for (I = 0; I < BooksNum; I++) {
        if (strcmp(MyBooks[I].ISBN, ISBN) == 0) // Not strcasestr
        {
            Results = true;
            break;
        }
    }

    if (Results) {
        printf("\nEnter number of copies:");

        /* Validation */

        Here:
        CNOC = GetField();
        while (!IsNumber(CNOC)) { free(CNOC); CNOC = GetField(); }
        sscanf(CNOC,"%d",&NOC);
        while (NOC < 0) { free(CNOC); goto Here; }

        /********************************************************/

        MyBooks[I].NOC = NOC;
    }
    else
    {
        printf("Book is not found....!!\n\n");
        free(ISBN); free(CNOC);
        Redirect();
    }

    printf(":: Done ::\n\n");
    free(ISBN); free(CNOC);
    Redirect();
}

void Delete() {

    char *ISBN = NULL;
    int Results = false, I;

    printf(":: Delete Book ::\n");
    printf("-----------------\n\n");

    printf("Enter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");

    for (I = 0; I < BooksNum; I++) {
        if (strcmp(MyBooks[I].ISBN, ISBN) == 0) // Not strcasestr
        {
            Results = true;
            break;
        }
    }

    if (Results)
    {
        for (; I < BooksNum - 1; I++)
        {
            MyBooks[I].Title = MyBooks[I + 1].Title;
            MyBooks[I].Author = MyBooks[I + 1].Author;
            MyBooks[I].Publisher = MyBooks[I + 1].Publisher;
            MyBooks[I].ISBN = MyBooks[I + 1].ISBN;
            MyBooks[I].DOP = MyBooks[I + 1].DOP;
            MyBooks[I].Ca = MyBooks[I + 1].Ca;
            MyBooks[I].NOC = MyBooks[I + 1].NOC;
            MyBooks[I].AC = MyBooks[I + 1].AC;
        }

        free(ISBN);
        BooksNum--;
        MyBooks = (Book *) realloc(MyBooks, BooksNum * sizeof(Book));
    }
    else
    {
        printf("\nBook is not found....!!\n\n");
        free(ISBN);
        Redirect();
    }

    printf("\n:: Done ::\n\n");
    free(ISBN);
    Redirect();
}

void Find() {

    Book FindBook;
    int I,T = false, A = false, P = false, IS = false, D = false, C = false;

    printf(":: Find Book ::\n");
    printf("---------------\n");

    printf("Enter Book Title || (--):");
    FindBook.Title = GetField();
    printf("\nEnter Book Author || (--):");
    FindBook.Author = GetField();
    printf("\nEnter Publisher || (--):");
    FindBook.Publisher = GetField();
    printf("\nEnter ISBN || (--):");
    FindBook.ISBN = GetField();
    printf("\nEnter Date Of Publication (dd/mm/yy) || (--):");
    FindBook.DOP = GetField();
    printf("\nEnter Category || (--):");
    FindBook.Ca = GetField();

    for (I = 0; I < BooksNum; I++) {
        if (strcmp(FindBook.Title, "--") != 0)
            if (strcasestr(MyBooks[I].Title, FindBook.Title) != NULL) T = true;

        if (strcmp(FindBook.Author, "--") != 0)
            if (strcasestr(MyBooks[I].Author, FindBook.Author) != NULL) A = true;

        if (strcmp(FindBook.Publisher, "--") != 0)
            if (strcasestr(MyBooks[I].Publisher, FindBook.Publisher) != NULL) P =true;

        if (strcmp(FindBook.ISBN, "--") != 0)
            if (strcasestr(MyBooks[I].ISBN, FindBook.ISBN) != NULL) IS = true;

        if (strcmp(FindBook.DOP, "--") != 0)
            if (strcasestr(MyBooks[I].DOP, FindBook.DOP) != NULL) D = true;

        if (strcmp(FindBook.Ca, "--") != 0)
            if (strcasestr(MyBooks[I].Ca, FindBook.Ca) != NULL) C = true;

        if(T == true || A == true || P == true || IS == true || D == true || C == true)
        {

            printf("- %s, %s, %s, %s, %s, %d, %d, %s\n", MyBooks[I].Title, MyBooks[I].Author, MyBooks[I].Publisher,
                    MyBooks[I].ISBN, MyBooks[I].DOP, MyBooks[I].NOC, MyBooks[I].AC, MyBooks[I].Ca);
        }
    }

    Redirect();
}

void Edit() {

    char *ISBN = NULL;
    int Results = false, I;

    printf(":: Edit Book ::\n");
    printf("-----------------\n\n");

    printf("Enter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");

    for (I = 0; I < BooksNum; I++) {
        if (strcmp(MyBooks[I].ISBN, ISBN) == 0) // Not strcasestr
        {
            Results = true;
            break;
        }
    }

    if (Results)
    {

    }
    else
    {
        printf("\nBook is not found....!!\n\n");
        free(ISBN);
        Redirect();
    }

    printf("\n:: Done ::\n\n");
    free(ISBN);
    Redirect();
}

int Exist(char *InPut, char Field) {

    int I;
    int Found = 0;

    for (I = 0; I < BooksNum; I++) {
        switch (Field) {
            case 'T':
                if (strcasestr(MyBooks[I].Title, InPut) != NULL) Found++;
                break;
            case 'A':
                if (strcasestr(MyBooks[I].Author, InPut) != NULL) Found++;
                break;
            case 'P':
                if (strcasestr(MyBooks[I].Publisher, InPut) != NULL) Found++;
                break;
            case 'I':
                if (strcasestr(MyBooks[I].ISBN, InPut) != NULL) Found++;
                break;
            case 'D':
                if (strcasestr(MyBooks[I].DOP, InPut) != NULL) Found++;
                break;
            case 'C':
                if (strcasestr(MyBooks[I].Ca, InPut) != NULL) Found++;
                break;
            default:
                break;
        }
    }

    return Found;
}

char *GetField() {

    size_t I = 0;
    char *P;

    Here:
    P = GetString();
    while (P == NULL) P = GetString();

    bool Accept = false;

    while (P[I] != '\0') {
        if (P[I] != ' ') {
            Accept = true;
            break;
        }
        I++;
    }

    if (!Accept) {
        Accept = false;
        I = 0;
        free(P);
        goto Here;
    }

    return P;
}



// validate any allocation
//Redirect();
// Validate DOP IN Find , Create New Book
// fix choices
// validate any thing the user enters for each fn ( Date yy //bb//b) in create and edit
//comments
// Before Save Check presence of Temp_NB.txt
// And when the program close delete Temp_NB.txt all Temps and in create book method
// Check ISBN Before add
// handle all files errors
// free all pointers
// when program runs stop popular and others from work if books num is zero

void Load_Books() {

    int I = 0, DataRowCount = FileCounter("Books.txt");
    char Line[512], *Value = NULL;
    FILE *BookFile = fopen("Books.txt", "r");

    BooksNum = DataRowCount;
    MyBooks = malloc(sizeof(Book) * (DataRowCount));

    while (fgets(Line, 512, BookFile)) {

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
        Value = strtok(NULL, "\n");
        MyBooks[I].Ca = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Ca, Value);

        I++;
    }


    free(Value);
    fclose(BookFile);
}

void Save_B() {

    int I;
    FILE *BookFile;

    BookFile = fopen("Books.txt", "w");

    for (I = 0; I < BooksNum; ++I) {
        fprintf(BookFile, "%s, %s, %s, %s, %s, %d, %d, %s\n", MyBooks[I].Title, MyBooks[I].Author, MyBooks[I].Publisher,
                MyBooks[I].ISBN, MyBooks[I].DOP, MyBooks[I].NOC, MyBooks[I].AC, MyBooks[I].Ca);
    }

    fclose(BookFile);
}

void POP() {

    Book Temp;

    for (int I = 0; I < BooksNum; I++) {
        for (int J = 0; J < BooksNum - I; J++) {
            if (MyBooks[J].NOC - MyBooks[J].AC < MyBooks[J + 1].NOC - MyBooks[J + 1].AC) {

                Temp.Title = MyBooks[J + 1].Title;
                Temp.Author = MyBooks[J + 1].Author;
                Temp.Publisher = MyBooks[J + 1].Publisher;
                Temp.ISBN = MyBooks[J + 1].ISBN;
                Temp.DOP = MyBooks[J + 1].DOP;
                Temp.Ca = MyBooks[J + 1].Ca;
                Temp.NOC = MyBooks[J + 1].NOC;
                Temp.AC = MyBooks[J + 1].AC;

                MyBooks[J + 1].Title = MyBooks[J].Title;
                MyBooks[J + 1].Author = MyBooks[J].Author;
                MyBooks[J + 1].Publisher = MyBooks[J].Publisher;
                MyBooks[J + 1].ISBN = MyBooks[J].ISBN;
                MyBooks[J + 1].DOP = MyBooks[J].DOP;
                MyBooks[J + 1].Ca = MyBooks[J].Ca;
                MyBooks[J + 1].NOC = MyBooks[J].NOC;
                MyBooks[J + 1].AC = MyBooks[J].AC;

                MyBooks[J].Title = Temp.Title;
                MyBooks[J].Author = Temp.Author;
                MyBooks[J].Publisher = Temp.Publisher;
                MyBooks[J].ISBN = Temp.ISBN;
                MyBooks[J].DOP = Temp.DOP;
                MyBooks[J].Ca = Temp.Ca;
                MyBooks[J].NOC = Temp.NOC;
                MyBooks[J].AC = Temp.AC;
            }
        }
    }

    if( BooksNum >= 5 )
    {
        printf("\n:: Most Popular Books ::\n");
        for (int I = 0; I < 5; I++) {
            printf("- %s\n", MyBooks[I].Title);
        }
    }
}






