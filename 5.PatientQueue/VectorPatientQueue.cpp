#include "VectorPatientQueue.h"

VectorPatientQueue::VectorPatientQueue() {
    count = 0;
    order = 0;
    queue_p = new Vector<Patient>;
    queue = *queue_p;
}

VectorPatientQueue::~VectorPatientQueue() {
    delete queue_p;
}

void VectorPatientQueue::clear() {
    queue.clear();
    count = 0;
    order = 0;
}

string VectorPatientQueue::frontName() {
    if (queue.isEmpty()){
        throw "There is no patient in the queue.";
    }
    Patient frontPatient = queue[0];
    for (int i = 1; i < count; i++){
        if ((queue[i].priority < frontPatient.priority) || (queue[i].priority == frontPatient.priority && queue[i].order < frontPatient.order)){
            frontPatient = queue[i];
        }
    }
    return frontPatient.name;
}

int VectorPatientQueue::frontPriority() {
    if (queue.isEmpty()){
        throw "There is no patient in the queue.";
    }
    int minPriority = queue[0].priority;
    for (int i = 1; i < count; i++){
        if (queue[i].priority < minPriority){
            minPriority = queue[i].priority;
        }
    }
    return minPriority;
}

bool VectorPatientQueue::isEmpty() {
    return queue.isEmpty();
}

void VectorPatientQueue::newPatient(string name, int priority) {
    count += 1;
    order += 1;
    Patient NewPatient{priority, order, name};
    queue.add(NewPatient);
}

string VectorPatientQueue::processPatient() {
    if (isEmpty()){
        throw "There is no patient in the queue.";
    }
    Patient frontPatient = queue[0];
    int index = 0;
    for (int i = 1; i < count; i++){
        if ((queue[i].priority < frontPatient.priority) || (queue[i].priority == frontPatient.priority && queue[i].order < frontPatient.order)){
            frontPatient = queue[i];
            index = i;
        }
    }
    queue.remove(index);
    count -= 1;
    return frontPatient.name;
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    if (isEmpty()){
        throw "There is no patient in the queue.";
    }
    Patient FindPatient{};
    int index;
    for (int i = 0; i < count; i++){
        if ((queue[i].name == name) && queue[i].priority < FindPatient.priority){
            FindPatient = queue[i];
            index = i;
        }
    }
    if (FindPatient.name != name) {
        throw "There is no patient named "+ name + ".";
    }
    else if (FindPatient.priority <= newPriority){
        throw "The priority of patient " + name + " is already more or equally urgent than you want to update.";
    }
    queue[index].priority = newPriority;
    order += 1;
    queue[index].order = order;
}

string VectorPatientQueue::toString() {
    stringstream buffer;
    buffer << "{";
    if (count > 1){
        for (int i = 0; i < count-1; i++){
            buffer << queue[i].priority << ":" << queue[i].name << ", ";
        }
    }
    if (count >= 1) {
        buffer << queue[count - 1].priority << ":" << queue[count - 1].name;
    }
    buffer << "}";
    return buffer.str();
}
