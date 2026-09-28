/**
 * @file AccessControl.h
 * @brief Adapter pattern implementation for CampusGuard access control.
 *
 * Provides a modern AccessControlService interface (Target) and a
 * LegacyAccessAdapter that translates calls to the incompatible
 * LegacyAccessPanel (Adaptee). AccessControlService also participates
 * in the Mediator pattern as a Colleague.
 */

#ifndef ACCESSCONTROLSERVICE_H
#define ACCESSCONTROLSERVICE_H

#include <string>
#include "CampusMediator.h"
#include "Colleague.h"
#include "ResponseMediator.h"

using namespace std;

/**
 * @class AccessControlService
 * @brief Target interface for access-control operations (Adapter pattern).
 *
 * This is the interface that the rest of CampusGuard programs against.
 * It also inherits from Colleague so that it can be registered with the
 * CampusMediator.
 */
class AccessControlService : public Colleague {
public:
    /**
     * @brief Virtual destructor for polymorphic deletion.
     */
    virtual ~AccessControlService() {}

    /**
     * @brief Lock the given area.
     * @param area Human-readable area name (e.g. "Engineering-Floor3").
     */
    virtual void lock(const string& area) = 0;

    /**
     * @brief Unlock the given area.
     * @param area Human-readable area name.
     */
    virtual void unlock(const string& area) = 0;

    /**
     * @brief Restrict access to the given area.
     * @param area Human-readable area name.
     */
    virtual void restrict(const string& area) = 0;
};

/**
 * @class LegacyAccessPanel
 * @brief Adaptee – the existing incompatible legacy access-control system.
 *
 * This class represents an old university card-reader / door-control panel
 * whose interface cannot be changed. It only understands numeric zone IDs
 * and low-level commands.
 */
class LegacyAccessPanel {
public:
    /**
     * @brief Engage the lock for a numeric zone.
     * @param id Numeric zone identifier used by the legacy hardware.
     */
    void engageLock(int id);

    /**
     * @brief Release the lock for a numeric zone.
     * @param id Numeric zone identifier.
     */
    void releaseLock(int id);

    /**
     * @brief Set the operating mode of a zone.
     * @param id   Numeric zone identifier.
     * @param mode Mode string expected by the legacy system (e.g. "RESTRICTED").
     */
    void setZone(int id, const string& mode);
};

/**
 * @class LegacyAccessAdapter
 * @brief Adapter that makes LegacyAccessPanel usable via AccessControlService.
 *
 * Translates modern area-name calls into the numeric-ID / low-level calls
 * expected by the legacy panel. This is a classic Object Adapter.
 */
class LegacyAccessAdapter : public AccessControlService {
private:
    LegacyAccessPanel* panel;   ///< The adaptee (not owned)
    ResponseMediator* mediator;
    /**
     * @brief Translate a human-readable area name into a legacy zone ID.
     * @param area Area name used by CampusGuard.
     * @return Corresponding numeric ID understood by LegacyAccessPanel.
     */
    int areaToId(const string& area) const;

public:
    /**
     * @brief Construct the adapter.
     * @param p Pointer to the LegacyAccessPanel that will be adapted.
     *          The panel is not owned by the adapter.
     */
    explicit LegacyAccessAdapter(LegacyAccessPanel* p);

    /**
     * @brief Destructor. Does not delete the panel (owned elsewhere).
     */
    ~LegacyAccessAdapter() {}

    /**
     * @brief Translate lock(area) into LegacyAccessPanel::engageLock(id).
     */
    void lock(const string& area) override;

    /**
     * @brief Translate unlock(area) into LegacyAccessPanel::releaseLock(id).
     */
    void unlock(const string& area) override;

    /**
     * @brief Translate restrict(area) into LegacyAccessPanel::setZone(id, "RESTRICTED").
     */
    void restrict(const string& area) override;

     void setMediator(ResponseMediator* m) override { mediator = m; }
    ResponseMediator* getMediator() const override { return mediator; }
};

#endif // ACCESSCONTROL_H