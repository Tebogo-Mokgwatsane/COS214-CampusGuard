/**
 * @file SecurityUnit.cpp
 * @brief Implementation of the security responder.
 */
#include "SecurityUnit.h"
#include "Incident.h"
#include "ResponseMediator.h"
#include <iostream>

void SecurityUnit::onIncidentChanged(Incident& incident) {
    std::cout << "[SecurityUnit] notified of incident " << incident.getId()
              << " state=" << incident.getStateName()
              << " location=" << incident.getLocation() << "\n";
    if (incident.getLocation() == assignedArea && mediator) {
        mediator->notify(this, Event::SecurityNeeded, assignedArea);
        mediator->notify(this, Event::AccessLockRequested, assignedArea);
    }
}

void SecurityUnit::respond(const std::string& area) {
    std::cout << "[SecurityUnit] responding on site at " << area << "\n";
}