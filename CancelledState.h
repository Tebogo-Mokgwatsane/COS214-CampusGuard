/**
 * @file CancelledState.h
 * @brief Terminal incident state — incident cancelled.
 */
#ifndef CANCELLED_STATE_H
#define CANCELLED_STATE_H

#include "IncidentState.h"

/**
 * @brief Terminal state: further transitions are rejected.
 */
class CancelledState : public IncidentState {
public:
/** @copydoc IncidentState::handle */
    bool handle(Incident&) override;
     /** @copydoc IncidentState::name */
    const std::string& name() const override;
};

#endif