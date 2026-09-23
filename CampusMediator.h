/**
 * @file CampusMediator.h
 * @brief Concrete Mediator for CampusGuard.
 *
 * Holds a flat list of colleagues and fans events out to them without any
 * colleague ever knowing another colleague exists.
 */
#ifndef CAMPUS_MEDIATOR_H
#define CAMPUS_MEDIATOR_H

#include "ResponseMediator.h"
#include <string>
#include <vector>

class Colleague;
class Incident;
/**
 * @brief Concrete Mediator coordinating all CampusGuard response components.
 *
 * @note Colleagues are stored as non-owning raw pointers; their lifetime is
 *       managed by main() so they outlive the mediator.
 */
class CampusMediator : public ResponseMediator {
   /** @brief Non-owning list of registered colleagues. */
    std::vector<Colleague*> colleagues; 

    public:
     /** @copydoc ResponseMediator::registerColleague */
      void registerColleague(Colleague* c) override;
      /** @copydoc ResponseMediator::notify */
      void notify(Colleague* sender, Event e, const std::string& area) override;
       /** @copydoc ResponseMediator::dispatch */
      bool dispatch(const std::string& unitType, Incident& incident) override;
};

#endif