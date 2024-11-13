#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Optab
{
    char opcode[10];
    char mnemonic[10];
} optab[100];

int programLength;
int coptab = 0;
int csymtab = 0;
int txtrec = 0;
char fullrec[100];
struct Symtab
{
    char label[10];
    char locctr[10];
} symtab[100];

void addtoOptab(FILE *fp, struct Optab (*op)[100])
{

    char opcode[100], mnemonic[100];
    while (fscanf(fp, "%s\t%s", opcode, mnemonic) != EOF)
    {
        strcpy((*op)[coptab].opcode, opcode);
        strcpy((*op)[coptab].mnemonic, mnemonic);
        coptab++;
    }
}
void addtoSymtab(FILE *fp, struct Symtab (*sym)[100])
{

    char label[100], locctr[100];
    while (fscanf(fp, "%s\t%s", label, locctr) != EOF)
    {
        strcpy((*sym)[csymtab].label, label);
        strcpy((*sym)[csymtab].locctr, locctr);
        csymtab++;
    }
}

int searchOptab(char opcode[100])
{
    for (int i = 0; i < coptab; i++)
    {
        if (strcmp(opcode, optab[i].opcode) == 0)
        {
            return i;
        }
    }
    return -1;
}
int searchSymtab(char opcode[])
{
    for (int i = 0; i < csymtab; i++)
    {
        if (strcmp(opcode, symtab[i].label) == 0)
        {
            return i;
        }
    }
    return -1;
}
int main(void)
{
    FILE *f1 = fopen("intermediate.txt", "r");
    FILE *f2 = fopen("symtab.txt", "r");
    FILE *f3 = fopen("optab.txt", "r");
    FILE *f4 = fopen("length.txt", "r");
    FILE *f5 = fopen("ObjectProgram.txt", "w+");
    FILE *f6 = fopen("objectCode.txt", "w+");

    addtoOptab(f3, &optab);
    addtoSymtab(f2, &symtab);

    char label[100], opcode[100], operand[100], locctr[100], length[100], startingAddress[100];
    char progName[100], mnemonic[100], opAddress[100], rec[100];
    fscanf(f4, "%s %s", length, startingAddress);
    fscanf(f1, "%s\t%s\t%s\t%s", label, opcode, locctr, operand);
    fprintf(f6, "%s\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    if (strlen(label) > 6)
    {
        printf("Error! Program name too long\n");
    }
    int rest = 6 - strlen(label);

    if (rest != 0)
    {
        for (int i = 0; i < rest; i++)
        {
            strcat(progName, "_");
        }
    }
    strcat(progName, label);
    if (strcmp(opcode, "START") == 0)
    {
        fprintf(f5, "H^%s^%s^%s\n", progName, startingAddress, length);
    }
    fscanf(f1, "%s\t%s\t%s\t%s", label, opcode, operand, locctr);
    int toCheck;
    while (strcmp(opcode, "END") != 0)
    {
        strcpy(rec, "");
        int toCheck = searchOptab(opcode);
        if (toCheck != -1) // Opcode present in Optab
        {
            strcpy(mnemonic, optab[toCheck].mnemonic);
            int ind = searchSymtab(operand);
            if (ind != -1)
            {
                strcpy(opAddress, symtab[ind].locctr);
            }
            else
            {
                printf("Error ! Symbol not found in symtab\n");
                for (int i = 0; i < 4; i++)
                {
                    strcpy(opAddress, "0");
                }
            }
            strcat(rec, mnemonic);
            strcat(rec, opAddress);
        }
        else
        {
            if (!strcmp(opcode, "WORD") || !strcmp(opcode, "BYTE"))
            {
                if (strlen(operand) < 6)
                {
                    strcpy(opAddress, "");
                    int rest = 6 - strlen(operand);
                    for (int i = 0; i < rest; i++)
                    {
                        strcat(opAddress, "0");
                    }
                    strcat(opAddress, operand);
                }
                strcpy(rec, opAddress);
            }
            else if (!strcmp(opcode, "RESW") || !strcmp(opcode, "RESB"))
            {
                strcpy(rec, "_");
            }
            else
            {
                printf("Error ! Invalid Opcode\n");
            }
        }
        if (txtrec < 10)
        {
            if (strcmp(rec, "_") != 0)
            {
                strcat(fullrec, rec);
                strcat(fullrec, "^");
                txtrec++;
            }
        }
        if (txtrec == 10)
        {
            int len = 10 * 6 / 2;
            fprintf(f5, "T^%s^%02X^%s\n", startingAddress, len, fullrec);
            txtrec = 0;
            strcpy(fullrec, "");
        }
        fprintf(f6, "%s\t%s\t%s\t%s\t%s\n", locctr, label, opcode, operand, rec);
        fscanf(f1, "%s\t%s\t%s\t%s", label, opcode, operand, locctr);
    }
    if (strcmp(fullrec, "") != 0)
    {
        int len = txtrec * 6 / 2;
        fprintf(f5, "T^%s^%02X^%s\n", startingAddress, len, fullrec);
    }
    fprintf(f5, "E^%s", startingAddress);
}
