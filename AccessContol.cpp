/**
 * @file AccessControl.cpp
 * @brief Implementation of the Adapter pattern classes for CampusGuard.
 */

#include "AccessControl.h"
#include <iostream>

using namespace std;

// LegacyAccessPanel (Adaptee) =====
void LegacyAccessPanel::engageLock(int id) {
    std::cout << "[LegacyAccessPanel] engageLock(" << id << ")\n";
}

void LegacyAccessPanel::releaseLock(int id) {
    std::cout << "[LegacyAccessPanel] releaseLock(" << id << ")\n";
}

void LegacyAccessPanel::setZone(int id, const std::string& mode) {
    std::cout << "[LegacyAccessPanel] setZone(" << id << ", \"" << mode << "\")\n";
}

// LegacyAccessAdapter =====
LegacyAccessAdapter::LegacyAccessAdapter(LegacyAccessPanel* p) : panel(p) {}

int LegacyAccessAdapter::areaToId(const std::string& area) const {
    // Simple but realistic translation table – this is the core adaptation logic
    if (area.find("Engineering") != std::string::npos) return 17;
    if (area.find("Library")     != std::string::npos) return 23;
    if (area.find("Admin")       != std::string::npos) return 9;
    if (area.find("Residence")   != std::string::npos) return 42;
    return 1; // default zone
}

void LegacyAccessAdapter::lock(const std::string& area) {
    std::cout << "[Adapter] Translating lock(\"" << area << "\") -> ";
    panel->engageLock(areaToId(area));
}

void LegacyAccessAdapter::unlock(const std::string& area) {
    std::cout << "[Adapter] Translating unlock(\"" << area << "\") -> ";
    panel->releaseLock(areaToId(area));
}

void LegacyAccessAdapter::restrict(const std::string& area) {
    std::cout << "[Adapter] Translating restrict(\"" << area << "\") -> ";
    panel->setZone(areaToId(area), "RESTRICTED");
}