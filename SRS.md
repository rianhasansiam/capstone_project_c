# Software Requirements Specification (SRS)

## Library Management System

**Version:** 1.0  
**Date:** December 5, 2025  
**Prepared by:** Rian Hasan Siam, Fabiha, Karib  
**Organization:** Capstone Project Team

---

## Table of Contents
1. [Introduction](#1-introduction)
2. [Overall Description](#2-overall-description)
3. [System Features](#3-system-features)
4. [External Interface Requirements](#4-external-interface-requirements)
5. [System Requirements](#5-system-requirements)
6. [Non-Functional Requirements](#6-non-functional-requirements)

---

## 1. Introduction

### 1.1 Purpose
This Software Requirements Specification (SRS) document provides a complete description of the Library Management System. It details the functional and non-functional requirements for developers, testers, and stakeholders.

### 1.2 Scope
The Library Management System is a console-based application designed to manage library operations including book inventory, user registration, book issuing through a request-approval workflow, and administrative tasks.

**Benefits:**
- Automated book management
- User authentication and authorization
- Request-based book issuing workflow
- Persistent data storage
- Real-time database synchronization

### 1.3 Definitions, Acronyms, and Abbreviations
- **LMS**: Library Management System
- **Admin**: System administrator with full privileges
- **User**: Regular library user with limited privileges
- **CSV**: Comma-Separated Values
- **CRUD**: Create, Read, Update, Delete

### 1.4 References
- C Programming Language Standard
- File I/O operations in C
- Data structures and algorithms

### 1.5 Overview
This document is organized into sections describing the system's purpose, features, interfaces, and requirements in detail.

---

## 2. Overall Description

### 2.1 Product Perspective
The Library Management System is a standalone console application that operates independently. It uses text files as a database for persistent storage.

**System Interfaces:**
- Console-based user interface
- File system for data storage (books.txt, users.txt, messages.txt, requests.txt)

### 2.2 Product Functions
The major functions include:
- User authentication (Login/Register)
- Book management (Add, Update, Delete, Search)
- Request management (Request, Approve, Reject)
- Message system (User-to-Admin communication)
- Report generation

### 2.3 User Classes and Characteristics

#### 2.3.1 Administrator
- **Frequency of Use:** Daily
- **Functions:** Full system access, manage books, approve requests, view messages
- **Technical Expertise:** Basic computer skills
- **Security Level:** Highest

#### 2.3.2 Regular User
- **Frequency of Use:** As needed
- **Functions:** View books, request books, send messages, view issued books
- **Technical Expertise:** Basic computer skills
- **Security Level:** Limited

### 2.4 Operating Environment
- **Operating System:** Windows
- **Compiler:** GCC (MinGW)
- **Console:** Windows Command Prompt / PowerShell
- **Storage:** Local file system

### 2.5 Design and Implementation Constraints
- Console-based interface only (no GUI)
- Windows-specific (uses conio.h)
- Fixed maximum limits (100 books, 50 users, etc.)
- Text file-based database (no SQL)

### 2.6 Assumptions and Dependencies
- GCC compiler is installed
- User has read/write permissions for file system
- Files (books.txt, users.txt, etc.) are not corrupted
- System has adequate storage space

---

## 3. System Features

### 3.1 User Authentication

#### 3.1.1 Description
High priority. Allows users to register and login to the system.

#### 3.1.2 Functional Requirements
- **FR-1.1:** System shall allow new users to register with unique username and password
- **FR-1.2:** System shall validate username uniqueness during registration
- **FR-1.3:** System shall authenticate users during login
- **FR-1.4:** System shall distinguish between Admin and Regular users
- **FR-1.5:** System shall create default admin account on first run

### 3.2 Book Management

#### 3.2.1 Description
High priority. Allows administrators to manage book inventory.

#### 3.2.2 Functional Requirements
- **FR-2.1:** System shall allow admin to add new books with auto-generated ID
- **FR-2.2:** System shall allow admin to view all books with status
- **FR-2.3:** System shall allow admin to update book title or author
- **FR-2.4:** System shall allow admin to delete books (if not issued)
- **FR-2.5:** System shall allow admin to search books by title
- **FR-2.6:** System shall automatically save book changes to books.txt

### 3.3 Book Request System

#### 3.3.1 Description
High priority. Implements request-approval workflow for book issuing.

#### 3.3.2 Functional Requirements
- **FR-3.1:** System shall allow users to request available books
- **FR-3.2:** System shall prevent duplicate requests for same book
- **FR-3.3:** System shall store requests with status (Pending/Approved/Rejected)
- **FR-3.4:** System shall allow admin to view pending requests
- **FR-3.5:** System shall allow admin to approve or reject requests
- **FR-3.6:** System shall automatically issue book upon approval
- **FR-3.7:** System shall allow users to view their request history
- **FR-3.8:** System shall update book status when issued

### 3.4 Book Viewing

#### 3.4.1 Description
Medium priority. Allows users to view books and their issued books.

#### 3.4.2 Functional Requirements
- **FR-4.1:** System shall display all books with ID, title, author, and status
- **FR-4.2:** System shall show which books are issued and to whom (admin only)
- **FR-4.3:** System shall allow users to view books issued to them
- **FR-4.4:** System shall reload book data before display (live sync)

### 3.5 Message System

#### 3.5.1 Description
Low priority. Enables communication from users to admin.

#### 3.5.2 Functional Requirements
- **FR-5.1:** System shall allow users to send messages to admin
- **FR-5.2:** System shall store messages with username
- **FR-5.3:** System shall allow admin to view all messages
- **FR-5.4:** System shall save messages to messages.txt

### 3.6 Data Persistence

#### 3.6.1 Description
High priority. Ensures all data is saved and loaded correctly.

#### 3.6.2 Functional Requirements
- **FR-6.1:** System shall load all data from files at startup
- **FR-6.2:** System shall save data immediately after modifications
- **FR-6.3:** System shall use CSV format for all database files
- **FR-6.4:** System shall generate statistics report in project_info.txt
- **FR-6.5:** System shall handle missing files gracefully
- **FR-6.6:** System shall handle empty issuedTo fields correctly

### 3.7 System Initialization

#### 3.7.1 Description
High priority. Sets up system defaults on first run.

#### 3.7.2 Functional Requirements
- **FR-7.1:** System shall create default admin account if no users exist
- **FR-7.2:** System shall create 3 sample books if no books exist
- **FR-7.3:** System shall only initialize if data files are missing or empty

---

## 4. External Interface Requirements

### 4.1 User Interfaces

#### 4.1.1 Main Menu
```
[1] Register New User
[2] Login
[3] About Project
[0] Exit
```

#### 4.1.2 Admin Menu
```
[1] Display All Books
[2] Add New Book
[3] Update Book
[4] Delete Book
[5] Search Book
[6] View Pending Requests
[7] Approve/Reject Request
[8] View User Messages
[0] Logout
```

#### 4.1.3 User Menu
```
[1] View All Books
[2] Search Book
[3] Request a Book
[4] My Book Requests
[5] My Issued Books
[6] Send Message to Admin
[0] Logout
```

### 4.2 Hardware Interfaces
- Standard keyboard for input
- Standard display for output

### 4.3 Software Interfaces
- **File System:** Read/write access for .txt files
- **Console:** Windows console for display
- **Compiler:** GCC for compilation

### 4.4 Communication Interfaces
Not applicable (standalone application)

---

## 5. System Requirements

### 5.1 Functional Requirements Summary

| ID | Requirement | Priority |
|----|-------------|----------|
| FR-1 | User Authentication | High |
| FR-2 | Book Management (CRUD) | High |
| FR-3 | Request-Approval Workflow | High |
| FR-4 | Book Viewing | Medium |
| FR-5 | Messaging System | Low |
| FR-6 | Data Persistence | High |
| FR-7 | System Initialization | High |

---

## 6. Non-Functional Requirements

### 6.1 Performance Requirements
- **NFR-1:** System shall load all data within 2 seconds
- **NFR-2:** System shall respond to user input within 1 second
- **NFR-3:** System shall support up to 100 books
- **NFR-4:** System shall support up to 50 users
- **NFR-5:** System shall support up to 100 requests

### 6.2 Safety Requirements
- **NFR-6:** System shall save data before exit
- **NFR-7:** System shall not delete issued books
- **NFR-8:** System shall validate all user inputs
- **NFR-9:** System shall handle file errors gracefully

### 6.3 Security Requirements
- **NFR-10:** System shall require login for access
- **NFR-11:** System shall separate admin and user privileges
- **NFR-12:** System shall prevent duplicate usernames
- **NFR-13:** Passwords shall be stored in plain text (acceptable for educational project)

### 6.4 Usability Requirements
- **NFR-14:** System shall provide clear menu options
- **NFR-15:** System shall display appropriate error messages
- **NFR-16:** System shall allow users to return to menu
- **NFR-17:** System shall have beginner-friendly interface

### 6.5 Reliability Requirements
- **NFR-18:** System shall maintain data integrity
- **NFR-19:** System shall prevent data loss during crashes
- **NFR-20:** System shall auto-save after each operation

### 6.6 Maintainability Requirements
- **NFR-21:** Code shall be well-commented
- **NFR-22:** Code shall follow structured programming
- **NFR-23:** Functions shall be modular and reusable
- **NFR-24:** Code shall be easy to understand for beginners

### 6.7 Portability Requirements
- **NFR-25:** System shall run on Windows OS
- **NFR-26:** System shall be compilable with GCC
- **NFR-27:** System shall use standard C libraries where possible

---

## 7. Appendices

### Appendix A: Data Dictionary

#### Book
- **id**: String, unique identifier for book
- **title**: String, book title (max 100 chars)
- **author**: String, author name (max 100 chars)
- **isIssued**: Integer, 0=available, 1=issued
- **issuedTo**: String, username of borrower

#### User
- **username**: String, unique identifier (max 100 chars)
- **password**: String, user password (max 100 chars)
- **isAdmin**: Integer, 0=regular user, 1=admin

#### Message
- **username**: String, sender username
- **message**: String, message content (max 100 chars)

#### BookRequest
- **username**: String, requester username
- **bookId**: String, requested book ID
- **bookTitle**: String, book title for reference
- **status**: Integer, 0=pending, 1=approved, 2=rejected

---

## 8. Approval

This SRS document is approved by:

**Team Members:**
- Rian Hasan Siam
- Fabiha
- Karib

**Date:** December 5, 2025

---

**Document Version:** 1.0  
**Last Updated:** December 5, 2025
