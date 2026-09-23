/**
 * @file FacilitiesUnit.h
 * @brief Facilities responder — Mediator colleague and Incident observer.
 */
#ifndef FACILITIES_UNIT_H
#define FACILITIES_UNIT_H

#include "Colleague.h"
#include "IncidentObserver.h"
#include <string>

/**
 * @brief Campus facilities support unit.
 *
 * @see SecurityUnit for the dual colleague/observer role.
 */
class FacilitiesUnit : public Colleague, public IncidentObserver {
     ResponseMediator* mediator = nullptr;  /**< Non-owning mediator ref. */
    std::string assignedArea;              /**< Area this unit covers. */

public:
   /**
     * @brief Constructs a facilities unit assigned to a particular area.
     * @param area Human-readable area name.
     */
    explicit FacilitiesUnit(const std::string& area) : assignedArea(area) {}

    /** @copydoc Colleague::setMediator */
    void setMediator(ResponseMediator* m) override { mediator = m; }

    /** @copydoc Colleague::getMediator */
    ResponseMediator* getMediator() const override { return mediator; }

    /** @copydoc IncidentObserver::onIncidentChanged */
    void onIncidentChanged(Incident& incident) override;

    /**
     * @brief Performs the on-site facilities response.
     * @param area Area the unit is responding to.
     */
    void respond(const std::string& area);
};

#endif