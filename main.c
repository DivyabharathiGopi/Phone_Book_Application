#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

//STRUCTURE DS CREATED
struct person
{
    char name[20];
    char address[50];
    char fatherName[20];
    char motherName[20];
    char gender[10];
    char mailId[25];
    char citisionNo[20];
    long int mobileNo;
};

//FUNCTION PROTOTYPE DECLARATION
void back();
void start();
void menu();
void got(char*);
void addNewContact();
void showContacts();
void modifyContacts();
void searchContacts();
void deleteContacts();

//MAIN FUNCTION
int main()
{
    //system("color 5f"); //CAN CHANGE THE BACKGROUND COLOR OF THE OUTPUT CONSOLE
    start();
    return 0;
}

//BACK TO MENU
void back()
{
    start();
}

//MENU
void start()
{
    menu();
}

//MENU FUNCTION DEFINITION
void menu()
{
    //int N;
    system("cls");
    printf("\033[1;37m");
    printf("\n**********PHONEBOOL APPLICATION**********\n");
    printf("\n MENU \n");
    printf("\n 1.Add New Contact \n 2.Show Contacts \n 3.Modify Contacts \n 4.Search Contacts \n 5.Delete Contacts \n 6.Exit");
    printf("\n\n");
    //scanf("%d",&N);
    switch(getch())
    {
        case '1':
            addNewContact();
            break;
        case '2':
            showContacts();
            break;
        case '3':
            modifyContacts();
            break;
        case '4':
            searchContacts();
            break;
        case '5':
            deleteContacts();
            break;
        case '6':
            exit(0);
            break;
        default:
            system("cls");
            printf("\nEnter 1 to 6 only!");
            printf("Enter any key");
            getch();
            menu();
    }
}

// ADDING NEW CONTACT
void addNewContact()
{
    system("cls");
    FILE *f;
    struct person p;
    f=fopen("project","ab+"); //OPEN FILE IF DOESN'T EXIST WILL CREATE NEW ONE (BINARY TYPE FILE)
    printf("\nEnter Name: ");
    got(p.name);
    printf("\nEnter Address: ");
    got(p.address);
    printf("\nEnter Father Name: ");
    got(p.fatherName);
    printf("\nEnter Mother Name: ");
    got(p.motherName);
    printf("\nEnter Mobile No: ");
    scanf("%ld",&p.mobileNo);
    printf("\nEnter Gender: ");
    got(p.gender);
    printf("\nEnter Mail ID: ");
    got(p.mailId);
    printf("\nEnter Citision No: ");
    got(p.citisionNo);
    fwrite(&p,sizeof(p),1,f); //WRITING DATA INTO THAT CREATED FILE
    fclose(f); //CLOSING FILE
    printf("\n\nContact Saved");
    printf("\nEnter any key!");
    getch();
    system("cls");
    menu();
}

//SHOW CONTACTS
void showContacts()
{
    system("cls");
    FILE *f;
    struct person p;
    f=fopen("project","rb"); //OPEN FILE IN READING MODE
    if(f==NULL)
    {
        printf("\n\nError in file opening!");
        getch();
        back();
    }
    printf("\n\nContact List\n\n");
    while(fread(&p,sizeof(p),1,f)==1)
    {
        //printf("\n\nContact List\n\n");
        printf("\nName:%s \nMobile No:%ld \nAddress:%s \nGender:%s \nMail Id:%s \nFather Name:%s \nMother Name:%s \nCitision No:%s\n\n",
               p.name,p.mobileNo,p.address,p.gender,p.mailId,p.fatherName,p.motherName,p.citisionNo);
    }
    fclose(f);
    printf("\nEnter any key!");
    getch();
    system("cls");
    menu();
}

//MODIFY CONTACTS
void modifyContacts()
{
    struct person p,s;
    char name[50];
    int flag=0;
    FILE *f;
    f=fopen("project","rb");
    if(f==NULL)
    {
        printf("\n\nCONTACTS NOT YET ADDED!\n\n");
        exit(1);
    }
    else
    {
        system("cls");
        printf("\n\nEnter Contact's name to modify\n\n");
        got(name);
        while(fread(&p,sizeof(p),1,f)==1)
        {
            if(strcmp(name,p.name)==0)
            {
                printf("\nEnter Name: ");
                got(s.name);
                printf("\nEnter Address: ");
                got(s.address);
                printf("\nEnter Father Name: ");
                got(s.fatherName);
                printf("\nEnter Mother Name: ");
                got(s.motherName);
                printf("\nEnter Mobile No: ");
                scanf("%ld",&p.mobileNo);
                printf("\nEnter Gender: ");
                got(s.gender);
                printf("\nEnter Mail ID: ");
                got(s.mailId);
                printf("\nEnter Citision No: ");
                got(s.citisionNo);
                fseek(f,-sizeof(p),SEEK_CUR);
                fwrite(&s,sizeof(s),1,f);
                flag=1;
                break;
            }
            fflush(stdin);
        }
        if(flag==1)
            printf("\n\nContact Successfully Modified!\n\n");
        else
            printf("\n\nContact Not Found\n\n");
    }
    fclose(f);
    printf("\nEnter any key!");
    getch();
    system("cls");
    menu();
}

//SEARCH CONTACTS
void searchContacts()
{
    system("cls");
    char name[50];
    struct person p;
    FILE *f;
    f=fopen("project","rb");
    if(f==NULL)
    {
        printf("\nError in opening!\n");
        exit(1);
    }
    else
    {
        printf("\nEnter name to search!\n");
        got(name);
        while(fread(&p,sizeof(p),1,f)==1)
        {
            if(strcmp(p.name,name)==0)
            {
                printf("\nName:%s \nMobile No:%ld \nAddress:%s \nGender:%s \nMail Id:%s \nFather Name:%s \nMother Name:%s \nCitision No:%s\n\n",
                p.name,p.mobileNo,p.address,p.gender,p.mailId,p.fatherName,p.motherName,p.citisionNo);
            }
            //else
                //printf("\nContact mot found!\n");
        }
    }
    fclose(f);
    printf("\nEnter any key!");
    getch();
    system("cls");
    menu();
}

//DELETE CONATCTS
void deleteContacts()
{
    struct person p;
    char name[50];
    int flag;
    FILE *f,*ft;
    f=fopen("project","rb");
    if(f==NULL)
    {
        printf("\nError in opening!");
    }
    else
    {
        ft=fopen("temp","wb+");
        if(ft==NULL)
        {
            printf("\nContacts not yet added!");
        }
        else
        {
            printf("\nEnter Contact Name to Delete!\n");
            got(name);
            fflush(stdin);
            while(fread(&p,sizeof(p),1,f==1))
            {
                if(strcmp(p.name,name)!=0)
                    fwrite(&p,sizeof(p),1,ft);
                if(strcmp(p.name,name)==0)
                    flag=1;
            }
        }
        if(flag!=0)
        {
            printf("\nNo Contact Record to Delete!");
            remove("temp.txt");
        }
        else
        {
            remove("project");
            rename("temp.txt","project");
            printf("\nContact Record Successfully Deleted!");
        }

    }
    fclose(f);
    printf("\nEnter any key!");
    getch();
    system("cls");
    menu();
}

//INPUT GET FUNCTION
void got(char *name)
{
    int i=0,j;
    char c,ch;
    do
    {
        c=getch();
        if(c!=8 && c!=13)
        {
            *(name+i)=c;
            putch(c);
            i++;
        }
        if(c==8)
        {
            if(i>0)
            {
                i--;
            }
            system("cls");
            for(j=0;j<1;j++)
            {
                ch=*(name+j);
                putch(ch);
            }
        }
    }while(c!=13);
    *(name+i)='\0';
}
