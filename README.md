# COS214-CampusGuard

CampusGuard coordinates campus security, medical, and facilities responders during an incident. It registers incidents, dispatches units, controls building access, and integrates with a legacy access-control panel — all without components depending directly on one another.

//////////////////////////////////////////////////////////////////////
Local build: 
make 
./campusguard

With Docker:
docker compose up --build
To stop the container press ctrl+c then:
docker compose down
///////////////////////////////////////////////////////////////////////

The program runs two end-to-end scenarios automatically:

Story 1 — Fire in Engineering Floor 3: Facade orchestrates a full response; Mediator dispatches units; Observer notifies them; Adapter locks the legacy panel; Command is issued and undone.

Story 2 — Medical + Suspicious Package at the Library: Command-driven dispatch and evacuation; Facade locks an area through the Adapter; both commands are undone.

////////////////////////////////////////////////////////////////////////
Done by yours truly,
Tebogo Mokgwatsane (25042239)

Lisakhanya Tatane (25514424)

Amira Ajanaku (25111699)
