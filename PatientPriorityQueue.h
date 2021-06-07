//Jeremiah Hobbs
//PatientPriorityQueue.h
//June 7, 2021
//Header file for PatientPriorityQueue that is used in the P3 that uses
//a heap and queue for functionality.

#ifndef HW8_PATIENTPRIORITYQUEUE_H
#define HW8_PATIENTPRIORITYQUEUE_H

#include <vector>
#include "Patient.h"
#include <sstream>
#include <iostream>
#include <iomanip>

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
/**
 * Patient Priority Queue constructor that sets the next patient number to 0.
 */
PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 0;
}
/**
 * Adds a patient to the queue
 * @param name string name of the patient
 * @param priority string patient priority
 */
void PatientPriorityQueue::add(string name, string priority) {
    Patient p(name, priority, nextPatientNumber);
    patients.push_back(p);
    int newDataIndex = nextPatientNumber;
    bool inPlace = false;
    //Sifting process
    while ((newDataIndex > 0) && !inPlace) {
        int parentIndex = (newDataIndex - 1) / 2;
        //Replacing
        if (patients.at(newDataIndex) > patients.at(parentIndex)) {
            Patient temp = patients.at(newDataIndex);
            patients.at(newDataIndex) = patients.at(parentIndex);
            patients.at(parentIndex) = temp;
            newDataIndex = parentIndex;
        } else
            inPlace = true;
    }
    nextPatientNumber++;//Increment the number
}
/**
 * Peeks the top of the queue
 * @return Patient at the top of the queue
 */
Patient PatientPriorityQueue::peek() {
    return patients.at(0);
}
/**
 * Removes the patient at the top of the queue
 * @return Patient removed from the top of the queue
 */
Patient PatientPriorityQueue::remove() {
    Patient p = patients.at(0);
    patients.at(0) = patients.at(nextPatientNumber - 1);
    nextPatientNumber--;
    heapRebuild(0);
    return p;
}
/**
 * Returns the current size of the queue
 * @return int the size of the queue
 */
int PatientPriorityQueue::size() {
    return nextPatientNumber;
}
/**
 * Returns the PatientPriorityQueue in string format
 * @return string of PatientPriorityQueue
 */
string PatientPriorityQueue::to_string() {
    stringstream line;
    for(int i = 0; i < patients.size(); i++){
        line <<std::setw(5)<<patients.at(i).getArrivalOrder() + 1;
        line<<std::setw(17)<<patients.at(i).getPriority();
        line<<std::setw(22)<<patients.at(i).getName();
        line<<"\n";

    }
    return line.str();
}
/**
 *
 * @param rootIndex
 */
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
