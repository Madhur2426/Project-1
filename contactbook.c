#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
void inputdetails(void);
void menu(void);
void getoption(void);
void displaycontactinfo(void);
void searchcontact(void);
void deletecontact(void);
void checkupdate(void);
void pass(void);
int check=0,u=0,l=0;
char password[30];
struct phonebook
{
    char name[30];
    char number[15];
}phone;
void main()
{
COORD d;
d.X=20;
d.Y=0;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),d);
printf("*******WELCOME TO PHONEBOOK*********\n");
menu();
getoption();
}
void menu()
{
    printf("\n");
    printf("1.SAVE CONTACT\n");
    printf("2.SEE YOUR SAVED CONTACTS\n");
    printf("3.SEARCH A CONTACT\n");
    printf("4.DELETE A CONTACT \n");
    printf("5.TO CHECK FOR UPDATES\n");
    printf("6.EXIT\n");
}
void getoption()
{
    while(1)
         {
             switch(getch())
    {
        case '1':inputdetails();
              break;
        case '2':if(check==0)
            {
                displaycontactinfo();
              break;
            }
            else
                pass();
        case '3':searchcontact();
               break;
        case '4':deletecontact();
              break;
        case '5':checkupdate();
              break;
        case '6':printf("THANKS FOR USING PHONEBOOK\n");
            exit(0);
              break;
        default:printf("\nINCORRECT CHOICE ENTER CHOICE AGAIN\n");
    }
    menu();
}
exit(0);
}
void inputdetails()
{
    printf("\n");
    FILE *fp;
    fp=fopen("contact.dat","ab+");
    if(fp==NULL)
 {

    printf("CANNOT OPEN FILE");
    exit(0);
 }
    printf("ENTER NAME\n");
    fflush(stdin);
    gets(phone.name);
    printf("ENTER NUMBER\n");
    scanf("%s",phone.number);
    fwrite(&phone,sizeof(phone),1,fp);
    printf("\nCONTACT SUCCESSFULLY SAVED\n");
    fclose(fp);
}
void displaycontactinfo()
{
    FILE *fp;
    fp=fopen("contact.dat","r");
    if(fp==NULL)
    {
        printf("CANNOT OPEN FILE\n");
        exit(0);
    }
    else
    {
         printf("\n--------YOUR CONTACT LIST-----------\n");
        while(fread(&phone,sizeof(phone),1,fp)==1)
    {
        printf("NAME-------%s\nNUMBER------%s\n",phone.name,phone.number);
    }
    fclose(fp);
}
}
void searchcontact()
{
    printf("\n");
    char searchname[20];
    int flag=0;
    FILE *fp;
    fp=fopen("contact.dat","rb");
    if(fp==NULL)
    {
        printf("CANNOT OPEN FILE\n");
        exit(0);
    }
    else
    {
        fflush(stdin);
        printf("ENTER A NAME TO SEARCH\n");
        gets(searchname);
        printf("\n");
        while(fread(&phone,sizeof(phone),1,fp)==1)
        {
            if(strcmp(phone.name,searchname)==0)
            {
                printf("CONTACT FOUND\n");
                printf("NAME-----%s\nNUMBER----%s\n",phone.name,phone.number);
                flag=1;
            }
        }
        if(flag==0)
        printf("CONTACT NOT FOUND\n");
    }
}
void deletecontact()
{
    int counter=0;
    printf("\n\nENTER A NAME TO DELETE\n");
    FILE *fp;
    FILE *ff;
    char search[20];
    int flag=0;
    fp=fopen("contact.dat","rb");
    ff=fopen("contacts.dat","w");
    if(fp==NULL)
    {
        printf("\nCANNOT OPEN FILE\n");
        exit(0);
    }
    if(ff==NULL)
    {
        printf("\nCANNOT DELETE FILE\n");
        exit(0);
    }
        fflush(stdin);
        gets(search);
     while(fread(&phone,sizeof(phone),1,fp)==1)
     {
         if(strcmp(phone.name,search)!=0)
             fwrite(&phone,sizeof(phone),1,ff);
             if(strcmp(phone.name,search)==0)
                flag=1;
     }
     fclose(ff);
     fclose(fp);
     if(flag!=1)
      {
          printf("\nCONTACT NOT FOUND\n");
          remove("contacts.dat");
      }
         else
     {
         remove("contact.dat");
         rename("contacts.dat","contact.dat");
         printf("\nCONTACT SUCCESSFULLY DELETED\n");
}
}
void checkupdate()
{
    int q,r,h;
    if(u==0)
    {
    printf("\n\n");
    printf("UPDATE FOUND\n");
    printf("ENTER 8 TO UPDATE\n");
    scanf("%d",&h);
    if(h==8)
    {
        u=1;
        check=1;
    printf("DOWNLOADING UPDATE PLEASE WAIT\n");
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    printf("\nINSTALLING UPDATE PLEASE WAIT\n");
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    printf("\nUPDATE SUCCESSFULLY INSTALLED NOW YOU CAN SETUP A PASSWORD TO SEE YOUR SAVED CONTATS\n");
    printf("ENTER PASSWORD\n");
    pass();
    ++u;
}
}
else
{
    printf("NO UPDATE AVAILABLE\n");
}
}
void pass()
{
    int k=2,i;
    char inputpassword[30];
    if(l==0)
    {
    fflush(stdin);
    gets(password);
    l=1;
    }
    printf("\nENTER YOUR PASSWORD TO SEE YOUR SAVED CONTACTS\n");
    fflush(stdin);
    gets(inputpassword);
    for(i=-1;i<k;i++)
    {
    if(strcmp(inputpassword,password)==0)
    {
        displaycontactinfo();
        break;
    }
    else
    {
     k=k-1;
     printf("YOU HAVE %d CHANCES LEFT\n",k);
     printf("ENTER YOUR PASSWORD AGAIN\n");
     fflush(stdin);
     gets(inputpassword);
     if(k==0)
     {
       printf("YOU HAVE TRIED TOO MANY ATTEMPTS\n");
       printf("THANKS FOR USING PHONEBOOK\n");
       exit(0);
     }
    }
    }
}
