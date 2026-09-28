//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

// IncidentObserver.h
#ifndef INCIDENTOBSERVER_H
#define INCIDENTOBSERVER_H

#include <iostream>
#include <vector>
#include <string>

//forward declaration of the IncidentState and Incident classes


class Incident;

/**
 * @brief abstract observer of the Observer design pattern
 * 
 * Concrete response units (SecurityUnit, MedicalUnit, facilitiesUnit ) 
 * implement this interface such that they can be notified when the Incident that they are attached to changes state
 * */
class IncidentObserver {
    public:
        /**
         * @brief The destructor for an IncidentObserver object.
         * 
         * Virtual so that deleting a derived observer through a base pointer
         * correctly invokes the derived destructor
         */
        virtual ~IncidentObserver() = default;

        /**
         * @brief Called y an IncidentSubject when the incident it is attached to changes state
         */
        virtual void onIncidentChanged(Incident& incident) = 0;
};


#endif