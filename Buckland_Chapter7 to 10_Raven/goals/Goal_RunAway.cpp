#include "Goal_RunAway.h"
#include "Goal_Explore.h"
#include "Goal_MoveToPosition.h"
#include "..\Raven_Bot.h"
#include "Goal_FollowPath.h"
#include "..\Raven_SteeringBehaviors.h"

#include "Messaging/Telegram.h"
#include "..\Raven_Messages.h"

#include "debug/DebugConsole.h"
#include "misc/cgdi.h"

//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_RunAway::Activate()
{
    m_iStatus = active;

    //if this goal is reactivated then there may be some existing subgoals that
    //must be removed
    RemoveAllSubgoals();

    //it is possible for the target to die whilst this goal is active so we
    //must test to make sure the bot always has an active target
    if (m_pOwner->GetTargetSys()->isTargetPresent())
    {
        //grab a local copy of the last recorded position (LRP) of the target
        const Vector2D lrp = m_pOwner->GetTargetSys()->GetLastRecordedPosition();

        //recherche d'un lieu de fuite
        Vector2D targetPos;
        if (lrp.x > m_pOwner->Pos().x) {
            targetPos.x = 50;
        }
        else {
            targetPos.x = 380;
        }
        if (lrp.y > m_pOwner->Pos().y) {
            targetPos.y = 50;
        }
        else {
            targetPos.y = 380;
        }

        //si le lieu de fuite est atteint mais que l'ennemie est encore en vue, on change de lieu de fuite
        if (targetPos.isZero() || m_pOwner->isAtPosition(targetPos))
        {
            if (abs(lrp.x - m_pOwner->Pos().x) < abs(lrp.y - m_pOwner->Pos().y)) {
                if (targetPos.x == 380) {
                    targetPos.x = 50;
                }
                else {
                    targetPos.x = 380;
                }
            }
            else {
                if (targetPos.y == 380) {
                    targetPos.y = 50;
                }
                else {
                    targetPos.y = 380;
                }
            }
        }

        //request a path to the escape position
        m_pOwner->GetPathPlanner()->RequestPathToPosition(targetPos);

        //the bot may have to wait a few update cycles before a path is calculated
        //so for appearances sake it starts moving towards the position
        AddSubgoal(new Goal_MoveToPosition(m_pOwner, targetPos));
    }

    //if their is no active target then this goal can be removed from the queue
    else
    {
        m_iStatus = completed;
    }

}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_RunAway::Process()
{
    //if status is inactive, call Activate()
    ActivateIfInactive();

    m_iStatus = ProcessSubgoals();

    //if target is not in view this goal is satisfied
    if (!m_pOwner->GetTargetSys()->isTargetWithinFOV())
    {
        m_iStatus = completed;
    }

    return m_iStatus;
}

//---------------------------- HandleMessage ----------------------------------
//-----------------------------------------------------------------------------
bool Goal_RunAway::HandleMessage(const Telegram& msg)
{
    //first, pass the message down the goal hierarchy
    bool bHandled = ForwardMessageToFrontMostSubgoal(msg);

    //if the msg was not handled, test to see if this goal can handle it
    if (bHandled == false)
    {
        switch (msg.Msg)
        {
        case Msg_PathReady:

            //clear any existing goals
            RemoveAllSubgoals();

            AddSubgoal(new Goal_FollowPath(m_pOwner,
                m_pOwner->GetPathPlanner()->GetPath()));

            return true; //msg handled


        case Msg_NoPathAvailable:

            m_iStatus = failed;

            return true; //msg handled

        default: return false;
        }
    }

    //handled by subgoals
    return true;
}


//------------------------------- Render --------------------------------------
//-----------------------------------------------------------------------------
void Goal_RunAway::Render()
{
    //forward the request to the subgoals
    Goal_Composite<Raven_Bot>::Render();

}