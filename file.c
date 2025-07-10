#include <stdio.h>              // Standard I/O functions
#include <string.h>             // For string operations like strlen, strcpy
#include <errno.h>              // For error reporting using errno and strerror
#include "file.h"               // Custom header file for AddressBook structure

// Function to save contacts to file
void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp = fopen("AddressBook.csv", "w");  // Open file in write mode
    if (fp == NULL) {  // Check if file failed to open
        fprintf(stderr, "Error opening file for writing: %s\n", strerror(errno));  // Print error
        return;  // Exit function on failure
    }

    fprintf(fp, "#%d\n", addressBook->contactCount);  // Write contact count as header

    // Loop through all contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        // Ensure all fields are non-empty before writing
        if (strlen(addressBook->contacts[i].name) > 0 &&
            strlen(addressBook->contacts[i].phone) > 0 &&
            strlen(addressBook->contacts[i].email) > 0) 
        {
            // Write contact in CSV format: name,phone,email
            fprintf(fp, "%s,%s,%s\n",
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
        }
    }

    fclose(fp);  // Close the file after writing
    printf("Contacts saved to file successfully.\n");  // Success message
}

// Function to load contacts from file
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("AddressBook.csv", "r");  // Open file in read mode
    if (fp == NULL) {  // Check if file failed to open
        fprintf(stderr, "Error opening file for reading: %s\n", strerror(errno));  // Print error
        addressBook->contactCount = 0;  // Set contact count to 0 if file not loaded
        return;  // Exit function
    }

    int expectedCount = 0;  // Variable to hold the expected number of contacts
    fscanf(fp, "#%d\n", &expectedCount);  // Read header line (e.g., #5)

    int actualCount = 0;  // Counter for how many contacts were actually read
    while (!feof(fp) && actualCount < MAX_CONTACTS) {  // Loop until end of file or limit
        char name[50], phone[20], email[50];  // Temp buffers for each contact field

        // Read one contact using comma-separated format
        int scanned = fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n", name, phone, email);
        if (scanned == 3) {  // Ensure all 3 fields were read successfully
            strcpy(addressBook->contacts[actualCount].name, name);  // Copy name to structure
            strcpy(addressBook->contacts[actualCount].phone, phone);  // Copy phone to structure
            strcpy(addressBook->contacts[actualCount].email, email);  // Copy email to structure
            actualCount++;  // Increment contact count
        } else {
            fscanf(fp, "%*[^\n]\n");  // Skip malformed line
        }
    }

    addressBook->contactCount = actualCount;  // Update contact count in structure
    fclose(fp);  // Close the file
}
