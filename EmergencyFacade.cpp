//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

//EmergencyFacade.cpp

#include "EmergencyFacade.h"
#include "AccessControl.h"     
#include "CampusMediator.h"    
#include "Incident.h"          
#include "DispatchedState.h"   
#include <iostream>
#include <string>

EmergencyFacade::EmergencyFacade(AccessControl* access, CampusMediator* mediator, Incident* incident) 
    : access(access), mediator(mediator), incident(incident){}

void EmergencyFacade::lockdown(const std::string& area){
    mediator->dispatch("security", *incident);
    mediator->dispatch("facilities", *incident);
    
    access->lock(area);
    cout << "[EmergencyFacade] lockdown(\"" << area << "\") complete\n";
    
}


void EmergencyFacade::fullResponse(const std::string& area){
    lockdown(area);
    mediator->dispatch("medical", *incident);

    access->restrict(area);

    cout << "[EmergencyFacade] fullResponse(\"" << area << "\") complete\n";
}