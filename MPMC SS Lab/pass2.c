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

struct Symtab
{
    char label[10];
    char locctr[10];
} symtab[100];

void addtoOptab(FILE* fp,struct Optab (*op)[100]){
    
   char opcode[100], mnemonic[100]; 
   while(fscanf(fp,"%s\t%s",opcode,mnemonic) != EOF)
   {
       strcpy((*op)[coptab].opcode,opcode);
       strcpy((*op)[coptab].mnemonic,mnemonic);
       coptab++;
   }
}
void addtoSymtab(FILE* fp,struct Symtab (*sym)[100]){
    
   char label[100], locctr[100]; 
   while(fscanf(fp,"%s\t%s",label,locctr) != EOF)
   {
       strcpy((*sym)[csymtab].label,label);
       strcpy((*sym)[csymtab].locctr,locctr);
       csymtab++;
   }
}
int main(void){
    FILE *f1 = fopen("intermediate.txt", "r");
    FILE *f2 = fopen("symtab.txt","r");
    FILE* f3 = fopen("optab.txt","r");
    FILE* f4 = fopen("length.txt","r");
    FILE* f5 = fopen("ObjectProgram.txt","w+");

    addtoOptab(f3,&optab);
    addtoSymtab(f2,&symtab);

    char label[100],opcode[100],operand[100],locctr[100],length[100],startingAddress[100];
    fscanf(f4,"%s %s",length,startingAddress);
    fscanf(f1,"%s\t%s\t%s\t%s",label,opcode,locctr,operand);
    printf("%s %s %s",label,opcode,locctr);
    if(strlen(label) > 6)
    {
        printf("Error! Program name too long\n");
    }
    printf("%s",opcode);
    int rest = 6 - strlen(opcode);
    if(rest!= 0)
    {
        for(int i = 0; i < rest;i++)
        {
            strcat("_",opcode);
        }
    }
    printf("%s",opcode);
    //if(strcmp(opcode,"START") == 0){
    //    printf("H^")
    //}

    

}
