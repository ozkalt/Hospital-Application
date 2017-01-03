/*
 @Author
 Student Name	:Tuba ÷zkal
 Student Number	:150120053
 */

#define POLICLINIC_NUM 10
#define NAME_LENGHT 30
#define DIAGNOSIS_LENGHT 30
#define BRANCH_LENGHT 20
#define MPNIOPC 10		//Max Patient Number in one Polyclinic
#define POLYCLINIC_NUMBER 2
#define PATIENT_ID 4

struct patient_record {
    char name[NAME_LENGHT], doctorName[NAME_LENGHT], diagnosis[DIAGNOSIS_LENGHT];
    int patientNumber, polyclinicNumber;
    char branchName[BRANCH_LENGHT];
};
