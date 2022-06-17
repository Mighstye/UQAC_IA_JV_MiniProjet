#ifndef RAVEN_RUN_AWAY_GOAL_EVALUATOR
#define RAVEN_RUN_AWAY_GOAL_EVALUATOR
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   AttackTargetGoal_Evaluator.h
//
//  Desc:  class to calculate how desirable the goal of running away from the bot's
//         current target is
//-----------------------------------------------------------------------------

#include "Goal_Evaluator.h"
#include "../Raven_Bot.h"


class RunAwayGoal_Evaluator : public Goal_Evaluator
{
public:

	RunAwayGoal_Evaluator(double bias) :Goal_Evaluator(bias) {}

	double CalculateDesirability(Raven_Bot* pBot);

	void  SetGoal(Raven_Bot* pEnt);

	void RenderInfo(Vector2D Position, Raven_Bot* pBot);
};



#endif