//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

//MedicalUnit.cpp

#include "MedicalUnit.h"
#include "Incident.h"
#include "ResponseMediator.h"
#include <iostream>

/**
 * @copydoc IncidentObserver::onIncidentChange
 */


void MedicalUnit::onIncidentChanged(Incident& incident) {
    std::cout << "[MedicalUnit] notified of incident " << incident.getId()
              << " state=" << incident.getStateName() << "\n";

}

void MedicalUnit::respond(const std::string& area) {
    std::cout << "[MedicalUnit] responding on site at " << area << "\n";
}
