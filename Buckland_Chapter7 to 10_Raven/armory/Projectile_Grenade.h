#ifndef GRENADE_H
#define GRENADE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Grenade.h
//
//  Desc:   class to implement a grenade
//
//-----------------------------------------------------------------------------

#include "Raven_Projectile.h"

class Raven_Bot;

class Grenade : public Raven_Projectile
{
private:

    //the radius of damage, once the grenade explodes
    double    m_dBlastRadius;

    //this is used to render the splash when the grenade explodes
    double    m_dCurrentBlastRadius;

    //this is the timer of the grenade, the grenade explodes when the timer hits 0
    double    m_dTimer;

    //this is used to know if the grenade has exploded or no
    bool      m_bExploded;

    //If the grenades explodes we test all bots to see if they are within the 
    //blast radius and reduce their health accordingly
    void InflictDamageOnBotsWithinBlastRadius();

    //tests the trajectory of the grenade for an impact
    void TestForImpact();

public:

    Grenade(Raven_Bot* shooter, Vector2D target);

    void Render();

    void Update();

};


#endif