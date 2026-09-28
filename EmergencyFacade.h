//TEBOGO MOKGWATSANE (25042239) 
//LISAKHANYA TATANE (25514424)
//AMIRA AJANAKU (25111699)

//EmergencyFacade.h

#ifndef EMERGENCYFACADE_H
#define EMERGENCYFACADE_H


#include "AccessControlService.h"
#include "CampusMediator.h"
#include "Incident.h"
#include <string>



/**
 * @brief Facade over access control, the response mediator and the incident.
 */

class EmergencyFacade
{
    private:
        AccessControlService* access;
        CampusMediator* mediator;
        Incident* incident;
    public:

        /**
         * @brief Construct over existing subsystems
         */
        EmergencyFacade(AccessControlService* access, CampusMediator* mediator, Incident* incident);
        
        /**
         * @brief Lockdown an area dispatch security and facilities, then lock it.
         * 
         */
        void lockdown(const string& area);
        void fullResponse(const string& area);

};


#endif