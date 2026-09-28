//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

// IncidentSubject.h
#ifndef INCIDENTSUBJECT_H
#define INCIDENTSUBJECT_H

#include <iostream>
#include <vector>
#include <string>

class IncidentObserver;



/**
 * @brief Abstract Subject of the Observer Pattern 
 * concrete Subject (Incident) implement this interface 
 */
class IncidentSubject {
    public:
        /**
         * @brief Destructor for an IncidentSubect object
         */
        virtual ~IncidentSubject() = default;

        /**
         * @brief Registers an observer to recieve future notifications.
         * @param obs Pointer to the observer to attach. Not owned by the subject.
         */
        virtual void attach(IncidentObserver* obs) = 0;

        /**
         * @brief Deregisters an attached observer.
         * @param obs Pointer to the observer to detach
         */
        virtual void detach(IncidentObserver* obs) = 0;

        /**
         * @brief Notifies objects attached to it when state changes occur 
         */
        virtual void notify() = 0;
};

#endif