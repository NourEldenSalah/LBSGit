#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "Admin.h"
#include "Book.h"
#include "MeM.h"

// validate any allocation

//Redirect(); you and omar
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


int FirstTime = true;
int Saved = false;

void main() {

    if(FirstTime)
    {
        Load_Books();
        Load_Borrow();
        Load_User();

        FirstTime = false;
    }


    int Select = 0;

    printf("\n:::[Main Menu]:::\n\n");
    printf("1.Book Management\n");
    printf("2.Member Management\n");
    printf("3.Administrative actions\n");
    printf("4.Save Changes\n");
    printf("5.Exit\n");
    printf("------------------------\n");

    POP();

    while (Select != 1 && Select != 2 && Select != 3 && Select != 4 && Select != 5) {
        printf("Enter your choice: ");
        scanf("%d", &Select);
    }

    system("@cls||clear");

    if (Select == 1) GotoBook();
    if (Select == 2) GotoMeM();
    if (Select == 3) GotoAdmin();
    if (Select == 4) GotoSave();
    if (Select == 5) exit(0);
}

void GotoSave() {

    Save_B();
    Save_Borrows();
    Save_Mem();

    exit(0);
}

// Some Base Methods


bool IsNumber(const char *str) {
    char *E = NULL;
    (void) strtol(str, &E, 0); /* Base can be 0 or anything cuz u don't seek numbers, but chars */
    return E != NULL && *E == (char) 0;
}

void Redirect() {

    int Choice = 0;
    char *CChoice = NULL;

    printf("\n\n");
    printf("----------\n");
    printf("Move to...\n");
    printf("----------\n");

    printf("1.Book Management\n");
    printf("2.Member Management\n");
    printf("3.Administrative actions\n");
    printf("4.Main Menu\n");
    printf("------------------------\n");

    /* Validation */

    Here:
    CChoice = GetField();

    while (!IsNumber(CChoice)) { free(CChoice); CChoice = GetField(); }
    sscanf(CChoice, "%d", &Choice);
    while (Choice <= 0 || Choice > 4) { free(CChoice); goto Here; }

    /********************************************************/

    system("@cls||clear");

    if (Choice == 1) GotoBook();
    if (Choice == 2) GotoMeM();
    if (Choice == 3) GotoAdmin();
    if (Choice == 4) main();
}

char *GetString() {

    char *Text, Input;
    size_t CH = 1, Index = 0;

    Text = malloc(sizeof(char) * CH);
    if (!Text) return NULL;


    while ((Input = getchar()) != '\n' && Input != EOF) {

        Text = realloc(Text, CH++ * sizeof(char));
        if (!Text) return NULL;

        Text[Index++] = Input;
    }

    Text[Index] = '\0';

    if (Text[0] == '\0') {
        free(Text);
        return NULL;
    }

    return Text;
}

int FileCounter(char *FileName) {

    FILE *MF = fopen(FileName, "r");

    int ch, Lines = 0;

    do {
        ch = fgetc(MF);
        if (ch == '\n') Lines++;

    } while (ch != EOF);

    fclose(MF);

    return Lines;
}

char *strcasestr(const char *S, const char *Input) {

    size_t i;

    if (!*Input)
        return (char *) S;

    for (; *S; S++) {

        if (toupper(*S) == toupper(*Input)) {
            for (i = 1;; i++) {
                if (!Input[i])
                    return (char *) S;
                if (toupper(S[i]) != toupper(Input[i]))
                    break;
            }
        }
    }

    return NULL;
}



