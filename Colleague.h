/**
 * @file Colleague.h
 * @brief Abstract Colleague role for the Mediator pattern.
 *
 * Every response component (security, medical, facilities, access control)
 * implements this interface so it can be registered with a ResponseMediator
 * without any colleague needing a direct reference to any other colleague.
 */
#ifndef COLLEAGUE_H
#define COLLEAGUE_H

class ResponseMediator;
/**
 * @brief Abstract base for any participant that coordinates via a mediator.
 *
 * @note A Colleague never calls another Colleague directly; all coordination
 *       flows through the ResponseMediator.
 * @see ResponseMediator
 */
class Colleague {
    /** @brief Virtual destructor — polymorphic base class. */
    public:
        virtual ~Colleague() {}
         /**
     * @brief Binds this colleague to the mediator it will talk to.
     * @param m Non-owning pointer to the mediator; may be nullptr if unset.
     */
        virtual void setMediator(ResponseMediator* m) = 0;
        /**
     * @brief Returns the mediator currently bound to this colleague.
     * @return Non-owning pointer to the mediator, or nullptr if unset.
     */
        virtual ResponseMediator* getMediator() const = 0;
};

#endif