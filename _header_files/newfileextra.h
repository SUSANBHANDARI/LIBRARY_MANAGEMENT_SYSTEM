// These are some functions created in order to perform with some additional file actions

#include<stdio.h>

int filecheck(const char []);
void filecreate(const char []);
int fileemptycheck(const char []);

int filecheck(const char file[])
{
    FILE *fptr;
    fptr=fopen(file,"r");
    if(fptr==NULL)
    {
        fclose(fptr);
        return 0; 
    }
    fclose(fptr);
    return 1;
}

void filecreate(const char file[])
{
    FILE *fptr=fopen(file,"a");
    fclose(fptr);
}

int fileemptycheck(const char file[])
{
    FILE *fptr=NULL;
    fptr=fopen(file,"r");
    fseek(fptr,0,SEEK_END);
    if(ftell(fptr)==0)
    {
        fclose(fptr); 
        return 1; // file empty
    }
    fclose(fptr);
    return 0; // file not empty
}