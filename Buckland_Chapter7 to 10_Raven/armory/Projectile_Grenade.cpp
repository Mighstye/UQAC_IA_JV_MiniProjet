#include "Projectile_Grenade.h"
#include "../lua/Raven_Scriptor.h"
#include "misc/cgdi.h"
#include "../Raven_Bot.h"
#include "../Raven_Game.h"
#include "../constants.h"
#include "2d/WallIntersectionTests.h"
#include "../Raven_Map.h"

#include "../Raven_Messages.h"
#include "Messaging/MessageDispatcher.h"


//-------------------------- ctor ---------------------------------------------
//-----------------------------------------------------------------------------
Grenade::Grenade(Raven_Bot* shooter, Vector2D target) :

    Raven_Projectile(target,
        shooter->GetWorld(),
        shooter->ID(),
        shooter->Pos(),
        shooter->Facing(),
        script->GetInt("Grenade_Damage"),
        script->GetDouble("Grenade_Scale"),
        script->GetDouble("Grenade_MaxSpeed"),
        script->GetDouble("Grenade_Mass"),
        script->GetDouble("Grenade_MaxForce")),

    m_dCurrentBlastRadius(0.0),
    m_dBlastRadius(script->GetDouble("Grenade_BlastRadius")),
    m_dTimer(script->GetDouble("Grenade_Timer"))
{
    assert(target != Vector2D());
    m_vVelocity = MaxSpeed() * Heading();

    //make sure vehicle does not exceed maximum velocity
    m_vVelocity.Truncate(m_dMaxSpeed);

    m_bExploded = false;
}


//------------------------------ Update ---------------------------------------
//-----------------------------------------------------------------------------
void Grenade::Update()
{
    if (Clock->GetCurrentTime() < m_dTimeOfCreation + m_dTimer)
    {
        //update the position
        m_vPosition += m_vVelocity;

        TestForImpact();
    }

    else
    {
        if (!m_bExploded) {
            //test for bots within the blast radius and inflict damage
            InflictDamageOnBotsWithinBlastRadius();

            m_bExploded = true;
        }
        else {
            m_dCurrentBlastRadius += script->GetDouble("Grenade_ExplosionDecayRate");

            //when the rendered blast circle becomes equal in size to the blast radius
            //the Grenade can be removed from the game
            if (m_dCurrentBlastRadius > m_dBlastRadius)
            {
                m_bDead = true;
            }
        }
    }

    
}

void Grenade::TestForImpact()
{
    //if the projectile has reached the target position or it hits an entity
    //or wall it should bounce off and slow down


    //test to see if the line segment connecting the Grenade's current position
    //and previous position intersects with any bots.
    Raven_Bot* hit = GetClosestIntersectingBot(m_vPosition - m_vVelocity, m_vPosition);

    //if hit
    if (hit)
    {
        //send a message to the bot to let it know it's been hit, and who the
        //shot came from
        Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
            m_iShooterID,
            hit->ID(),
            Msg_TakeThatMF,
            (void*)&m_iDamageInflicted);

        //the grenade bounces off and slows down
        m_vVelocity = m_vVelocity * -0.5;
    }

    //test for impact with a wall
    double dist;
    if (FindClosestPointOfIntersectionWithWalls(m_vPosition - m_vVelocity,
        m_vPosition,
        dist,
        m_vImpactPoint,
        m_pWorld->GetMap()->GetWalls()))
    {
        //the grenade bounces off and slows down
        m_vPosition = m_vImpactPoint;
        m_vVelocity = m_vVelocity * -0.5;

        return;
    }

    //test to see if Grenade has reached target position.
    const double tolerance = 5.0;
    if (Vec2DDistanceSq(Pos(), m_vTarget) < tolerance * tolerance)
    {
        //the grenade bounces off the ground so it only slows down
        m_vVelocity = m_vVelocity * 0.5;
    }
}

//--------------- InflictDamageOnBotsWithinBlastRadius ------------------------
//
//  If the Grenade has exploded we test all bots to see if they are within the 
//  blast radius and reduce their health accordingly
//-----------------------------------------------------------------------------
void Grenade::InflictDamageOnBotsWithinBlastRadius()
{
    std::list<Raven_Bot*>::const_iterator curBot = m_pWorld->GetAllBots().begin();

    for (curBot; curBot != m_pWorld->GetAllBots().end(); ++curBot)
    {
        if (Vec2DDistance(Pos(), (*curBot)->Pos()) < m_dBlastRadius + (*curBot)->BRadius())
        {
            //send a message to the bot to let it know it's been hit, and who the
            //shot came from
            Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                m_iShooterID,
                (*curBot)->ID(),
                Msg_TakeThatMF,
                (void*)&m_iDamageInflicted);

        }
    }
}


//-------------------------- Render -------------------------------------------
//-----------------------------------------------------------------------------
void Grenade::Render()
{

    gdi->RedPen();
    gdi->OrangeBrush();
    gdi->Circle(Pos(), 2);

    if (m_bExploded)
    {
        gdi->HollowBrush();
        gdi->Circle(Pos(), m_dCurrentBlastRadius);
    }
}