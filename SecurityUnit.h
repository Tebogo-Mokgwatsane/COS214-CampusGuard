//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

#ifndef SECURITYUNIT_H
#define SECURITYUNIT_H

#include "IncidentObserver.h"
#include "Colleague.h"

/**
 * @brief Concrete Observer of the Observer Pattern.
 * Reacts to the incident state changes that are relevent to campus security 
 */
class SecurityUnit : public IncidentObserver, public Colleague {
    ResponseMediator* mediator = nullptr;   
    public:

    SecurityUnit() = default;
    void setMediator(ResponseMediator* m) override { mediator = m; }
    ResponseMediator* getMediator() const override { return mediator; }
    /**
     * @copydoc IncidentObserver::onIncidentChange
     */
    void onIncidentChanged(Incident& incident) override;

    void respond(const std::string& area);
};

#endif