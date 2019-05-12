#include "HeapPatientQueue.h"
#include <sstream>

HeapPatientQueue::HeapPatientQueue() {
    capacity = 8;
    size = 0;
    arrayPtr = new PatientNode*[capacity];
}

HeapPatientQueue::~HeapPatientQueue() {
    for (int i = 1; i <= size; i++) {
        delete arrayPtr[i];
    }
    delete [] arrayPtr;
}

void HeapPatientQueue::clear() {
    if (arrayPtr != nullptr){
        for (int i = 1; i <= size; i++) {
            delete arrayPtr[i];
        }
        delete [] arrayPtr;
    }
    capacity = size = 0;
    arrayPtr = nullptr;
}

string HeapPatientQueue::frontName() {
    if (isEmpty()){
        throw "There is no patient in the queue.";
    }
    return arrayPtr[1]->name;
}

int HeapPatientQueue::frontPriority() {
    if (isEmpty()){
        throw "There is no patient in the queue.";
    }
    return arrayPtr[1]->priority;
}

bool HeapPatientQueue::isEmpty() {
    return size == 0;
}

void HeapPatientQueue::expand(){
    PatientNode** newArray = new PatientNode*[capacity*2];
    for (int i = 0; i < capacity; i++){
        newArray[i] = arrayPtr[i];
    }
    delete [] arrayPtr;
    arrayPtr = newArray;
    capacity *= 2;
}

void HeapPatientQueue::swap(int a, int b){
    PatientNode* temp = arrayPtr[a];
    arrayPtr[a] = arrayPtr[b];
    arrayPtr[b] = temp;
}

void HeapPatientQueue::swapUp(int down){
    int up = down/2;
    while (up >=1 && (arrayPtr[up]->priority > arrayPtr[down]->priority || (arrayPtr[up]->priority == arrayPtr[down]->priority && arrayPtr[up]->name > arrayPtr[down]->name))){
        swap(up,down);
        down = up;
        up = down/2;
    }
}

void HeapPatientQueue::swapDown(int up){
    int left = 2 * up;
    int right = 2 * up + 1;
    int toUp;
    while (right <= size+1){
        if (right <= size && (arrayPtr[right]->priority < arrayPtr[left]->priority || (arrayPtr[right]->priority == arrayPtr[left]->priority && arrayPtr[right]->name < arrayPtr[left]->name))) {toUp = right;}
        else {toUp = left;}
        if (arrayPtr[toUp]->priority < arrayPtr[up]->priority || (arrayPtr[toUp]->priority == arrayPtr[up]->priority && arrayPtr[toUp]->name < arrayPtr[up]->name)){swap(up,toUp);}
        else {break;}
        up = toUp;
        left = 2 * up;
        right = 2 * up + 1;
    }
}

void HeapPatientQueue::newPatient(string name, int priority) {
    if (size == capacity - 1){
        expand();
    }
    size += 1;
    arrayPtr[size] = new PatientNode {name, priority};
    int down = size;
    swapUp(down);
}

string HeapPatientQueue::processPatient() {
    if (isEmpty()){
        throw "There is no patient in the queue.";
    }
    PatientNode* result = arrayPtr[1];
    string name = result->name;
    delete result;
    arrayPtr[1] = arrayPtr[size];
    arrayPtr[size] = nullptr;

    size -= 1;

    int up = 1;
    swapDown(up);

    return name;
}

void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    if (isEmpty()){
        throw "There is no patient in the queue.";
    }
    for (int i = 1; i <= size; i++){
        PatientNode tmp = *arrayPtr[i];
        if (tmp.name == name){
            if (tmp.priority <= newPriority){
                throw "The priority of patient " + name + " is already more or equally urgent than you want to update.";
            }
            arrayPtr[i]->priority = newPriority;
            if (i>1 && (newPriority < arrayPtr[i/2]->priority || (newPriority == arrayPtr[i/2]->priority && name < arrayPtr[i/2]->name))){
                swapUp(i);
            }
            return;
        }
    }
    throw "There is no patient named "+ name + ".";
}


string HeapPatientQueue::toString() {
    stringstream buffer;
    buffer << "{";
    if (!isEmpty()){
        buffer << *arrayPtr[1];
        if (size > 1){
            for (int i = 2; i <= size; i++){
            buffer << ", " << *arrayPtr[i];
            //buffer << result->priority << ":" << result->name;
            }
        }
    }
    buffer << "}";
    return buffer.str();
}
