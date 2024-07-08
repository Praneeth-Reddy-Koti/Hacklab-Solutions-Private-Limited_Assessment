#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function prototypes
struct Node* createNode(int data);
void addNode(struct Node** head, int data);
void deleteNode(struct Node** head, int position);
void deleteNodesWithValue(struct Node** head, int value);
void deleteEntireList(struct Node** head);
void displayList(struct Node* head);
void displayInverted(struct Node* head);
void displayMemoryUsage(struct Node* head);
void deleteNodeWithValueAndNext(struct Node** head, int value);

// Main function
int main() {
    struct Node* head = NULL;
    int choice, data, position, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a new node\n");
        printf("2. Delete a particular node\n");
        printf("3. Delete all nodes with a particular value\n");
        printf("4. Delete the entire linked list\n");
        printf("5. Display the linked list\n");
        printf("6. Display the inverted linked list\n");
        printf("7. Display the total memory space occupied by the linked list\n");
        printf("8. Delete all nodes with a particular value and the next subsequent node\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to add: ");
                scanf("%d", &data);
                addNode(&head, data);
                break;
            case 2:
                printf("Enter the position of the node to delete: ");
                scanf("%d", &position);
                deleteNode(&head, position);
                break;
            case 3:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                deleteNodesWithValue(&head, value);
                break;
            case 4:
                deleteEntireList(&head);
                break;
            case 5:
                displayList(head);
                break;
            case 6:
                displayInverted(head);
                break;
            case 7:
                displayMemoryUsage(head);
                break;
            case 8:
                printf("Enter the value to delete along with the next node: ");
                scanf("%d", &value);
                deleteNodeWithValueAndNext(&head, value);
                break;
            case 9:
                deleteEntireList(&head);
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add a node at the end
void addNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (!newNode) return;
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to delete a node at a given position
void deleteNode(struct Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* temp = *head;

    if (position == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position not found\n");
        return;
    }

    struct Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

// Function to delete all nodes with a specific value
void deleteNodesWithValue(struct Node** head, int value) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data == value) {
            if (prev == NULL) {
                *head = temp->next;
                free(temp);
                temp = *head;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

// Function to delete the entire linked list
void deleteEntireList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Helper function to display the inverted linked list
void displayInvertedHelper(struct Node* head) {
    if (head == NULL) return;
    displayInvertedHelper(head->next);
    printf("%d -> ", head->data);
}

// Function to display the inverted linked list
void displayInverted(struct Node* head) {
    displayInvertedHelper(head);
    printf("NULL\n");
}

// Function to display the total memory space occupied by the linked list
void displayMemoryUsage(struct Node* head) {
    struct Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total memory space occupied: %lu bytes\n", count * sizeof(struct Node));
}

// Function to delete all nodes with a specific value and the next subsequent node
void deleteNodeWithValueAndNext(struct Node** head, int value) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data == value) {
            if (prev == NULL) {
                *head = temp->next ? temp->next->next : NULL;
                free(temp->next);
                free(temp);
                temp = *head;
            } else {
                struct Node* toDelete = temp->next;
                prev->next = temp->next ? temp->next->next : NULL;
                free(temp);
                if (toDelete) {
                    free(toDelete);
                }
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}
