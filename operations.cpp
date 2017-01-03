#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "operations.h"

using namespace std;

void RecOpr::create(){
    recordbook = fopen("database.txt", "r+");
    int rec_num = 0;
    patientnumber = 0;
    fseek(recordbook, 0, SEEK_SET);
    while (!feof(recordbook)){
        if (feof(recordbook)) break;
        fscanf(recordbook, "%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n", k[rec_num].name, k[rec_num].doctorName, k[rec_num].diagnosis, &k[rec_num].patientNumber, &k[rec_num].polyclinicNumber, k[rec_num].branchName);
        insert(&k[rec_num]);
        rec_num++;
    }
    fclose(recordbook);
}

void RecOpr::insert(patient_record *nr){
    patient_record * t = k;
    if (patientnumber == 0){
        strcpy(t->name, nr->name);
        strcpy(t->doctorName, nr->doctorName);
        strcpy(t->diagnosis, nr->diagnosis);
        t->patientNumber = nr->patientNumber;
        t->polyclinicNumber = nr->polyclinicNumber;
        strcpy(t->branchName, nr->branchName);
    }
    else if (patientnumber > 0){
        for (int i = 1; i < patientnumber; i++){
            t++;
        }
        t++;
        strcpy(t->name, nr->name);
        strcpy(t->doctorName, nr->doctorName);
        strcpy(t->diagnosis, nr->diagnosis);
        t->patientNumber = nr->patientNumber;
        t->polyclinicNumber = nr->polyclinicNumber;
        strcpy(t->branchName, nr->branchName);
        
        patient_record * temp = new patient_record;
        
        while (strcmp(t->branchName, (t - 1)->branchName) <= 0){
            //if branch name of the last element should come after the new record, it will be under the new record. So they are shifted.
            if (strcmp(t->branchName, (t - 1)->branchName) == 0 && t->polyclinicNumber < (t - 1)->polyclinicNumber){
                strcpy(temp->name, (t - 1)->name);
                strcpy(temp->doctorName, (t - 1)->doctorName);
                strcpy(temp->diagnosis, (t - 1)->diagnosis);
                temp->patientNumber = (t - 1)->patientNumber;
                temp->polyclinicNumber = (t - 1)->polyclinicNumber;
                strcpy(temp->branchName, (t - 1)->branchName);
                
                strcpy((t - 1)->name, t->name);
                strcpy((t - 1)->doctorName, t->doctorName);
                strcpy((t - 1)->diagnosis, t->diagnosis);
                (t - 1)->patientNumber = t->patientNumber;
                (t - 1)->polyclinicNumber = t->polyclinicNumber;
                strcpy((t - 1)->branchName, t->branchName);
                
                strcpy(t->name, temp->name);
                strcpy(t->doctorName, temp->doctorName);
                strcpy(t->diagnosis, temp->diagnosis);
                t->patientNumber = temp->patientNumber;
                t->polyclinicNumber = temp->polyclinicNumber;
                strcpy(t->branchName, temp->branchName);
            }
            else if (strcmp(t->branchName, (t - 1)->branchName) < 0){
                strcpy(temp->name, (t - 1)->name);
                strcpy(temp->doctorName, (t - 1)->doctorName);
                strcpy(temp->diagnosis, (t - 1)->diagnosis);
                temp->patientNumber = (t - 1)->patientNumber;
                temp->polyclinicNumber = (t - 1)->polyclinicNumber;
                strcpy(temp->branchName, (t - 1)->branchName);
                
                strcpy((t - 1)->name, t->name);
                strcpy((t - 1)->doctorName, t->doctorName);
                strcpy((t - 1)->diagnosis, t->diagnosis);
                (t - 1)->patientNumber = t->patientNumber;
                (t - 1)->polyclinicNumber = t->polyclinicNumber;
                strcpy((t - 1)->branchName, t->branchName);
                
                strcpy(t->name, temp->name);
                strcpy(t->doctorName, temp->doctorName);
                strcpy(t->diagnosis, temp->diagnosis);
                t->patientNumber = temp->patientNumber;
                t->polyclinicNumber = temp->polyclinicNumber;
                strcpy(t->branchName, temp->branchName);
            }
            t--;
        }
    }
    patientnumber++;
}


bool RecOpr::searchpatnum(int rn){
    patient_record * t = k;
    for (int i = 0; i < patientnumber; i++){
        if (rn == t->patientNumber)
            return false;
        t++;
    }
    return true;
}


void RecOpr::close(){
    recordbook = fopen("database.txt", "w");
    int del = 0;
    fseek(recordbook, 0, SEEK_SET);
    for (del = 0; del < patientnumber; del++){
        fprintf(recordbook, "%s\t%s\t%s\t%d\t%d\t%s\n", &k[del].name, &k[del].doctorName, &k[del].diagnosis, k[del].patientNumber, k[del].polyclinicNumber, &k[del].branchName);
    }
    fclose(recordbook);
}

int RecOpr::searchbybranch(char b[BRANCH_LENGHT]){
    patient_record * tr = k;
    int counter = 0;
    for (int i = 0; i < patientnumber; i++){
        if (strcmp(tr->branchName, b) == 0){
            counter++;
            cout << tr->name << '\t';
            cout << tr->doctorName << '\t';
            cout << tr->diagnosis << '\t';
            cout << tr->patientNumber << '\t';
            cout << tr->polyclinicNumber << '\t';
            cout << tr->branchName << endl;
        }
        tr++;
    }
    /*
     for (int i = 0; i<patientnumber; i++){
     if (strcmp(k[i].branchName, b) == 0){
     counter++;
     cout << k[i].name << '\t';
     cout << k[i].doctorName << '\t';
     cout << k[i].diagnosis << '\t';
     cout << k[i].patientNumber << '\t';
     cout << k[i].polyclinicNumber << '\t';
     cout << k[i].branchName << endl;
     }
     }
     */
    return counter;
}

int RecOpr::searchbranch(int n, char b[BRANCH_LENGHT]){
    patient_record * tr = k;
    int counter = 0;
    for (int i = 0; i < patientnumber; i++){
        if (strcmp(tr->branchName, b) == 0 && tr->polyclinicNumber == n){
            counter++;
        }
        tr++;
    }
    return counter;
}

patient_record * RecOpr::searchbyclinic(int b){
    patient_record * tr = k;
    int counter = 0;
    for (int i = 0; i < patientnumber; i++){
        if (b == tr->polyclinicNumber){
            counter++;
            cout << tr->name << '\t';
            cout << tr->doctorName << '\t';
            cout << tr->diagnosis << '\t';
            cout << tr->patientNumber << '\t';
            cout << tr->polyclinicNumber << '\t';
            cout << tr->branchName << endl;
        }
        tr++;
    }
    return tr;
}


patient_record * RecOpr::searchclinic(int b){
    patient_record * tr = k;
    for (int i = 0; i < patientnumber; i++){
        if (b == tr->polyclinicNumber){
            return tr;
        }
        tr++;
    }
    return NULL;
}


int RecOpr::clinicnum(int b){
    patient_record * tr = k;
    int counter = 0;
    for (int i = 0; i < patientnumber; i++){
        if (b == tr->polyclinicNumber){
            counter++;
        }
        tr++;
    }
    return counter;
}

bool RecOpr::remove(int pn){
    patient_record * tr = k;
    int deleted = false;
    for (int i = 0; i < patientnumber; i++){
        if (pn == tr->patientNumber){
            for (int j = i; j < patientnumber; j++){
                strcpy(tr->name, (tr + 1)->name);
                strcpy(tr->doctorName, (tr + 1)->doctorName);
                strcpy(tr->diagnosis, (tr + 1)->diagnosis);
                tr->patientNumber = (tr + 1)->patientNumber;
                tr->polyclinicNumber = (tr + 1)->polyclinicNumber;
                strcpy(tr->branchName, (tr + 1)->branchName);
                tr++;
            }
            patientnumber--;
            deleted = true;
        }
        tr++;
    }
    return deleted;
}

void RecOpr::print(){
    patient_record * tr = k;
    for (int i = 0; i < patientnumber; i++){
        cout << i + 1 << ". ";
        cout << tr->name << '\t';
        cout << tr->doctorName << '\t';
        cout << tr->diagnosis << '\t';
        cout << tr->patientNumber << '\t';
        cout << tr->polyclinicNumber << '\t';
        cout << tr->branchName << endl;
        tr++;
    }
}
