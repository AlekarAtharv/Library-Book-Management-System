#include <stdio.h>
#include <stdlib.h>

// Structure
struct Book {
    int id;
    char name[100];
    char author[100];
    struct Book* next;
};

struct Book* head = NULL;

// Add Book
void addBook() {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));

    printf("Enter Book ID: ");
    scanf("%d", &newBook->id);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", newBook->name);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", newBook->author);

    newBook->next = NULL;

    if (head == NULL) {
        head = newBook;
    } else {
        struct Book* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }

    printf("Book Added Successfully!\n");
}

// Display Books
void displayBooks() {
    struct Book* temp = head;

    if (temp == NULL) {
        printf("No books available.\n");
        return;
    }

    while (temp != NULL) {
        printf("\nID: %d", temp->id);
        printf("\nBook Name: %s", temp->name);
        printf("\nAuthor: %s\n", temp->author);
        temp = temp->next;
    }
}

// Search Book
void searchBook() {
    int id, found = 0;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    struct Book* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nBook Found!\n");
            printf("Book Name: %s\n", temp->name);
            printf("Author: %s\n", temp->author);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (found == 0) {
        printf("Book not found.\n");
    }
}

// Delete Book
void deleteBook() {
    int id;

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    struct Book *temp = head, *prev = NULL;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        printf("Book Deleted.\n");
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Book not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);

    printf("Book Deleted.\n");
}

// Main Function
int main() {
    int choice;

    do {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
