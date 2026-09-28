//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

//SecurityUnit.cpp

#include "SecurityUnit.h"
#include "Incident.h"
#include "ResponseMediator.h"
#include <iostream>



/**
 * @copydoc IncidentObserver::onIncidentChange
 */
void SecurityUnit::onIncidentChanged(Incident& incident){
    std::cout << "[SecurityUnit] notified of incident " <<incident.getId()
    << " state=" << incident.getStateName() <<" location=" << incident.getLocation()<<std::endl; 

    if (mediator != nullptr) {
        mediator->notify(this, Event::SecurityNeeded,        incident.getLocation());
        mediator->notify(this, Event::AccessLockRequested,   incident.getLocation());
    }

}

void SecurityUnit::respond(const std::string& area){
     std::cout << "[SecurityUnit] responding on site at " << area << "\n";
}

