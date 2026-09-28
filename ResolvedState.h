/**
 * @file ResolvedState.h
 * @brief Terminal incident state — response complete.
 */
#ifndef RESOLVED_STATE_H
#define RESOLVED_STATE_H

#include "IncidentState.h"

/**
 * @brief Terminal state: further transitions are rejected.
 */
class ResolvedState : public IncidentState {
public:
     /** @copydoc IncidentState::handle */
    bool handle(Incident&) override;
    /** @copydoc IncidentState::name */
    const std::string& name() const override;
};

#endif