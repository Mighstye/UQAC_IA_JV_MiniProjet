#ifndef DROP_WEAPON_H
#define DROP_WEAPON_H
#pragma warning (disable:4786)

#include "Triggers/Trigger_Respawning.h"
#include "../Raven_Bot.h"
#include <iosfwd>
#include "2d/vector2d.h"



class Trigger_DropWeapon : public Trigger<Raven_Bot>
{
private:

	//vrtex buffers for rocket shape
	std::vector<Vector2D>         m_vecRLVB;
	std::vector<Vector2D>         m_vecRLVBTrans;

public:

	//this type of trigger is created when reading a map file
	Trigger_DropWeapon(Raven_Bot* bot);
 	//~Trigger_DropWeapon() {};
	//if triggered, this trigger will call the PickupWeapon method of the
	//bot. PickupWeapon will instantiate a weapon of the appropriate type.
	void Try(Raven_Bot*);

	//draws a symbol representing the weapon type at the trigger's location
	void Render();
	virtual void Update() {}
};




#endif