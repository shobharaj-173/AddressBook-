#include <stdio.h>
#include "file.h"
#include "contact.h"

// Function to save all contacts to a CSV file
void saveContactsToFile(AddressBook *addressBook)
{
    // Open file in write mode
    FILE *fptr = fopen("contact.csv", "w");
    if (fptr == NULL)
    {
        fprintf(stderr, "Cannot open the file for writing\n");
        return;
    }

    // Write total number of contacts at the top of the file
    fprintf(fptr, "%d\n", addressBook->contactCount);

    // Write each contact's details in CSV format
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    // Close the file
    fclose(fptr);
}

// Function to load all contacts from a CSV file
void loadContactsFromFile(AddressBook *addressBook)
{
    // Open file in read mode
    FILE *fptr = fopen("contact.csv", "r");
    if (fptr == NULL)
    {
        printf("No previous contacts found. Starting with an empty address book.\n");
        addressBook->contactCount = 0;
        return;
    }

    // Read total number of contacts from the file
    fscanf(fptr, "%d\n", &addressBook->contactCount);

    int i = 0;

    // Read each contact line until EOF or MAX_CONTACTS reached
    while (i < MAX_CONTACTS)
    {
        int ret = fscanf(fptr, "%99[^,],%19[^,],%99[^\n]\n",
                         addressBook->contacts[i].name,
                         addressBook->contacts[i].phone,
                         addressBook->contacts[i].email);

        // Stop if reading fails (not exactly 3 fields)
        if (ret != 3)
            break;

        i++;
    }

    // Update actual count of loaded contacts
    addressBook->contactCount = i;

    // Close the file
    fclose(fptr);
}
