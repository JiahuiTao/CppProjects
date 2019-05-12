/*
 * CS 106B/X Patient Queue
 * This file implements the members of the PatientNode structure.
 * See patientnode.h for declaration and documentation of each member.
 */

#include "patientnode.h"

PatientNode::PatientNode(std::string name, int priority, PatientNode* next) {
    this->name = name;
    this->priority = priority;
    this->next = next;
}

std::ostream& operator <<(std::ostream& out, const PatientNode& node) {
    return out << node.priority << ":" << node.name;
}
