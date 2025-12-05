# Use Case Diagram & Scenarios

## Library Management System

**Version:** 1.0  
**Date:** December 5, 2025  
**Prepared by:** Rian Hasan Siam, Fabiha, Karib

---

## Table of Contents
1. [Use Case Diagram](#1-use-case-diagram)
2. [Actors](#2-actors)
3. [Use Case List](#3-use-case-list)
4. [Detailed Use Case Scenarios](#4-detailed-use-case-scenarios)

---

## 1. Use Case Diagram

```
+------------------------------------------------------+
|         Library Management System                    |
|                                                      |
|  +---------------+                +---------------+  |
|  |               |                |               |  |
|  |     ADMIN     |                |     USER      |  |
|  |               |                |               |  |
|  +-------+-------+                +-------+-------+  |
|          |                                |          |
|          |                                |          |
|          | (Login)                        | (Login) |
|          |                                |          |
|          v                                v          |
|  +-------+--------------------------------+-------+  |
|  |         [Authenticate User]                   |  |
|  +-----------------------------------------------+  |
|          |                                |          |
|          |                                |          |
|          v                                v          |
|  +---------------+                +---------------+  |
|  | Admin Menu    |                | User Menu     |  |
|  |               |                |               |  |
|  | • Add Book    |                | • View Books  |  |
|  | • Update Book |                | • Search Book |  |
|  | • Delete Book |                | • Request Book|  |
|  | • View Books  |                | • View My     |  |
|  | • Search Book |                |   Requests    |  |
|  | • View        |                | • View My     |  |
|  |   Pending     |                |   Issued Books|  |
|  |   Requests    |                | • Send        |  |
|  | • Approve/    |                |   Message     |  |
|  |   Reject      |                |               |  |
|  |   Request     |                +-------+-------+  |
|  | • View        |                        |          |
|  |   Messages    |                        |          |
|  +-------+-------+                        |          |
|          |                                |          |
|          |                                |          |
|          v                                v          |
|  +-------+--------------------------------+-------+  |
|  |         [Database Operations]                 |  |
|  |                                               |  |
|  |  books.txt | users.txt | messages.txt |       |  |
|  |  requests.txt | project_info.txt              |  |
|  +-----------------------------------------------+  |
|                                                      |
+------------------------------------------------------+
```

### Simplified Actor-Use Case Diagram

```
        ADMIN                                      USER
          |                                         |
          |                                         |
          +---------> [Register] <-----------------+
          |                                         |
          +---------> [Login] <--------------------+
          |              |                          |
          |              v                          |
          |      [Authenticate]                     |
          |                                         |
          +---> [Add Book]                          |
          |                                         |
          +---> [Update Book]                       |
          |                                         |
          +---> [Delete Book]                       |
          |                                         |
          +---> [View All Books] <-----------------+
          |                                         |
          +---> [Search Book] <--------------------+
          |                                         |
          +---> [View Pending Requests]             |
          |                                         |
          +---> [Approve/Reject Request]            |
          |         |                               |
          |         v                               |
          |    [Auto Issue Book] <--- Include ---+  |
          |                                      |  |
          +---> [View User Messages]             |  |
          |                                      |  |
          |                              [Request Book]
          |                                      |  |
          |                                      +--+
          |                                         |
          |                              [View My Requests]
          |                                         |
          |                              [View My Issued Books]
          |                                         |
          +-------- [Send Message] <---------------+
                        |
                        v
                  [Save to Database]
```

---

## 2. Actors

### 2.1 Administrator (Admin)
**Description:** System administrator with full privileges  
**Responsibilities:**
- Manage books (add, update, delete)
- View all books with issued status
- Approve or reject book requests
- View user messages
- Access all system features

**Characteristics:**
- Has admin credentials (username: admin, password: admin123)
- Can perform all operations
- Cannot delete issued books

### 2.2 Regular User
**Description:** Library user with limited privileges  
**Responsibilities:**
- Register and login to system
- View available books
- Request books for issuing
- View personal request history
- View personally issued books
- Send messages to admin

**Characteristics:**
- Must register before login
- Cannot access admin features
- Can only request available books

### 2.3 System (Secondary Actor)
**Description:** Database and file system  
**Responsibilities:**
- Store and retrieve data
- Maintain data persistence
- Auto-save after operations
- Generate reports

---

## 3. Use Case List

| Use Case ID | Use Case Name | Actor(s) | Priority |
|-------------|---------------|----------|----------|
| UC-01 | Register New User | User, Admin | High |
| UC-02 | Login | User, Admin | High |
| UC-03 | Add Book | Admin | High |
| UC-04 | Update Book | Admin | Medium |
| UC-05 | Delete Book | Admin | Medium |
| UC-06 | View All Books | User, Admin | High |
| UC-07 | Search Book | User, Admin | Medium |
| UC-08 | Request Book | User | High |
| UC-09 | View Pending Requests | Admin | High |
| UC-10 | Approve/Reject Request | Admin | High |
| UC-11 | View My Requests | User | Medium |
| UC-12 | View My Issued Books | User | Medium |
| UC-13 | Send Message to Admin | User | Low |
| UC-14 | View User Messages | Admin | Low |
| UC-15 | Logout | User, Admin | Medium |
| UC-16 | View Project Info | User, Admin | Low |

---

## 4. Detailed Use Case Scenarios

### UC-01: Register New User

**Actor:** User, Admin  
**Preconditions:** None  
**Postconditions:** New user account created

**Basic Flow:**
1. User selects "Register New User" from main menu
2. System prompts for username
3. User enters username
4. System checks if username is unique
5. System prompts for password
6. User enters password
7. System saves user to users.txt
8. System displays success message
9. User returns to main menu

**Alternative Flows:**
- **4a. Username already exists:**
  1. System displays "Username already exists!"
  2. Returns to step 2

**Exception Flows:**
- **File write error:** System displays error and returns to menu

---

### UC-02: Login

**Actor:** User, Admin  
**Preconditions:** User must be registered  
**Postconditions:** User authenticated and directed to appropriate menu

**Basic Flow:**
1. User selects "Login" from main menu
2. System prompts for username
3. User enters username
4. System prompts for password
5. User enters password
6. System validates credentials
7. System checks user type (admin/user)
8. System displays appropriate menu

**Alternative Flows:**
- **6a. Invalid credentials:**
  1. System displays "Invalid username or password!"
  2. Returns to step 2

---

### UC-03: Add Book

**Actor:** Admin  
**Preconditions:** Admin is logged in  
**Postconditions:** New book added to library

**Basic Flow:**
1. Admin selects "Add New Book" from admin menu
2. System checks if book limit reached (MAX_BOOKS)
3. System generates new book ID
4. System prompts for book title
5. Admin enters title
6. System prompts for author name
7. Admin enters author
8. System creates book with status "available"
9. System saves to books.txt
10. System displays success message with book ID
11. Returns to admin menu

**Alternative Flows:**
- **2a. Book limit reached:**
  1. System displays "Book limit reached!"
  2. Returns to admin menu

---

### UC-08: Request Book

**Actor:** User  
**Preconditions:** User is logged in, book is available  
**Postconditions:** Request created with pending status

**Basic Flow:**
1. User selects "Request a Book" from user menu
2. System reloads book database
3. System displays all available books
4. System prompts for book ID
5. User enters book ID
6. System validates book exists and is available
7. System checks for duplicate request
8. System creates request with status "Pending"
9. System saves to requests.txt
10. System displays success message
11. Returns to user menu

**Alternative Flows:**
- **6a. Book not found:**
  1. System displays "Book not found!"
  2. Returns to step 4

- **6b. Book already issued:**
  1. System displays "Book is already issued!"
  2. Returns to step 4

- **7a. Duplicate request exists:**
  1. System displays "You have already requested this book!"
  2. Returns to user menu

**Exception Flows:**
- **Request limit reached:** System displays error

---

### UC-10: Approve/Reject Request

**Actor:** Admin  
**Preconditions:** Admin is logged in, pending requests exist  
**Postconditions:** Request status updated, book issued if approved

**Basic Flow:**
1. Admin selects "Approve/Reject Request" from admin menu
2. System loads pending requests
3. System displays all pending requests with details
4. System prompts for request number
5. Admin enters request number
6. System validates request exists
7. System prompts for action (1=Approve, 2=Reject)
8. Admin selects action
9. **If Approve:**
   - System finds book by ID
   - System marks book as issued
   - System sets issuedTo = requester username
   - System updates request status to "Approved"
   - System saves books.txt and requests.txt
   - System displays "Request approved and book issued!"
10. **If Reject:**
    - System updates request status to "Rejected"
    - System saves requests.txt
    - System displays "Request rejected!"
11. Returns to admin menu

**Alternative Flows:**
- **6a. Invalid request number:**
  1. System displays "Invalid request number!"
  2. Returns to step 4

- **9a. Book not found:**
  1. System displays error
  2. Request status not changed

---

### UC-11: View My Requests

**Actor:** User  
**Preconditions:** User is logged in  
**Postconditions:** User views their request history

**Basic Flow:**
1. User selects "My Book Requests" from user menu
2. System reloads request database
3. System filters requests by current username
4. System displays all user's requests with:
   - Book ID
   - Book Title
   - Status (Pending/Approved/Rejected)
5. User presses any key to continue
6. Returns to user menu

**Alternative Flows:**
- **3a. No requests found:**
  1. System displays "You have not made any requests!"
  2. Returns to user menu

---

### UC-12: View My Issued Books

**Actor:** User  
**Preconditions:** User is logged in  
**Postconditions:** User views books issued to them

**Basic Flow:**
1. User selects "My Issued Books" from user menu
2. System reloads book database
3. System filters books where issuedTo = username
4. System displays issued books with:
   - Book ID
   - Title
   - Author
5. User presses any key to continue
6. Returns to user menu

**Alternative Flows:**
- **3a. No issued books:**
  1. System displays "You have no issued books currently!"
  2. Returns to user menu

---

### UC-13: Send Message to Admin

**Actor:** User  
**Preconditions:** User is logged in  
**Postconditions:** Message saved and visible to admin

**Basic Flow:**
1. User selects "Send Message to Admin" from user menu
2. System checks if message limit reached (MAX_MESSAGES)
3. System prompts for message
4. User enters message
5. System saves message with username to messages.txt
6. System displays "Message sent successfully!"
7. Returns to user menu

**Alternative Flows:**
- **2a. Message limit reached:**
  1. System displays "Message limit reached!"
  2. Returns to user menu

---

### UC-05: Delete Book

**Actor:** Admin  
**Preconditions:** Admin is logged in, book exists and is not issued  
**Postconditions:** Book removed from library

**Basic Flow:**
1. Admin selects "Delete Book" from admin menu
2. System displays all books
3. System prompts for book ID
4. Admin enters book ID
5. System searches for book by ID
6. System checks if book is issued
7. System confirms deletion
8. Admin confirms
9. System removes book from array
10. System decrements book count
11. System saves to books.txt
12. System displays success message
13. Returns to admin menu

**Alternative Flows:**
- **5a. Book not found:**
  1. System displays "Book not found!"
  2. Returns to step 3

- **6a. Book is issued:**
  1. System displays "Cannot delete issued book!"
  2. Returns to admin menu

- **8a. Admin cancels:**
  1. System displays "Deletion cancelled"
  2. Returns to admin menu

---

## 5. Use Case Relationships

### Include Relationships
- **Approve Request** includes **Auto Issue Book**
  - When admin approves, book is automatically issued

### Extend Relationships
- **Add Book** extends to **Generate Book ID**
  - System auto-generates unique ID

- **Request Book** extends to **Check Availability**
  - System validates before creating request

### Generalization
- **View All Books** generalizes to:
  - Admin View (shows issued status and borrower)
  - User View (shows only availability)

---

## 6. System Sequence Diagrams

### Sequence: Request and Approve Book

```
User              System           Admin           Database
 |                  |                |                 |
 |--[Request Book]->|                |                 |
 |                  |--[Save Request]--------------->|
 |                  |                |                 |
 |<-[Success Msg]---|                |                 |
 |                  |                |                 |
 |                  |                |                 |
 |                  |      [View Pending Requests]    |
 |                  |                |                 |
 |                  |<-[Load Requests]----------------|
 |                  |                |                 |
 |                  |--[Display]---->|                 |
 |                  |                |                 |
 |                  |      [Approve Request]          |
 |                  |                |                 |
 |                  |<-[Update]------|                 |
 |                  |                |                 |
 |                  |--[Issue Book]----------------->|
 |                  |                |                 |
 |                  |--[Update Request]-------------->|
 |                  |                |                 |
 |                  |--[Success]---->|                 |
 |                  |                |                 |
```

---

## 7. Business Rules

**BR-01:** Books can only be deleted if not issued  
**BR-02:** Users cannot request books they already requested  
**BR-03:** Only available books can be requested  
**BR-04:** Book issuing happens only through request approval  
**BR-05:** Usernames must be unique  
**BR-06:** Maximum 100 books allowed  
**BR-07:** Maximum 50 users allowed  
**BR-08:** Maximum 100 requests allowed  
**BR-09:** Admin credentials: admin/admin123  
**BR-10:** Data auto-saves after each operation

---

## 8. Traceability Matrix

| Use Case | Functional Requirement | Priority |
|----------|------------------------|----------|
| UC-01 | FR-1.1, FR-1.2 | High |
| UC-02 | FR-1.3, FR-1.4 | High |
| UC-03 | FR-2.1, FR-2.6 | High |
| UC-04 | FR-2.3, FR-2.6 | Medium |
| UC-05 | FR-2.4, FR-2.6 | Medium |
| UC-06 | FR-4.1, FR-4.2 | High |
| UC-07 | FR-2.5 | Medium |
| UC-08 | FR-3.1, FR-3.2, FR-3.3 | High |
| UC-09 | FR-3.4 | High |
| UC-10 | FR-3.5, FR-3.6, FR-3.8 | High |
| UC-11 | FR-3.7 | Medium |
| UC-12 | FR-4.3 | Medium |
| UC-13 | FR-5.1, FR-5.2, FR-5.4 | Low |
| UC-14 | FR-5.3 | Low |

---

**Document Version:** 1.0  
**Last Updated:** December 5, 2025  
**Approved by:** Rian Hasan Siam, Fabiha, Karib
