/**
 * @file IncidentState.h
 * @brief Abstract State role for the State pattern.
 *
 * Each concrete state encapsulates the rules and side-effects of one
 * operational status of an Incident.
 */
#ifndef INCIDENT_STATE_H
#define INCIDENT_STATE_H

#include <string>

class Incident;
/**
 * @brief Abstract base for all incident states.
 *
 * @see DispatchedState
 * @see OnGoingState
 * @see ResolvedState
 * @see CancelledState
 */
class IncidentState {
public:
     /** @brief Virtual destructor — polymorphic base class. */
    virtual ~IncidentState() {}
     /**
     * @brief Advances the incident to its next state, if the transition is legal.
     * @param incident The context whose state is being changed.
     * @return true if the transition was accepted; false if it was rejected.
     */
    virtual bool handle(Incident& incident) = 0;
     /**
     * @brief Human-readable name of this state.
     * @return Reference to a static string — safe to bind to const&.
     */
    virtual const std::string& name() const = 0;
};

#endif