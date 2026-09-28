//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

#ifndef SECURITYUNIT_H
#define SECURITYUNIT_H

#include "IncidentObserver.h"

/**
 * @brief Concrete Observer of the Observer Pattern.
 * Reacts to the incident state changes that are relevent to campus security 
 */
class SecurityUnit : public IncidentObserver {
    public:
    /**
     * @copydoc IncidentObserver::onIncidentChange
     */
    void onIncidentChange() override;
};

#endif