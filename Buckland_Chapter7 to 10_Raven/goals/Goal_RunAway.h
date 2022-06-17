#ifndef GOAL_RUN_AWAY_H
#define GOAL_RUN_AWAY_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_HuntTarget.h
//
//  Desc:   Causes a bot to run away from another bot
//-----------------------------------------------------------------------------
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"


class Goal_RunAway : public Goal_Composite<Raven_Bot>
{
private:
    //true if a path to the escape position has been formulated
    bool                    m_bFollowingPath;
public:

    Goal_RunAway(Raven_Bot* pBot) :Goal_Composite<Raven_Bot>(pBot, goal_run_away),
        m_bFollowingPath(false)
    {}

    bool HandleMessage(const Telegram& msg);

    //the usual suspects
    void Activate();
    int  Process();
    void Terminate() {}

    void Render();


};





#endif
