// LIBRARY MANAGEMENT SYSTEM PROJECT

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h> // for getch() 
#include<direct.h>
#include"_header_files\newinput.h" // for string input only
#include"_header_files\strpolicy.h"
#include"_header_files\newfileextra.h"

// Structure Definition

typedef struct acc_dt
{
    char num[10];
    char acc[17];
    char username[17];
	char password[16];
}Account_Detail;

typedef struct record_file
{
	char bk_file[18];
	char mem_file[17];
}Record_File;

typedef struct book_rec
{
    int book_num;
    char book_name[21];
    char book_author[26];
}Book_Record;

typedef struct book_provide
{
    char book_name[21];
    char book_author[26];
}Book_Provide;

typedef struct mem_rec
{
    int mem_id;
    char mem_name[26];
    long long mem_phone;
    int book_borrow;
    Book_Provide pvd[3];
}Member_Record;

// Function Declarations
void enter_to_move();
void title_format(char [],int);
void input_clear(void *,int);
int continue_return();
int digit_count(const void *,int);

void sign_up();
int User_Validation(const char []);
int user_not_allowed_case(const char []);
int user_duplicate_check(const char []);
int Password_Validation(const char []);
void Account_Create(const char [],const char []);
void file_add_by_1(char [10],char [17],const char []);

void sign_in();
int User_Check(const char []);
int Password_Check(const char [],const char[],char [17]);
void number_extraction(const char [17],char [10]);
void account_file_implementation(const char [17],char [10]);
void Library_actions(const char []);

void book_section(const Record_File);
void book_add(const char []);
int book_duplicate(const char [],const char [],const char []);
void ascending_book(const char []);
void booknumblocks(const char [],int *);
void bkarr_fill(Book_Record *,const char [],int);
void book_list(const char [],int);
void book_delete(const char []);
void book_update(const char []);
void book_update_field(char [],int,char [],int,int *,int *,const char []);
void book_provide_return(const Record_File);
void book_provide(const Record_File);
void provide_detail(const Record_File);
void bookprovidecount(const char [],int *);
void book_return(const Record_File);

void member_section(const char []);
void member_add(const char []);
int memberid_duplicate(const int,const char []);
int memberph_duplicate(const long long,const char []);
void ascending_member(const char []);
void membernumblocks(const char [],int *);
void memarr_fill(Member_Record *,const char [],int);
void member_list(const char [],int);
void member_delete(const char []);
void member_update(const char []);
void member_update_field(int *,char [],int,long long *,int *,const char []);

// Main Function
int main()
{
    int ch=0;
    printf("\nPress Enter Button To Get Started");
    while(1)
    {
        title_format("MAIN MENU",1);
        printf("\nEnter choice :\n1. SIGN UP\n2. SIGN IN\n3. EXIT\n");
        printf("\nYour choice:"); 
        input_clear(&ch,sizeof(ch)); 
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                sign_up();
                printf("\nPress Enter to return to main menu...");
                break;
            case 2:
                sign_in();
                printf("\nPress Enter to return to main menu...");
                break;
            case 3:
                printf("\nExiting the system...\n\n");
                exit(0);
            default:
                printf("Enter a number from 1 to 3.\n");
                printf("\nPress Enter to return to menu...");
        }
    }
    return 0;
}

// Functions Definition
void enter_to_move()
{
    int a=0;
    top:
    a=getch();
    if(a!=13)
    {
        goto top;
    }
}

void title_format(char str[],int num)
{
    int len=strlen(str)+4;
    if(num!=0)
    {
        enter_to_move();
        system("CLS");
    }
    for(int i=0;i<=len-1;i++)
    {
        printf("-");
    }
    printf("\n");
    printf("  %s\n",str);
    for(int i=0;i<=len-1;i++)
    {
        printf("-");
    }
    printf("\n");
}

void input_clear(void *ch,int size)
{
    fflush(stdin); 
    if(size==sizeof(int))
    {
        *((int *)ch)=0; // if you enter right input and then wrong input then fflush isn't enough, we have to set the value to zero to remove previous value
    }
    else if(size==sizeof(long long))
    {
        *((long long *)ch)=0;
    }
}

int continue_return()
{
    int a=0;
    printf("\nPress enter to continue or press backspace to go back");
    top:
    a=getch();
    if(a==13) // enter
    {
        printf("\n");
        return 1;
    }
    else if(a==8) // backspace
    {
        printf("\n");
        return 0;
    }
    goto top;
}

int digit_count(const void *num,int size)
{
    int count=0;
    if(size==sizeof(int))
    {
        int inum=*((int *)num);
        while(inum>0)
        {
            count++;
            inum=inum/10;
        }
    }
    else if(size==sizeof(long long))
    {
        long long lnum=*((long long *)num);
        while(lnum>0)
        {
            count++;
            lnum=lnum/10;
        }  
    }
    return count;
}

void sign_up()
{
    char user[17],pass[16];
    etop:
    system("CLS");
    printf("\nCreate Your Account [Eg:ABC123(USERNAME),name1234@(PASSWORD)]\n");
    printf("\nUSERNAME:");
    fixinput(user,sizeof(user),0);
    if(User_Validation(user))
    {
        ptop:
        printf("\nPASSWORD:");
        fixinput(pass,sizeof(pass),0);
        if(Password_Validation(pass))
        {
            Account_Create(user,pass);
        }
        else
        {
            if(continue_return()==0)
            {
                return;
            }
            system("CLS");
            printf("\nCreate Your Account [Eg:ABC123(Username),name1234@(Password)]\n");
            printf("\nUSERNAME:%s\n",user);
            goto ptop;
        }
    }
    else
    {
        if(continue_return()==0)
        {
            return;
        }
        goto etop;
    }
}

int User_Validation(const char user[])
{
    int ocapck=0,numck=0,lenck=0,spck=0;
    ocapck=onlycapitalcheck(user),numck=numcheck(user),lenck=lengthcheck(user,4,16),spck=spacecheck(user);
    if(ocapck==1&&numck==1&&lenck==1&&spck!=1)
    {
        if(user_not_allowed_case(user))
        {
            if(!(user_duplicate_check(user)))
            {
                return 1;
            }
        }      
    }
    return 0;
}

int user_not_allowed_case(const char user[])
{
    for(int i=0;user[i]!='\0';i++)
    {
        if(!((user[i]>=48&&user[i]<=57)||(user[i]>=65&&user[i]<=90)))
        {
            printf("\nError only enter capital letters and numbers");
            return 0;
        }
    }
    return 1;
}

int user_duplicate_check(const char user[])
{
    int cou=0;
    char fpath[50]="_text_files\\";
    strcat(fpath,"reg.txt");
    _mkdir("_text_files");
    Account_Detail det;
    if(filecheck(fpath))
    {
        FILE *fptr=fopen(fpath,"r");
        while(fread(&det,sizeof(Account_Detail),1,fptr))
        {
            if(strcmp(det.username,user)==0)
            {
                cou++;
                break;
            }
        }
        fclose(fptr);
        if(cou!=0)
        {
            printf("\nError already have this Username Registered. Try another one");
            return 1;
        }
    }
    return 0;
}

int Password_Validation(const char pass[])
{
    int letck=0,numck=0,symck=0,lenck=0,spck=0;
    letck=lettercheck(pass),numck=numcheck(pass),symck=symbolcheck(pass),lenck=lengthcheck(pass,8,15),spck=spacecheck(pass);
    if(letck==1&&numck==1&&symck==1&&lenck==1&&spck!=1)
    {
        return 1;
    }
    return 0;

}

void Account_Create(const char user[],const char pass[])
{
    Account_Detail det;
    char reg_fl[]="reg.txt",fpath[50]="_text_files\\";
    strcat(fpath,reg_fl);
    _mkdir("_text_files");
    if(!filecheck(fpath))
    {
        filecreate(fpath);
    }
    char num[10],account[17];
    file_add_by_1(num,account,reg_fl);
    strcpy(det.num,num),strcpy(det.acc,account),strcpy(det.username,user),strcpy(det.password,pass);
    FILE *fptr=fopen(fpath,"a");
    fwrite(&det,sizeof(det),1,fptr);
    fclose(fptr);
    printf("\nAccount Created Successfully\n");
}

void file_add_by_1(char num[10],char acc[17],const char reg_fl[])
{
    char a[10],add='1',car=0,fpath[50]="_text_files\\";
    int cou=0;
    strcat(fpath,reg_fl);
    strcpy(acc,"acc");
    FILE *fptr=fopen(fpath,"r");
    if(fileemptycheck(fpath))
    {
        strcpy(num,"0");
    }
    else
    {
        Account_Detail det;
        fseek(fptr,-sizeof(Account_Detail),SEEK_END);
        fread(&det,sizeof(Account_Detail),1,fptr);
        strcpy(num,det.num);// use fseek() and fread() function to get last value of every element
    }
    fclose(fptr);
    strcpy(a,num);
    strrev(a);
    top:
    if(a[cou]!='9')
	{
		a[cou]=a[cou]+add-48+car;
		car='0'-'0';
		add='1';
	}
    else if(a[cou]=='9')
	{
		car='1';
		a[cou]='0';
		cou++;
		if(a[cou]=='\0')
		{
			a[cou]='0';
			a[cou+1]='\0';
		}
		add='0'-'0';
		goto top;
	}
    strrev(a);
    strcpy(num,a);
    strcat(acc,a);
    strcat(acc,".txt");
}

void sign_in()
{
    char user[17],pass[16],acc_fl[17],num[10];
    etop:
    system("CLS");
    printf("\nEnter your Account Details\n");
    printf("\nUSERNAME:");
    fixinput(user,sizeof(user),0);
    if(User_Check(user))
    {
        ptop:
        printf("\nPASSWORD:");
        fixinput(pass,sizeof(pass),1);
        if(Password_Check(user,pass,acc_fl))
        {
            number_extraction(acc_fl,num);
            account_file_implementation(acc_fl,num);
            printf("\nSuccessful Sign in");
            Library_actions(acc_fl);
        }
        else
        {
            if(continue_return()==0)
            {
                return;
            }
            system("CLS");
            printf("\nEnter your Account Details\n");
            printf("\nUSERNAME:%s\n",user);
            goto ptop;
        }
    }
    else
    {
        if(continue_return()==0)
        {
            return;
        }
        goto etop;
    }
}

int User_Check(const char user[])
{
    Account_Detail det;
    char fpath[50]="_text_files\\";
    int cou=0;
    strcat(fpath,"reg.txt");
    _mkdir("_text_files");
    FILE *fptr=fopen(fpath,"r");
    while(fread(&det,sizeof(Account_Detail),1,fptr))
    {
        if(strcmp(det.username,user)==0)
        {
            cou++;
            break;
        }
    }
    fclose(fptr);
    if(cou!=0)
    {
        return 1;
    }
    printf("\nDon't have this username registered into the system\n");
    return 0;
}

int Password_Check(const char user[],const char pass[],char acc_fl[17])
{
    Account_Detail det;
    char fpath[50]="_text_files\\";
    int cou=0;
    strcat(fpath,"reg.txt");
    FILE *fptr=fopen(fpath,"r");
    while(fread(&det,sizeof(Account_Detail),1,fptr))
    {
        if(strcmp(det.username,user)==0)
        {
            if(strcmp(det.password,pass)==0)
            {
                strcpy(acc_fl,det.acc);
                cou++;
                break;
            }
        }
    }
    fclose(fptr);
    if(cou!=0)
    {
        return 1;
    }
    printf("\nWrong Password\n");
    return 0;
}

void number_extraction(const char acc_fl[17],char num[10])
{
    int cou=0;
    for(int i=0;acc_fl[i]!='\0';i++)
    {
        if(acc_fl[i]>=48&&acc_fl[i]<=57)
        {
            num[cou]=acc_fl[i];
            cou++;
        }
    }
    num[cou]='\0';
}

void account_file_implementation(const char acc_fl[17],char num[10])
{
    char fpath[50]="_text_files\\";
    strcat(fpath,acc_fl);
    if(!filecheck(fpath))
    {
        filecreate(fpath);
    }
    Record_File rec;
    char bk_fl[18]="book",mem_fl[17]="mem";
    if(fileemptycheck(fpath))
    {
        strcat(bk_fl,num),strcat(mem_fl,num);
        strcat(bk_fl,".txt"),strcat(mem_fl,".txt");
        strcpy(rec.bk_file,bk_fl),strcpy(rec.mem_file,mem_fl);
        FILE *fptr=fopen(fpath,"w");
        fwrite(&rec,sizeof(rec),1,fptr);
        fclose(fptr);
    }
}

void Library_actions(const char acc_fl[])
{
    Record_File rec;
    char fpath[50]="_text_files\\";
    strcat(fpath,acc_fl);
    FILE *fptr=fopen(fpath,"r");
    fread(&rec,sizeof(Record_File),1,fptr);
    fclose(fptr);
    int ch=0;
    while(1)
    {
        title_format("LIBRARY MENU",1);
        printf("\nEnter choice :\n1. BOOK SECTION\n2. MEMBER SECTION\n3. RETURN\n");
        printf("\nYour choice:");
        input_clear(&ch,sizeof(ch));
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                book_section(rec);
                printf("\nPress Enter to return to library menu...");
                break;
            case 2:
                member_section(rec.mem_file);
                printf("\nPress Enter to return to library menu...");
                break;
            case 3:
                return;
            default:
                printf("Enter a number from 1 to 3.\n");
                printf("\nPress Enter to go back...");
        }
    }
}

void book_section(const Record_File rec)
{
    char fpath[50]="_text_files\\";
    int ch=0;
    strcat(fpath,rec.bk_file);
    printf("\nPress Enter again...");
    while(1)
    {
        title_format("BOOK MENU",1);
        printf("\nEnter choice :\n1. BOOK ADD\n2. BOOK LIST\n3. BOOK DELETE\n4. BOOK UPDATE\n5. PROVIDE RETURN\n6. RETURN\n");
        printf("\nYour choice:");
        input_clear(&ch,sizeof(ch));
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                book_add(fpath);
                printf("\nPress Enter to return to book menu...");
                break;
            case 2:
                book_list(fpath,1);
                printf("\nPress Enter to return to book menu...");
                break;
            case 3:
                book_delete(fpath);
                printf("\nPress Enter to return to book menu...");
                break;
            case 4:
                book_update(fpath);
                printf("\nPress Enter to return to book menu...");
                break;
            case 5:
                book_provide_return(rec);
                printf("\nPress Enter to return to book menu...");
                break;
            case 6:
                return;
            default:
                printf("Enter a number from 1 to 6.\n");
                printf("\nPress Enter to go back...");           
        }
    }
}

void book_add(const char bk_file[])
{
    char book_name[21],book_author[26];
    int book_num;
    printf("\nPress Enter again...");
    title_format("BOOK ADD",1);
    dtop:
    printf("\nBOOK_NAME[ADD]:");
    fixinput(book_name,sizeof(book_name),0);
    printf("\nBOOK_AUTHOR[ADD]:");
    fixinput(book_author,sizeof(book_author),0);
    if(!book_duplicate(book_name,book_author,bk_file))
    {
        ntop:
        printf("\nBOOK_QTY[ADD]:");
        input_clear(&book_num,sizeof(book_num));
        if(scanf("%d",&book_num)==1)
        {
            Book_Record bk;
            strcpy(bk.book_name,book_name),strcpy(bk.book_author,book_author);
            bk.book_num=book_num;
            FILE *fptr=fopen(bk_file,"a");
            fwrite(&bk,sizeof(Book_Record),1,fptr);
            fclose(fptr);
            ascending_book(bk_file);
            printf("\nBOOK RECORD ADDED: BOOK_NAME=%s ,BOOK_AUTHOR=%s ,BOOK_NUM=%d\n",book_name,book_author,book_num);
        }
        else
        {
            printf("\nError You have to input number. Press Enter to continue");
            title_format("BOOK ADD",1);
            printf("\nBOOK_NAME[ADD]:%s\n",book_name);
            printf("\nBOOK_AUTHOR[ADD]:%s\n",book_author);
            goto ntop;
        }
    }
    else
    {
        printf("\nAlready have the book of same name and author\n");
        if(!continue_return())
        {
            return;
        }
        system("CLS");
        title_format("BOOK ADD",0);
        goto dtop;
    }
}

int book_duplicate(const char book_name[],const char book_author[],const char bk_file[])
{
    if(filecheck(bk_file))
    {
        FILE *fptr=fopen(bk_file,"r");
        Book_Record bk;
        while(fread(&bk,sizeof(Book_Record),1,fptr))
        {
            if(strcmp(book_name,bk.book_name)==0&&strcmp(book_author,bk.book_author)==0)
            {
                fclose(fptr);
                return 1;
            }
        }
        fclose(fptr);
    }
    return 0;
}

void ascending_book(const char bk_file[])
{
    int count=0; 
    booknumblocks(bk_file,&count);  
    Book_Record btemp,*bk=(Book_Record *)calloc(count,sizeof(Book_Record));
    bkarr_fill(bk,bk_file,count);
    for(int i=0;i<=count-1;i++)
    {
        for(int j=i+1;j<=count-1;j++)
        {
            if(strcmp(bk[i].book_name,bk[j].book_name)>0)
            {
                btemp=bk[i];
                bk[i]=bk[j];
                bk[j]=btemp;
            }
            else if(strcmp(bk[i].book_name,bk[j].book_name)==0)
            {
                if(strcmp(bk[i].book_author,bk[j].book_author)>0)
                {
                    btemp=bk[i];
                    bk[i]=bk[j];
                    bk[j]=btemp;
                }
            }
        }
    }
    FILE *fptr=fopen(bk_file,"w");
    fwrite(bk,sizeof(Book_Record),count,fptr);
    fclose(fptr);    
    free(bk);
}

void booknumblocks(const char bk_file[],int *count)
{
    Book_Record bk;
    FILE *fptr=fopen(bk_file,"r");
    *count=0;
    while(fread(&bk,sizeof(Book_Record),1,fptr))
    {
        (*count)++;
    }
    fclose(fptr);
}

void bkarr_fill(Book_Record *bk,const char bk_file[],int count)
{
    FILE *fptr=fopen(bk_file,"r");
    fread(bk,sizeof(Book_Record),count,fptr);
    fclose(fptr);    
}

void book_list(const char bk_file[],int num)
{
    int i=0,count=0;
    if(filecheck(bk_file))
    {
        booknumblocks(bk_file,&count);
        if(count!=0)
        {
            if(num==0)
            {
                title_format("BOOK RECORDS",0);
            }
            else
            {
                printf("\nPress Enter again...");
                title_format("BOOK RECORDS",1);
            }
            FILE *fptr=fopen(bk_file,"r");
            Book_Record bk;
            printf("\n");
            printf("--------------------------------------------------------------------------\n");
            printf("%-5s %-25s %-30s %-5s\n","S.N.", "BOOK NAME", "AUTHOR", "QTY");
            printf("--------------------------------------------------------------------------\n");
            while(fread(&bk,sizeof(Book_Record),1,fptr))
            {
                printf("%-5d %-25s %-30s %-5d\n",++i,bk.book_name,bk.book_author,bk.book_num);
            }
            printf("--------------------------------------------------------------------------\n");
            fclose(fptr);
        }
    }
    if(count==0)
    {
        printf("\nPress Enter again...");
        enter_to_move();
        system("CLS");
        printf("\nNOTHING IN BOOK RECORDS\n");
    }
}

void book_delete(const char bk_file[])
{
    char book_name[21],book_author[26];
    int cou=0,count=0;
    if(filecheck(bk_file))
    {
        booknumblocks(bk_file,&count);
        if(count!=0)
        {
            book_list(bk_file,1);
            top:
            title_format("BOOK DELETE",0);
            printf("\nBOOK_NAME[DELETE]:");
            fixinput(book_name,sizeof(book_name),0);
            printf("\nBOOK_AUTHOR[DELETE]:");
            fixinput(book_author,sizeof(book_author),0);
            FILE *fptr=fopen(bk_file,"r");
            FILE *tptr=fopen("_text_files\\temp.txt","w");
            Book_Record bk;
            while(fread(&bk,sizeof(Book_Record),1,fptr))
            {
                if(!(strcmp(bk.book_name,book_name)==0&&strcmp(bk.book_author,book_author)==0))
                {
                    fwrite(&bk,sizeof(Book_Record),1,tptr);
                }
                else
                {
                    printf("\nRecord with BOOK_NAME[%s] and BOOK_AUTHOR[%s] Deleted\n",bk.book_name,bk.book_author);
                    cou++;
                }
            }
            fclose(fptr);
            fclose(tptr);
            remove(bk_file);
            rename("_text_files\\temp.txt",bk_file);
            if(cou==0)
            {
                printf("\nDon't have Record with BOOK_NAME[%s] and BOOK_AUTHOR[%s]\n",book_name,book_author);
                if(!continue_return())
                {
                    return;
                }
                system("CLS");
                book_list(bk_file,0);
                goto top;
            }
        }
    }
    if(count==0)
    {
        printf("\nPress Enter again...");
        enter_to_move();
        system("CLS");
        printf("\nNOTHING IN BOOK RECORDS TO DELETE\n");
    }
}

void book_update(const char bk_file[])
{
    int count=0,cou=0,cngcou=0;
    char book_name[21],book_author[26];
    if(filecheck(bk_file))
    {
        booknumblocks(bk_file,&count);
        if(count!=0)
        {
            book_list(bk_file,1);
            top:
            title_format("BOOK UPDATE[RECORD]",0);
            printf("\nBOOK_NAME[UPDATE]:");
            fixinput(book_name,sizeof(book_name),0);
            printf("\nBOOK_AUTHOR[UPDATE]:");
            fixinput(book_author,sizeof(book_author),0);
            FILE *fptr=fopen(bk_file,"r+");
            Book_Record bk;
            while(fread(&bk,sizeof(Book_Record),1,fptr))
            {
                if(strcmp(book_name,bk.book_name)==0&&strcmp(book_author,bk.book_author)==0)
                {
                    printf("\nBook's Record with BOOK_NAME[%s] and BOOK_AUTHOR[%s] Available",book_name,book_author);
                    book_update_field(bk.book_name,sizeof(bk.book_name),bk.book_author,sizeof(bk.book_author),&bk.book_num,&cngcou,bk_file);
                    if(cngcou!=0)
                    {
                        fseek(fptr,-sizeof(Book_Record),SEEK_CUR);
                        fwrite(&bk,sizeof(Book_Record),1,fptr);
                        printf("\nUPDATED BOOK RECORD:\n--> BOOK_NAME:%s\n--> Book_Author:%s\n--> BOOK_QTY:%d\n",bk.book_name,bk.book_author,bk.book_num);
                    }
                    cou++;
                    fflush(fptr);
                }
            }
            fclose(fptr);
            if(cou==0)
            {
                printf("\nDon't have Record with BOOK_NAME[%s] and BOOK_AUTHOR[%s]\n",book_name,book_author);
                if(!continue_return())
                {
                    return;
                }
                system("CLS");
                book_list(bk_file,0);
                goto top;
            }
            if(cngcou!=0&&count>=2)
            {
                ascending_book(bk_file);
            }
        }
    }
    if(count==0)
    {
        printf("\nPress Enter again...");
        enter_to_move();
        system("CLS");
        printf("\nNOTHING IN BOOK RECORDS TO UPDATE\n");
    }
}

void book_update_field(char book_name[],int name_size,char book_author[],int author_size,int *book_num,int *change,const char bk_file[])
{
    int temp_bnum=0,ch=0;
    char temp_bname[name_size],temp_bauthor[author_size];
    top:
    title_format("BOOK UPDATE[FIELD]",1);
    printf("\nEnter choice :\n1. BOOK_NAME[%s]\n2. BOOK_AUTHOR[%s]\n3. BOOK_QTY[%d]\n\nYOUR CHOICE:",book_name,book_author,*book_num);
    input_clear(&ch,sizeof(ch));
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
            printf("\nBOOK_NAME[NEW]:");
            fixinput(temp_bname,name_size,0);
            if(!book_duplicate(temp_bname,book_author,bk_file))
            {
                strcpy(book_name,temp_bname);
                (*change)++;
            }
            else
            {
                printf("\nAlready have the record with matching name and author\n");
            }
            break;
        case 2:
            printf("\nBOOK_AUTHOR[NEW]:");
            fixinput(temp_bauthor,author_size,0);
            if(!book_duplicate(book_name,temp_bauthor,bk_file))
            {
                strcpy(book_author,temp_bauthor);
                (*change)++;
            }
            else
            {
                printf("\nAlready have the record with matching name and author\n");
            }
            break;
        case 3:
            printf("\nBOOK_QTY[NEW]:");
            input_clear(&temp_bnum,sizeof(temp_bnum));
            if(scanf("%d",&temp_bnum)==1)
            {
                *book_num=temp_bnum;
                (*change)++;
            }
            else
            {
                printf("\nError You have to input number. Press Enter to continue");
                goto top;
            }
            break;
        default:
            printf("Enter a number from 1 to 3.\n");
            printf("\nPress Enter to go back...");
            goto top;  
    }
}

void book_provide_return(const Record_File rec)
{
    int ch=0;
    printf("\nPress Enter again...");
    while(1)
    {
        title_format("BOOK PROVIDE RETURN",1);
        printf("\nEnter choice :\n1. BOOK PROVIDE\n2. PROVIDE DETAIL\n3. BOOK RETURN\n4. RETURN\n");
        printf("\nYour choice:");
        input_clear(&ch,sizeof(ch));
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                book_provide(rec);
                printf("\nPress Enter to return to book menu...");
                break;
            case 2:
                provide_detail(rec);
                printf("\nPress Enter to return to book menu...");
                break;
            case 3:
                book_return(rec);
                printf("\nPress Enter to return to book menu...");
                break;
            case 4:
                return;
            default:
                printf("Enter a number from 1 to 4.\n");
                printf("\nPress Enter to go back...");           
        }
    }
}

void book_provide(const Record_File rec)
{
    int mem_id=0,count=0,mcou=0,bcou=0;
    char book_name[21],book_author[26],bpath[50]="_text_files\\",mpath[50]="_text_files\\";
    strcat(bpath,rec.bk_file),strcat(mpath,rec.mem_file);
    printf("\nPress Enter again...");
    if(filecheck(bpath)==1&&filecheck(mpath)==1)
    {
        if(fileemptycheck(bpath)==0&&fileemptycheck(mpath)==0)
        {
            count++;
            top:
            enter_to_move();
            mtop:
            system("CLS");
            book_list(bpath,0);
            title_format("BOOK PROVIDE",0);
            printf("MEMBER_ID[PROVIDE]:");
            input_clear(&mem_id,sizeof(mem_id));
            if(scanf("%d",&mem_id)==0)
            {
                printf("\nError You have to input number. Press Enter to continue");
                goto top;
            }
            FILE *mfptr=fopen(mpath,"r+");
            Member_Record mem;
            while(fread(&mem,sizeof(Member_Record),1,mfptr))
            {
                if(mem.mem_id==mem_id)
                {
                    mcou++;
                    if(mem.book_borrow<3)
                    {
                        btop:
                        printf("\nBOOK_NAME[PROVIDE]:");
                        fixinput(book_name,sizeof(book_name),0);
                        printf("\nBOOK_AUTHOR[PROVIDE]:");
                        fixinput(book_author,sizeof(book_author),0);
                        FILE *bfptr=fopen(bpath,"r+");
                        Book_Record bk;
                        while(fread(&bk,sizeof(Book_Record),1,bfptr))
                        {
                            if(strcmp(bk.book_name,book_name)==0&&strcmp(bk.book_author,book_author)==0)
                            {
                                bcou++;
                                if(bk.book_num>0)
                                {
                                    strcpy(mem.pvd[mem.book_borrow].book_name,book_name),strcpy(mem.pvd[mem.book_borrow].book_author,book_author);
                                    mem.book_borrow=mem.book_borrow+1;
                                    fseek(mfptr,-sizeof(Member_Record),SEEK_CUR);
                                    fwrite(&mem,sizeof(Member_Record),1,mfptr);
                                    bk.book_num=bk.book_num-1;
                                    fseek(bfptr,-sizeof(Book_Record),SEEK_CUR);
                                    fwrite(&bk,sizeof(Book_Record),1,bfptr);
                                    printf("\nBOOK[%s(NAME),%s(AUTHOR)] PROVIDED TO MEMBER[%d(ID)]\n",book_name,book_author,mem_id);
                                }
                                else
                                {
                                    printf("\nBOOK'S STOCK WITH BOOK_NAME[%s] AND BOOK_AUTHOR[%s] IS EMPTY\n",book_name,book_author);
                                }
                                fflush(bfptr);
                            }
                        }
                        fclose(bfptr);
                        if(bcou==0)
                        {
                            printf("\nDon't have record with BOOK_NAME[%s] and BOOK_AUTHOR[%s]\n",book_name,book_author);
                            if(continue_return())
                            {
                                system("CLS");
                                book_list(bpath,0);
                                title_format("BOOK PROVIDE",0);
                                printf("MEMBER_ID[PROVIDE]:%d\n",mem_id);
                                goto btop;
                            }
                        }
                    }
                    else
                    {
                        printf("\nMEMBER WITH MEMBER_ID[%d] ALREADY HAS MAX_NUM[3] BOOK PROVIDED\n",mem.mem_id);
                    }
                    fflush(mfptr); 
                }
            }
            fclose(mfptr);
            if(mcou==0)
            {
                printf("\nDon't have record with MEMBER_ID[%d]\n",mem_id);
                if(!continue_return())
                {
                    return;
                }
                goto mtop;
            }
        }
    }
    if(count==0)
    {
        enter_to_move();
        system("CLS");
        printf("\nBOTH BOOK_RECORD AND MEMBER_RECORD SHOULD BE AVAILABLE\n");
    }
}

void provide_detail(const Record_File rec)
{
    char bpath[50]="_text_files\\",mpath[50]="_text_files\\";
    int count=0;
    strcat(bpath,rec.bk_file),strcat(mpath,rec.mem_file);
    printf("\nPress Enter again...");
    if(filecheck(bpath)==1&&filecheck(mpath)==1)
    {
        if(fileemptycheck(bpath)==0&&fileemptycheck(mpath)==0)
        {
            bookprovidecount(mpath,&count);
            if(count!=0)
            {
                title_format("BOOK PROVIDE DETAILS",1);
                Member_Record mem;
                FILE *fptr=fopen(mpath,"r");
                while(fread(&mem,sizeof(Member_Record),1,fptr))
                {
                    if(mem.book_borrow>0)
                    {
                        printf("\n%-12s:%-5d %-20s %-13s:%-5d\n%-12s:%-s\n%-12s:%-lld\n","MEMBER_ID",mem.mem_id," ","BOOK_PVD_QTY",mem.book_borrow,"MEMBER_NAME",mem.mem_name,"MEMBER_PH",mem.mem_phone);
                        printf("-------------------------------------------------------\n");
                        printf("    %-25s %-30s\n","BOOK_NAME","BOOK_AUTHOR");
                        for(int i=0;i<=mem.book_borrow-1;i++)
                        {
                            printf("--> %-25s %-30s\n",mem.pvd[i].book_name,mem.pvd[i].book_author);
                        }
                        printf("-------------------------------------------------------\n\n");
                    }
                }
                fclose(fptr);
            }
        }
    }
    if(count==0)
    {
        enter_to_move();
        system("CLS");
        printf("\nNOTHING IN BOOK PROVIDE DETAIL\n");
    }
}

void bookprovidecount(const char mem_fl[],int *pvdcou)
{
    if(filecheck(mem_fl)==1)
    {
        if(fileemptycheck(mem_fl)==0)
        {
            Member_Record mem;
            FILE *fptr=fopen(mem_fl,"r");
            while(fread(&mem,sizeof(Member_Record),1,fptr))
            {
                if(mem.book_borrow>0)
                {
                    (*pvdcou)=(*pvdcou)+mem.book_borrow;
                }
            }
            fclose(fptr);
        }
    }
}

void book_return(const Record_File rec)
{
    int mem_id=0,count=0,mcou=0,bcou=0,bpcou=0,ind=0;
    char book_name[21],book_author[26],bpath[50]="_text_files\\",mpath[50]="_text_files\\";
    strcat(bpath,rec.bk_file),strcat(mpath,rec.mem_file);
    printf("\nPress Enter again...");
    if(filecheck(mpath)==1)
    {
        if(fileemptycheck(mpath)==0)
        {
            bookprovidecount(mpath,&count);
            if(count!=0)
            {
                top:
                title_format("BOOK RETURN",1);
                mtop:
                printf("MEMBER_ID[RETURN]:");
                input_clear(&mem_id,sizeof(mem_id));
                if(scanf("%d",&mem_id)==0)
                {
                    printf("\nError You have to input number. Press Enter to continue");
                    goto top;
                }
                FILE *mfptr=fopen(mpath,"r+");
                Member_Record mem;
                while(fread(&mem,sizeof(Member_Record),1,mfptr))
                {
                    if(mem.mem_id==mem_id)
                    {
                        mcou++;
                        if(mem.book_borrow>0)
                        {
                            btop:
                            printf("\n%-12s:%-5d %-20s %-13s:%-5d\n%-12s:%-s\n%-12s:%-lld\n","MEMBER_ID",mem.mem_id," ","BOOK_PVD_QTY",mem.book_borrow,"MEMBER_NAME",mem.mem_name,"MEMBER_PH",mem.mem_phone);
                            printf("-------------------------------------------------------\n");
                            printf("    %-25s %-30s\n","BOOK_NAME","BOOK_AUTHOR");
                            for(int i=0;i<=mem.book_borrow-1;i++)
                            {
                                printf("--> %-25s %-30s\n",mem.pvd[i].book_name,mem.pvd[i].book_author);
                            }
                            printf("-------------------------------------------------------\n\n");
                            printf("\nBOOK_NAME[RETURN]:");
                            fixinput(book_name,sizeof(book_name),0);
                            printf("\nBOOK_AUTHOR[RETURN]:");
                            fixinput(book_author,sizeof(book_author),0);
                            for(int i=0;i<=mem.book_borrow-1;i++)
                            {
                                if(strcmp(mem.pvd[i].book_name,book_name)==0&&strcmp(mem.pvd[i].book_author,book_author)==0)
                                {
                                    ind=i;
                                    bpcou++;
                                    break;
                                }
                            }
                            if(bpcou!=0)
                            {
                                for(int i=ind;i<=mem.book_borrow-2;i++)
                                {
                                    strcpy(mem.pvd[i].book_name,mem.pvd[i+1].book_name);
                                    strcpy(mem.pvd[i].book_author,mem.pvd[i+1].book_author);
                                }
                                mem.book_borrow=mem.book_borrow-1;
                                Book_Record bk;
                                if(filecheck(bpath)==1)
                                {
                                    FILE *bfptr=fopen(bpath,"r+");
                                    while(fread(&bk,sizeof(Book_Record),1,bfptr))
                                    {
                                        if(strcmp(book_name,bk.book_name)==0&&strcmp(book_author,bk.book_author)==0)
                                        {
                                            bcou++;
                                            bk.book_num=bk.book_num+1;
                                            fseek(bfptr,-sizeof(Book_Record),SEEK_CUR);
                                            fwrite(&bk,sizeof(Book_Record),1,bfptr);
                                            fflush(bfptr);
                                        }
                                    }
                                    fclose(bfptr);
                                }
                                if(bcou==0)
                                {
                                    FILE *bfptr=fopen(bpath,"a");
                                    strcpy(bk.book_name,book_name),strcpy(bk.book_author,book_author);
                                    bk.book_num=1;
                                    fwrite(&bk,sizeof(Book_Record),1,bfptr);
                                    fclose(bfptr);
                                    ascending_book(bpath);
                                }
                                fseek(mfptr,-sizeof(Member_Record),SEEK_CUR);
                                fwrite(&mem,sizeof(Member_Record),1,mfptr);
                                printf("\nMEMBER[%d(ID)] RETURNED BOOK[%s(NAME),%s(AUTHOR)]\n",mem_id,book_name,book_author);
                            }
                            else if(bpcou==0)
                            {
                                printf("\nBOOK_NAME[%s] AND BOOK_AUTHOR[%s] DON'T MATCH WITH BORROWED BOOK RECORD OF MEM_ID[%d]\n",book_name,book_author,mem_id);
                                if(continue_return())
                                {
                                    system("CLS");
                                    title_format("BOOK RETURN",0);
                                    printf("MEMBER_ID[RETURN]:%d\n",mem_id);
                                    goto btop;
                                }
                            }
                        }
                        else if(mem.book_borrow==0)
                        {
                            printf("\nMEMBER_ID[%d] HAS ZERO NUMBER OF BOOK BORROWED\n",mem_id,book_name,book_author);
                        }
                        fflush(mfptr);
                    }
                }
                fclose(mfptr);
                if(mcou==0)
                {
                    printf("\nMEMBER_ID[%d] RECORD ISN'T IN THE MEMBER LIST\n",mem_id);
                    if(!continue_return())
                    {
                        return;
                    }
                    system("CLS");
                    title_format("BOOK RETURN",0);
                    goto mtop;
                }
            }
        }
    }
    if(count==0)
    {
        enter_to_move();
        system("CLS");
        printf("\nNOTHING IN BOOK BORROWED RECORD TO RETURN\n");
    }
}

void member_section(const char mem_file[])
{
    char fpath[50]="_text_files\\";
    int ch=0;
    strcat(fpath,mem_file);
    printf("\nPress Enter again...");
    while(1)
    {
        title_format("MEMBER MENU",1);
        printf("\nEnter choice :\n1. MEMBER ADD\n2. MEMBER LIST\n3. MEMBER DELETE\n4. MEMBER UPDATE\n5. RETURN\n");
        printf("\nYour choice:");
        input_clear(&ch,sizeof(ch));
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                member_add(fpath);
                printf("\nPress Enter to return to member menu...");
                break;
            case 2:
                member_list(fpath,1);
                printf("\nPress Enter to return to member menu...");
                break;
            case 3:
                member_delete(fpath);
                printf("\nPress Enter to return to member menu...");
                break;
            case 4:
                member_update(fpath);
                printf("\nPress Enter to return to member menu...");
                break;
            case 5:
                return;
            default:
                printf("Enter a number from 1 to 5.\n");
                printf("\nPress Enter to go back...");
        }
    }
}

void member_add(const char mem_file[])
{
    int mem_id=0,book_borrow=0;
    char mem_name[26];
    long long mem_phone=0;
    printf("\nPress Enter again...");
    idtop:
    title_format("MEMBER ADD",1);
    ctop:
    printf("\nMEMBER_ID[ADD]:");
    input_clear(&mem_id,sizeof(mem_id));
    if(scanf("%d",&mem_id)==1)
    {
        if(!memberid_duplicate(mem_id,mem_file))
        {
            printf("\nMEMBER_NAME[ADD]:");
            fixinput(mem_name,sizeof(mem_name),0);
            ptop:
            printf("\nMEMBER_PHONE[ADD]:");
            input_clear(&mem_phone,sizeof(mem_phone));  
            if(scanf("%lld",&mem_phone)==1)
            {
                if(digit_count(&mem_phone,sizeof(mem_phone))==10)
                {
                    if(!memberph_duplicate(mem_phone,mem_file))
                    {
                        book_borrow=0;
                        Member_Record mem;
                        mem.mem_id=mem_id,mem.mem_phone=mem_phone,mem.book_borrow=book_borrow;
                        strcpy(mem.mem_name,mem_name);
                        FILE *fptr=fopen(mem_file,"a");
                        fwrite(&mem,sizeof(Member_Record),1,fptr);
                        fclose(fptr);
                        ascending_member(mem_file);
                        printf("\nMEMBER Record ADDED: MEMBER_ID=%d ,MEMBER_NAME=%s ,MEMBER_PH=%lld\n",mem_id,mem_name,mem.mem_phone);
                    }
                    else
                    {
                        printf("\nAlready have the member of same phone no.\n");
                        if(!continue_return())
                        {
                            return;
                        }
                        system("CLS");
                        title_format("MEMBER ADD",0);
                        goto phtop;
                    }
                }
                else
                {
                    printf("\nError Require 10 digits for phone number. Press Enter to continue");
                    goto dtop;
                }
            }
            else
            {
                printf("\nError You have to input number. Press Enter to continue");
                dtop:
                title_format("MEMBER ADD",1);
                phtop:
                printf("\nMEMBER_ID[ADD]:%d\n",mem_id);
                printf("\nMEMBER_NAME[ADD]:%s\n",mem_name);
                goto ptop;
            }         
        }
        else
        {
            printf("\nAlready have the member of same id\n");
            if(!continue_return())
            {
                return;
            }
            system("CLS");
            title_format("BOOK ADD",0);
            goto ctop;
        }
    }
    else
    {
        printf("\nError You have to input number. Press Enter to continue");
        goto idtop; 
    }
}

int memberid_duplicate(const int mem_id,const char mem_file[])
{
    if(filecheck(mem_file))
    {
        FILE *fptr=fopen(mem_file,"r");
        Member_Record mem;
        while(fread(&mem,sizeof(Member_Record),1,fptr))
        {
            if(mem.mem_id==mem_id)
            {
                fclose(fptr);
                return 1;
            }
        }
        fclose(fptr);
    }
    return 0;
}

int memberph_duplicate(const long long mem_phone,const char mem_file[])
{
    if(filecheck(mem_file))
    {
        FILE *fptr=fopen(mem_file,"r");
        Member_Record mem;
        while(fread(&mem,sizeof(Member_Record),1,fptr))
        {
            if(mem.mem_phone==mem_phone)
            {
                fclose(fptr);
                return 1;
            }
        }
        fclose(fptr);
    }
    return 0;
}

void ascending_member(const char mem_file[])
{
    int count=0; 
    membernumblocks(mem_file,&count);  
    Member_Record mtemp,*mem=(Member_Record *)calloc(count,sizeof(Member_Record));
    memarr_fill(mem,mem_file,count);
    for(int i=0;i<=count-1;i++)
    {
        for(int j=i+1;j<=count-1;j++)
        {
            if(mem[i].mem_id>mem[j].mem_id)
            {
                mtemp=mem[i];
                mem[i]=mem[j];
                mem[j]=mtemp;
            }
        }
    }
    FILE *fptr=fopen(mem_file,"w");
    fwrite(mem,sizeof(Member_Record),count,fptr);
    fclose(fptr);    
    free(mem);
}

void membernumblocks(const char mem_file[],int *count)
{
    Member_Record mem;
    FILE *fptr=fopen(mem_file,"r");
    *count=0;
    while(fread(&mem,sizeof(Member_Record),1,fptr))
    {
        (*count)++;
    }
    fclose(fptr);
}

void memarr_fill(Member_Record *mem,const char mem_file[],int count)
{
    FILE *fptr=fopen(mem_file,"r");
    fread(mem,sizeof(Member_Record),count,fptr);
    fclose(fptr);    
}

void member_list(const char mem_file[],int num)
{
    int i=0,count=0;
    if(filecheck(mem_file))
    {
        membernumblocks(mem_file,&count);
        if(count!=0)
        {
            if(num==0)
            {
                title_format("MEMBER RECORDS",0);
            }
            else
            {
                printf("\nPress Enter again...");
                title_format("MEMBER RECORDS",1);
            }
            FILE *fptr=fopen(mem_file,"r");
            Member_Record mem;
            printf("\n");
            printf("---------------------------------------------------------------------\n");
            printf("%-5s %-8s %-25s %-15s %-5s\n","S.N.", "ID", "NAME", "PHONE", "BOOK_BORROW");
            printf("---------------------------------------------------------------------\n");
            while(fread(&mem,sizeof(Member_Record),1,fptr))
            {
                printf("%-5d %-8d %-25s %-15lld %-5d\n",++i,mem.mem_id,mem.mem_name,mem.mem_phone,mem.book_borrow);
            }
            printf("---------------------------------------------------------------------\n");
            fclose(fptr);
        }
    }
    if(count==0)
    {
        printf("\nPress Enter again...");
        enter_to_move();
        system("CLS");
        printf("\nNOTHING IN MEMBER RECORDS\n");
    }
}

void member_delete(const char mem_file[])
{
    int mem_id=0,count=0,cou=0;
    if(filecheck(mem_file))
    {
        membernumblocks(mem_file,&count);
        if(count!=0)
        {
            member_list(mem_file,1);
            ctop:
            title_format("MEMBER DELETE",0);
            printf("\nMEMBER_ID[DELETE]:");
            input_clear(&mem_id,sizeof(mem_id));
            if(scanf("%d",&mem_id)==1)
            {
                FILE *fptr=fopen(mem_file,"r");
                FILE *tptr=fopen("_text_files\\temp.txt","w");
                Member_Record mem;
                while(fread(&mem,sizeof(Member_Record),1,fptr))
                {
                    if(mem.mem_id!=mem_id)
                    {
                        fwrite(&mem,sizeof(Member_Record),1,tptr);
                    }
                    else
                    {
                        printf("\nRecord with MEMBER_ID[%d] Deleted\n",mem.mem_id);
                        cou++;
                    }
                }
                fclose(fptr);
                fclose(tptr);
                remove(mem_file);
                rename("_text_files\\temp.txt",mem_file);
                if(cou==0)
                {
                    printf("\nDon't have record with MEMBER_ID[%d]\n",mem_id);
                    if(!continue_return())
                    {
                        return;
                    }
                    top:
                    system("CLS");
                    member_list(mem_file,0);
                    goto ctop;
                }
            }
            else
            {
                printf("\nError You have to input number. Press Enter to continue");
                enter_to_move();
                goto top;
            }
        }
    }
    if(count==0)
    {
        printf("\nPress Enter again...");
        enter_to_move();
        system("CLS");
        printf("\nNOTHING IN MEMBER RECORDS TO DELETE\n");
    }
}

void member_update(const char mem_file[])
{
    int count=0,cou=0,mem_id=0,cngcou=0;
    if(filecheck(mem_file))
    {
        membernumblocks(mem_file,&count);
        if(count!=0)
        {
            member_list(mem_file,1);
            top:
            title_format("MEMBER UPDATE[RECORD]",0);
            printf("\nMEMBER_ID[UPDATE]:");
            input_clear(&mem_id,sizeof(mem_id));
            if(scanf("%d",&mem_id)==1)
            {
                FILE *fptr=fopen(mem_file,"r+");
                Member_Record mem;
                while(fread(&mem,sizeof(Member_Record),1,fptr))
                {
                    if(mem_id==mem.mem_id)
                    {
                        printf("\nMember's Record with MEMBER_ID[%d] Available",mem_id);
                        member_update_field(&mem.mem_id,mem.mem_name,sizeof(mem.mem_name),&mem.mem_phone,&cngcou,mem_file);
                        if(cngcou!=0)
                        {
                            fseek(fptr,-sizeof(Member_Record),SEEK_CUR);
                            fwrite(&mem,sizeof(Member_Record),1,fptr);
                            printf("\nUPDATED MEMBER RECORD:\n--> MEMBER_ID:%d\n--> MEMBER_NAME:%s\n--> MEMBER_PHONE:%lld\n",mem.mem_id,mem.mem_name,mem.mem_phone);
                        }
                        cou++;
                        fflush(fptr);
                    }
                }
                fclose(fptr);
            }
            else
            {
                printf("\nError You have to input number. Press Enter to continue");
                enter_to_move();
                system("CLS");
                member_list(mem_file,0);
                goto top;
            }
            if(cou==0)
            {
                printf("\nDon't have record with MEMBER_ID[%d]\n",mem_id);
                if(!continue_return())
                {
                    return;
                }
                system("CLS");
                member_list(mem_file,0);
                goto top;
            }
            if(cngcou!=0&&count>=2)
            {
                ascending_member(mem_file);
            }
        }
    }
    if(count==0)
    {
        printf("\nPress Enter again...");
        enter_to_move();
        system("CLS");
        printf("\nNOTHING IN MEMBER RECORDS TO UPDATE\n");
    }
}

void member_update_field(int *mem_id,char mem_name[],int name_size,long long *mem_phone,int *change,const char mem_file[])
{
    int temp_mid=0,ch=0;
    long long temp_mph=0;
    top:
    title_format("MEMBER UPDATE[FIELD]",1);
    printf("\nEnter choice :\n1. MEMBER_ID[%d]\n2. MEMBER_NAME[%s]\n3. MEMBER_PHONE[%lld]\n\nYOUR CHOICE:",*mem_id,mem_name,*mem_phone);
    input_clear(&ch,sizeof(ch));
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
            printf("\nMEMBER_ID[NEW]:");
            input_clear(&temp_mid,sizeof(temp_mid));
            if(scanf("%d",&temp_mid)==1)
            {
                if(!memberid_duplicate(temp_mid,mem_file))
                {
                    *mem_id=temp_mid;
                    (*change)++;
                }
                else
                {
                    printf("\nAlready have the record with same Id\n");
                }
            }
            else
            {
                printf("\nError You have to input number. Press Enter to continue");
                goto top;
            }
            break;
        case 2:
            printf("\nMEMBER_NAME[NEW]:");
            fixinput(mem_name,name_size,0);
            (*change)++;
            break;
        case 3:
            printf("\nMEMBER_PHONE[NEW]:");
            input_clear(&temp_mph,sizeof(temp_mph));
            if(scanf("%lld",&temp_mph)==1)
            {
                if(digit_count(&temp_mph,sizeof(temp_mph))==10)
                {
                    if(!memberph_duplicate(temp_mph,mem_file))
                    {
                        *mem_phone=temp_mph;
                        (*change)++;
                    }
                    else
                    {
                        printf("\nAlready have the record with same Phone no.\n");
                    }
                }
                else
                {
                    printf("\nError Require 10 digits for phone number. Press Enter to continue");
                    goto top;
                }
            }
            else
            {
                printf("\nError You have to input number. Press Enter to continue");
                goto top;   
            }
            break;
        default:
            printf("Enter a number from 1 to 3.\n");
            printf("\nPress Enter to go back...");
            goto top;  
    }
}

