/**
 * @file CancelledState.cpp
 * @brief Implementation of the terminal Cancelled incident state.
 */
#include "CancelledState.h"
#include "Incident.h"
#include <iostream>

bool CancelledState::handle(Incident& incident) {
    std::cout << "[State] Incident " << incident.getId()
              << " is Cancelled; no further transition allowed\n";
    return false;
}

const std::string& CancelledState::name() const {
    static const std::string n = "Cancelled";
    return n;
}