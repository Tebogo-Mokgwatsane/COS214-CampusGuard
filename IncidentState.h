#ifndef INCIDENTSTATE_H
#define INCIDENTSTATE_H
#include <string>
using namespace std;
class IncidentState {
    public:
        virtual ~IncidentState() = default;
        virtual string name() = 0;
};
#endif