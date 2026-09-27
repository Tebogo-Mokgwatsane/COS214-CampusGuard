/**
 * @file Command.h
 * @brief Command pattern implementation for CampusGuard operator actions.
 *
 * This file defines the Command interface, three concrete commands
 * (DispatchUnitCommand, SecureAreaCommand, EvacuateCommand) and the
 * OperatorConsole invoker. These classes allow operator requests to be
 * encapsulated as objects, supporting execution, undo and logging.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using namespace std;

// Forward declarations to reduce header coupling
class CampusMediator;
class AccessControlService;
class Incident;

/**
 * @class Command
 * @brief Abstract base class for all operator commands (Command pattern).
 *
 * Participants:
 * - Command (this class)
 * - ConcreteCommand (DispatchUnitCommand, SecureAreaCommand, EvacuateCommand)
 * - Invoker (OperatorConsole)
 * - Receiver (CampusMediator / AccessControlService)
 *
 * Every concrete command must implement execute(), undo() and description().
 * A virtual destructor is provided to guarantee correct polymorphic cleanup.
 */
class Command {
public:
    /**
     * @brief Virtual destructor.
     * Ensures derived command objects are destroyed correctly when deleted
     * through a Command pointer.
     */
    virtual ~Command() {}

    /**
     * @brief Execute the command (perform the real domain action).
     */
    virtual void execute() = 0;

    /**
     * @brief Undo the effects of a previously executed command.
     */
    virtual void undo() = 0;

    /**
     * @brief Return a human-readable description of the command.
     * @return string Description used for logging and the interactive menu.
     */
    virtual string description() const = 0;
};

/**
 * @class DispatchUnitCommand
 * @brief Concrete command that dispatches a response unit to an incident.
 *
 * Receiver: CampusMediator.
 * On execute() the mediator is asked to send the requested unit type.
 * On undo() the incident is moved to the Cancelled state.
 */
class DispatchUnitCommand : public Command {
private:
    CampusMediator* mediator;   ///< Receiver that will perform the dispatch
    string     unitType;   ///< "Security", "Medical" or "Facilities"
    Incident*       incident;   ///< Target incident

public:
    /**
     * @brief Construct a DispatchUnitCommand.
     * @param m     Pointer to the CampusMediator (receiver).
     * @param type  Unit type to dispatch ("Security", "Medical", "Facilities").
     * @param inc   Pointer to the Incident that needs the unit.
     */
    DispatchUnitCommand(CampusMediator* m, const string& type, Incident* inc);

    /**
     * @brief Ask the mediator to dispatch the unit and advance incident state.
     */
    void execute() override;

    /**
     * @brief Undo the dispatch by moving the incident to CancelledState.
     */
    void undo() override;

    /**
     * @brief Return a short description of this command.
     */
    string description() const override;
};

/**
 * @class SecureAreaCommand
 * @brief Concrete command that secures (locks/restricts) a campus area.
 *
 * Receiver: AccessControlService (normally reached through the Adapter).
 * Stores whether the area was locked so that undo() can reverse the action.
 */
class SecureAreaCommand : public Command {
private:
    AccessControlService* access;     ///< Receiver (modern access-control interface)
    string           area;       ///< Area name to secure
    bool                  prevLocked; ///< Used by undo() to know whether to unlock

public:
    /**
     * @brief Construct a SecureAreaCommand.
     * @param a   Pointer to the AccessControlService (receiver).
     * @param ar  Name of the area to lock/restrict.
     */
    SecureAreaCommand(AccessControlService* a, const string& ar);

    /**
     * @brief Restrict the given area via the AccessControlService.
     */
    void execute() override;

    /**
     * @brief Unlock the area if it was previously locked by this command.
     */
    void undo() override;

    /**
     * @brief Return a short description of this command.
     */
    string description() const override;
};

/**
 * @class EvacuateCommand
 * @brief Concrete command that initiates an evacuation of an area.
 *
 * Dispatches both Security and Facilities units and stores the previous
 * incident state so that undo() can restore it.
 */
class EvacuateCommand : public Command {
private:
    CampusMediator* mediator;       ///< Receiver
    string     area;           ///< Area being evacuated
    Incident*       incident;       ///< Related incident
    string     prevStateName;  ///< State before execute() (for undo)

public:
    /**
     * @brief Construct an EvacuateCommand.
     * @param m   Pointer to the CampusMediator.
     * @param ar  Name of the area to evacuate.
     * @param inc Pointer to the related Incident.
     */
    EvacuateCommand(CampusMediator* m, const string& ar, Incident* inc);

    /**
     * @brief Dispatch Security + Facilities and record previous state.
     */
    void execute() override;

    /**
     * @brief Restore the incident to the state it had before execute().
     */
    void undo() override;

    /**
     * @brief Return a short description of this command.
     */
    string description() const override;
};

/**
 * @class OperatorConsole
 * @brief Invoker in the Command pattern.
 *
 * Holds a history of executed commands so that the most recent command
 * can be undone. Owns the Command objects it receives (deletes them in
 * its destructor or when undoLast() is called).
 */
class OperatorConsole {
private:
    vector<Command*> history;  ///< Owned command history (most recent at back)

public:
    /**
     * @brief Destructor – deletes any remaining commands in the history.
     */
    ~OperatorConsole();

    /**
     * @brief Execute a command and store it in the history.
     * @param cmd Pointer to a heap-allocated Command. Ownership is transferred
     *            to the OperatorConsole.
     */
    void run(Command* cmd);

    /**
     * @brief Undo the most recently executed command and delete it.
     */
    void undoLast();
};

#endif // COMMAND_H