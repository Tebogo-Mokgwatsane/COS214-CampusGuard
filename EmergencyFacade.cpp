//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

//EmergencyFacade.cpp

#include "EmergencyFacade.h"
#include "AccessControlService.h"     
#include "CampusMediator.h"    
#include "Incident.h"          
#include "DispatchedState.h"   
#include <iostream>
#include <string>

EmergencyFacade::EmergencyFacade(AccessControlService* access, CampusMediator* mediator, Incident* incident) 
    : access(access), mediator(mediator), incident(incident){}

void EmergencyFacade::lockdown(const std::string& area){
    cout << "\n[EmergencyFacade] lockdown(\"" << area << "\")\n";

     if (incident->getStateName() == "Unknown") {
        incident->setState(new DispatchedState());
    }

    mediator->dispatch("security", *incident);
    mediator->dispatch("facilities", *incident);
    
    access->lock(area);
    cout << "[EmergencyFacade] lockdown(\"" << area << "\") complete\n";
    
}


void EmergencyFacade::fullResponse(Incident& inc) {
    cout << "\n[EmergencyFacade] fullResponse(\""
         << inc.getLocation() << "\")\n";

    incident = &inc;

    lockdown(inc.getLocation());
    mediator->dispatch("medical", *incident);
    access->restrict(inc.getLocation());

    cout << "[EmergencyFacade] fullResponse(\""
         << inc.getLocation() << "\") complete\n";
}