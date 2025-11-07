/* Name : Shobharaj H L
   Date : 13/10/2025
   Description : Address Book */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h> 

//***************************** VALIDATION PART *****************************************************************

// VALIDATING THE PHONE NUMBER
int validate_phone(AddressBook *addressBook, char phone[]) {
    for (int i = 0; phone[i]; i++) {
        if (phone[i] < '0' || phone[i] > '9') { // check non-digit
            printf("Enter Only The Digits \n");
            return 0;
        }
    }
    int len = strlen(phone);
    if (len != 10) { // check length
        printf("Phone Number should Contain 10 Digits Only\n"); 
        return 0;
    }
    for (int i = 0; i < addressBook->contactCount; i++) { // check duplicates
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
            printf("Phone number already exists❗\n");
            return 0; 
        }
    }
    return 1;
}

// VALIDATING THE EMAIL ID
int validate_Email(AddressBook *addressBook, char email[]) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) { // check duplicate email
            printf("Email already exists❗\n");
            return 0; 
        }
    }
    for (int i = 0; email[i]; i++) {
        if (email[i] == ' ') { // check spaces
            printf("Email contain space\n");
            return 0;
        }
        if (email[i] >= 'A' && email[i] <= 'Z') { // check uppercase
            printf("Email should have lowercase characters \n");
            return 0;
        }
    }
    int len = strlen(email);
    char *ret;
    ret = strchr(email, '@'); // check '@'
    if (ret == NULL) {
        printf(" Invalid Email ID Plese Re-enter\n"); 
        return 0;
    }
    if (!(isalnum(*(ret + 1)))) { // check char after '@'
        printf(" Invalid Email ID Plese Re-enter\n");
        return 0;
    }
    if (email[0] == '@') { // check starts with '@'
        printf(" Invalid Email ID Plese Re-enter\n");
        return 0;
    }
    char *result = strstr(email, ".com"); // check .com
    if (result != NULL) {
        if ((strlen(result)) != 4) { // check valid .com
            printf(" Invalid Email Id Plese Re-enter\n");
            return 0;
        } else {
            return 1;
        }   
    } else {
        printf(" Invalid Email ID Plese Re-enter\n");
        return 0;
    }
}

//****************************************************************************** SEARCHING PART **********************************************************************************

// SEARCHING CONTACT BY NAME 
int searchContactbyname(AddressBook *addressBook, char *Searchname) {
    int i, flag = 0;
    printf("\nContact Found \n---------------------------------------------------------------------------\n");
    printf("%-13s %-17s %-17s %-17s","Sl No","NAME","Phone Number","E-mail");
    printf("\n---------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) { // print all
        if (strcmp(addressBook->contacts[i].name, Searchname) == 0) { // name match
            printf("%-13d %-17s %-17s %-17s\n",++flag, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("---------------------------------------------------------------------------\n");
        }
    }
    if (!flag) { // not found
        printf("\t\t\t%s name is not found \n", Searchname);
        printf("---------------------------------------------------------------------------\n\n");
    }
}

// SEARCHING CONTACT BY PHONE NUMBER
int searchContactbyphone(AddressBook *addressBook, char *Searchphone) {
    int i, flag = 0;
    printf("\nContact Found \n---------------------------------------------------------------------------\n");
    printf("%-13s %-17s %-17s %-17s","Sl No","NAME","Phone Number","E-mail");
    printf("\n---------------------------------------------------------------------------\n");
    for (i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, Searchphone) == 0) { // phone match
            printf("%-13d %-17s %-17s %-17s\n", ++flag, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("---------------------------------------------------------------------------\n\n");
            return i;
        }
   
    }
    if (!flag) { // not found
        printf("\t\t%s phone number is not found \n", Searchphone);
        printf("---------------------------------------------------------------------------\n\n");
        return -1;
    }
}

// SEARCHING CONTACT BY EMAIL
int searchContactbyemail(AddressBook *addressBook, char *Searchemail) {
    int i, flag = 0;
    printf("\nContact Found \n---------------------------------------------------------------------------\n");
    printf("%-13s %-17s %-17s %-17s","Sl No","NAME","Phone Number","E-mail");
    printf("\n---------------------------------------------------------------------------\n");
    for (i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, Searchemail) == 0) { // email match
            printf("%-13d %-17s %-17s %-17s\n", ++flag, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("---------------------------------------------------------------------------\n\n");
            return i;
        }   
    }
    if (!flag) { // not found
        printf("\t\t%s Email ID is not found \n", Searchemail);
        printf("---------------------------------------------------------------------------\n\n");
        return -1;
    }
}

//*********************************************************** EDIT CONTACT ***************************************************************************

// SEARCH EDIT CONTACT BY NAME
int searchEditContactbyname(AddressBook *addressBook, char *Searchname, int index[], int *contact) {
    int i, flag = 0;
    printf("\nContact Found \n---------------------------------------------------------------------------\n");
    printf("%-13s %-17s %-17s %-17s","Sl No","NAME","Phone Number","E-mail");
    printf("\n---------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, Searchname) == 0) { // match
            printf("%-13d %-17s %-17s %-17s\n", *(contact) + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            flag = 1;
            index[(*contact)++] = i;
            printf("---------------------------------------------------------------------------\n");
        }   
    }
    if (!flag) { // not found
        printf("\t\t%s name is not found \n", Searchname);
        printf("---------------------------------------------------------------------------\n\n");
        return 0;
    }
}

// EDIT CONTACT
void Edit_Contact(AddressBook *addressBook, int i) {
    int ch;
    do {
        printf("\n---------------------------\nEdit Contact Menu \n---------------------------\n1.Edit Name \n2.Edit Phone Number \n3.Edit Email \n4.Exit \n---------------------------\n");
        printf("Enter Your Choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: // edit name
                char edit_name[100];
                printf("Enter New Name :");
                scanf(" %[^\n]", edit_name);
                strcpy(addressBook->contacts[i].name, edit_name);
                printf("Name Saved Successfully \n");
                break;
            case 2: // edit phone
                char edit_phone[100];
                int ret;
                do {
                    printf("Enter New Phone Number :");
                    scanf(" %[^\n]", edit_phone);
                    ret = validate_phone(addressBook, edit_phone);
                    if(ret==1){
                        strcpy(addressBook->contacts[i].phone, edit_phone);
                        printf("Phone Number Saved Successfully \n");
                    }
                } while (ret == 0);
                break;
            case 3: // edit email
                char edit_email[100];
                do{
                    printf("Enter New Email ID :");
                    scanf(" %[^\n]", edit_email);
                    ret = validate_Email(addressBook,edit_email);
                    if(ret==1){
                        strcpy(addressBook->contacts[i].email, edit_email);
                        printf("Email ID Saved Successfully \n");
                    }
                } while (ret == 0);
                break;
            default:
                printf("Invalid Input \n");
                break;
        }
    } while (ch != 4); // exit condition
}

//********************************************************************* DELETE CONTACT *********************************************************************************************

void Delete_Contact(AddressBook *addressBook, int ret) {
    if (ret != -1) {
        char Y;
        printf("Do you want delete contact(Y/N) : ");
        scanf(" %c", &Y);
        if (Y == 'Y' || Y == 'y') { // confirm delete
            for (int i = ret; i < addressBook->contactCount; i++) { // shift contacts
                strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
                strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
                strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);
            }
            addressBook->contactCount--; // reduce count
            printf("Contact Deleted Successfully \n");
        }
    }
}

//************************************************************************************************************************************************************************ 

// LISTING THE CONTACTS
void listContacts(AddressBook *addressBook) {
    if(addressBook->contactCount==0){
        printf("\nNo contacts found....!\n");
        return ;
    }
    printf("\nTotal Number of Contacts = %d ",addressBook->contactCount);
    printf("\n---------------------------------------------------------------------------\n");
    printf("%-13s %-17s %-17s %-17s\n","Sl No","NAME","Phone Number","E-mail");
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) { // print all
        printf("%-13d %-17s %-17s %-17s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        printf("---------------------------------------------------------------------------\n"); 
    }
    printf("\n");
}

// INITIALIZE CONTACT BOOK
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    loadContactsFromFile(addressBook);  
}

// SAVE AND EXIT
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // save to file
    exit(EXIT_SUCCESS); // exit
}

// CREATING CONTACTS
void createContact(AddressBook *addressBook) {
    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf("\nAddress book is full. Cannot add more contacts.\n");
        return;
    }

    printf("\n---------------------------\nCreate Contact\n---------------------------\n");
    printf("Enter the Name : ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
    int ret;
    do {
        printf("Enter the phone number :");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
        ret = validate_phone(addressBook, addressBook->contacts[addressBook->contactCount].phone);
    } while (ret == 0);
    do {   
        printf("Enter the Email ID :");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
        ret = validate_Email(addressBook, addressBook->contacts[addressBook->contactCount].email);
    } while (ret == 0);
    printf("---------------------------\nContact Saved Successfully \n\n");
    addressBook->contactCount++;
}

// SEARCHING THE CONTACT
void searchContact(AddressBook *addressBook) {
    int ch;
    printf("\n---------------------------\nSearch contact Menu :\n---------------------------\n1.Search by Name \n2.Search by Phone Number \n3.Search by Email \n---------------------------\n");
    printf("Enter Your Choice: ");
    scanf("%d", &ch);
    switch (ch) {
        case 1: // search name
            char Searchname[50];
            printf("Enter the Name :");
            scanf(" %[^\n]", Searchname);
            searchContactbyname(addressBook, Searchname);
            break;
        case 2: // search phone
            char Searchphone[20];
            printf("Enter the Phone Number :");
            scanf(" %[^\n]", Searchphone);
            searchContactbyphone(addressBook, Searchphone);
            break;
        case 3: // search email
            char Searchemail[20];
            printf("Enter the Email ID :");
            scanf(" %[^\n]", Searchemail);
            searchContactbyemail(addressBook, Searchemail);
            break;
        default:
            printf("Invalid Input ");
    }
}

// EDIT CONTACT MAIN MENU
void editContact(AddressBook *addressBook) {
    int ch;
    int contact = 0, index[10];
    do {
        printf("\n---------------------------\nEdit contact Menu:\n---------------------------\n1.Search by Name \n2.Search by Phone Number \n3.Search by Email \n4.Exit \n---------------------------\n");
        printf("Enter Your Choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: // edit by name
                char Searchname[50];
                printf("Enter the Name :");
                scanf(" %[^\n]", Searchname);
                int ret = searchEditContactbyname(addressBook, Searchname, index, &contact);
                if (ret != 0) {
                    if (contact > 1) { // multiple found
                        int ind;
                        printf("Enter Your Contact :");
                        scanf("%d", &ind);
                        Edit_Contact(addressBook, index[ind - 1]);
                    } else {
                        Edit_Contact(addressBook, index[0]);
                    }
                }
                break;
            case 2: // edit by phone
                char Searchphone[20];
                printf("Enter the Phone Number :");
                scanf(" %[^\n]", Searchphone);
                int ret1 = searchContactbyphone(addressBook, Searchphone);
                if (ret1 != -1) {
                    Edit_Contact(addressBook, ret1);
                }
                break;
            case 3: // edit by email
                char Searchemail[20];
                printf("Enter the Email ID :");
                scanf(" %[^\n]", Searchemail);
                int ret2 = searchContactbyemail(addressBook, Searchemail);
                if (ret2 != -1) {
                    Edit_Contact(addressBook, ret2);
                }
                break;
            default:
                printf("Invalid Input ");
        }
    } while (ch != 4);
}

// DELETE CONTACT MAIN MENU
void deleteContact(AddressBook *addressBook) {
    int ch;
    int contact = 0, index[10];
    printf("---------------------------\nSearch contact Menu :\n---------------------------\n1.Search by Name \n2.Search by Phone Number \n3.Search by Email \n---------------------------\n");
    printf("Enter Your Choice: ");
    scanf("%d", &ch);
    switch (ch) {
        case 1: // delete by name
            char Searchname[50];
            printf("Enter the Name :");
            scanf(" %[^\n]", Searchname);
            searchEditContactbyname(addressBook, Searchname, index, &contact);
            if (contact > 1) {
                int ind;
                printf("Multiple contacts found. Enter your choice: ");
                scanf("%d", &ind);
                Delete_Contact(addressBook, index[ind - 1]);
            } else if (contact == 1) {
                Delete_Contact(addressBook, index[0]);
            }
            break;
        case 2: // delete by phone
            char Searchphone[20];
            printf("Enter the Phone Number :");
            scanf(" %[^\n]", Searchphone);
            int ret = searchContactbyphone(addressBook, Searchphone);
            Delete_Contact(addressBook, ret); 
            break;
        case 3: // delete by email
            char Searchemail[20];
            printf("Enter the Email ID :");
            scanf(" %[^\n]", Searchemail);
            int ret1 = searchContactbyemail(addressBook, Searchemail);
            Delete_Contact(addressBook, ret1);
            break;
        default:
            printf("Invalid Input ");
    }
}
