#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100

// Structures
struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char address[100];
    char contact[15];
};

struct Appointment {
    int id;
    char patientName[50];
    int doctorId;
    char date[20];
    char time[10];
};

// Global Variables
struct Patient patients[MAX_PATIENTS];
int patientCount = 0;

struct Appointment appointments[MAX_APPOINTMENTS];
int appointmentCount = 0;

// Function Declarations
void mainMenu();
void patientMenu();
void appointmentMenu();
void addPatient();
void viewPatients();
void bookAppointment();
void viewAppointments();
void savePatientsToFile();
void loadPatientsFromFile();
void saveAppointmentsToFile();
void loadAppointmentsFromFile();

int main() {
    loadPatientsFromFile();
    loadAppointmentsFromFile();
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    while (1) {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Patient Management\n");
        printf("2. Appointment Scheduling\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                patientMenu();
                break;
            case 2:
                appointmentMenu();
                break;
            case 3:
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void patientMenu() {
    int choice;
    while (1) {
        printf("\n--- Patient Management ---\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void appointmentMenu() {
    int choice;
    while (1) {
        printf("\n--- Appointment Scheduling ---\n");
        printf("1. Book Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                bookAppointment();
                break;
            case 2:
                viewAppointments();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Patient Management
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("\nPatient limit reached. Cannot add more patients.\n");
        return;
    }

    struct Patient *p = &patients[patientCount];
    printf("\n--- Add New Patient ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &p->id);
    getchar();  // Clear the newline character left by scanf
    printf("Enter Name: ");
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = '\0';
    printf("Enter Age: ");
    scanf("%d", &p->age);
    getchar();  // Clear the newline character left by scanf
    printf("Enter Gender: ");
    fgets(p->gender, sizeof(p->gender), stdin);
    p->gender[strcspn(p->gender, "\n")] = '\0';
    printf("Enter Address: ");
    fgets(p->address, sizeof(p->address), stdin);
    p->address[strcspn(p->address, "\n")] = '\0';
    printf("Enter Contact: ");
    fgets(p->contact, sizeof(p->contact), stdin);
    p->contact[strcspn(p->contact, "\n")] = '\0';

    patientCount++;
    savePatientsToFile();
    printf("\nPatient Added Successfully.\n");
}

void viewPatients() {
    if (patientCount == 0) {
        printf("\nNo patient records available yet.\n");
        return;
    }

    printf("\n--- List of Patients ---\n");
    for (int i = 0; i < patientCount; i++) {
        struct Patient *p = &patients[i];
        printf("ID: %d, Name: %s, Age: %d, Gender: %s, Address: %s, Contact: %s\n",
               p->id, p->name, p->age, p->gender, p->address, p->contact);
    }
}

// Appointment Management
void bookAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("\nAppointment limit reached. Cannot book more appointments.\n");
        return;
    }

    struct Appointment *a = &appointments[appointmentCount];
    printf("\n--- Book Appointment ---\n");
    printf("Enter Appointment ID: ");
    scanf("%d", &a->id);
    getchar();

    printf("Enter Patient Name: ");
    fgets(a->patientName, sizeof(a->patientName), stdin);
    a->patientName[strcspn(a->patientName, "\n")] = '\0';

    printf("Enter Doctor ID: ");
    scanf("%d", &a->doctorId);
    getchar();

    printf("Enter Date (e.g., 2024-11-20): ");
    fgets(a->date, sizeof(a->date), stdin);
    a->date[strcspn(a->date, "\n")] = '\0';

    printf("Enter Time (e.g., 10:30 AM): ");
    fgets(a->time, sizeof(a->time), stdin);
    a->time[strcspn(a->time, "\n")] = '\0';

    appointmentCount++;
    saveAppointmentsToFile();
    printf("\nAppointment Booked Successfully!\n");
}

void viewAppointments() {
    loadAppointmentsFromFile();
    if (appointmentCount == 0) {
        printf("\nNo appointment records available yet.\n");
        return;
    }

    printf("\n--- List of Appointments ---\n");
    for (int i = 0; i < appointmentCount; i++) {
        struct Appointment *a = &appointments[i];
        printf("Appointment ID: %d\n", a->id);
        printf("Patient Name: %s\n", a->patientName);
        printf("Doctor ID: %d\n", a->doctorId);
        printf("Date: %s\n", a->date);
        printf("Time: %s\n\n", a->time);
    }
}

// File Operations for Patients
void savePatientsToFile() {
    FILE *file = fopen("patients.txt", "w");
    if (!file) {
        printf("\nError saving patient records.\n");
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        struct Patient *p = &patients[i];
        fprintf(file, "%d\n%s\n%d\n%s\n%s\n%s\n",
                p->id, p->name, p->age, p->gender, p->address, p->contact);
    }
    fclose(file);
}

void loadPatientsFromFile() {
    FILE *file = fopen("patients.txt", "r");
    if (!file) {
        patientCount = 0;
        return;
    }

    patientCount = 0;
    while (fscanf(file, "%d\n", &patients[patientCount].id) == 1) {
        fgets(patients[patientCount].name, sizeof(patients[patientCount].name), file);
        patients[patientCount].name[strcspn(patients[patientCount].name, "\n")] = '\0';
        fscanf(file, "%d\n", &patients[patientCount].age);
        fgets(patients[patientCount].gender, sizeof(patients[patientCount].gender), file);
        patients[patientCount].gender[strcspn(patients[patientCount].gender, "\n")] = '\0';
        fgets(patients[patientCount].address, sizeof(patients[patientCount].address), file);
        patients[patientCount].address[strcspn(patients[patientCount].address, "\n")] = '\0';
        fgets(patients[patientCount].contact, sizeof(patients[patientCount].contact), file);
        patients[patientCount].contact[strcspn(patients[patientCount].contact, "\n")] = '\0';
        patientCount++;
    }
    fclose(file);
}

// File Operations for Appointments
void saveAppointmentsToFile() {
    FILE *file = fopen("appointments.txt", "w");
    if (!file) {
        printf("\nError saving appointments.\n");
        return;
    }

    for (int i = 0; i < appointmentCount; i++) {
        struct Appointment *a = &appointments[i];
        fprintf(file, "%d\n%s\n%d\n%s\n%s\n",
                a->id, a->patientName, a->doctorId, a->date, a->time);
    }
    fclose(file);
}

void loadAppointmentsFromFile() {
    FILE *file = fopen("appointments.txt", "r"); // Open file in read mode
    if (!file) { // If the file doesn't exist
        appointmentCount = 0;
        return;
    }

    appointmentCount = 0; // Reset appointment count
    while (fscanf(file, "%d %[^\n] %d %[^\n] %[^\n]",
                  &appointments[appointmentCount].id,
                  appointments[appointmentCount].patientName,
                  &appointments[appointmentCount].doctorId,
                  appointments[appointmentCount].date,
                  appointments[appointmentCount].time) == 5) {
        appointmentCount++;
    }
    fclose(file); // Close the file after reading
}

