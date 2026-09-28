//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

#ifndef FACILITIESUNIT_H
#define FACILITIESUNIT_H

#include "IncidentObserver.h"
/**
 * @brief Concrete Observer of the Observer Pattern 
 * Reacts to the incident state changes that are relevent to facilities
 * 
 */
class FacilitiesUnit : public IncidentObserver {
        public:
    /**
     * @copydoc IncidentObserver::onIncidentChange
     */
    void onIncidentChange() override;

};


#endif