#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Optab
{
    char opcode[10];
    char mnemonic[10];
} optab[100];

int coptab = 0;
int csymtab = 0;
int programLength;
struct Symtab
{
    char label[10];
    char locctr[10];
} symtab[100];

int search_symtab(char Label[100])
{
    for (int i = 0; i < csymtab; i++)
    {
        if (strcmp(symtab[i].label, Label) == 0)
        {
            return 1; // Label exists
        }
    }
    return 0;
}

void addSymtab(char Label[100], int Locctr)
{
    strcpy(symtab[csymtab].label, Label);
    // strcpy(symtab[csymtab].locctr, Locctr);
    // symtab[csymtab].locctr = Locctr;
    sprintf(symtab[csymtab].locctr, "%04X", Locctr);
    csymtab++;
}

int checkOptable(char opcode[100])
{
    for (int i = 0; i < coptab; i++)
    {
        if (strcmp(optab[i].opcode, opcode) == 0)
        {
            return 1;
        }
    }
    return 0;
}
// int toHex(int preloc)
// {
//     if ()
// }
int main(void)
{
    FILE *f1 = fopen("input.txt", "r");
    FILE *f2 = fopen("intermediate.txt", "w");
    FILE *f3 = fopen("optab.txt", "r");
    FILE *f4 = fopen("symtab.txt", "w");

    char op[100];
    char mnemonic_code[100], mne[100];
    while (fscanf(f3, "%s %s", op, mne) != EOF)
    {
        strcpy(optab[coptab].opcode, op);
        strcpy(optab[coptab].mnemonic, mne);
        coptab++;
    }

    fclose(f3);

    char label[100], opcode[100], operand[100];
    int locationctr, prevLocationctr;

    fscanf(f1, "%s %s %s", label, opcode, operand);
    // printf("%s %s %s\n", label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        locationctr = atoi(operand);
        // int start = fpr
        fprintf(f2, "%s\t%s\t%04X\n", label, opcode, locationctr);
        fscanf(f1, "%s %s %s", label, opcode, operand);
    }
    // printf("%s %s %s\n", label, opcode, operand);
    while (strcmp(opcode, "END") != 0)
    {

        // fprintf(f4, "%s\t%s\t%s\n", label, opcode, operand);

        if (strcmp(label, "_") != 0)
        {
            if (search_symtab(label) == 1)
            {
                printf("Error ! Label exists\n");
            }
            else
            {
                addSymtab(label, locationctr);
            }
        }
        prevLocationctr = locationctr;
        if (checkOptable(opcode) == 1)
        {
            locationctr += 3;
        }
        else
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                locationctr += 3;
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                locationctr++;
            }
            else if (strcmp(opcode, "RESB") == 0)
            {
                locationctr += atoi(operand);
            }
            else if (strcmp(opcode, "RESW") == 0)
            {
                locationctr += atoi(operand) * 3;
            }
            else
            {
                printf("Error ! Invalid opcode\n");
            }
        }
        // printf("%d", prevLocationctr);
        // int prevLocationctr1 = toHex(prevLocationctr);
        fprintf(f2, "%s\t\t%s\t\t%s\t\t%04X\n", label, opcode, operand, prevLocationctr);
        fscanf(f1, "%s %s %s ", label, opcode, operand);
    }
    if (strcmp(opcode, "END") == 0)
    {
        fprintf(f2, "%s %s", opcode, operand);
        programLength = locationctr;
    }
    for (int i = 0; i < csymtab; i++)
    {
        fprintf(f4, "%s\t%s\n", symtab[i].label, symtab[i].locctr);
    }
}