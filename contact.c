#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "contact.h"
#include "file.h"
#include "populate.h"


#include <stdio.h>

// Function to display all contacts in a formatted table with emojis
void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("📘 No contacts to display.\n");
        return;
    }

    // Decorative header
    printf("\n╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                       📘 My Contact Book — Contacts List 👥                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");

    // Table headers with emojis
    printf("🔢 %-3s  👤 %-18s 📞 %-13s 📧 %-28s\n", "No.", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------------------------\n");

    // Print each contact with its details
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("   %-3d  %-20s %-15s %-30s\n", 
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    // Footer
    printf("-------------------------------------------------------------------------------\n");
    printf("✅ Total Contacts: %d\n\n", addressBook->contactCount);
}


// Initialize address book (load dummy data if desired)
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook); // optional, comment if not needed
     loadContactsFromFile(addressBook);
}


// Save contacts and exit
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // stubbed out currently
    exit(EXIT_SUCCESS);
}


// Create new contact with emoji-based prompts
void createContact(AddressBook *addressBook)
{
    char name[50], number[20], mail[50];
    int valid = 0;

    // 🔤 Name Input
    printf("👤 Enter your Name: ");
    scanf(" %[^\n]", name);
    name[strcspn(name, "\n")] = '\0'; // remove trailing newline

    //  Phone Number Input & Validation
    valid = 0;
    while (!valid)
    {
        printf("📞 Enter 10-digit phone number: ");
        scanf("%s", number);

        if (strlen(number) != 10)
        {
            printf("Invalid: Number must be exactly 10 digits.\n");
            continue;
        }

        valid = 1;
        for (int i = 0; i < 10; i++)
        {
            if (!isdigit(number[i]))
            {
                printf("Invalid: Only digits (0-9) allowed.\n");
                valid = 0;
                break;
            }
        }

        // 🔁 Duplicate phone check
        if (valid) {
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].phone, number) == 0) {
                    printf("⚠️  This phone number already exists in contacts!\n");
                    valid = 0;
                    break;
                }
            }
        }
    }

    // 📧 Email Input & Validation
    valid = 0;
    while (!valid)
    {
        printf("📧 Enter email (lowercase only): ");
        scanf("%s", mail);

        valid = 1;

        for (int i = 0; i < strlen(mail); i++)
        {
            char ch = mail[i];
            if (!(islower(ch) || isdigit(ch) || ch == '@' || ch == '.' || ch == '_'))
            {
                printf("Invalid: Email contains invalid character: %c\n", ch);
                valid = 0;
                break;
            }
        }

        if (!valid) continue;

        // @ Check
        char *at = strchr(mail, '@');
        if (!at || at == mail || *(at + 1) == '\0') {
            printf("Invalid: '@' must have characters before and after it.\n");
            valid = 0;
            continue;
        }
        if (strchr(at + 1, '@')) {
            printf("Invalid: Email contains multiple '@' symbols.\n");
            valid = 0;
            continue;
        }

        int hasLetterBefore = 0, hasLetterAfter = 0;
        int atIndex = at - mail;
        int len = strlen(mail);

        for (int i = 0; i < atIndex; i++) {
            if (isalpha(mail[i])) {
                hasLetterBefore = 1;
                break;
            }
        }
        for (int i = atIndex + 1; i < len; i++) {
            if (isalpha(mail[i])) {
                hasLetterAfter = 1;
                break;
            }
        }

        if (!hasLetterBefore || !hasLetterAfter) {
            printf("Invalid: Must contain at least one letter before and after '@'.\n");
            valid = 0;
            continue;
        }

        if (len < 5 || strcmp(&mail[len - 4], ".com") != 0)
        {
            printf("Invalid: Email must end with '.com'\n");
            valid = 0;
            continue;
        }

        char *dotCom = strstr(at, ".com");
        if (!dotCom || dotCom == at + 1) {
            printf("Invalid: Missing characters between '@' and '.com'\n");
            valid = 0;
            continue;
        }

        int validBetween = 0;
        for (char *ptr = at + 1; ptr < dotCom; ptr++) {
            if (isalpha(*ptr)) {
                validBetween = 1;
                break;
            }
        }
        if (!validBetween) {
            printf("Invalid: Must be at least one letter between '@' and '.com'\n");
            valid = 0;
            continue;
        }

        // 🧾 Duplicate email check
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, mail) == 0)
            {
                printf("⚠️ Duplicate: This email already exists.\n");
                valid = 0;
                break;
            }
        }
    }

    // ✅ Save Contact
    if (valid)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, number);
        strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
        addressBook->contactCount++;
        printf("✅ Contact added successfully!\n");
    }
}


// Function to search for a contact with interactive emojis
void searchContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("📭 No contacts to search.\n");
        return;
    }

    int choice;
    char input[50];
    int found = 0;

    // 🔍 Search Menu
    printf("\n🔍 Search contact by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");

    while (1)
    {
        printf("👉 Enter your choice (1-3): ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 3)
        {
            printf("❌ Invalid choice. Please select 1, 2, or 3.\n");
            continue;
        }

        // 📥 Input search value
        printf("🔎 Enter search value: ");
        scanf(" %[^\n]", input); // To allow spaces

        found = 0;

        // 🧾 Search Logic
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if ((choice == 1 && strcasestr(addressBook->contacts[i].name, input) != NULL) ||
                (choice == 2 && strcmp(addressBook->contacts[i].phone, input) == 0) ||
                (choice == 3 && strcmp(addressBook->contacts[i].email, input) == 0))
            {
                printf("\n📇 Contact Found!\n");
                printf("──────────────────────────────\n");
                printf("📌 Contact %d\n", i + 1);
                printf("👤 Name  : %s\n", addressBook->contacts[i].name);
                printf("📞 Phone : %s\n", addressBook->contacts[i].phone);
                printf("📧 Email : %s\n", addressBook->contacts[i].email);
                printf("──────────────────────────────\n");
                found = 1;
            }
        }

        if (!found)
        {
            printf("❗ No matching contact found. Please try again.\n");
        }
        else
        {
            printf("✅ Search completed successfully!\n");
            break; // Exit loop after successful search
        }
    }
}


// Helper to get a validated 10-digit phone number
void getValidPhone(char *number, AddressBook *ab, int skipIndex) {
    int valid = 0;
    while (!valid) {
        printf("Enter 10-digit phone number: ");
        scanf("%s", number);

        if (strlen(number) != 10) {
            printf("Invalid: Number must be exactly 10 digits.\n");
            continue;
        }

        valid = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(number[i])) {
                printf("Invalid: Only digits (0-9) allowed.\n");
                valid = 0;
                break;
            }
        }

        if (valid) {
            for (int i = 0; i < ab->contactCount; i++) {
                if (i != skipIndex && strcmp(ab->contacts[i].phone, number) == 0) {
                    printf("This phone number already exists in contacts!\n");
                    valid = 0;
                    break;
                }
            }
        }
    }
}

// Helper to get a validated email
void getValidEmail(char *email, AddressBook *ab, int skipIndex) {
    int valid = 0;
    while (!valid) {
        printf("Enter email (lowercase only): ");
        scanf("%s", email);

        valid = 1;
        int len = strlen(email);

        for (int i = 0; i < len; i++) {
            char ch = email[i];
            if (!(islower(ch) || isdigit(ch) || ch == '@' || ch == '.' || ch == '_')) {
                printf("Invalid: Email contains invalid character: %c\n", ch);
                valid = 0; break;
            }
        }
        if (!valid) continue;

        char *at = strchr(email, '@');
        if (!at || at == email || *(at + 1) == '\0') {
            printf("Invalid: '@' must have characters before and after it.\n");
            valid = 0; continue;
        }
        if (strchr(at + 1, '@')) {
            printf("Invalid: Multiple '@' symbols.\n");
            valid = 0; continue;
        }

        int hasBefore = 0, hasAfter = 0;
        for (int i = 0; i < at - email; i++) {
            if (isalpha(email[i])) { hasBefore = 1; break; }
        }
        for (int i = at - email + 1; i < len; i++) {
            if (isalpha(email[i])) { hasAfter = 1; break; }
        }
        if (!hasBefore || !hasAfter) {
            printf("Invalid: Must contain letters before and after '@'.\n");
            valid = 0; continue;
        }

        if (len < 5 || strcmp(&email[len - 4], ".com") != 0) {
            printf("Invalid: Email must end with '.com'\n");
            valid = 0; continue;
        }

        char *dotCom = strstr(at, ".com");
        if (!dotCom || dotCom == at + 1) {
            printf("Invalid: Missing characters between '@' and '.com'\n");
            valid = 0; continue;
        }

        int betweenValid = 0;
        for (char *ptr = at + 1; ptr < dotCom; ptr++) {
            if (isalpha(*ptr)) { betweenValid = 1; break; }
        }
        if (!betweenValid) {
            printf("Invalid: Must have alphabet between '@' and '.com'\n");
            valid = 0; continue;
        }

        for (int i = 0; i < ab->contactCount; i++) {
            if (i != skipIndex && strcmp(ab->contacts[i].email, email) == 0) {
                printf("Duplicate: This email already exists.\n");
                valid = 0; break;
            }
        }
    }
}

void editContact(AddressBook *ab) {
    if (ab->contactCount == 0) {
        puts("📭 No contacts to edit."); return;
    }

    char input[50], phone[50], email[50];
    int matchedIdx[100], matchCount = 0, selectedIndex = -1, choice;

    while (1) {
        puts("\n✏️  Edit contact by:\n1️. Name\n2️. Phone Number\n3️. Email");
        printf("👉 Enter your choice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); continue; }
        while (getchar() != '\n');
        if (choice < 1 || choice > 3) { puts("❌ Invalid choice."); continue; }

        if (choice == 2) getValidPhone(input, ab, -1);
        else if (choice == 3) getValidEmail(input, ab, -1);
        else { printf("🔎 Enter name to search: "); scanf(" %[^\n]", input); }

        for (int i = 0; i < ab->contactCount; i++) {
            if ((choice == 1 && strcasestr(ab->contacts[i].name, input)) ||
                (choice == 2 && strcmp(ab->contacts[i].phone, input) == 0) ||
                (choice == 3 && strcmp(ab->contacts[i].email, input) == 0))
                matchedIdx[matchCount++] = i;
        }

        if (matchCount == 0) { puts("❗ No matching contact found. Try again."); continue; }
        break;
    }

    if (matchCount > 1) {
        puts("\n📋 Multiple matches found:");
        for (int i = 0; i < matchCount; i++) {
            int j = matchedIdx[i];
            printf("[%d] 👤 %s | 📞 %s | 📧 %s\n", i + 1, ab->contacts[j].name, ab->contacts[j].phone, ab->contacts[j].email);
        }
        printf("👉 Choose (1-%d): ", matchCount);
        int sel;
        if (scanf("%d", &sel) != 1 || sel < 1 || sel > matchCount) {
            puts("Invalid selection. Edit cancelled.");
            return;
        }
        while (getchar() != '\n');
        selectedIndex = matchedIdx[sel - 1];
    } else selectedIndex = matchedIdx[0];

    Contact *c = &ab->contacts[selectedIndex];
    printf("\n📇 Selected Contact:\n👤 Name: %s\n📞 Phone: %s\n📧 Email: %s\n", c->name, c->phone, c->email);

    puts("\n✍️  Edit field:\n1️. Name\n2️. Phone\n3️. Email\n4️. All");
    printf("👉 Enter your choice: ");
    if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); return; }
    while (getchar() != '\n');

    switch (choice) {
        case 1:
            printf("✏️ Enter new name: ");
            scanf(" %[^\n]", c->name);
            break;
        case 2:
            getValidPhone(phone, ab, selectedIndex);
            strcpy(c->phone, phone);
            break;
        case 3:
            getValidEmail(email, ab, selectedIndex);
            strcpy(c->email, email);
            break;
        case 4:
            printf("✏️ Enter new name: ");
            scanf(" %[^\n]", c->name);
            getValidPhone(phone, ab, selectedIndex);
            strcpy(c->phone, phone);
            getValidEmail(email, ab, selectedIndex);
            strcpy(c->email, email);
            break;
        default:
            puts("❌ Invalid edit option. Edit cancelled.");
            return;
    }

    puts("\n✅ Contact updated successfully!");
    printf("👤 Name: %s\n📞 Phone: %s\n📧 Email: %s\n", c->name, c->phone, c->email);
}


// Function to delete a contact with emoji-enhanced prompts
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("📭 No contacts to delete.\n");
        return;
    }

    int searchChoice;
    char input[50];
    int matchIdx[100];     // indices of matching contacts
    int matchCount = 0;

    while (1)
    {
        matchCount = 0;

        // 🔍 How to search for contact to delete
        printf("\n🗑️ Delete contact by:\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email\n");
        printf("👉  Enter your choice: ");
        scanf("%d", &searchChoice);
        while (getchar() != '\n'); // clear buffer

        if (searchChoice < 1 || searchChoice > 3)
        {
            printf("❌ Invalid choice. Please enter 1, 2, or 3.\n");
            continue;
        }

        printf("🔎 Enter the value to delete: ");
        scanf(" %[^\n]", input);

        // 🔍 Gather matching contacts
        for (int i = 0; i < addressBook->contactCount; ++i)
        {
            int match = 0;
            if (searchChoice == 1 && strcasecmp(addressBook->contacts[i].name, input) == 0)
                match = 1;
            else if (searchChoice == 2 && strcmp(addressBook->contacts[i].phone, input) == 0)
                match = 1;
            else if (searchChoice == 3 && strcmp(addressBook->contacts[i].email, input) == 0)
                match = 1;

            if (match)
                matchIdx[matchCount++] = i;
        }

        if (matchCount == 0)
        {
            printf("❗ No matching contact found. Please try again.\n");
            continue;
        }

        break; // Exit search loop
    }

    int target = matchIdx[0]; // default to first match
    if (matchCount > 1)
    {
        printf("\n📋 Multiple matching contacts:\n");
        for (int i = 0; i < matchCount; ++i)
        {
            int idx = matchIdx[i];
            printf("\n[%d] 👤 Name : %s\n", i + 1, addressBook->contacts[idx].name);
            printf("    📞 Phone: %s\n", addressBook->contacts[idx].phone);
            printf("    📧 Email: %s\n", addressBook->contacts[idx].email);
        }

        int sel;
        printf("\n👉 Enter the number of the contact to delete (1‑%d): ", matchCount);
        scanf("%d", &sel);
        while (getchar() != '\n');

        if (sel < 1 || sel > matchCount)
        {
            printf("❌ Invalid selection. Delete aborted.\n");
            return;
        }
        target = matchIdx[sel - 1];
    }

    // 🔧 Delete contact
    for (int j = target; j < addressBook->contactCount - 1; ++j)
        addressBook->contacts[j] = addressBook->contacts[j + 1];

    addressBook->contactCount--;
    printf("✅ Contact deleted successfully!\n");
    printf("\n");
}
