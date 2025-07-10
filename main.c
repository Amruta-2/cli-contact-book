#include "contact.h"  // Include the header file where AddressBook and function declarations exist

int main() 
{
printf("\n\n♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦\n");
printf("   📘 Welcome to the Address Book 📘\n");
printf("Conatct Management System by Amruta Patil\n");
printf("♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦♦\n\n");
    int choice;  // Variable to store user menu choice

    AddressBook addressBook;  // Declare the address book structure
    initialize(&addressBook); // Initialize address book (e.g., load from file or clear)

    do 
    {
    
        printf("\n📒 Address Book Menu:\n");
        printf("1. ➕ Add Contact\n");
        printf("2. 🔍 Search Contact\n");
        printf("3. 📝 Edit Contact\n");
        printf("4. 🗑️  Delete Contact\n");
        printf("5. 📋 List All Contacts\n");
        printf("6. ❌ Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on user's choice
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);  // Add a new contact
                break;
            case 2:
                searchContact(&addressBook);  // Search for a contact by name/phone/email
                break;
            case 3:
                editContact(&addressBook);  // Edit existing contact's details
                break;
            case 4:
                deleteContact(&addressBook);  // Delete a contact from the list
                break;
            case 5:
                listContacts(&addressBook);  // Display all contacts
                break;
            case 6:
                printf("Saving and Exiting...\n");  // Inform user before exit
                saveContactsToFile(&addressBook);  // Save all contacts to file before exiting
                break;
            default:
                printf("Invalid choice. Please try again.\n");  // Handle invalid menu input
        }

    } while (choice != 6);  // Keep repeating until the user chooses to exit

    // cleanup(); // Optional: cleanup resources like memory if dynamically allocated

    return 0;  // Exit the program
}
