#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "Admin.h"
#include "Book.h"
#include "MeM.h"


void main() {

    Load_Books();

    int Select = 0;

    printf("\n:::[Main Menu]:::\n\n");
    printf("1.Book Management\n");
    printf("2.Member Management\n");
    printf("3.Administrative actions\n");
    printf("4.Save Changes\n");
    printf("5.Exit\n");
    printf("------------------------\n");

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
    printf("------------------------\n");

    /* Validation */

    Here:
    CChoice = GetField();

    while (!IsNumber(CChoice)) { free(CChoice); CChoice = GetField(); }
    sscanf(CChoice, "%d", &Choice);
    while (Choice <= 0 || Choice > 3) { free(CChoice); goto Here; }

    /********************************************************/

    system("@cls||clear");

    if (Choice == 1) GotoBook();
    if (Choice == 2) GotoMeM();
    if (Choice == 3) GotoAdmin();
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



