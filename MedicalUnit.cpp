// MedicalUnit.cpp
#include "MedicalUnit.h"
#include "Incident.h"
#include "ResponseMediator.h"
#include <iostream>

void MedicalUnit::onIncidentChanged(Incident& incident) {
    std::cout << "[MedicalUnit] notified of incident " << incident.getId()
              << " state=" << incident.getStateName() << "\n";

    if (mediator != nullptr && incident.getStateName() == "OnGoing") {
        mediator->notify(this, Event::MedicalNeeded, incident.getLocation());
    }
}

void MedicalUnit::respond(const std::string& area) {
    std::cout << "[MedicalUnit] responding on site at " << area << "\n";
}