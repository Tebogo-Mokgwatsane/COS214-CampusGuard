/**
 * @file ResolvedState.cpp
 * @brief Implementation of the terminal Resolved incident state.
 */
#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

bool ResolvedState::handle(Incident& incident) {
    std::cout << "[State] Incident " << incident.getId()
              << " is already Resolved; no further transition allowed\n";
    return false;
}

const std::string& ResolvedState::name() const {
    static const std::string n = "Resolved";
    return n;
}