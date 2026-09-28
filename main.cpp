// ============================================================
// main.cpp — CampusGuard Automated Test Suite
// COS214 Practical 5 — Emergency Response Coordination
// ============================================================
// This driver exercises every public method of every class so
// that the submission achieves 100% line and branch coverage
// while telling two coherent end-to-end stories.
//
// Story 1 (Fire — Engineering Floor 3):
//   Facade -> Command -> Mediator -> State -> Observer -> Adapter
//
// Story 2 (Medical + Suspicious Package — Library):
//   Command -> Mediator -> Observer -> State -> Facade -> Adapter
//
// Both stories also exercise the two additional GoF patterns
// chosen by the team: State and Observer.
// ============================================================

#include <iostream>
#include <memory>
#include <string>

#include "AccessControlService.h"      // Adapter pattern
#include "CampusMediator.h"     // Mediator pattern
#include "Command.h"            // Command pattern
#include "EmergencyFacade.h"    // Facade pattern
#include "Incident.h"           // State + Observer context
#include "DispatchedState.h"
#include "OnGoingState.h"
#include "ResolvedState.h"
#include "CancelledState.h"
#include "SecurityUnit.h"
#include "MedicalUnit.h"
#include "FacilitiesUnit.h"

using namespace std;

// ------------------------------------------------------------
// Helper: type-safe state transition that still calls the
// raw-pointer setState() API required by the existing headers.
// Only this helper changes if Incident::setState ever becomes
// smart-pointer-based.
// ------------------------------------------------------------
template <typename S>
static void moveTo(Incident& inc) {
    inc.setState(new S());
}

// ------------------------------------------------------------
// Helper: small section banner for readable runtime output.
// ------------------------------------------------------------
static void banner(const string& title) {
    cout << "\n============================================================\n";
    cout << " " << title << "\n";
    cout << "============================================================\n";
}

int main() {
    cout << "===== CampusGuard Automated Test Suite =====\n";
    cout << "COS214 Practical 5 — Emergency Response Coordination\n";

    // ============================================================
    // SETUP — construct all subsystems and colleagues
    // ============================================================
    banner("SETUP");

    // --- Adapter pattern: adapt LegacyAccessPanel to AccessControlService ---
    LegacyAccessPanel legacyPanel;                  // Adaptee
    LegacyAccessAdapter adapter(&legacyPanel);      // Adapter
    AccessControlService* access = &adapter;        // Target interface

    // --- Mediator pattern: concrete mediator ---
    CampusMediator mediator;

    // --- Colleagues (also Observers) ---
    SecurityUnit   security("Engineering-Floor3");
    MedicalUnit    medical("Library");
    FacilitiesUnit facilities("Engineering-Floor3");

    // Register colleagues with the mediator (exercises registerColleague
    // for all four colleagues, including the duplicate-guard path).
    mediator.registerColleague(&security);
    mediator.registerColleague(&medical);
    mediator.registerColleague(&facilities);
    mediator.registerColleague(access);
    mediator.registerColleague(&security);   // duplicate — must be ignored

    // --- Two incidents with different runtime data ---
    Incident incident1(1, "Engineering-Floor3");
    Incident incident2(2, "Library");

    // Set initial state BEFORE attaching observers so units do not
    // receive a spurious "now Dispatched" notification at construction.
    moveTo<DispatchedState>(incident1);
    moveTo<DispatchedState>(incident2);

    // Attach observers (exercises attach() and the null-guard branch).
    incident1.attach(&security);
    incident1.attach(&medical);
    incident1.attach(&facilities);
    incident1.attach(nullptr);            // null-guard branch
    incident2.attach(&security);
    incident2.attach(&medical);
    incident2.attach(&facilities);

    // --- Invoker and Facade ---
    OperatorConsole  console;
    EmergencyFacade  facade(access, &mediator, &incident1);

    // ============================================================
    // STORY 1 — Fire in Engineering Floor 3
    // Demonstrates: Facade + Command + Mediator + State + Observer + Adapter
    // ============================================================
    banner("STORY 1: Fire — Engineering Floor 3");

    cout << "\n-- Step 1: Facade fullResponse (Facade + Command + Mediator "
            "+ State + Observer + Adapter) --\n";
    facade.fullResponse(incident1);

    cout << "\n-- Step 2: Explicit SecureAreaCommand (Command + Adapter) --\n";
    console.run(new SecureAreaCommand(access, "Engineering-Floor3"));

    cout << "\n-- Step 3: Advance to OnGoing (State + Observer) --\n";
    // DispatchedState::handle currently moves to ResolvedState;
    // call advance() to exercise the legal-transition path.
    bool advanced = incident1.advance();
    cout << "advance() returned " << (advanced ? "true" : "false") << "\n";

    cout << "\n-- Step 4: Advance to Resolved (State + Observer) --\n";
    moveTo<ResolvedState>(incident1);

    cout << "\n-- Step 5: Undo the SecureAreaCommand (Command::undo) --\n";
    console.undoLast();

    // ============================================================
    // STORY 2 — Medical + Suspicious Package at the Library
    // Demonstrates: Command + Mediator + Observer + State + Facade + Adapter
    // ============================================================
    banner("STORY 2: Medical + Suspicious Package — Library");

    cout << "\n-- Step 1: Dispatch Medical via Command (Command + Mediator) --\n";
    console.run(new DispatchUnitCommand(&mediator, "medical", &incident2));

    cout << "\n-- Step 2: Evacuate Library via Command "
            "(Command + Mediator + Observer) --\n";
    console.run(new EvacuateCommand(&mediator, "Library", &incident2));

    cout << "\n-- Step 3: Facade lockdown Admin-Block "
            "(Facade + Mediator + Adapter) --\n";
    facade.lockdown("Admin-Block");

    cout << "\n-- Step 4: Cancel incident 2 (State + Observer) --\n";
    moveTo<CancelledState>(incident2);

    cout << "\n-- Step 5: Undo the EvacuateCommand (Command::undo) --\n";
    console.undoLast();

    cout << "\n-- Step 6: Undo the DispatchUnitCommand (Command::undo) --\n";
    console.undoLast();

    // ============================================================
    // FAILURE / INVALID-OPERATION CASES
    // ============================================================
    banner("FAILURE CASES");

    cout << "\n-- Case A: Advance an already-Resolved incident --\n";
    ResolvedState resolved;
    bool accepted = resolved.handle(incident1);
    cout << "Transition accepted? "
         << (accepted ? "yes (BUG)" : "no (correct)") << "\n";

    cout << "\n-- Case B: Advance an already-Cancelled incident --\n";
    CancelledState cancelled;
    bool accepted2 = cancelled.handle(incident2);
    cout << "Transition accepted? "
         << (accepted2 ? "yes (BUG)" : "no (correct)") << "\n";

    cout << "\n-- Case C: Dispatch an unknown unit type --\n";
    bool ok = mediator.dispatch("robot", incident2);
    cout << "Dispatch accepted? "
         << (ok ? "yes (BUG)" : "no (correct)") << "\n";

    cout << "\n-- Case D: Undo with empty history --\n";
    {
        OperatorConsole emptyConsole;
        emptyConsole.undoLast();   // must print "Nothing to undo"
    }

    cout << "\n-- Case E: Detach an observer then advance --\n";
    incident1.detach(&medical);
    incident1.detach(nullptr);     // null-guard in detach
    moveTo<OnGoingState>(incident1);
    cout << "Incident 1 state after detach+move: "
         << incident1.getStateName() << "\n";

    cout << "\n-- Case F: OnGoingState::handle self-loop path --\n";
    OnGoingState ongoing;
    bool accepted3 = ongoing.handle(incident1);
    cout << "OnGoing handle accepted? "
         << (accepted3 ? "yes" : "no") << "\n";

    // ============================================================
    // COVERAGE COMPLETION — exercise remaining public methods
    // ============================================================
    banner("COVERAGE COMPLETION");

    cout << "\n-- Direct respond() calls on all three units --\n";
    security.respond("Engineering-Floor3");
    medical.respond("Library");
    facilities.respond("Engineering-Floor3");

    cout << "\n-- Colleague mediator getters/setters --\n";
    cout << "security.getMediator()   = "
         << (security.getMediator()   ? "set" : "null") << "\n";
    cout << "medical.getMediator()    = "
         << (medical.getMediator()    ? "set" : "null") << "\n";
    cout << "facilities.getMediator() = "
         << (facilities.getMediator() ? "set" : "null") << "\n";
    cout << "access->getMediator()    = "
         << (access->getMediator()    ? "set" : "null") << "\n";

    cout << "\n-- Incident accessors --\n";
    cout << "incident1.getId()       = " << incident1.getId()       << "\n";
    cout << "incident1.getLocation() = " << incident1.getLocation() << "\n";
    cout << "incident2.getId()       = " << incident2.getId()       << "\n";
    cout << "incident2.getLocation() = " << incident2.getLocation() << "\n";

    cout << "\n-- AccessControlService adapter: all three operations --\n";
    access->lock("Residence-Hall");
    access->unlock("Residence-Hall");
    access->restrict("Residence-Hall");

    cout << "\n-- Mediator: every Event enum branch --\n";
    mediator.notify(&security, Event::SecurityNeeded,      "Engineering-Floor3");
    mediator.notify(&security, Event::MedicalNeeded,       "Library");
    mediator.notify(&security, Event::FacilitiesNeeded,    "Engineering-Floor3");
    mediator.notify(&security, Event::AccessLockRequested, "Admin-Block");
    mediator.notify(&security, Event::IncidentResolved,    "Engineering-Floor3");
    mediator.notify(&security, Event::IncidentCancelled,   "Library");

    cout << "\n-- State name() coverage for every concrete state --\n";
    DispatchedState ds;  cout << "DispatchedState::name() = " << ds.name()  << "\n";
    OnGoingState    os;  cout << "OnGoingState::name()    = " << os.name()  << "\n";
    ResolvedState   rs;  cout << "ResolvedState::name()   = " << rs.name()  << "\n";
    CancelledState  cs;  cout << "CancelledState::name()  = " << cs.name()  << "\n";

    cout << "\n-- DispatchedState::handle legal transition --\n";
    Incident incident3(3, "Admin-Block");
    moveTo<DispatchedState>(incident3);
    bool accepted4 = incident3.advance();
    cout << "Dispatched advance accepted? "
         << (accepted4 ? "yes" : "no") << "\n";

    // ============================================================
    // DONE — all destructors run here (cleanup + ownership policy)
    // ============================================================
    banner("ALL AUTOMATED TESTS COMPLETED");
    cout << "OperatorConsole, Incidents, Units, Mediator, Adapter and\n"
            "LegacyAccessPanel destructors will now run in reverse order\n"
            "of construction. Run under Valgrind to confirm zero leaks.\n";

    return 0;
}