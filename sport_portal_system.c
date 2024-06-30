#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sport
{
    int age;
    char contact[20];
    char Name[50];
    char dob[20];
    char user_id[100];
    char reg_date[20];
    char sport[50];
} sport;

typedef struct node
{
    sport spt;
    struct node *next;
} node;
typedef struct trans
{
    char user_id[100];
    char sport_category[50];
    char date[50];
}trans;

typedef struct nnode
{
    trans tra;
    struct nnode *next;
} nnode;



node *head = NULL;
nnode *head1=NULL;

void save_file();
void print_list();
void append(int age, char *cont, char *name, char *dob, char *uid, char *sport);
void update(char *uid);
void save_file();
void get_file();
void clear_mainfile();
void clear_mainll();
void clear_trancll();
void clear_transacfile();
void display_profile();
void remove_user(char *uid);
void display_transaction(char *uid);


void clear_mainll()
{
    while(head!=NULL)
    {
        node*temp=head;
        head=head->next;
        free(temp);
    }
}
void clear_mainfile()
{
    FILE *ptr;
    ptr=fopen("sport.txt","w");
    fclose(ptr);
}

void clear_trancll()
{
    while(head1!=NULL)
    {
        nnode*temp=head1;
        head1=head1->next;
        free(temp);
    }
}

void clear_transacfile()
{
    FILE *ptr;
    ptr=fopen("transaction.txt","w");
    fclose(ptr);
}

void print_list()
{
    clear_mainll();
    get_file();
    node *current = head;

    while (current != NULL)
    {
        printf("Name: %s\n", current->spt.Name);
        printf("Contact: %s\n", current->spt.contact);
        printf("Date of Birth: %s\n", current->spt.dob);
        printf("User ID: %s\n", current->spt.user_id);
        printf("Sport: %s\n", current->spt.sport);
        printf("Age: %d\n", current->spt.age);

        current = current->next;
        printf("\n\n\n");   
    }
}
void transaction_append(char *uid, char *date, char *sport)
{
    nnode *ptr = (nnode *)malloc(sizeof(nnode));
    strcpy(ptr->tra.date, date);
    strcpy(ptr->tra.sport_category, sport);
    strcpy(ptr->tra.user_id, uid);
    ptr->next = NULL;

    nnode *temp = head1;

    if (head1 == NULL)
    {
        head1 = ptr;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = ptr;
    }

    FILE *file_ptr;
    file_ptr = fopen("transaction.txt", "a");

    if (file_ptr == NULL)
    {
        printf("Error in opening the file\n");
        return;
    }

    fprintf(file_ptr, "%s,", ptr->tra.user_id);
    fprintf(file_ptr, "%s,", ptr->tra.sport_category);
    fprintf(file_ptr, "%s\n", ptr->tra.date);
    fclose(file_ptr);
}

void display_transaction(char *uid)
{
    FILE *ptr;
    ptr = fopen("transaction.txt", "r");

    if (ptr == NULL)
    {
        printf("Error in opening the file\n");
        return;
    }

    trans tr;

    while (fscanf(ptr, "%[^,],%[^,],%[^\n]\n", tr.user_id, tr.sport_category, tr.date) == 3)
    {
        if (strcmp(tr.user_id, uid) == 0)
        {
            printf("USER-ID %s\n", tr.user_id);
            printf("SPORT %s\n", tr.sport_category);
            printf("DATE %s\n", tr.date);
        }
    }

    fclose(ptr);
}




void append(int age, char *cont, char *name, char *dob, char *uid, char *sport)
{
    node *temp = (node *)malloc(sizeof(node));
    strcpy(temp->spt.Name, name);
    strcpy(temp->spt.contact, cont);
    strcpy(temp->spt.dob, dob);
    strcpy(temp->spt.user_id, uid);
    strcpy(temp->spt.sport, sport);
    temp->spt.age = age;
    temp->next = NULL;

    node *ptr = head;

    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    // save_file();
}

void update(char *uid)
{
    clear_mainll();
    get_file();
    int ch;
    char cont[20];
    char s[50];
    printf("1. Update Phone Number \n");
    printf("2. Update Sport Preference\n");
    printf("Select what you want to update: ");
    scanf("%d", &ch);
    
    node *temp = head;
    int found = 0;

    while (temp != NULL)
    {
        if (strcmp(temp->spt.user_id, uid) == 0)
        {
            found = 1;
            break;
        }
        temp = temp->next;
    }   

    if (!found)
    {
        printf("User ID not found\n");
        return;
    }

    switch (ch)
    {
    case 1:
        printf("Enter new phone number: ");
        scanf("%s", cont);
        strcpy(temp->spt.contact, cont);
        break;
    case 2:
        printf("Enter new sport preference: ");
        scanf("%s", s);
        strcpy(temp->spt.sport, s);
        break;
    default:
        printf("Invalid option\n");
        break;
    }
    clear_mainfile();
}


void display_profile()
{
    clear_mainll();
    get_file();

    int ch;
    char uname[50];
    char uid[20];
    int found=0;
    
    
    node* temp=head;

    printf("   VIEW PROFILE  \n");
    printf("  1.Enter Username  \n");
    printf("  2.Enter user id  \n");
    printf("Through what would you want to view profile\n");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
            printf("Enter Username\n");
            scanf("%s",uname);


            while (temp != NULL)
            {
                if (strcmp(temp->spt.Name, uname) == 0)
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }   

            if (!found)
            {
                printf("User ID not found\n");
                return;
            }

            printf("USER-ID %s\n",temp->spt.user_id);
            printf("NAME %s\n",temp->spt.Name);
            printf("CONTACT %s\n",temp->spt.contact);
            printf("DATE-OF-BIRTH %s\n",temp->spt.dob);
            printf("AGE %d\n",temp->spt.age);
            printf("SPORT %s\n",temp->spt.sport);

            break;


            case 2:
            printf("Enter User ID\n");
            scanf("%s",uid);

            while (temp != NULL)
            {
                if (strcmp(temp->spt.user_id, uid) == 0)
                {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }   

            if (!found)
            {
                printf("User ID not found\n");
                return;
            }

            printf("USER-ID %s\n",temp->spt.user_id);
            printf("NAME %s\n",temp->spt.Name);
            printf("CONTACT %s\n",temp->spt.contact);
            printf("DATE-OF-BIRTH %s\n",temp->spt.dob);
            printf("AGE %d\n",temp->spt.age);
            printf("SPORT %s\n",temp->spt.sport);

            break;

            default:
            printf("Enter valid option\n");  
            break;


    }
}

void remove_user(char *uid)
{
    clear_mainll();
    get_file();
    node *temp = head;
    node *prev = NULL; 
    int found = 0;
    while (temp != NULL)
    {
        if (strcmp(temp->spt.user_id, uid) == 0)
        {
            found = 1;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (!found)
    {
        printf("User ID not found\n");
        return;
    }

    if (prev != NULL)
    {
        
        prev->next = temp->next;
    }
    else
    {
        
        head = temp->next;
    }

    free(temp);
    clear_mainfile();
}


void save_file()
{
    FILE *ptr;
    ptr = fopen("sport.txt", "a");

    if (ptr == NULL)
    {
        printf("Error in opening the file\n");
        return;
    }

    node *current = head;

    while (current != NULL)
    {
        fprintf(ptr, "%s,", current->spt.Name);
        fprintf(ptr, "%s,", current->spt.contact);
        fprintf(ptr, "%s,", current->spt.dob);
        fprintf(ptr, "%s,", current->spt.user_id);
        fprintf(ptr, "%s,", current->spt.sport);
        fprintf(ptr, "%d\n", current->spt.age);
        current = current->next;
    }

    fclose(ptr);
    clear_mainll();
}



void get_file()
{
    FILE *ptr;
    ptr = fopen("sport.txt", "r");

    if (ptr == NULL)
    {
        printf("Error in opening the file\n");
        return;
    }

    while (head != NULL)
    {
        node *temp = head;
        head = head->next;
        free(temp);
    }

    node *curr = head;

    while (!feof(ptr))
    {
        sport sp;
        fscanf(ptr, "%[^,],", sp.Name);
        fscanf(ptr, "%[^,],", sp.contact);
        fscanf(ptr, "%[^,],", sp.dob);
        fscanf(ptr, "%[^,],", sp.user_id);
        fscanf(ptr, "%[^,],", sp.sport);
        fscanf(ptr, "%d\n", &sp.age);
        append(sp.age, sp.contact, sp.Name, sp.dob, sp.user_id, sp.sport);
        
    }
    //
    // printf("Appending\n");
    // print_list();
    //
    fclose(ptr);
}

int main()
{
    int age;
    char contact[20];
    char Name[50];
    char dob[20];
    char user_id[100];
    char sport[50];
    char sport_category[50];
    char date[15];

    int ch;
    while (1)
    {
        printf("------------------------------------------------------------------------------------------------------------------------------------------");   
        printf("                                                                  MENU                                                                   \n");
        printf("                                                       1     CREATE PROFILE                                                              \n");
        printf("                                                       2      SAVE PROFILE                                                               \n");
        printf("                                                       3     UPDATE PROFILE                                                              \n");
        printf("                                                       4      VIEW PROFILE                                                               \n");
        printf("                                                       5     REMOVE PROFILE                                                              \n");
        printf("                                                       6     EVENT REGISTRATION                                                          \n");
        printf("                                                       7  DISPLAY EVENT TRANSACTIONS                                                      \n");
        printf("                                                       8  VIEW SPORT PORTAL DIRECTORY                                                     \n");
        printf("                                                 PRESS ANY KEY APART FROM THE OPTION TO EXIT                                              \n");

        printf("Select your option \n");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter your Name \n");
            scanf("%s", Name);

            printf("Enter your contact \n");
            scanf("%s", contact);

            printf("Enter your date of birth \n");
            scanf("%s", dob);

            printf("Enter your user id\n");
            scanf("%s", user_id);

            printf("Enter your Sport \n");
            scanf("%s", sport);

            printf("Enter your age \n");
            scanf("%d", &age);

            append(age, contact, Name, dob, user_id, sport);

            break;
        case 2:
            save_file();
            break;
        case 3:
            printf("Enter userid for updation:\t");
            scanf("%s",user_id);
            update(user_id);
            break;

        case 4:
            display_profile();
            break;
        
        case 5:
            printf("Enter user id to delete\n");
            scanf("%s",user_id);
            remove_user(user_id);
            break;

        case 6:
            printf("Enter your User ID\n");
            scanf("%s",user_id);

            printf("Enter your event sports\n");
            scanf("%s",sport);

            printf("Enter date \n");
            scanf("%s",date);

            transaction_append(user_id,date,sport);
            break;

        case 7:
            printf("Enter user_id\n");
            scanf("%s",user_id);
            display_transaction(user_id);
            break;

        case 8:
            print_list();
            break;

        default:
            exit(1);
        }
    }

    return 0;
}
