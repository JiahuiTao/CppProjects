#pragma once

#include <iostream>
#include <string>
#include "patientqueue.h"
#include "vector.h"
using namespace std;

class VectorPatientQueue : public PatientQueue {
public:
    VectorPatientQueue();
    ~VectorPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    struct Patient {
        int priority;
        int order;
        string name;
        Patient (int priority = 100, int order = 0, string name=""){
            this -> priority = priority;
            this -> order = order;
            this -> name = name;
        }
    };
    Vector<Patient> queue;
    Vector<Patient>* queue_p;
    int count;
    int order;
};
