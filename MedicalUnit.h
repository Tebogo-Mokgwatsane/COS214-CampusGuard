/**
 * @file MedicalUnit.h
 * @brief Medical responder — Mediator colleague and Incident observer.
 */
#ifndef MEDICAL_UNIT_H
#define MEDICAL_UNIT_H

#include "Colleague.h"
#include "IncidentObserver.h"
#include <string>

/**
 * @brief Campus medical response unit.
 *
 * @see SecurityUnit for the dual colleague/observer role.
 */
class MedicalUnit : public Colleague, public IncidentObserver {
     ResponseMediator* mediator = nullptr;  /**< Non-owning mediator ref. */
    std::string assignedArea;              /**< Area this unit covers. */

public:
    /**
     * @brief Constructs a medical unit assigned to a particular area.
     * @param area Human-readable area name.
     */
    explicit MedicalUnit(const std::string& area) : assignedArea(area) {}

    /** @copydoc Colleague::setMediator */
    void setMediator(ResponseMediator* m) override { mediator = m; }

    /** @copydoc Colleague::getMediator */
    ResponseMediator* getMediator() const override { return mediator; }

    /** @copydoc IncidentObserver::onIncidentChanged */
    void onIncidentChanged(Incident& incident) override;

    /**
     * @brief Performs the on-site medical response.
     * @param area Area the unit is responding to.
     */
    void respond(const std::string& area);
};

#endif