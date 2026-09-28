/**
 * @file OnGoingState.h
 * @brief Active incident state — response is in progress.
 */
#ifndef ONGOING_STATE_H
#define ONGOING_STATE_H

#include "IncidentState.h"

/**
 * @brief Legal transition: OnGoing -> Resolved.
 */
class OnGoingState : public IncidentState {
public:
     /** @copydoc IncidentState::handle */
    bool handle(Incident& incident) override;
     /** @copydoc IncidentState::name */
    const std::string& name() const override;
};

#endif