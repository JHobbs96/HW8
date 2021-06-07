//Jeremiah Hobbs
//Patient.h
//June 7, 2021
//Header file for Patient that is used in the Patient Priority Queue.

#ifndef HW8_PATIENT_H
#define HW8_PATIENT_H
#include <string>
using namespace std;

class Patient {
private:
    string name;
    string priorityCode;//Translate these into integers to compare.
    //Can associate priority w integer i.e. 'immediate' = 1.
    int arrivalOrder;
    int compareCode() const{
        if(this->priorityCode == "immediate") {
            return 1;
        }
        if(this->priorityCode == "emergency"){
            return 2;
        }
        if(this->priorityCode == "urgent"){
            return 3;
        }
        if(this->priorityCode == "minimal"){
            return 4;
        }
        else{
            return 0;
        }
    }


public:
    Patient(string n, string code, int order) : name(n), priorityCode(code),
    arrivalOrder(order) {}

    string getName() const{
        return name;
    };//Returns the name of the patient
    string getPriority() const{
        return priorityCode;
    };//Returns the priority of the patient

    int getArrivalOrder(){
        return arrivalOrder;
    }//Returns the arrival order of the Patient
    /**
     * '=' overload operator
     * @param other The other Patient
     * @return a new Patient
     */
    Patient& operator =(const Patient& other){
        if(this != &other){
            name = other.name;
            priorityCode = other.priorityCode;
            arrivalOrder = other.arrivalOrder;
        }
        return *this;
    }
    /**
     * Overload operator for '<'
     * @param other Object to be compared
     * @return true if less than
     */
    bool operator < (const Patient& other){
        if(compareCode() == other.compareCode()){
            if(arrivalOrder > other.arrivalOrder){
                return true;
            }
            else{
                return false;
            }
        }
        if(compareCode() > other.compareCode()){
            return true;
        }
        else{
            return false;
        }
    }
    /**
     * Overload operator for '>'
     * @param other Object to be compared
     * @return true if greater than
     */
    bool operator > (const Patient& other){
        if(this->compareCode() == other.compareCode()){
            if(this->arrivalOrder < other.arrivalOrder){
                return true;
            }
            else{
                return false;
            }
        }
        if(this->compareCode() < other.compareCode()){
            return true;
        }
        else{
            return false;
        }
    }
    /**
     * To string method for a patient object
     * @return Patient in string format
     */
    string to_string(){
        return(name + "pri = " + this->priorityCode + ". arrive: " +
        std::to_string(arrivalOrder));
    }



};




#endif //HW8_PATIENT_H
