#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Define a structure for a book
struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
    int issued;
    char due_date[20];
};

//capatalize 
void capitalize(char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

// Function to add a book to the library
void addBook(struct Book books[], int *num_books) {
    printf("Enter the ID of the book: ");
    scanf("%d", &books[*num_books].id);
    
    printf("Enter the title of the book: ");
    getchar(); 
    fgets(books[*num_books].title, sizeof(books[*num_books].title), stdin);
    books[*num_books].title[strcspn(books[*num_books].title, "\n")] = '\0'; 
    capitalize(books[*num_books].title);
    
    printf("Enter the author of the book: ");
    fgets(books[*num_books].author, sizeof(books[*num_books].author), stdin);
    books[*num_books].author[strcspn(books[*num_books].author, "\n")] = '\0'; 
    capitalize(books[*num_books].author);
    
    printf("Enter the quantity of the book: ");
    scanf("%d", &books[*num_books].quantity);
    books[*num_books].issued = 0;
    time_t t = time(NULL);
    strcpy(books[*num_books].due_date, ctime(&t));
    (*num_books)++;
}

// Function to issue a book to a user
void issueBook(struct Book books[], int num_books) {
    int id, i;
    printf("Enter the ID of the book: ");
    scanf("%d", &id);
    for (i = 0; i < num_books; i++) {
        if (books[i].id == id && books[i].quantity > 0 && books[i].issued == 0) {
            books[i].issued = 1;
            books[i].quantity--;
            printf("Book issued successfully.\n");
            return;
        }
    }
    printf("Book not available or already issued.\n");
}

// Function to return a book to the library
void returnBook(struct Book books[], int num_books) {
    int id, i;
    printf("Enter the ID of the book: ");
    scanf("%d", &id);
    for (i = 0; i < num_books; i++) {
        if (books[i].id == id && books[i].issued == 1) {
            books[i].issued = 0;
            books[i].quantity++;
            printf("Book returned successfully.\n");
            return;
        }
    }
    printf("Book not issued or not found.\n");
}

// Function to display the details of all the books in the library
void displayBooks(struct Book books[], int num_books) {
    int i;
    int choice;
    int id;
    char title[100];
    char author[100];
    
    printf("Search book by:\n(1) ID\n(2) Name\n(3)Author\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter the ID of the book: ");
        scanf("%d", &id);
        
        int found = 0; // Flag to indicate if book is found
        
        for (i = 0; i < num_books; i++) {
            if (books[i].id == id) {
                printf("ID: %d\n", books[i].id);
                printf("Title: %s\n", books[i].title);
                printf("Author: %s\n", books[i].author);
                printf("Quantity: %d\n", books[i].quantity);
                if (books[i].issued == 1) {
                    printf("Status: Issued\n");
                } else {
                    printf("Status: Available\n");
                    printf("Due Date: %s\n", books[i].due_date);
                }
                printf("\n");
                found = 1;
                break; // Stop searching once the book is found
            }
        }
        
        if (!found) {
            printf("BOOK NOT FOUND!!!\n");
        }
    } 
    else if (choice == 2) {
        printf("Enter the title of the book: ");
        scanf(" %[^\n]", title);
        capitalize(title);
        
        int found = 0; // Flag to indicate if book is found
        
        for (i = 0; i < num_books; i++) {
            if (strcmp(books[i].title, title) == 0) {
                printf("ID: %d\n", books[i].id);
                printf("Title: %s\n", books[i].title);
                printf("Author: %s\n", books[i].author);
                printf("Quantity: %d\n", books[i].quantity);
                if (books[i].issued == 1) {
                    printf("Status: Issued\n");
                } 
                else {
                    printf("Status: Available\n");
                    printf("Due Date: %s\n", books[i].due_date);
                }
                printf("\n");
                found = 1;
            }
        }
        
        if (!found) {
            printf("BOOK NOT FOUND!!!\n");
        }
    }
    else if (choice == 3) {
        printf("Enter the author of the book: ");
        scanf(" %[^\n]", author);
        capitalize(author);
        
        int found = 0; // Flag to indicate if book is found
        
        for (i = 0; i < num_books; i++) {
            if (strcmp(books[i].author, author) == 0) {
                printf("ID: %d\n", books[i].id);
                printf("Title: %s\n", books[i].title);
                printf("Author: %s\n", books[i].author);
                printf("Quantity: %d\n", books[i].quantity);
                if (books[i].issued == 1) {
                    printf("Status: Issued\n");
                } 
                else {
                    printf("Status: Available\n");
                    printf("Due Date: %s\n", books[i].due_date);
                }
                printf("\n");
                found = 1;
                 }
                if (!found) {
            printf("BOOK NOT FOUND!!!\n");
                            }
            }
        } 
            
}

int main() {
    struct Book books[100];
    int num_books = 0;
    int choice;

    do {
        printf("Library Management System\n");
        printf("1. Add Book\n");
        printf("2. Issue Book\n");
        printf("3. Return Book\n");
        printf("4. Display Books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &num_books);
                break;
            case 2:
                issueBook(books, num_books);
                break;
            case 3:
                returnBook(books, num_books);
                break;
            case 4:
                displayBooks(books, num_books);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}