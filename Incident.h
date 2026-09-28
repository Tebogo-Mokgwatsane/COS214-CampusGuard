//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

#ifndef INCIDENT_H
#define INCIDENT_H

#include "IncidentSubject.h"
#include <vector>
#include <string>

/** 
 * @brief Concrete Subject of the Observer pattern; also the Context of the State Pattern
 * Represents a reported incident. Holds the current incident state and notifies attached observers whenever the state changes
 */
class Incident : public IncidentSubject{
    private:
        IncidentState* state;
        vector<IncidentObserver*> observers;
        int id;
        string location;

    public:
        /**
         * @brief Constructor with no state set
         * @param id Unique incident identifier
         * @param location Campus Location 
         */
        Incident(int id, string location);
        
        /**
         * @copydoc IncidentSubject::attach
         */
        void attach(IncidentObserver* obs) override;

        /**
         * @copydoc IncidentSubject::detach
         */
        void detach(IncidentObserver* obs) override;

        /**
         * @copydoc IncidentSubject::notify
         */        
        void notify() override;

        /**
         * @brief Transitions the incident to a new state and notify observers.
         * @param s Pointer to the new state
         */        
        void setState(IncidentState* s);

        /**
         * @brief Get the incident's current state
         * @return The current state's name
         */        
        string getStateName();

        ~Incident();

        int getId() const;

        string getLocation() const;

        bool advance();

};


#endif