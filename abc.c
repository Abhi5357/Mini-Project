#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10  // Hash table size

// Structure for Product Node (Chaining for HashMap)
typedef struct Product {
    char id[20];
    int quantity;
    struct Product *next;
} Product;

// Structure for Transaction Node (Linked List)
typedef struct Transaction {
    char message[100];
    struct Transaction *next;
} Transaction;

// Global hash table (array of linked lists)
Product *hashTable[SIZE] = {NULL};

// Head of transaction list
Transaction *transactionHead = NULL;

// Hash function for product ID
int hashFunction(char *id) {
    int sum = 0;
    for (int i = 0; id[i] != '\0'; i++)
        sum += id[i];
    return sum % SIZE;
}

// Add product or update quantity
void addProduct() {
    char id[20];
    int qty;
    printf("Enter Product ID: ");
    scanf("%s", id);
    printf("Enter Quantity to Add: ");
    scanf("%d", &qty);

    int index = hashFunction(id);
    Product *temp = hashTable[index];

    // Search for existing product
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            temp->quantity += qty;
            break;
        }
        temp = temp->next;
    }

    // If product not found, create new node
    if (temp == NULL) {
        Product *newProd = (Product *)malloc(sizeof(Product));
        strcpy(newProd->id, id);
        newProd->quantity = qty;
        newProd->next = hashTable[index];
        hashTable[index] = newProd;
    }

    // Record transaction
    Transaction *newT = (Transaction *)malloc(sizeof(Transaction));
    sprintf(newT->message, "Added %d units of Product ID: %s", qty, id);
    newT->next = transactionHead;
    transactionHead = newT;

    printf("✅ Product added successfully!\n\n");
}

// Remove product quantity
void removeProduct() {
    char id[20];
    int qty;
    printf("Enter Product ID: ");
    scanf("%s", id);
    printf("Enter Quantity to Remove: ");
    scanf("%d", &qty);

    int index = hashFunction(id);
    Product *temp = hashTable[index];

    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            if (temp->quantity >= qty) {
                temp->quantity -= qty;

                Transaction *newT = (Transaction *)malloc(sizeof(Transaction));
                sprintf(newT->message, "Removed %d units of Product ID: %s", qty, id);
                newT->next = transactionHead;
                transactionHead = newT;

                printf("✅ Product removed successfully!\n\n");
            } else {
                printf("❌ Not enough stock!\n\n");
            }
            return;
        }
        temp = temp->next;
    }

    printf("❌ Product ID not found!\n\n");
}

// Display all products
void displayInventory() {
    printf("\n📦 Current Inventory:\n");
    for (int i = 0; i < SIZE; i++) {
        Product *temp = hashTable[i];
        while (temp != NULL) {
            printf("Product ID: %s | Quantity: %d\n", temp->id, temp->quantity);
            temp = temp->next;
        }
    }
    printf("\n");
}

// Show transaction history
void showTransactions() {
    printf("\n🧾 Transaction History:\n");
    Transaction *temp = transactionHead;
    while (temp != NULL) {
        printf("%s\n", temp->message);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int choice;
    do {
        printf("===== WAREHOUSE INVENTORY TRACKER =====\n");
        printf("1. Add Product\n");
        printf("2. Remove Product\n");
        printf("3. Display Inventory\n");
        printf("4. Show Transaction History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: displayInventory(); break;
            case 4: showTransactions(); break;
            case 5: printf("Exiting... Thank you!\n"); break;
            default: printf("❌ Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
