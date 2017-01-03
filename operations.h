#ifndef DIZIISLEMLERI_H
#define DIZIISLEMLERI_H
#include <stdio.h>
#include <iostream>
#include <string>
#include<string.h>
#include "record.h"
#define MAX_KAYIT 100

struct RecOpr{
    FILE * recordbook;
    patient_record k[MAX_KAYIT];
    void create();
    void close();
    void insert(patient_record*);
    int searchbybranch(char[]);
    int searchbranch(int, char[]);
    bool searchpatnum(int);
    patient_record * searchbyclinic(int);
    patient_record * searchclinic(int);
    bool remove(int);
    void print();
    int patientnumber;
    int clinicnum(int);
};

#endif
