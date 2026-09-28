// main for fitchfork (Non-interactive)

#include <iostream>
#include <memory>
#include <string>

#include "AccessControl.h"     // AccessControlService, LegacyAccessPanel, LegacyAccessAdapter (Adapter)
#include "CampusMediator.h"    // CampusMediator (Mediator)
#include "Command.h"           // Command, DispatchUnitCommand, SecureAreaCommand, EvacuateCommand, OperatorConsole
#include "EmergencyFacade.h"   // EmergencyFacade (Facade)
#include "Incident.h"          // Incident (Subject + State context)
#include "DispatchedState.h"   // State pattern
#include "OnGoingState.h"
#include "ResolvedState.h"
#include "CancelledState.h"
#include "SecurityUnit.h"      // Colleagues + Observers
#include "MedicalUnit.h"
#include "FacilitiesUnit.h"

// Single place that knows how an Incident takes ownership of a new state (If Incident::setState ends up taking a raw pointer, only this changes)
template <typename S>
static void moveTo(Incident& inc) {
    inc.setState(unique_ptr<IncidentState>(new S()));
}

using namespace std;

int main() {
    cout << "===== CampusGuard Automated Test Suite =====\n\n";

    //Setup (same as interactive)
    LegacyAccessPanel   legacyPanel;
    LegacyAccessAdapter adapter(&legacyPanel);
    AccessControlService* access = &adapter;

    CampusMediator mediator;

    SecurityUnit security("Engineering-Floor3");
    MedicalUnit medical("Library");
    FacilitiesUnit facilities("Engineering-Floor3");

    mediator.registerColleague(&security);
    mediator.registerColleague(&medical);
    mediator.registerColleague(&facilities);
    mediator.registerColleague(access);

    Incident incident1(1, "Engineering-Floor3");
    Incident incident2(2, "Library");

    // Incidents start with no state, so set the initial one BEFORE attaching
    // observers (otherwise every unit gets a "now Dispatched" notification)
    moveTo<DispatchedState>(incident1);
    moveTo<DispatchedState>(incident2);

    incident1.attach(&security);
    incident1.attach(&medical);
    incident1.attach(&facilities);
    incident2.attach(&security);
    incident2.attach(&medical);
    incident2.attach(&facilities);

    OperatorConsole console;
    EmergencyFacade facade(access, &mediator);

    // ========== SCENARIO 1 - Fire in Engineering (5 patterns) ==========
    cout << "\nSCENARIO 1: Fire - Engineering Floor 3\n";

    cout << "\n-- Step 1: Facade fullResponse (Facade + Command + Mediator + State + Observer + Adapter) --\n";
    facade.fullResponse(incident1, "Engineering-Floor3");

    cout << "\n-- Step 2: Explicit SecureAreaCommand (Command + Adapter) --\n";
    console.run(new SecureAreaCommand(access, "Engineering-Floor3"));

    cout << "\n-- Step 3: Advance to Resolved (State + Observer) --\n";
    moveTo<ResolvedState>(incident1);

    // ========== SCENARIO 2 - Medical + Suspicious package ==========
    cout << "\nSCENARIO 2: Library Medical + Admin Package\n";

    cout << "\n-- Step 1: Dispatch Medical via Command --\n";
    console.run(new DispatchUnitCommand(&mediator, "medical", &incident2));

    cout << "\n-- Step 2: Evacuate Library via Command --\n";
    console.run(new EvacuateCommand(&mediator, "Library", &incident2));

    cout << "\n-- Step 3: Facade lockdown Admin-Block --\n";
    facade.lockdown("Admin-Block");

    cout << "\n-- Step 4: Cancel incident 2 (State + Observer) --\n";
    moveTo<CancelledState>(incident2);

    // ========== Failure / invalid operation ==========
    cout << "\nFAILURE CASE\n";
    cout << "-- Trying to advance an already Resolved incident --\n";
    ResolvedState resolved;
    bool accepted = resolved.handle(incident1);   // ResolvedState must reject this
    cout << "Transition accepted? " << (accepted ? "yes (BUG)" : "no (correct)") << "\n";

    cout << "\n-- Undo last command --\n";
    console.undoLast();

    cout << "\n===== All automated tests completed =====\n";
    return 0;
}