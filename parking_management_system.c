#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold vehicle details
struct Vehicle {
    char number[20]; // Changed data type to store characters
    int type;
};

// Function Prototypes
void ShowDetails();
void Delete();
void two_wheeler();
void three_wheeler();
void four_wheeler();
void six_wheeler();
int Menu();
void SaveData();
void LoadData();
void ShowVehicleNumbers(); // New function
void DeleteByNumber(char *number); // New function

// Global Variables
struct Vehicle vehicles[100]; // Array to store vehicle details
int notwo = 0, nothree = 0, nofour = 0, nosix = 0, amount = 0, count = 0, ch, choice;

int main() {
    LoadData();  // Load Data from the file at the beginning

    while (1) {
        switch (Menu()) {
            case 1:
                two_wheeler();
                break;
            case 2:
                three_wheeler();
                break;
            case 3:
                four_wheeler();
                break;
            case 4:
                six_wheeler();
                break;
            case 5:
                ShowDetails();
                break;
            case 6:
                Delete();
                break;
            case 7:
                ShowVehicleNumbers(); // Show Vehicle Numbers
                break;
            case 8:
                SaveData();  // Save Data to the file before exiting
                exit(0);
            default:
                printf("\nInvalid Choice!");
        }

        while (getchar() != '\n'); // Clear input buffer
        printf("\n\nPress Enter to continue...");
        while (getchar() != '\n'); // Wait for Enter key
    }

    return 0;
}

int Menu() {
    printf("\n\nPARKING MANAGEMENT SYSTEM");
    printf("\n\n1: Entry For Two-Wheelers ");
    printf("\n2: Entry For Three-Wheelers ");
    printf("\n3: Entry For Four-Wheelers ");
    printf("\n4: Entry For Six-Wheelers ");
    printf("\n5: Show Status ");
    printf("\n6: Delete Entry ");
    printf("\n7: Show Vehicle Numbers "); // New Option
    printf("\n8: Exit ");
    printf("\n\nEnter Your Choice: ");
    scanf("%d", &ch);
    return ch;
}

void ShowDetails() {
    printf("\nNumber of Two-Wheelers: %d", notwo);
    printf("\nNumber of Three-Wheelers: %d", nothree);
    printf("\nNumber of Four-Wheelers: %d", nofour);
    printf("\nNumber of Six-Wheelers: %d", nosix);
    printf("\nNumber of Total Vehicles: %d", count);
    printf("\nTotal Gain Amount: %d\n", amount);
}

void Delete() {
    char deleteNumber[20];
    printf("\nEnter the vehicle number to delete: ");
    scanf("%s", deleteNumber);
    DeleteByNumber(deleteNumber);
}

void DeleteByNumber(char *number) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(vehicles[i].number, number) == 0) {
            switch (vehicles[i].type) {
                case 2:
                    notwo--, amount -= 50, count--;
                    break;
                case 3:
                    nothree--, amount -= 100, count--;
                    break;
                case 4:
                    nofour--, amount -= 150, count--;
                    break;
                case 6:
                    nosix--, amount -= 200, count--;
                    break;
                default:
                    break;
            }
            printf("\nEntry with vehicle number %s deleted!", vehicles[i].number);
            // Remove the deleted entry by shifting the remaining entries
            for (int j = i; j < count - 1; j++) {
                vehicles[j] = vehicles[j + 1];
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nEntry with vehicle number %s not found!", number);
    }
    SaveData();  // Save data after the delete operation
}

void two_wheeler() {
    printf("\nEntry Successful");
    struct Vehicle newVehicle;
    newVehicle.type = 2;
    printf("\nEnter vehicle number: ");
    scanf("%s", newVehicle.number); // Use %s to read string
    vehicles[count] = newVehicle;
    notwo++, amount += 50, count++;
    SaveData();  // Save data after the entry operation
}

void three_wheeler() {
    printf("\nEntry Successful");
    struct Vehicle newVehicle;
    newVehicle.type = 3;
    printf("\nEnter vehicle number: ");
    scanf("%s", newVehicle.number); // Use %s to read string
    vehicles[count] = newVehicle;
    nothree++, amount += 100, count++;
    SaveData();  // Save data after the entry operation
}

void four_wheeler() {
    printf("\nEntry Successful");
    struct Vehicle newVehicle;
    newVehicle.type = 4;
    printf("\nEnter vehicle number: ");
    scanf("%s", newVehicle.number); // Use %s to read string
    vehicles[count] = newVehicle;
    nofour++, amount += 150, count++;
    SaveData();  // Save data after the entry operation
}

void six_wheeler() {
    printf("\nEntry Successful");
    struct Vehicle newVehicle;
    newVehicle.type = 6;
    printf("\nEnter vehicle number: ");
    scanf("%s", newVehicle.number); // Use %s to read string
    vehicles[count] = newVehicle;
    nosix++, amount += 200, count++;
    SaveData();  // Save data after the entry operation
}

void ShowVehicleNumbers() {
    printf("\nVehicle Numbers Stored:");
    for (int i = 0; i < count; i++) {
        printf("\nVehicle %d: %s", i + 1, vehicles[i].number);
    }
}

void SaveData() {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("\nError opening file for writing.");
        exit(1);
    }

    fprintf(file, "%d %d %d %d %d %d\n", notwo, nothree, nofour, nosix, amount, count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s\n", vehicles[i].type, vehicles[i].number);
    }
    fclose(file);
}

void LoadData() {
    FILE *file = fopen("data.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d %d %d %d %d %d", &notwo, &nothree, &nofour, &nosix, &amount, &count);
        for (int i = 0; i < count; i++) {
            fscanf(file, "%d %s", &vehicles[i].type, vehicles[i].number);
        }
        fclose(file);
    }
}
