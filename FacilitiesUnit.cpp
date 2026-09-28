//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

//FacilitiesUnit.cpp

#include "FacilitiesUnit.h"
#include "Incident.h"
#include "ResponseMediator.h"
#include <iostream>


/**
 * @copydoc IncidentObserver::onIncidentChange
 */
void FacilitiesUnit::onIncidentChanged(Incident& incident) {
    std::cout << "[FacilitiesUnit] notified of incident " << incident.getId()
              << " state=" << incident.getStateName() << "\n";

    if (mediator != nullptr && incident.getStateName() == "OnGoing") {
        mediator->notify(this, Event::FacilitiesNeeded, incident.getLocation());
    }
}

void FacilitiesUnit::respond(const std::string& area) {
    std::cout << "[FacilitiesUnit] responding on site at " << area << "\n";
}