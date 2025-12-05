# Library Management System

**A console-based Library Management System built with C programming language**

**Team Members:** Rian Hasan Siam || Fabiha || Karib  
**Version:** 1.0  
**Language:** C Programming  
**Platform:** Windows (Console Application)

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Installation & Setup](#installation--setup)
- [Usage Guide](#usage-guide)
- [Database Structure](#database-structure)
- [Documentation](#documentation)

---

## 🎯 Overview

This Library Management System is a beginner-friendly console application that demonstrates fundamental programming concepts including file handling, data structures, user authentication, and menu-driven interfaces. The system manages books, users, requests, and messages with persistent storage in text files.

### Key Highlights
- ✅ User authentication (Admin & Regular Users)
- ✅ Book CRUD operations (Create, Read, Update, Delete)
- ✅ Request-based book issuing workflow
- ✅ Message system (User to Admin communication)
- ✅ Real-time database synchronization
- ✅ Automatic data persistence
- ✅ CSV-based file storage

---

## ✨ Features

### Main Menu
- **Register**: Create a new user account (automatically saved)
- **Login**: Authenticate as Admin or Regular User
- **About Project**: View project information and features
- **Exit**: Safely close with automatic data backup

### 👨‍💼 Admin Features
- 📚 Display all books with status (Available/Issued)
- ➕ Add new books to the library
- ✏️ Update book information (title/author)
- 🗑️ Delete books (validation: cannot delete issued books)
- 🔍 Search books by title
- 📬 View pending book requests from users
- ✅ Approve/Reject book requests (auto-issues on approval)
- 💬 View messages from users
- 📊 Generate system statistics

### 👤 User Features
- 📖 Browse all available books
- 🔍 Search books by title
- 📝 Request a book (duplicate prevention)
- 📋 View request history (Pending/Approved/Rejected)
- 📚 View books currently issued to you
- 💬 Send messages to admin
- 🔐 Secure login system

---

## 🏗️ System Architecture

### Request-Based Workflow
```
┌─────────┐         ┌──────────┐         ┌────────┐
│  USER   │────────▶│  SYSTEM  │────────▶│ ADMIN  │
└─────────┘         └──────────┘         └────────┘
    │                    │                     │
    │ 1. Request Book    │                     │
    ├───────────────────▶│                     │
    │                    │ 2. Store Request    │
    │                    ├────────────────────▶│
    │                    │                     │
    │                    │ 3. Review & Approve │
    │                    │◀────────────────────┤
    │ 4. Auto-Issue      │                     │
    │◀───────────────────┤                     │
    │ 5. View Issued Books                     │
    └───────────────────▶                      │
```

### Data Flow
```
Program Start
    ↓
Load Data (books.txt, users.txt, messages.txt, requests.txt)
    ↓
Initialize System (create defaults if needed)
    ↓
Main Menu → Login → Admin/User Menu
    ↓
Operations (Add/Delete/Request/Approve)
    ↓
Auto-Save to Files (real-time sync)
    ↓
Exit → Generate Statistics Report
```

---

## 💾 Database Structure

### Files & Format

**1. books.txt** (CSV Format)
```
id,title,author,isIssued,issuedTo
1,C Programming,Dennis Ritchie,0,
2,Data Structures,John Smith,1,rian
```

**2. users.txt** (CSV Format)
```
username,password,isAdmin
admin,admin123,1
rian,123,0
```

**3. messages.txt** (CSV Format)
```
username,message
rian,Need more programming books
```

**4. requests.txt** (CSV Format)
```
username,bookId,bookTitle,status
rian,1,C Programming,0
```
*Status: 0=Pending, 1=Approved, 2=Rejected*

**5. project_info.txt** (Statistics Report)
```
Total Books: 3
Total Users: 2
Available Books: 2
Issued Books: 1
Pending Requests: 1
```

---

## 🚀 Installation & Setup

### Prerequisites
- GCC Compiler (MinGW for Windows)
- Windows OS (for conio.h support)

### Compilation
```cmd
gcc library_system.c -o library_system.exe
```

### Run
```cmd
library_system.exe
```

---

## 📖 Usage Guide

### First Time Setup
1. Run the program - default admin account is created automatically
2. Sample books are added on first run

### For Regular Users
1. **Register**: Select option [1] → Enter username & password
2. **Login**: Select option [2] → Enter credentials
3. **Request Books**: Browse books → Enter book ID → Wait for admin approval
4. **Check Status**: View "My Book Requests" to see approval status

### For Admin
1. **Login**: Use `admin` / `admin123`
2. **Manage Books**: Add, Update, Delete books
3. **Process Requests**: View pending requests → Approve or Reject
4. **Monitor System**: View messages and generate reports

### Default Admin Credentials
- **Username:** `admin`
- **Password:** `admin123`

---

## 📚 Sample Books

Pre-loaded books (created on first run):
1. **C Programming** by Dennis Ritchie
2. **Data Structures** by John Smith  
3. **Algorithms** by Robert Sedgewick

---

## 📄 Documentation

For detailed technical documentation, please refer to:
- **SRS.md** - Software Requirements Specification
- **USECASE_DIAGRAM.md** - Use Case Diagram and scenarios

---

## 🔧 Technical Details

### Data Structures
- `struct Book` - Book information (id, title, author, issue status)
- `struct User` - User credentials and role
- `struct Message` - User-to-admin messages
- `struct BookRequest` - Book request details and status

### Key Features
- **Live Database Sync**: Changes saved immediately to files
- **Data Validation**: Prevents duplicates, invalid operations
- **Session Management**: Tracks current user and permissions
- **Error Handling**: File I/O error checks and user feedback

---

## ⚠️ Important Notes

1. **File Persistence**: All data is saved to `.txt` files - don't delete them!
2. **CSV Format**: Database files use comma-separated values
3. **Cannot Delete Issued Books**: Books must be returned first
4. **Duplicate Prevention**: System checks for duplicate usernames and requests
5. **Auto-Save**: No manual save required - everything is automatic

---

## 🤝 Contributing

This is a beginner-level capstone project. Contributions and improvements are welcome!

---

## 📞 Contact

**Team:** Rian Hasan Siam || Fabiha || Karib  
**Project Type:** Capstone Project (Academic)  
**Year:** 2025

---

**© 2025 Library Management System - All Rights Reserved**

### File Operations:
- **Automatic Load**: On program start, all data loads from text files
- **Automatic Save**: Every change is immediately saved to files
- **Persistent Data**: Close and reopen - all data remains!

## System Limits
- Maximum Books: 100
- Maximum Users: 50
- Maximum Messages: 50

## Key Functions Explained

### Registration
- Users can create new accounts with unique usernames
- Passwords are required for security
- **Immediately saved to `users.txt`**

### Book Management (Admin Only)
- Add new books with title and author
- Update existing book information
- Delete books (only if not issued)
- Search books by title
- **Review book requests from users**
- **Approve requests** - automatically issues book to user
- **Reject requests** - notifies user
- **All changes immediately saved to files**

### User Features
- Browse all books with their status
- Search for specific books by title
- **Request books** - submit request to admin
- **Track request status** - see if pending/approved/rejected
- View books issued to them
- Send messages to admin for requests or queries
- **Book requests immediately saved to `requests.txt`**

### Automatic File Operations
- On startup: Loads data from all 3 files
- After each change: Saves to appropriate file
- On exit: Final save of all data
- Data persists between program runs

## Notes for Beginners

- The code uses simple C concepts: structures, arrays, loops, and functions
- **Data automatically saves to text files** - no manual save needed!
- Uses `struct` keyword (no typedef) for better understanding
- Simple file handling with `fopen`, `fprintf`, `fscanf`
- The `system("cls")` command clears the screen (Windows)
- Uses `gets()` for reading strings with spaces

## File Formats

### books.txt
```
id,title,author,isIssued,issuedTo
1,C Programming,Dennis Ritchie,0,
2,Data Structures,John Smith,1,user123
```

### users.txt
```
username,password,isAdmin
admin,admin123,1
john,pass123,0
```

### messages.txt
```
username,message
john,Please add more programming books
alice,When is the library open?
```

### requests.txt
```
username,bookId,bookTitle,status
john,3,Algorithms,0
alice,1,C Programming,1
bob,2,Data Structures,2
```
*Status: 0=Pending, 1=Approved, 2=Rejected*

### project_info.txt
```
========================================
   LIBRARY MANAGEMENT SYSTEM
   PROJECT DATABASE INFORMATION
========================================

Project Name: Library Management System
Language: C Programming
Version: 1.0
Date: December 3, 2025

========================================
   SYSTEM STATISTICS
========================================
Total Books: 3
Total Users: 3
Total Messages: 2
Total Requests: 3

Available Books: 1
Issued Books: 2

Admin Users: 1
Regular Users: 2

Pending Requests: 1
Approved Requests: 1
Rejected Requests: 1

[Complete list of all books, users, and requests...]
```
*Auto-generated comprehensive database report*

## Code Structure

The code follows this pattern (similar to your student management system):
```c
struct Book { ... }           // Data structure
void loadAllData()            // Load all data on startup
void saveAllData()            // Save all data on exit
void saveBooksToFile()        // Save books immediately
void loadBooksFromFile()      // Load books from file
void addBook()                // Add + auto-save
void updateBook()             // Update + auto-save
void deleteBook()             // Delete + auto-save
```

## Tips

1. **Users**: Request books instead of asking admin to manually issue
2. **Admin**: Check pending requests regularly and approve/reject them
3. All data saves automatically - no need to remember to save!
4. Close the program anytime - your data is safe
5. Delete the .txt files to reset the system to default
6. Check the .txt files to see how data is stored
7. Search for books using partial titles (e.g., "Data" will find "Data Structures")
8. Track your request status - see if admin approved your request

## Future Enhancements (Optional)

- Better password security (encryption)
- Due dates for issued books
- Fine calculation for late returns
- More detailed search options
- Export reports to CSV

---

**Happy Learning! 📚**
