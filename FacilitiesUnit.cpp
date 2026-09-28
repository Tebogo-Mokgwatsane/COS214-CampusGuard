/**
 * @file FacilitiesUnit.cpp
 * @brief Implementation of the facilities responder.
 */
#include "FacilitiesUnit.h"
#include "Incident.h"
#include "ResponseMediator.h"
#include <iostream>

void FacilitiesUnit::onIncidentChanged(Incident& incident) {
    std::cout << "[FacilitiesUnit] notified of incident " << incident.getId()
              << " state=" << incident.getStateName() << "\n";
    if (incident.getLocation() == assignedArea && mediator
        && incident.getStateName() == "OnGoing") {
        mediator->notify(this, Event::FacilitiesNeeded, assignedArea);
    }
}

void FacilitiesUnit::respond(const std::string& area) {
    std::cout << "[FacilitiesUnit] responding on site at " << area << "\n";
}