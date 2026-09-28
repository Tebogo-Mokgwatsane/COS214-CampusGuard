//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

//EmergencyFacade.cpp

#include "EmergencyFacade.h"

EmergencyFacade::EmergencyFacade(AccessControlService* access, CampusMediator* mediator, Incident* incident) 
    : access(access), mediator(mediator), incident(incident){}

void EmergencyFacade::lockdown(const string& area){
    mediator->dispatch("security", *incident);
    mediator->dispatch("facilities", *incident);
    access->lock(area);
    
}


void EmergencyFacade::fullResponse(const string& area){
    lockdown(area);
    mediator->dispatch("medical", *incident);
}