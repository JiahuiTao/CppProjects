#include "LinkedListPatientQueue.h"
#include <sstream>

LinkedListPatientQueue::LinkedListPatientQueue() {
    head = nullptr;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    while (head != nullptr){
        PatientNode* next = head->next;
        delete head;
        head = next;
    }
}

void LinkedListPatientQueue::clear() {
    while (head != nullptr){
        PatientNode* next = head->next;
        delete head;
        head = next;
    }
}

string LinkedListPatientQueue::frontName() {
    return head->name;
}

int LinkedListPatientQueue::frontPriority() {
    return head->priority;
}

bool LinkedListPatientQueue::isEmpty() {
    return head == nullptr;
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    if (head == nullptr){
        head = new PatientNode {name, priority, head};
        return;
    }
    if (head->priority > priority){
        head = new PatientNode {name, priority, head};
        return;
    }
    PatientNode* result = head;
    while (true){
        if (result->priority <= priority && (result->next == nullptr || result->next->priority > priority)){
            result->next = new PatientNode {name, priority, result->next};
            return;
        }
    result = result->next;
    }
}

string LinkedListPatientQueue::processPatient() {
    if (isEmpty()){
        throw "There is no patient in the queue.";
    }
    PatientNode* result = head;
    head = result->next;
    string name = result->name;
    delete result;
    return name;
}

void LinkedListPatientQueue::moveUpPatient(PatientNode* toMove, PatientNode* last){
    last->next = toMove->next;
    if (head->priority > toMove->priority){
        toMove->next = head;
        head = toMove;
        return;
    }
    PatientNode* result = head;
    while (true){
        if (result->priority <= toMove->priority && result->next->priority > toMove->priority){
            toMove->next = result->next;
            result->next = toMove;
            return;
        }
    result = result->next;
    }
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    if (isEmpty()){
        throw "There is no patient in the queue.";
    }
    PatientNode* result = head;
    PatientNode* last = nullptr;
    while (result!=nullptr) {
        if (result->name == name){
            if (result->priority <= newPriority){
                throw "The priority of patient " + name + " is already more or equally urgent than you want to update.";
            }
            result->priority = newPriority;
            if (last != nullptr && newPriority < last->priority){
                moveUpPatient(result, last);
            }
            return;
        }
        last = result;
        result = result->next;
    }
    throw "There is no patient named "+ name + ".";
}

string LinkedListPatientQueue::toString() {
    stringstream buffer;
    buffer << "{";
    if (!isEmpty()){
        PatientNode* result = head;
        //buffer << *result;
        buffer << result->priority << ":" << result->name;
        result = result->next;
        while (result!=nullptr) {
            buffer << ", "<< result->priority << ":" << result->name;
            result = result->next;
        }
    }
    buffer << "}";
    return buffer.str();
}
