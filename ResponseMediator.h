/**
 * @file ResponseMediator.h
 * @brief Abstract Mediator role and the events colleagues may raise.
 *
 * Defines the coordination contract that all concrete mediators must honour,
 * plus the enum of coordination events that colleagues send back through it.
 */
#ifndef RESPONSE_MEDIATOR_H
#define RESPONSE_MEDIATOR_H

#include <string>

class Colleague;
class Incident;
/**
 * @brief Events a colleague can raise to the mediator.
 *
 * @note Used instead of raw strings or magic integers so that the compiler
 *       checks every coordination call site.
 */
enum class Event {
   SecurityNeeded,       /**< Security response is required in the area. */
    MedicalNeeded,        /**< Medical response is required in the area. */
    FacilitiesNeeded,     /**< Facilities support is required in the area. */
    AccessLockRequested,  /**< Area must be locked (routes to access control). */
    IncidentResolved,     /**< Incident has been resolved; units stand down. */
    IncidentCancelled     /**< Incident cancelled; all actions withdrawn. */
};
/**
 * @brief Abstract Mediator for all response-component coordination.
 *
 * @see Colleague
 * @see CampusMediator
 */
class ResponseMediator {
    public:
     /** @brief Virtual destructor — polymorphic base class. */
     virtual ~ResponseMediator() {}
      /**
     * @brief Registers a colleague with this mediator.
     * @param c Non-owning pointer to the colleague; duplicates are ignored.
     */
     virtual void registerColleague( Colleague* c) = 0;
      /**
     * @brief Receives a coordination event from a colleague.
     *
     * @param sender The colleague that raised the event (skipped during
     *               fan-out so it does not react to its own notification).
     * @param e      The event being reported.
     * @param area   The area the event applies to.
     */
     virtual void notify(Colleague* sender, Event e, const std::string& area) = 0;
     /**
     * @brief Dispatches a response unit to an incident.
     *
     * @param unitType One of "security", "medical", "facilities".
     * @param incident The incident the unit is being sent to.
     * @return true on success; false if @p unitType is unknown.
     */
     virtual bool dispatch(const std::string& unitType, Incident& incident) = 0;
};

#endif