//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

#ifndef FACILITIESUNIT_H
#define FACILITIESUNIT_H

#include "Colleague.h"
#include "IncidentObserver.h"
#include <string>

class Incident;
/**
 * @brief Concrete Observer of the Observer Pattern 
 * Reacts to the incident state changes that are relevent to facilities
 * 
 */
class FacilitiesUnit : public IncidentObserver, public Colleague {
        public:
    /**
     * @copydoc IncidentObserver::onIncidentChange
     */
    void onIncidentChanged(Incident& incident) override;

    void respond(const std::string& area);
};


#endif