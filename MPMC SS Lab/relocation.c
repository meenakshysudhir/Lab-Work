#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

char bMask[MAX];

void check_bitmask(char bitmask[MAX])
{
    int i = 0;
    strcpy(bMask, "");
    for (int i = 0; i < 3; i++)
    {
        switch (bitmask[i])
        {
        case '0':
            strcat(bMask, "0000");
            break;
        case '1':
            strcat(bMask, "0001");
            break;
        case '2':
            strcat(bMask, "0010");
            break;
        case '3':
            strcat(bMask, "0011");
            break;

        case '4':
            strcat(bMask, "0100");
            break;

        case '5':
            strcat(bMask, "0101");
            break;

        case '6':
            strcat(bMask, "0110");
            break;

        case '7':
            strcat(bMask, "0111");
            break;

        case '8':
            strcat(bMask, "1000");
            break;

        case '9':
            strcat(bMask, "1001");
            break;

        case 'A':
            strcat(bMask, "1010");
            break;

        case 'B':
            strcat(bMask, "1011");
            break;

        case 'C':
            strcat(bMask, "1100");
            break;

        case 'D':
            strcat(bMask, "1101");
            break;

        case 'E':
            strcat(bMask, "1110");
            break;

        case 'F':
            strcat(bMask, "1111");
            break;
        }
    }
}

int main(void)
{
    int relocAd, txtad;

    char progName[MAX], rec[MAX], bitmask[MAX], txtLen[MAX];
    char first[10], second[10];
    int startingAd, length, recAdr, ind;
    FILE *fp = fopen("relocation_input.txt", "r");
    printf("Enter the adress to relocate the program  : ");
    scanf("%X", &relocAd);

    fscanf(fp, "%s", rec);
    if (strcmp(rec, "H") == 0)
    {
        fscanf(fp, "%s %X %X", progName, &startingAd, &length);
    }

    strcpy(rec, "");
    fscanf(fp, "%s", rec);

    while (strcmp(rec, "E") != 0)
    {
        if (strcmp(rec, "T") == 0)
        {
            fscanf(fp, "%X %X %s", &recAdr, &txtLen, bitmask);
            check_bitmask(bitmask);
            recAdr += relocAd;
            ind = 0;
            fscanf(fp, "%s", rec);
        }
        if (bMask[ind++] == '1')
        {

            for (int i = 0; i < 6; i++)
            {
                if (i < 2)
                {
                    first[i] = rec[i];
                }
                else
                {
                    second[i - 2] = rec[i];
                }
            }
            first[2] = '\0';
            second[6] = '\0';

            int new_code = strtol(second, NULL, 16);
            new_code += relocAd;
            // printf("%X", recAdr);
            printf("%X\t%s%04X\n", recAdr, first, new_code);
        }
        else
        {
            printf("%X\t%s\n", recAdr, rec);
        }
        recAdr += 3;
        fscanf(fp, "%s", rec);
    }
}