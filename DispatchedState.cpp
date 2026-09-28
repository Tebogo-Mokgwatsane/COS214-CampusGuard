/**
 * @file DispatchedState.cpp
 * @brief Implementation of the Dispatched incident state.
 */
#include "DispatchedState.h"
#include "Incident.h"
#include "OnGoingState.h"
#include "ResolvedState.h" 
#include <iostream>

bool DispatchedState::handle(Incident& incident) {
    std::cout << "[State] Incident " << incident.getId()
              << " moving Dispatched -> OnGoing\n";
    //incident.setState(std::unique_ptr<IncidentState>(new OnGoingState()));
    incident.setState(new ResolvedState());
    return true;
}

const std::string& DispatchedState::name() const {
    static const std::string n = "Dispatched";
    return n;
}