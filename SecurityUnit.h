/**
 * @file SecurityUnit.h
 * @brief Security responder — Mediator colleague and Incident observer.
 */
#ifndef SECURITY_UNIT_H
#define SECURITY_UNIT_H

#include "Colleague.h"
#include "IncidentObserver.h"
#include <string>

/**
 * @brief Campus security response unit.
 *
 * Plays two roles:
 *  - **ConcreteColleague**: receives coordination events from the mediator
 *    and raises its own back through it.
 *  - **ConcreteObserver**: listens to Incident state changes and reacts.
 *
 * @note Never holds references to other colleagues.
 */
class SecurityUnit : public Colleague, public IncidentObserver {
    ResponseMediator* mediator = nullptr;  /**< Non-owning mediator ref. */
    std::string assignedArea;              /**< Area this unit covers. */
public:
 /**
     * @brief Constructs a security unit assigned to a particular area.
     * @param area Human-readable area name.
     */
    explicit SecurityUnit(const std::string& area) : assignedArea(area) {}
/** @copydoc Colleague::setMediator */
    void setMediator(ResponseMediator* m) override { mediator = m; }

    /** @copydoc Colleague::getMediator */
    ResponseMediator* getMediator() const override { return mediator; }

    /** @copydoc IncidentObserver::onIncidentChanged */
    void onIncidentChanged(Incident& incident) override;

    /**
     * @brief Performs the on-site security response.
     * @param area Area the unit is responding to.
     *
     * @note Called by the mediator, not by the incident or by other units.
     */
    void respond(const std::string& area);
};

#endif