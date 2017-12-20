#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "Book.h"
#include "main.h"

typedef struct D {
    int dd;
    int mm;
    int yy;
}Date;

void GotoMeM()
{

    Date ReturnDate;
    char *GetDate,*DD,*MM,*YY,*Value;
    int CheckDD = true, CheckMM = true, CheckYY = true;  // Validation for tokens
                                                         // true = 1 , false = 0

    time_t t = time(NULL);
    struct tm today = *localtime(&t);

    printf("now: %d/%d/%d\n", today.tm_mday, today.tm_mon + 1, today.tm_year + 1900); // search to know what 1900 and other mean


    Here:
    printf("\nEnter Return Day(dd/mm/yy):\n");
    GetDate = GetField();  /* to make sure he doesnt enter white spaces or empty value */

    /* To make sure he enterd two(/) and nothing else cuz code depend on (/) */

    int counter = 0;
    for (int i=0; GetDate[i]!= '\0'; i++){

        if ( GetDate[i] == '/') counter++;
    }
    if(counter != 2)
    {
        free(GetDate); goto Here;
    }
    /* You can make function(s) for next code to reduce lines */

    /* split (GetDate) into tokens */
    //DD
    Value = strtok(GetDate, "/");
    DD = malloc(strlen(Value) + 1);
    strcpy(DD, Value);

    //MM
    Value = strtok(NULL, "/");
    MM = malloc(strlen(Value) + 1);
    strcpy(MM, Value);

    //YY
    Value = strtok(NULL, "/");
    YY = malloc(strlen(Value) + 1);
    strcpy(YY, Value);

    for (int i=0; DD[i]!= '\0'; i++)
        if (isalpha(DD[i]) != 0) { CheckDD = false; break; }  /* isalpha = 1 or 0 (true,false) */

    for (int i=0; MM[i]!= '\0'; i++)
        if (isalpha(MM[i]) != 0) { CheckMM = false; break; }

    for (int i=0; YY[i]!= '\0'; i++)
        if (isalpha(YY[i]) != 0) { CheckYY = false; break; }


    if (CheckDD == false && CheckMM == false && CheckYY == false)
    {
        free(DD); free(MM); free(YY); free(Value); free(GetDate); goto Here;
    }
    else
    {
        int A,B,C;

        /* Convert data into int */

        sscanf(DD, "%d", &A);
        sscanf(MM, "%d", &B);
        sscanf(YY, "%d", &C);

        if (A > 0 && A <= 30 && B > 0  && B <= 12 && C > 0) // 30 days per month & 12 months per year
        {
            ReturnDate.dd = A; ReturnDate.mm = B; ReturnDate.yy = C;
        }
        else
        {
            free(DD); free(MM); free(YY); free(Value); free(GetDate); goto Here;
        }
    }


    free(DD); free(MM); free(YY); free(Value); free(GetDate);
}

char * DateToString(int d, int m, int y){

    char str[512];

    sprintf(str,512,"%d/%d/%d",)

    return  str;
}