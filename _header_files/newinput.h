#include<stdio.h>
#include<conio.h>//for getch() and for putch()
void fixinput(char [],int,int); 
// size - pass the size of string variable
// str - pass the string variable
// hide - passing 0 will let input be incripted , other numbers won't
void fixinput(char str[],int size,int hide)
{
    // ascii returned by getch()
    // 8 is ascii of backspace
    // 13 is ascii of enter
    // 32 is ascii of whitespace
    int len=0;
    int cursor=0;
    int a=0;
    size=size-1;
    while(1)
    {
        a=getch();
        if(a==0||a==224) // arrow key
        {
            a=getch();
            if(a==75&&cursor!=0) // left arrow
            {
                printf("\b");
                cursor--;
            }
            else if(a==77&&cursor!=len) // right arrow
            {
                if(hide==0)
                {
                    putch(str[cursor]);
                }
                else
                {
                    printf("*");
                }
                cursor++;
            }
            continue;
        }
        if(a>=32&&a<=126&&len!=size) // alphabets
        {
            if(a!=32||cursor!=0)
            {
                for(int i=len-1;i>=cursor;i--) //for cursor<len
                {
                    str[i+1]=str[i];
                }
                len++;
                str[cursor]=a; // up to here every element is updates in string
                for(int i=cursor;i<=len-1;i++) // Now overwrite character from cursor(suppose 0) to len(updated_above)-1
                {
                    if(hide==0)
                    {
                        putch(str[i]);
                    }
                    else
                    {
                        printf("*");
                    }
                }
                cursor++; 
                for(int i=len-1;i>=cursor;i--) // We have increased cursor to ensure it is at prev_cursor+1 after string is increased in middle 
                {
                    printf("\b");
                }
            }
        }
        else if(a==8&&cursor>0) // backspace
        {
            printf("\b \b");
            cursor--;
            len--;
            for(int i=cursor;i<len;i++)
            {
                str[i]=str[i+1];
                if(hide==0)
                {
                    putch(str[i]);
                }
                else
                {
                    printf("*");
                }
            }
            printf(" \b");
            for(int i=len;i>cursor;i--)
            {
                printf("\b");
            }
        }
        else if(a==13&&len!=0)
        {
            break;
        }
    }
    if(hide==0)
    {
        for(int i=len-1;i>=0;i--)
        {
            if(str[i]!=32)
            {
                str[i+1]='\0';
                break;
            }
        }
    }
    else
    {
        str[len]='\0';
    }
    printf("\n");
}
