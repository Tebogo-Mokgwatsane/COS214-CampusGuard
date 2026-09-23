/**
 * @file DispatchedState.h
 * @brief Initial incident state — a unit has been dispatched.
 */
#ifndef DISPATCHED_STATE_H
#define DISPATCHED_STATE_H

#include "IncidentState.h"

/**
 * @brief Legal transition: Dispatched -> OnGoing.
 */
class DispatchedState : public IncidentState {
public:
    /** @copydoc IncidentState::handle */
    bool handle(Incident& incident) override;
    /** @copydoc IncidentState::name */
    const std::string& name() const override;
};

#endif