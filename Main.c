#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket {
    int ticket_id;
    char name[50];
    int age;
    char gender[10];
    char destination[50];
    struct Ticket *next;
};

struct Ticket *front = NULL, *rear = NULL;
int ticket_counter = 1000;

struct Ticket* createTicket(char name[], int age, char gender[], char destination[]);
void bookTicket();
void cancelTicket(int id);
void displayTickets();
void countTickets();
void searchTicket(int id);

struct Ticket* createTicket(char name[], int age, char gender[], char destination[]) {
    struct Ticket *newTicket = (struct Ticket*)malloc(sizeof(struct Ticket));
    
    if (newTicket == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    
    newTicket->ticket_id = ++ticket_counter;
    strcpy(newTicket->name, name);
    newTicket->age = age;
    strcpy(newTicket->gender, gender);
    strcpy(newTicket->destination, destination);
    newTicket->next = NULL;
    
    return newTicket;
}

void bookTicket() {
    char name[50], gender[10], destination[50];
    int age;
    
    printf("\nEnter Name: ");
    scanf("%s", name);
    printf("Enter Age: ");
    scanf("%d", &age);
    printf("Enter Gender: ");
    scanf("%s", gender);
    printf("Enter Destination: ");
    scanf("%s", destination);
    
    struct Ticket *newTicket = createTicket(name, age, gender, destination);
    
    if (rear == NULL) {
        front = rear = newTicket;
    } else {
        rear->next = newTicket;
        rear = newTicket;
    }
    
    printf("Ticket Booked Successfully! Ticket ID: %d\n", newTicket->ticket_id);
}

void cancelTicket(int id) {
    if (front == NULL) {
        printf("No bookings available.\n");
        return;
    }
    
    struct Ticket *temp = front, *prev = NULL;
    
    while (temp != NULL && temp->ticket_id != id) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Ticket ID not found.\n");
        return;
    }
    
    if (temp == front) {
        front = front->next; 
    } else {
        prev->next = temp->next; 
    }
    
    if (temp == rear) {
        rear = prev; 
    }
    
    free(temp);
    printf("Ticket %d cancelled successfully.\n", id);
}

void displayTickets() {
    if (front == NULL) {
        printf("No bookings.\n");
        return;
    }
    
    struct Ticket *temp = front;
    printf("\nCurrent Bookings:\n");
    
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Age: %d | Gender: %s | Destination: %s\n",
               temp->ticket_id, temp->name, temp->age, temp->gender, temp->destination);
        temp = temp->next;
    }
}

void countTickets() {
    int count = 0;
    struct Ticket *temp = front;
    
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total Bookings: %d\n", count);
}

void searchTicket(int id) {
    struct Ticket *temp = front;
    
    while (temp != NULL) {
        if (temp->ticket_id == id) {
            printf("Found Ticket ID %d for %s, Destination: %s\n",
                   temp->ticket_id, temp->name, temp->destination);
            return;
        }
        temp = temp->next;
    }
    printf("Ticket ID not found.\n");
}

int main() {
    int choice, id;
    
    while (1) {
        printf("\n--- TRAIN TICKET RESERVATION SYSTEM ---\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Display Bookings\n");
        printf("4. Search Ticket\n");
        printf("5. Count Tickets\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
             int c;
             while ((c = getchar()) != '\n' && c != EOF);
             printf("Invalid input. Please enter a number.\n");
             continue;
        }

        switch (choice) {
            case 1: 
                bookTicket(); 
                break;
            case 2: 
                printf("Enter Ticket ID to Cancel: "); 
                if (scanf("%d", &id) == 1) {
                    cancelTicket(id); 
                } else {
                    printf("Invalid ID input.\n");
                }
                break;
            case 3: 
                displayTickets(); 
                break;
            case 4: 
                printf("Enter Ticket ID to Search: "); 
                if (scanf("%d", &id) == 1) {
                    searchTicket(id); 
                } else {
                     printf("Invalid ID input.\n");
                }
                break;
            case 5: 
                countTickets(); 
                break;
            case 6: 
                printf("Exiting...\n"); 
                exit(0);
            default: 
                printf("Invalid choice.\n");
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return 0;
}
