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
void Incident::setState(std::unique_ptr<IncidentState> s) {
    if(!s){
        return;
    }

    std::unique_ptr<IncidentState> old = std::move(state);
    state = std::move(s);
    notify();
}
void Incident::setState(IncidentState* s) {
    setState(std::unique_ptr<IncidentState>(s));
    
 }

/**
 * @brief Gets the incident's current state name
 * @return The current state's name"
 */

string Incident::getStateName() {
    if (state ==nullptr) return "Unknown";
    return state->name();
}

Incident::~Incident(){
}

int Incident::getId() const {
    return id;
}

string Incident::getLocation() const {
    return location;
}

bool Incident::advance() {
    return state != nullptr && state->handle(*this);
}
