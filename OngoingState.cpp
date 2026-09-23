/**
 * @file OnGoingState.cpp
 * @brief Implementation of the OnGoing incident state.
 */
#include "OnGoingState.h"
#include "Incident.h"
#include "ResolvedState.h"
#include <iostream>

bool OnGoingState::handle(Incident& incident) {
    std::cout << "[State] Incident " << incident.getId()
              << " moving OnGoing -> Resolved\n";
    incident.setState(std::unique_ptr<IncidentState>(new ResolvedState()));
    return true;
}

const std::string& OnGoingState::name() const {
    static const std::string n = "OnGoing";
    return n;
}