#include "RunAwayGoal_Evaluator.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "../Raven_WeaponSystem.h"
#include "../Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"


#include "debug/DebugConsole.h"

//------------------ CalculateDesirability ------------------------------------
//
//  returns a value between 0 and 1 that indicates the Rating of a bot (the
//  lower the score, the stronger the bot).
//-----------------------------------------------------------------------------
double RunAwayGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
    double Desirability = 0.0;

    //only do the calculation if there is a target present
    if (pBot->GetTargetSys()->isTargetPresent())
    {
        const double Tweaker = 1.0;

        //score of the bot
        const double BotScore = Tweaker *
            Raven_Feature::Health(pBot) *
            Raven_Feature::TotalWeaponStrength(pBot);

        //score of the ennemy bot
        const double EnnemyScore = Tweaker *
            Raven_Feature::Health(pBot->GetTargetSys()->GetTarget()) *
            Raven_Feature::TotalWeaponStrength(pBot->GetTargetSys()->GetTarget());

        if (EnnemyScore > BotScore) {
            Desirability = 1.0;
        }
        else {
            Desirability = 0.0;
        }

        //bias the value according to the personality of the bot
        Desirability *= m_dCharacterBias;
    }

    return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void RunAwayGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
    pBot->GetBrain()->AddGoal_RunAway();
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void RunAwayGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
    gdi->TextAtPos(Position, "AT: " + ttos(CalculateDesirability(pBot), 2));
    return;

    std::string s = ttos(Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::TotalWeaponStrength(pBot));
    gdi->TextAtPos(Position + Vector2D(0, 12), s);
}