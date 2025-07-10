
# 📒 Address Book Management System in C

## 📁 Project Information
**Name:** Amruta Pradip Patil  
**Date of Submission:** 08/July/2025  
**GitHub Repository:** *(Add your GitHub repo URL here)*

---

## 📝 Description

This **Address Book Management System** is a C-based CLI project that allows users to manage their personal and professional contacts. It supports creation, searching, editing, deletion, and listing of contacts in a structured format. All contacts are saved persistently in a CSV file using file I/O operations.

---

### 🔧 Key Features

- 📇 Create new contacts (Name, Phone, Email)
- 🔍 Case-insensitive search by name, phone, or email
- ✏️ Edit contact details field-by-field
- 🗑️ Delete contacts securely
- ✅ Validations for:
  - 10-digit phone number
  - Properly formatted email
  - Non-empty name
- 💾 File persistence using `contacts.csv`
- 📋 List view in tabular format
- 📂 Modular structure with header and source files
- 🧪 Dummy data population for testing

---

## 📂 File Structure

```
contact.h       - Header file with data structures and function declarations
contact.c       - Implementation of contact management functions
file.h          - Header for file operations
file.c          - Implementation of file I/O functions
main.c          - Main program with menu interface
populate.h      - Header for dummy data population
populate.c      - Dummy contact data for testing
contacts.csv    - Data file storing contacts in CSV format
```

---

## 💻 Sample Input/Output

### ➕ Creating a Contact

```
Enter your choice: 1

Enter name: Jane Smith
Enter phone number (10 digits): 9876543210
Enter email: jane.smith@gmail.com
Contact added successfully!
```

### 📜 Listing Contacts

```
Enter your choice: 5

No.  Name                 Phone          Email                         
-----------------------------------------------------------
1    Amruta Patil         9876543210     amruta@example.com           
2    Sakshi               1234567898     sakshi03@gmail.com            
...
Total contacts: 13
```

### 🔍 Searching Contacts

```
Enter your choice: 2
Search by:
1. Name
2. Phone
3. Email
4. Back to Menu
Enter your choice (1-4): 1
Enter search term: Amruta

Search results for "Amruta":
-----------------------------------------------------------
Name                 Phone          Email                         
-----------------------------------------------------------
Amruta               7777852414     amruta02@gmail.com             
Shahid               9999999998     amruta123@gmail.com          
```

### ✏️ Editing a Contact

```
Enter your choice: 3
Edit by:
1. Name
2. Phone
3. Email
4. Cancel
Enter your choice: 1
Enter search term: Jane Smith

Select field to edit (1-4): 1
Enter new name: Jane Doe

Contact updated successfully!
```

### 🗑️ Deleting a Contact

```
Enter your choice: 4
Delete by:
1. Name
2. Phone
3. Email
4. Cancel
Enter your choice: 2
Enter search term: 1234567890

Are you sure? (y/n): y
Contact deleted successfully!
```

### 🚪 Exiting

```
Enter your choice: 6
Saving and Exiting...
Contacts saved to contacts.csv successfully!
```

---

## ⚙️ How to Compile and Run

```bash
gcc main.c contact.c file.c populate.c -o addressbook
./addressbook
```

---

## 👩‍💻 Developed By

**Amruta Pradip Patil**  
🎓 Final-Year CSE Student | 🌐 IoT • C Programming • Embedded Systems  
🛠️ e-Yantra Club Leader @ IIT Bombay  
📍 Sangli, Maharashtra

---

## 📄 License

This project is licensed under the MIT License – feel free to use and modify it.

---

## ⭐ GitHub Tip

If you find this project useful, please ⭐ star the repository and share your feedback!

