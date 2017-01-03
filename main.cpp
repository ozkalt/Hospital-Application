#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <string.h>
//#include <conio.h>
#include <ctype.h>
#include "operations.h"

using namespace std;

typedef RecOpr DataStructure;
DataStructure book;

bool operate(char);
void menu();
void insert_record();
void remove_record();
void search_branch();
void search_clinic();
void print_records();

int main(){
    book.create();
    bool end = false;
    char choice;
    while (!end) {
        menu();
        cin >> choice;
        end = operate(choice);
    }
    book.close();
    return EXIT_SUCCESS;
}

void menu(){
    cout << endl << endl;
    cout << "Clinic Application" << endl;
    cout << "Choose an operation:" << endl;
    cout << "P: Print all patient records" << endl;
    cout << "B: Search the data by the branch name" << endl;
    cout << "C: Search the data by the polyclinic number" << endl;
    cout << "I: Insert a new patient record" << endl;
    cout << "R: Remove a patient record" << endl;
    cout << "E: Exit" << endl << endl;
    cout << "Enter an option {P, B, C, I, R, E} : ";
}

bool operate(char choice){
    bool end = false;
    switch (choice) {
        case 'P': case 'p':
            print_records();
            break;
        case 'B': case 'b':
            search_branch();
            break;
        case 'C': case 'c':
            search_clinic();
            break;
        case 'I': case 'i':
            insert_record();
            break;
        case 'R': case 'r':
            remove_record();
            break;
        case 'E': case 'e':
            cout << "Are you sure that you want to terminate the program? (Y/N):";
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
                end = true;
            break;
        default:
            cout << "Error: You have made an invalid choice." << endl;
            break;
    }
    return end;
}

void insert_record(){
    patient_record nr;
    patient_record * found;
    int d,f;
    
    cout << "Please enter the information of the person you want to save." << endl;
    cin.ignore(1000, '\n');
    cout << "Branch : ";
    cin.getline(nr.branchName, BRANCH_LENGHT);
    cout << "Polyclinic number:";
    cin >> setw(POLYCLINIC_NUMBER) >> nr.polyclinicNumber;
    d = book.clinicnum(nr.polyclinicNumber);
    if (d < 10){
        found = book.searchclinic(nr.polyclinicNumber);
        if (found != NULL){
            if (strcmp(found->branchName, nr.branchName) == 0){
                cin.ignore(1000, '\n');
                cout << "Patient's Name : ";
                cin.getline(nr.name, NAME_LENGHT);
                cout << "Doctor's Name : ";
                cin.getline(nr.doctorName, NAME_LENGHT);
                cout << "Diagnosis : ";
                cin.getline(nr.diagnosis, DIAGNOSIS_LENGHT);
                cout << "Patient number:";
                cin >> setw(PATIENT_ID) >> nr.patientNumber;
                if (book.searchpatnum(nr.patientNumber)){
                    book.insert(&nr);
                    cout << "Record has been added." << endl;
                }
                else
                    cout << "Another patient has this ID." << endl;
            }
            else
                cout << "Another branch has this policlinic." << endl;
        }
        else {
            f = book.searchbranch(nr.polyclinicNumber, nr.branchName);
            if (f == 2){
                cout << "A branch cannot take polyclinic more than 2." << endl;
            }
            else if (f == 1 || f == 0){
                cin.ignore(1000, '\n');
                cout << "Patient's Name : ";
                cin.getline(nr.name, NAME_LENGHT);
                cout << "Doctor's Name : ";
                cin.getline(nr.doctorName, NAME_LENGHT);
                cout << "Diagnosis : ";
                cin.getline(nr.diagnosis, DIAGNOSIS_LENGHT);
                cout << "Patient number:";
                cin >> setw(PATIENT_ID) >> nr.patientNumber;
                if (book.searchpatnum(nr.patientNumber)){
                    book.insert(&nr);
                    cout << "Record has been added." << endl;
                }
                else
                    cout << "Another patient has this ID." << endl;
            }
        }
    }
    else{
        cout << "The polyclinic is full." << endl;
    }
    getchar();
}


void remove_record(){
    int dr;
    bool d;
    cout << "Please enter the number of the patient you want to remove." << endl;
    cout << "Patient ID : ";
    cin.ignore(1000, '\n');
    cin >> setw(BRANCH_LENGHT) >> dr;
    d = book.remove(dr);
    if (d)
        cout << dr << ". patient has been deleted." << endl;
    else
        cout << "Patient cannot be found." << endl;
}


void search_branch(){
    char find[BRANCH_LENGHT];
    cout << "Please enter the branch." << endl;
    cin.ignore(1000, '\n');
    cout << "Branch : ";
    cin.getline(find, BRANCH_LENGHT);
    int a = book.searchbybranch(find);
    if (!a)
        cout << "Branch cannot be found." << endl;
}


void search_clinic(){
    int find;
    cout << "Please enter the polyclinic number." << endl;
    cout << "Polyclinic ID : ";
    cin.ignore(1000, '\n');
    cin >> setw(BRANCH_LENGHT) >> find;
    patient_record * a = book.searchbyclinic(find);
    if (!a)
        cout << "Clinic cannot be found." << endl;
}

void print_records(){
    book.print();
    getchar();
}
