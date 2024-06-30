#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_STRING_LENGTH 150

typedef struct {
    char acquisition_date[MAX_STRING_LENGTH];
    int book_id;
    char title[MAX_STRING_LENGTH];
    char author[MAX_STRING_LENGTH];
    char publication_date[MAX_STRING_LENGTH];
    char genre[MAX_STRING_LENGTH];
    char ISBN[MAX_STRING_LENGTH];
    int quantity_available;
} Book;

void addBook(Book *book) {
    FILE *file = fopen("library.txt", "a+");
    if (file != NULL) {
        fprintf(file, "%s %d %s %s %s %s %s %d\n",
                book->acquisition_date, book->book_id, book->title, book->author,
                book->publication_date, book->genre, book->ISBN, book->quantity_available);
        fclose(file);
        printf("Book is added\n");
    } else {
        printf("Can't open file\n");
    }
}

void displayBook(const Book *book) {
    printf("Book ID: %d\n", book->book_id);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Quantity: %d\n\n", book->quantity_available);
}

void checkBookDetailsById(int book_id) {
    FILE *file = fopen("library.txt", "r");
    if (file != NULL) {
        Book book;
        int found = 0;
        while (fscanf(file, "%s %d %s %s %s %s %s %d\n",
                      book.acquisition_date, &book.book_id, book.title, book.author,
                      book.publication_date, book.genre, book.ISBN, &book.quantity_available) == 8) {
            if (book.book_id == book_id) {
                displayBook(&book);
                found = 1;
                break;
            }
        }
        fclose(file);
        if (!found) {
            printf("Book not found\n");
        }
    } else {
        printf("Can't open file\n");
    }
}

void removeExistingBookRecord(int book_id) {
    FILE *file = fopen("library.txt", "r+");
    if (file != NULL) {
        Book book;
        int found = 0;
        while (fscanf(file, "%s %d %s %s %s %s %s %d\n",
                      book.acquisition_date, &book.book_id, book.title, book.author,
                      book.publication_date, book.genre, book.ISBN, &book.quantity_available) == 8) {
            if (book.book_id == book_id) {
                book.quantity_available = 0;
                fseek(file, -sizeof(Book), SEEK_CUR);
                fprintf(file, "%s %d %s %s %s %s %s %d\n",
                        book.acquisition_date, book.book_id, book.title, book.author,
                        book.publication_date, book.genre, book.ISBN, book.quantity_available);
                found = 1;
                printf("Book removed\n");
                break;
            }
        }
        fclose(file);
        if (!found) {
            printf("Book not found\n");
        }
    } else {
        printf("Can't open file\n");
    }
}

void viewLibraryCatalog() {
    FILE *file = fopen("library.txt", "r");
    if (file != NULL) {
        Book book;
        while (fscanf(file, "%s %d %s %s %s %s %s %d\n",
                      book.acquisition_date, &book.book_id, book.title, book.author,
                      book.publication_date, book.genre, book.ISBN, &book.quantity_available) == 8) {
            displayBook(&book);
        }
        fclose(file);
    } else {
        printf("Can't open file\n");
    }
}

int main() {
    Book books[MAX_BOOKS];
    int count = 0;

    while (1) {
        int choice;
        printf("\n1. Add Book\n2. Check Book Details\n3. Remove Book Record\n4. View Library Catalog\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (count < MAX_BOOKS) {
                    printf("Adding book details\n");
                    printf("Acquisition Date (dd/mm/yyyy): ");
                    scanf("%s", books[count].acquisition_date);

                    printf("Book ID: ");
                    scanf("%d", &books[count].book_id);

                    printf("Title: ");
                    scanf("%s", books[count].title);

                    printf("Author: ");
                    scanf("%s", books[count].author);

                    printf("Publication Date (dd/mm/yyyy): ");
                    scanf("%s", books[count].publication_date);

                    printf("Genre: ");
                    scanf("%s", books[count].genre);

                    printf("ISBN: ");
                    scanf("%s", books[count].ISBN);

                    printf("Quantity: ");
                    scanf("%d", &books[count].quantity_available);

                    addBook(&books[count]);
                    count++;
                } else {
                    printf("Maximum books reached.\n");
                }
                break;
            }
            case 2: {
                int book_id;
                printf("Enter Book ID to check details: ");
                scanf("%d", &book_id);
                checkBookDetailsById(book_id);
                break;
            }
            case 3: {
                int book_id;
                printf("Enter Book ID to remove record: ");
                scanf("%d", &book_id);
                removeExistingBookRecord(book_id);
                break;
            }
            case 4: {
                printf("Viewing library catalog\n");
                viewLibraryCatalog();
                break;
            }
            case 5: {
                printf("Exiting program\n");
                exit(0);
            }
            default: {
                printf("Invalid choice\n");
            }
        }
    }

    return 0;
}
