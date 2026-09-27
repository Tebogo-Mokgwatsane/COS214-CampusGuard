/**
 * @file Command.cpp
 * @brief Implementation of the Command pattern classes for CampusGuard.
 */

#include "Command.h"
#include "Mediator.h"          // CampusMediator
#include "AccessControl.h"     // AccessControlService
#include "Incident.h"          // Incident + concrete states
#include <iostream>

using namespace std;

// DispatchUnitCommand =====
DispatchUnitCommand::DispatchUnitCommand(CampusMediator* m, const string& type, Incident* inc) : mediator(m), unitType(type), incident(inc) {}

void DispatchUnitCommand::execute() {
    cout << "[Command] DispatchUnitCommand executing -> " << unitType << "\n";
    mediator->dispatch(*incident, unitType);
}

void DispatchUnitCommand::undo() {
    cout << "[Command] Undo DispatchUnitCommand -> cancelling incident\n";
    incident->setState(new CancelledState());
}

string DispatchUnitCommand::description() const {
    return "Dispatch " + unitType + " to Incident " + to_string(incident->getId());
}

// SecureAreaCommand =====
SecureAreaCommand::SecureAreaCommand(AccessControlService* a, const string& ar) : access(a), area(ar), prevLocked(false) {}

void SecureAreaCommand::execute() {
    cout << "[Command] SecureAreaCommand executing -> " << area << "\n";
    access->restrict(area);
    prevLocked = true;
}

void SecureAreaCommand::undo() {
    if (prevLocked) {
        cout << "[Command] Undo SecureAreaCommand -> unlocking " << area << "\n";
        access->unlock(area);
        prevLocked = false;
    }
}

string SecureAreaCommand::description() const {
    return "Secure area " + area;
}

// EvacuateCommand =====
EvacuateCommand::EvacuateCommand(CampusMediator* m, const string& ar, Incident* inc) : mediator(m), area(ar), incident(inc) {}

void EvacuateCommand::execute() {
    cout << "[Command] EvacuateCommand executing -> " << area << "\n";
    prevStateName = incident->getStateName();
    mediator->dispatch(*incident, "Security");
    mediator->dispatch(*incident, "Facilities");
}

void EvacuateCommand::undo() {
    cout << "[Command] Undo EvacuateCommand -> restoring state " << prevStateName << "\n";
    if (prevStateName == "Dispatched")
        incident->setState(new DispatchedState());
    else if (prevStateName == "OnGoing")
        incident->setState(new OnGoingState());
    else if (prevStateName == "Resolved")
        incident->setState(new ResolvedState());
}

string EvacuateCommand::description() const {
    return "Evacuate " + area;
}

// OperatorConsole (Invoker) =====
OperatorConsole::~OperatorConsole() {
    for (Command* cmd : history) {
        delete cmd;
    }
    history.clear();
}

void OperatorConsole::run(Command* cmd) {
    cout << "\n>>> OperatorConsole running: " << cmd->description() << "\n";
    cmd->execute();
    history.push_back(cmd);// take ownership
}

void OperatorConsole::undoLast() {
    if (history.empty()) {
        cout << "[OperatorConsole] Nothing to undo\n";
        return;
    }
    Command* cmd = history.back();
    history.pop_back();
    cout << "\n>>> OperatorConsole undoing: " << cmd->description() << "\n";
    cmd->undo();
    delete cmd;// release ownership
}