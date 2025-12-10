#include <stdio.h>      
#include <stdlib.h>      // Standard library (memory allocation, system commands)
#include <string.h>      
#include <conio.h>       // Console input/output (getch function)

// Maximum limits for arrays
#define MAX_BOOKS 100       
#define MAX_USERS 50       
#define MAX_MESSAGES 50     
#define MAX_REQUESTS 100    
#define MAX_STRING 100      



// Structure to store book information
struct Book
{
    char id[20];                  // Book ID (unique identifier)
    char title[MAX_STRING];       // Book title
    char author[MAX_STRING];      // Author name
    int isIssued;                 // 0 = available, 1 = issued
    char issuedTo[MAX_STRING];    // Username of person who borrowed the book
};

// Structure to store user information
struct User
{
    char username[MAX_STRING];    // Username (unique)
    char password[MAX_STRING];    // Password
    int isAdmin;                  // 0 = regular user, 1 = admin
};

// Structure to store messages from users to admin
struct Message
{
    char username[MAX_STRING];    // Sender username
    char message[MAX_STRING];     // Message content
};

// Structure to store book issue requests
struct BookRequest
{
    char username[MAX_STRING];    // Requester username
    char bookId[20];              // Requested book ID
    char bookTitle[MAX_STRING];   // Book title
    int status;                   // 0 = pending, 1 = approved, 2 = rejected
};

/*
========================================
   GLOBAL VARIABLES
========================================
*/

// Arrays to store all data in memory
struct Book books[MAX_BOOKS];              
struct User users[MAX_USERS];              
struct Message messages[MAX_MESSAGES];     
struct BookRequest requests[MAX_REQUESTS]; 

// Counters to track number of records
int bookCount = 0;       
int userCount = 0;       
int messageCount = 0;    
int requestCount = 0;    

// Current session information
char currentUser[MAX_STRING];  // Logged in username
int isCurrentUserAdmin = 0;    // Is current user admin?

/*
========================================
   FUNCTION DECLARATIONS
========================================
*/

// Utility functions
void choice();                    // Ask user to continue or exit

// File operations
void loadAllData();               // Load all data from files
void saveAllData();               // Save all data to files


void saveBooksToFile();           // Save books to books.txt
void loadBooksFromFile();         // Load books from books.txt

void saveUsersToFile();           // Save users to users.txt
void loadUsersFromFile();         // Load users from users.txt

void saveMessagesToFile();        // Save messages to messages.txt
void loadMessagesFromFile();      // Load messages from messages.txt

void saveRequestsToFile();        // Save requests to requests.txt
void loadRequestsFromFile();      // Load requests from requests.txt

void saveProjectInfo();           // Generate project statistics report

// System functions
void viewProjectDetails();        // Show about/info page

// User management
void registerUser();              // Register new user
int loginUser();                  // Login and authenticate user

// Admin menu functions
void adminMenu();                 // Display admin panel
void displayBooks();              // Show all books (admin)
void addBook();                   // Add new book
void deleteBook();                // Delete book
void updateBook();                // Update book details
void searchBook();                // Search for books
void viewPendingRequests();       // View pending requests
void approveRequest();            // Approve or reject request

// User menu functions
void userMenu();                  // Display user panel
void viewAvailableBooks();        // View all books (user)
void viewIssuedBooks();           // View books issued to current user
void requestBook();               // Request a book
void viewMyRequests();            // View user's request history
void dropMessage();               // Send message to admin

/*
========================================
   UTILITY FUNCTIONS
========================================
*/

// Function to ask user if they want to continue or exit
void choice()
{
    printf("Press y for menu, n for exit: ");
    char ch;
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y')
    {
        system("cls");  // Clear screen
    }
    else if (ch == 'n' || ch == 'N')
    {
        printf("Thank You");
        exit(0);  // Exit program
    }
}

/*
========================================
   MAIN FUNCTION - PROGRAM ENTRY POINT
========================================
*/

int main()
{
    loadAllData();       // Load all existing data from database files
 
   int ch;
    
    while(1)
    {
        system("cls");
        printf("\n");
        printf("\t********************************************\n");
        printf("\t*                                          *\n");
        printf("\t*   LIBRARY MANAGEMENT SYSTEM              *\n");
        printf("\t*                                          *\n");
        printf("\t********************************************\n\n");
        printf("\t[1] Register New User\n");
        printf("\t[2] Login\n");
        printf("\t[3] About Project\n");
        printf("\t[0] Exit\n\n");
        printf("\t============================================\n");
        printf("\tEnter your choice: ");
        scanf("%d", &ch);
        
        if(ch == 1)
        {
            registerUser();
        }
        else if(ch == 2)
        {
            if(loginUser())
            {
                if(isCurrentUserAdmin)
                {
                    adminMenu();
                }
                else
                {
                    userMenu();
                }
            }
        }
        else if(ch == 3)
        {
            viewProjectDetails();
        }
        else if(ch == 0)
        {
            printf("\nSaving all data...\n");
            saveAllData();
            printf("Thank you for using Library Management System!\n");
            exit(0);
        }
        else
        {
            printf("\nInvalid choice! Please try again.\n");
            getchar();
            choice();
        }
    }

    return 0;
}

/*
========================================
   FILE OPERATIONS
========================================
*/

// Load all data from database files
void loadAllData()
{
    loadUsersFromFile();      // Load users from users.txt
    loadBooksFromFile();      // Load books from books.txt
    loadMessagesFromFile();   // Load messages from messages.txt
    loadRequestsFromFile();   // Load requests from requests.txt
}

// Save all data to database files
void saveAllData()
{
    saveBooksToFile();        // Save books to books.txt
    saveUsersToFile();        // Save users to users.txt
    saveMessagesToFile();     // Save messages to messages.txt
    saveRequestsToFile();     // Save requests to requests.txt
    saveProjectInfo();        // Generate statistics report
}





// Register new user
void registerUser()
{
    system("cls");
    printf("\n");
    printf("\t==========================================\n");
    printf("\t      USER REGISTRATION\n");
    printf("\t==========================================\n\n");
    
    if(userCount >= MAX_USERS)
    {
        printf("\tUser limit reached!\n");
      
        choice();
        return;
    }
    
    char username[MAX_STRING], password[MAX_STRING];
    
    printf("\tEnter username: ");
    scanf("%s", username);
    
    // Check if username already exists
    for(int i = 0; i < userCount; i++)
    {
        if(strcmp(users[i].username, username) == 0)
        {
            printf("Username already exists! Please try another.\n");
          
            choice();
            return;
        }
    }
    
    printf("Enter password: ");
    scanf("%s", password);
    
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].isAdmin = 0;
    userCount++;
    
    saveUsersToFile();  // Save to file immediately
    
    printf("\nRegistration successful!\n");
    choice();
}

// Login user
int loginUser()
{
    system("cls");
    printf("\n");
    printf("\t==========================================\n");
    printf("\t           LOGIN\n");
    printf("\t==========================================\n\n");
    
    char username[MAX_STRING], password[MAX_STRING];
    
    printf("\tUsername: ");
    scanf("%s", username);
    printf("\tPassword: ");
    scanf("%s", password);
    
    for(int i = 0; i < userCount; i++)
    {
        if(strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            strcpy(currentUser, username);
            isCurrentUserAdmin = users[i].isAdmin;
            printf("\n\t>> Login Successful! Welcome %s\n", username);
            printf("\tPress Enter to continue...");
            getch();
            return 1;
        }
    }
    
    printf("\n\t>> Invalid username or password!\n");
    printf("\tPress Enter to continue...");
    getch();
    return 0;
}

// View project details
void viewProjectDetails()
{
    system("cls");
    printf("\n");
    printf("\t==========================================\n");
    printf("\t      ABOUT THIS PROJECT\n");
    printf("\t==========================================\n\n");
    printf("\tProject Name: Library Management System\n");
    printf("\tLanguage: C Programming\n");
    printf("\tAuthor: Rian || Fabiha || Karib\n\n");
    printf("\t------------------------------------------\n");
    printf("\tFeatures:\n");
    printf("\t------------------------------------------\n");
    printf("\t* User Registration & Login\n");
    printf("\t* Book Management (Add/Update/Delete)\n");
    printf("\t* Book Request System\n");
    printf("\t* User Messaging System\n");
    printf("\t* Live Database Connection\n\n");
    printf("\t------------------------------------------\n");
    printf("\tDefault Admin Login:\n");
    printf("\t------------------------------------------\n");
    printf("\tUsername: admin\n");
    printf("\tPassword: admin123\n");
    printf("\t==========================================\n\n");
    getchar();
    choice();
}

// Admin Menu
void adminMenu()
{
    int ch;
    
    while(1)
    {
        system("cls");
        printf("\n");
        printf("\t==========================================\n");
        printf("\t        ADMIN PANEL\n");
        printf("\t==========================================\n\n");
        printf("\t[1] Display All Books\n");
        printf("\t[2] Add New Book\n");
        printf("\t[3] Update Book\n");
        printf("\t[4] Delete Book\n");
        printf("\t[5] Search Book\n");
        printf("\t[6] View Pending Requests\n");
        printf("\t[7] Approve/Reject Request\n");
        printf("\t[8] View User Messages\n");
        printf("\t[0] Logout\n\n");
        printf("\t==========================================\n");
        printf("\tEnter choice: ");
        scanf("%d", &ch);
        
        switch(ch)
        {
            case 1:
                displayBooks();
                break;
            case 2:
                addBook();
                break;
            case 3:
                updateBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                searchBook();
                break;
            case 6:
                viewPendingRequests();
                break;
            case 7:
                approveRequest();
                break;
            case 8:
                loadMessagesFromFile();
                system("cls");
                printf("\n\t==========================================\n");
                printf("\t       MESSAGES FROM USERS\n");
                printf("\t==========================================\n\n");
                if(messageCount == 0)
                {
                    printf("\tNo messages yet.\n");
                }
                else
                {
                    for(int i = 0; i < messageCount; i++)
                    {
                        printf("\t%d. From: %s\n", i+1, messages[i].username);
                        printf("\t   Message: %s\n\n", messages[i].message);
                    }
                }
                printf("\n");
                getchar();
                choice();
                break;
            case 0:
                return;
            default:
                printf("\nInvalid choice!\n");
                getchar();
                choice();
        }
    }
}

// User Menu
void userMenu()
{
    int ch;
    
    while(1)
    {
        system("cls");
        printf("\n");
        printf("\t==========================================\n");
        printf("\t        USER PANEL\n");
        printf("\t==========================================\n\n");
        printf("\t[1] View All Books\n");
        printf("\t[2] Search Book\n");
        printf("\t[3] Request a Book\n");
        printf("\t[4] My Book Requests\n");
        printf("\t[5] My Issued Books\n");
        printf("\t[6] Send Message to Admin\n");
        printf("\t[0] Logout\n\n");
        printf("\t==========================================\n");
        printf("\tEnter choice: ");
        scanf("%d", &ch);
        
        switch(ch)
        {
            case 1:
                viewAvailableBooks();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                requestBook();
                break;
            case 4:
                viewMyRequests();
                break;
            case 5:
                viewIssuedBooks();
                break;
            case 6:
                dropMessage();
                break;
            case 0:
                return;
            default:
                printf("\nInvalid choice!\n");
                getchar();
                choice();
        }
    }
}

// Display all books
void displayBooks()
{
    loadBooksFromFile();
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        ALL BOOKS\n");
    printf("\t==========================================\n\n");
    
    if(bookCount == 0)
    {
        printf("\tNo books available.\n");
    }
    else
    {
        printf("\t%-5s %-25s %-20s %-12s\n", "ID", "Title", "Author", "Status");
        printf("\t------------------------------------------------------------\n");
        for(int i = 0; i < bookCount; i++)
        {
            printf("\t%-5s %-25s %-20s %-12s\n", 
                   books[i].id, 
                   books[i].title, 
                   books[i].author,
                   books[i].isIssued ? "Issued" : "Available");
        }
    }
    printf("\n");
    getchar();
    choice();
}

// Add new book
void addBook()
{
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        ADD NEW BOOK\n");
    printf("\t==========================================\n\n");
    
    if(bookCount >= MAX_BOOKS)
    {
        printf("\tBook limit reached!\n");
        getchar();
        choice();
        return;
    }
    
    char id[20];
    sprintf(id, "%d", bookCount + 1);
    strcpy(books[bookCount].id, id);
    
    getchar();
    printf("\tBook Title: ");
    gets(books[bookCount].title);
    
    printf("\tAuthor Name: ");
    gets(books[bookCount].author);
    
    books[bookCount].isIssued = 0;
    strcpy(books[bookCount].issuedTo, "");
    
    bookCount++;
    saveBooksToFile();
    
    printf("\n\t>> Book added successfully!\n\n");
    choice();
}

// Delete book
void deleteBook()
{
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        DELETE BOOK\n");
    printf("\t==========================================\n\n");
    
    char search_id[20];
    printf("\tEnter Book ID: ");
    scanf("%s", search_id);
    
    int found = 0;
    for(int i = 0; i < bookCount; i++)
    {
        if(strcmp(books[i].id, search_id) == 0)
        {
            found = 1;
            
            if(books[i].isIssued)
            {
                printf("\n\t>> Cannot delete! Book is issued.\n\n");
                getchar();
                choice();
                return;
            }
            
            for(int j = i; j < bookCount - 1; j++)
            {
                books[j] = books[j + 1];
            }
            bookCount--;
            saveBooksToFile();
            printf("\n\t>> Book deleted successfully!\n\n");
            break;
        }
    }
    
    if(!found)
    {
        printf("\n\t>> Book not found!\n\n");
    }
    getchar();
    choice();
}

// Update book
void updateBook()
{
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        UPDATE BOOK\n");
    printf("\t==========================================\n\n");
    
    char search_id[20];
    int ch;
    printf("\tEnter Book ID: ");
    getchar();
    gets(search_id);
    
    int found = 0;
    for(int i = 0; i < bookCount; i++)
    {
        if(strcmp(books[i].id, search_id) == 0)
        {
            found = 1;
            printf("\n\tUpdate Options:\n");
            printf("\t[1] Book Title\n");
            printf("\t[2] Author Name\n");
            printf("\tChoice: ");
            scanf("%d", &ch);
            getchar();
            
            if(ch == 1)
            {
                printf("\tNew Title: ");
                gets(books[i].title);
            }
            else if(ch == 2)
            {
                printf("\tNew Author: ");
                gets(books[i].author);
            }
            else
            {
                printf("\n\t>> Invalid choice!\n\n");
                choice();
                return;
            }
            saveBooksToFile();
            printf("\n\t>> Book updated successfully!\n\n");
            break;
        }
    }
    
    if(!found)
    {
        printf("\n\t>> Book not found!\n\n");
    }
    choice();
}

// Search book
void searchBook()
{
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        SEARCH BOOK\n");
    printf("\t==========================================\n\n");
    
    if(bookCount == 0)
    {
        printf("\tNo books available.\n\n");
        getchar();
        choice();
        return;
    }
    
    char search_title[MAX_STRING];
    printf("\tEnter Book Title: ");
    getchar();
    gets(search_title);
    
    int found = 0;
    for(int i = 0; i < bookCount; i++)
    {
        if(strstr(books[i].title, search_title) != NULL)
        {
            if(found == 0)
            {
                printf("\n\t>> Search Results:\n\n");
                printf("\t%-5s %-25s %-20s %-12s\n", "ID", "Title", "Author", "Status");
                printf("\t------------------------------------------------------------\n");
            }


            found = 1;
            printf("\t%-5s %-25s %-20s %-12s\n",
                   books[i].id, 
                   books[i].title, 
                   books[i].author,
                   books[i].isIssued ? "Issued" : "Available");
        }
    }
    
    if(!found)
    {
        printf("\n\t>> Book not found!\n");
    }
    printf("\n");
    choice();
}

// Issue book to user
// View available books (User)
void viewAvailableBooks()
{
    loadBooksFromFile();
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        ALL BOOKS\n");
    printf("\t==========================================\n\n");
    
    int count = 0;
    if(bookCount == 0)
    {
        printf("\tNo books available.\n");
    }
    else
    {
        printf("\t%-5s %-25s %-20s %-12s\n", "ID", "Title", "Author", "Status");
        printf("\t------------------------------------------------------------\n");
        for(int i = 0; i < bookCount; i++)
        {
            printf("\t%-5s %-25s %-20s %-12s\n", 
                   books[i].id, 
                   books[i].title, 
                   books[i].author,
                   books[i].isIssued ? "Issued" : "Available");
            count++;
        }
    }
    
    if(count == 0)
    {
        printf("\tNo books available.\n");
    }
    printf("\n");
    getchar();
    choice();
}

// View issued books (User)
void viewIssuedBooks()
{
    loadBooksFromFile();
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        MY ISSUED BOOKS\n");
    printf("\t==========================================\n\n");
    
    int count = 0;
    printf("\t%-5s %-25s %-20s\n", "ID", "Title", "Author");
    printf("\t----------------------------------------------------\n");
    for(int i = 0; i < bookCount; i++)
    {
        if(books[i].isIssued && strcmp(books[i].issuedTo, currentUser) == 0)
        {
            printf("\t%-5s %-25s %-20s\n",  books[i].id, books[i].title, books[i].author);
            count++;
        }
    }
    
    if(count == 0)
    {
        printf("\tNo books issued to you.\n");
    }
    printf("\n");
    getchar();
    choice();
}

// Drop message to admin
void dropMessage()
{
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t      SEND MESSAGE TO ADMIN\n");
    printf("\t==========================================\n\n");
    
    if(messageCount >= MAX_MESSAGES)
    {
        printf("\tMessage limit reached!\n\n");
        getchar();
        choice();
        return;
    }
    
    strcpy(messages[messageCount].username, currentUser);
    
    getchar();
    printf("\tYour Message: ");
    gets(messages[messageCount].message);
    
    messageCount++;
    saveMessagesToFile();
    
    printf("\n\t>> Message sent successfully!\n\n");
    choice();
}

// Request a book (User)
void requestBook()
{
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        REQUEST A BOOK\n");
    printf("\t==========================================\n\n");
    
    if(requestCount >= MAX_REQUESTS)
    {
        printf("\tRequest limit reached!\n\n");
        getchar();
        choice();
        return;
    }
    
    char search_id[20];
    printf("\tEnter Book ID: ");
    scanf("%s", search_id);
    
    int found = 0;
    for(int i = 0; i < bookCount; i++)
    {
        if(strcmp(books[i].id, search_id) == 0)
        {
            found = 1;
            
            if(books[i].isIssued)
            {
                printf("\n\t>> Book is currently issued!\n\n");
                getchar();
                choice();
                return;
            }
            
            // Check duplicate request
            for(int j = 0; j < requestCount; j++)
            {
                if(strcmp(requests[j].username, currentUser) == 0 && strcmp(requests[j].bookId, search_id) == 0 && 
                   requests[j].status == 0)
                {
                    printf("\n\t>> You already requested this book!\n\n");
                    getchar();
                    choice();
                    return;
                }
            }
            
            strcpy(requests[requestCount].username, currentUser);
            strcpy(requests[requestCount].bookId, books[i].id);
            strcpy(requests[requestCount].bookTitle, books[i].title);
            requests[requestCount].status = 0;
            requestCount++;
            
            saveRequestsToFile();
            
            printf("\n\t>> Request submitted successfully!\n");
            printf("\t   Wait for admin approval.\n\n");
            break;
        }
    }
    
    if(!found)
    {
        printf("\n\t>> Book not found!\n\n");
    }
    getchar();
    choice();
}

// View my requests (User)
void viewMyRequests()
{
    loadRequestsFromFile();
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t        MY BOOK REQUESTS\n");
    printf("\t==========================================\n\n");
    
    int count = 0;
    printf("\t%-10s %-25s %-15s\n", "Book ID", "Book Title", "Status");
    printf("\t----------------------------------------------------\n");
    for(int i = 0; i < requestCount; i++)
    {
        if(strcmp(requests[i].username, currentUser) == 0)
        {
            char *status;
            if(requests[i].status == 0) status = "Pending";
            else if(requests[i].status == 1) status = "Approved";
            else status = "Rejected";
            
            printf("\t%-10s %-25s %-15s\n", 
                   requests[i].bookId,
                   requests[i].bookTitle,
                   status);
            count++;
        }
    }
    
    if(count == 0)
    {
        printf("\tNo requests yet.\n");
    }
    printf("\n");
    getchar();
    choice();
}

// View pending requests (Admin)
void viewPendingRequests()
{
    loadRequestsFromFile();
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t      PENDING BOOK REQUESTS\n");
    printf("\t==========================================\n\n");
    
    int count = 0;
    printf("\t%-5s %-15s %-25s %-10s\n", "No.", "Username", "Book Title", "Book ID");
    printf("\t------------------------------------------------------------\n");
    for(int i = 0; i < requestCount; i++)
    {
        if(requests[i].status == 0)
        {
            printf("\t%-5d %-15s %-25s %-10s\n", 
                   i+1,
                   requests[i].username,
                   requests[i].bookTitle,
                   requests[i].bookId);
            count++;
        }
    }
    
    if(count == 0)
    {
        printf("\tNo pending requests.\n");
    }
    printf("\n");
    getchar();
    choice();
}

// Approve or reject request (Admin)
void approveRequest()
{
    loadRequestsFromFile();
    loadBooksFromFile();
    system("cls");
    printf("\n\t==========================================\n");
    printf("\t    APPROVE/REJECT REQUEST\n");
    printf("\t==========================================\n\n");
    
    int count = 0;
    printf("\t%-5s %-15s %-25s %-10s\n", "No.", "Username", "Book Title", "Book ID");
    printf("\t------------------------------------------------------------\n");
    for(int i = 0; i < requestCount; i++)
    {
        if(requests[i].status == 0)
        {
            printf("\t%-5d %-15s %-25s %-10s\n", 
                   count+1,
                   requests[i].username,
                   requests[i].bookTitle,
                   requests[i].bookId);
            count++;
        }
    }
    
    if(count == 0)
    {
        printf("\n\tNo pending requests.\n\n");
        getchar();
        choice();
        return;
    }
    
    int requestNo;
    printf("\n\tEnter Request Number: ");
    scanf("%d", &requestNo);
    
    if(requestNo < 1 || requestNo > count)
    {
        printf("\n\t>> Invalid request number!\n\n");
        getchar();
        choice();
        return;
    }
    
    // Find request by pending number
    int pendingNum = 0;
    int actualIndex = -1;
    for(int i = 0; i < requestCount; i++)
    {
        if(requests[i].status == 0)
        {
            pendingNum++;
            if(pendingNum == requestNo)
            {
                actualIndex = i;
                break;
            }
        }
    }
    
    int action;
    printf("\n\t[1] Approve\n\t[2] Reject\n\tChoice: ");
    scanf("%d", &action);
    
    if(action == 1)
    {
        // Find and issue book
        for(int i = 0; i < bookCount; i++)
        {
            if(strcmp(books[i].id, requests[actualIndex].bookId) == 0)
            {
                if(books[i].isIssued)
                {
                    printf("\n\t>> Book already issued!\n\n");
                    requests[actualIndex].status = 2;
                }
                else
                {
                    books[i].isIssued = 1;
                    strcpy(books[i].issuedTo, requests[actualIndex].username);
                    requests[actualIndex].status = 1;
                    saveBooksToFile();
                    printf("\n\t>> Request approved! Book issued.\n\n");
                }
                break;
            }
        }
    }
    else if(action == 2)
    {
        requests[actualIndex].status = 2;
        printf("\n\t>> Request rejected!\n\n");
    }
    else
    {
        printf("\n\t>> Invalid choice!\n\n");
        getchar();
        choice();
        return;
    }
    
    saveRequestsToFile();
    getchar();
    choice();
}

// Save books to file
void saveBooksToFile()
{
    FILE *fp;
    fp = fopen("books.txt", "w");
    if(fp == NULL)
    {
        printf("Error saving books!\n");
        return;
    }
    for(int i = 0; i < bookCount; i++)
    {
        fprintf(fp, "%s,%s,%s,%d,%s\n", books[i].id, books[i].title, books[i].author,  books[i].isIssued, books[i].issuedTo);
    }
    fclose(fp);
}

// Load books from file
void loadBooksFromFile()
{
    FILE *fp;
    fp = fopen("books.txt", "r");
    if(fp == NULL)
    {
        return;
    }
    
    bookCount = 0;
    char line[500];
    while(bookCount < MAX_BOOKS && fgets(line, sizeof(line), fp) != NULL)
    {
        int result = sscanf(line, "%[^,],%[^,],%[^,],%d,%[^\n]",books[bookCount].id, books[bookCount].title,  books[bookCount].author, &books[bookCount].isIssued,books[bookCount].issuedTo);
        
        if(result >= 4)
        {
            if(result == 4)
            {
                strcpy(books[bookCount].issuedTo, "");
            }
            bookCount++;
        }
    }
    fclose(fp);
}



// Save users to file
void saveUsersToFile()
{
    FILE *fp;
    fp = fopen("users.txt", "w");
    if(fp == NULL)
    {
        printf("Error saving users!\n");
        return;
    }


    for(int i = 0; i < userCount; i++)
    {
        fprintf(fp, "%s,%s,%d\n", users[i].username, users[i].password, users[i].isAdmin);
    }
    fclose(fp);
}


// Load users from file
void loadUsersFromFile()
{
    FILE *fp;
    fp = fopen("users.txt", "r");
    if(fp == NULL)
    {
        return;  // File doesn't exist yet, that's okay
    }
    
    userCount = 0;
    while(userCount < MAX_USERS && 
          fscanf(fp, "%[^,],%[^,],%d\n", users[userCount].username,  users[userCount].password,&users[userCount].isAdmin) == 3)
    {
        userCount++;
    }
    fclose(fp);
}



// Save messages to file
void saveMessagesToFile()
{
    FILE *fp;
    fp = fopen("messages.txt", "w");
    if(fp == NULL)
    {
        printf("Error saving messages!\n");
        return;
    }
    for(int i = 0; i < messageCount; i++)
    {
        fprintf(fp, "%s,%s\n", 
                messages[i].username, 
                messages[i].message);
    }
    fclose(fp);
}

// Load messages from file
void loadMessagesFromFile()
{
    FILE *fp;
    fp = fopen("messages.txt", "r");
    if(fp == NULL)
    {
        return;  // File doesn't exist yet, that's okay
    }
    
    messageCount = 0;
    while(messageCount < MAX_MESSAGES && 
          fscanf(fp, "%[^,],%[^\n]\n",
                 messages[messageCount].username, 
                 messages[messageCount].message) == 2)
    {
        messageCount++;
    }
    fclose(fp);
}



// Save requests to file
void saveRequestsToFile()
{
    FILE *fp;
    fp = fopen("requests.txt", "w");
    if(fp == NULL)
    {
        printf("Error saving requests!\n");
        return;
    }
    for(int i = 0; i < requestCount; i++)
    {
        fprintf(fp, "%s,%s,%s,%d\n", 
                requests[i].username, 
                requests[i].bookId,
                requests[i].bookTitle,
                requests[i].status);
    }
    fclose(fp);
}

// Load requests from file
void loadRequestsFromFile()
{
    FILE *fp;
    fp = fopen("requests.txt", "r");
    if(fp == NULL)
    {
        return;  // File doesn't exist yet, that's okay
    }
    
    requestCount = 0;
    while(requestCount < MAX_REQUESTS && 
          fscanf(fp, "%[^,],%[^,],%[^,],%d\n",
                 requests[requestCount].username, 
                 requests[requestCount].bookId,
                 requests[requestCount].bookTitle,
                 &requests[requestCount].status) == 4)
    {
        requestCount++;
    }
    fclose(fp);
}

// Save project information and statistics
void saveProjectInfo()
{
    FILE *fp;
    fp = fopen("project_info.txt", "w");
    if(fp == NULL)
    {
        printf("Error saving project information!\n");
        return;
    }
    
    // Header
    fprintf(fp, "========================================\n");
    fprintf(fp, "   LIBRARY MANAGEMENT SYSTEM\n");
    fprintf(fp, "   PROJECT DATABASE INFORMATION\n");
    fprintf(fp, "========================================\n\n");
    
    // Project Details
    fprintf(fp, "Project Name: Library Management System\n");
    fprintf(fp, "Language: C Programming\n");
    fprintf(fp, "Version: 1.0\n");
    fprintf(fp, "Date: December 3, 2025\n\n");
    
    // System Statistics
    fprintf(fp, "========================================\n");
    fprintf(fp, "   SYSTEM STATISTICS\n");
    fprintf(fp, "========================================\n");
    fprintf(fp, "Total Books: %d\n", bookCount);
    fprintf(fp, "Total Users: %d\n", userCount);
    fprintf(fp, "Total Messages: %d\n", messageCount);
    fprintf(fp, "Total Requests: %d\n\n", requestCount);
    
    // Books Statistics
    int availableBooks = 0, issuedBooks = 0;
    for(int i = 0; i < bookCount; i++)
    {
        if(books[i].isIssued)
            issuedBooks++;
        else
            availableBooks++;
    }
    fprintf(fp, "Available Books: %d\n", availableBooks);
    fprintf(fp, "Issued Books: %d\n\n", issuedBooks);
    
    // User Statistics
    int adminCount = 0, regularUsers = 0;
    for(int i = 0; i < userCount; i++)
    {
        if(users[i].isAdmin)
            adminCount++;
        else
            regularUsers++;
    }
    fprintf(fp, "Admin Users: %d\n", adminCount);
    fprintf(fp, "Regular Users: %d\n\n", regularUsers);
    
    // Request Statistics
    int pendingReq = 0, approvedReq = 0, rejectedReq = 0;
    for(int i = 0; i < requestCount; i++)
    {
        if(requests[i].status == 0)
            pendingReq++;
        else if(requests[i].status == 1)
            approvedReq++;
        else
            rejectedReq++;
    }
    fprintf(fp, "Pending Requests: %d\n", pendingReq);
    fprintf(fp, "Approved Requests: %d\n", approvedReq);
    fprintf(fp, "Rejected Requests: %d\n\n", rejectedReq);
    
    // All Books List
    fprintf(fp, "========================================\n");
    fprintf(fp, "   ALL BOOKS IN LIBRARY\n");
    fprintf(fp, "========================================\n");
    for(int i = 0; i < bookCount; i++)
    {
        fprintf(fp, "ID: %s\n", books[i].id);
        fprintf(fp, "Title: %s\n", books[i].title);
        fprintf(fp, "Author: %s\n", books[i].author);
        fprintf(fp, "Status: %s\n", books[i].isIssued ? "Issued" : "Available");
        if(books[i].isIssued)
            fprintf(fp, "Issued To: %s\n", books[i].issuedTo);
        fprintf(fp, "\n");
    }
    
    // All Users List
    fprintf(fp, "========================================\n");
    fprintf(fp, "   ALL REGISTERED USERS\n");
    fprintf(fp, "========================================\n");
    for(int i = 0; i < userCount; i++)
    {
        fprintf(fp, "Username: %s\n", users[i].username);
        fprintf(fp, "Type: %s\n", users[i].isAdmin ? "Admin" : "Regular User");
        fprintf(fp, "\n");
    }
    
    // All Requests List
    if(requestCount > 0)
    {
        fprintf(fp, "========================================\n");
        fprintf(fp, "   ALL BOOK REQUESTS\n");
        fprintf(fp, "========================================\n");
        for(int i = 0; i < requestCount; i++)
        {
            fprintf(fp, "User: %s\n", requests[i].username);
            fprintf(fp, "Book: %s (ID: %s)\n", requests[i].bookTitle, requests[i].bookId);
            char *status;
            if(requests[i].status == 0) status = "Pending";
            else if(requests[i].status == 1) status = "Approved";
            else status = "Rejected";
            fprintf(fp, "Status: %s\n", status);
            fprintf(fp, "\n");
        }
    }
    
    // Footer
    fprintf(fp, "========================================\n");
    fprintf(fp, "   END OF PROJECT DATABASE\n");
    fprintf(fp, "========================================\n");
    
    fclose(fp);
}

// Clear screen

