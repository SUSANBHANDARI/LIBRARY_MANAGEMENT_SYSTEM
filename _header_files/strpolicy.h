// These are some functions will let you check certain rule in your string

#include<stdio.h>
#include<string.h>

int lettercheck(const char []);
int numcheck(const char []);
int symbolcheck(const char []);
int spacecheck(const char []);
int lengthcheck(const char [],int min,int max);
int onlycapitalcheck(const char []);
int emailend(const char []); // use this for email only

int lettercheck(const char str[])
{
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]>=65&&str[i]<=90||str[i]>=97&&str[i]<=123)
        {
            return 1;
        }
    }
    printf("\nError Letter must be included");
    return 0;
}

int numcheck(const char str[])
{
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]>=48&&str[i]<=57)
        {
            return 1;
        }
    }
    printf("\nError Number must be included");
    return 0;
}

int symbolcheck(const char str[])
{
    for(int i=0;str[i]!='\0';i++)
    {
        if(!(str[i]>=65&&str[i]<=90||str[i]>=97&&str[i]<=123||str[i]>=48&&str[i]<=57||str[i]==32))
        {
            return 1; 
        }
    }
    printf("\nError Symbol must be included");
    return 0;   
}

int spacecheck(const char pass[])
{
    for(int i=0;pass[i]!='\0';i++)
    {
        if(pass[i]==32)
        {
            printf("\nError space not required");
            return 1;
        }
    }
    return 0;
}

int lengthcheck(const char str[],int min,int max)
{
    int len=strlen(str);
    if(!(len>=min&&len<=max))
    {
        printf("\nError Length should be %d-%d word",min,max);
        return 0;
    }
    return 1;
}

int onlycapitalcheck(const char str[])
{
    for (int i=0;str[i]!='\0';i++)
    {
        if(str[i]>=97&&str[i]<=122)
        {
            printf("\nError all letters must be capital");
            return 0;            
        }
    }
    return 1;
}


int emailend(const char em[])
{
    int l=strlen(em);
    if(!(em[l-10]=='@'&&em[l-9]=='g'&&em[l-8]=='m'&&em[l-7]=='a'&&em[l-6]=='i'&&em[l-5]=='l'&&em[l-4]=='.'&&em[l-3]=='c'&&em[l-2]=='o'&&em[l-1]=='m'))
    {
        printf("\nError Email should end with \'@gmail.com\'");
        return 0;
    }
    return 1;
}