//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

// Incident.cpp

#include "Incident.h"
#include "IncidentState.h"
#include <algorithm>

/**
 * @brief Construct an Incident with no state set yet
 */
Incident::Incident(int id, string location) : state(nullptr), id(id), location(location) {}
/**
 * @copydoc IncidentSubject::attach
 */
void Incident::attach(IncidentObserver* obs){
    if (obs == nullptr){
        return;
    }
    observers.push_back(obs);
}

/**
 * @copydoc IncidentSubject::detach
 */

void Incident::detach(IncidentObserver* obs) {
    observers.erase(
        std::remove(observers.begin(),observers.end(), obs),observers.end()
    );
 }

/**
  * @copydoc IncidentSubject::notify
  */
void Incident::notify(){
    for (IncidentObserver* obs : observers)
    {
        obs->onIncidentChanged(*this);        
    }
    
}

/**
 * @brief Transitions the incident state to a new state and notififes the observers
 * @param s Pointer to the new state
 */

 void Incident::setState(IncidentState* s) {
    if (s == nullptr) return;
    delete state;
    state = s;
    notify();
    
 }

/**
 * @brief Gets the incident's current state name
 * @return The current state's name"
 */

string Incident::getStateName() {
    return state->name();
}

bool Incident::advance() {
    return state ? state->handle(*this) : false;
}

Incident::~Incident(){
    delete state;
}

