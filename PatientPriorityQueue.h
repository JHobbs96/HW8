//
// Created by Jeremiah Hobbs on 6/3/21.
//

#ifndef HW8_PATIENTPRIORITYQUEUE_H
#define HW8_PATIENTPRIORITYQUEUE_H

#include <vector>
#include "Patient.h"
#include <sstream>
#include <iostream>

using namespace std;
class PatientPriorityQueue{
private:
    int nextPatientNumber;
    void heapRebuild(int rootIndex);

public:
    vector<Patient> patients;
    PatientPriorityQueue();
    void add(string name, string priority);
    Patient peek();
    Patient remove();
    int size();
    string to_string();


};
//How do I initialize the Priority Queue and make sure they are in the right priority/move them around?
PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 0;
}

void PatientPriorityQueue::add(string name, string priority) {
    Patient p(name, priority, nextPatientNumber);
    patients.push_back(p);
    int newDataIndex = nextPatientNumber;
    bool inPlace = false;
    while ((newDataIndex > 0) && !inPlace) {
        int parentIndex = (newDataIndex - 1) / 2;
        if (patients.at(newDataIndex) > patients.at(parentIndex)) {
            Patient temp = patients.at(newDataIndex);
            patients.at(newDataIndex) = patients.at(parentIndex);
            patients.at(parentIndex) = temp;
            newDataIndex = parentIndex;
        } else
            inPlace = true;
    }
    nextPatientNumber++;
}

Patient PatientPriorityQueue::peek() {
    return patients.at(0);
}

Patient PatientPriorityQueue::remove() {
    Patient p = patients.at(0);
    patients.at(0) = patients.at(nextPatientNumber - 1);
    nextPatientNumber--;
    heapRebuild(0);
    return p;
}

int PatientPriorityQueue::size() {
    return nextPatientNumber;
}

string PatientPriorityQueue::to_string() {
    string line;
    for(int i = 0; i < patients.size(); i++){
        int arrival = patients.at(i).getArrivalOrder() + 1;
        string num = ::to_string(arrival);
        string prior = patients.at(i).getPriority();
        string name = patients.at(i).getName();
        line += "      " + num +"     " + prior + "      " +name +"\n";
    }
    return line;
}

void PatientPriorityQueue::heapRebuild(int rootIndex) {
    if(2 * rootIndex + 1 < nextPatientNumber) // the root is not a leaf (that is, it has a left child)
    {
        int largerChildIndex = 2 * rootIndex + 1; // left child index
        if(largerChildIndex + 1 < nextPatientNumber) // the root has a right child
        {
            int rightChildIndex = largerChildIndex + 1;
            if(patients.at(rightChildIndex) > patients.at(largerChildIndex))
                largerChildIndex = rightChildIndex;
        }

        if(patients.at(rootIndex) < patients.at(largerChildIndex))
        {	// swap
            Patient temp = patients.at(rootIndex);
            patients.at(rootIndex) = patients.at(largerChildIndex);
            patients.at(largerChildIndex) = temp;
            heapRebuild(largerChildIndex);
        }
    }
}


#endif //HW8_PATIENTPRIORITYQUEUE_H
