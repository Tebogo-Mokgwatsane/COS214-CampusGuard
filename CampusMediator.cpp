/**
 * @file CampusMediator.cpp
 * @brief Implementation of the concrete CampusGuard mediator.
 */
#include "CampusMediator.h"
#include "Colleague.h"
#include "Incident.h"
#include <algorithm>
#include <iostream>

void CampusMediator::registerColleague(Colleague* c) {
     if (c == nullptr) return;                                  // extra safety
    if (std::find(colleagues.begin(), colleagues.end(), c) == colleagues.end()) {
        colleagues.push_back(c);
        c->setMediator(this);
    }
}

void CampusMediator::notify(Colleague* sender, Event e,
                            const std::string& area) {
    std::cout << "[Mediator] event from colleague for area " << area << "\n";
    for (auto* c : colleagues) {
        if (c == sender) continue;
        (void)c;
    }
    switch (e) {
        case Event::SecurityNeeded:
            std::cout << "[Mediator] coordinating security response in "
                      << area << "\n"; break;
        case Event::MedicalNeeded:
            std::cout << "[Mediator] coordinating medical response in "
                      << area << "\n"; break;
        case Event::FacilitiesNeeded:
            std::cout << "[Mediator] coordinating facilities response in "
                      << area << "\n"; break;
        case Event::AccessLockRequested:
            std::cout << "[Mediator] coordinating access lock in "
                      << area << "\n"; break;
        case Event::IncidentResolved:
            std::cout << "[Mediator] standing down units for "
                      << area << "\n"; break;
        case Event::IncidentCancelled:
            std::cout << "[Mediator] cancelling all actions for "
                      << area << "\n"; break;
    }
}

bool CampusMediator::dispatch(const std::string& unitType, Incident& incident) {
    if (unitType != "security" && unitType != "medical"
        && unitType != "facilities") {
        std::cout << "[Mediator] unknown unit type '" << unitType
                  << "' — dispatch rejected\n";
        return false;
    }
    std::cout << "[Mediator] dispatching " << unitType
              << " to incident " << incident.getId()
              << " at " << incident.getLocation() << "\n";

    if (incident.getStateName() == "Dispatched") {
        incident.advance();
    }
    return true;
}