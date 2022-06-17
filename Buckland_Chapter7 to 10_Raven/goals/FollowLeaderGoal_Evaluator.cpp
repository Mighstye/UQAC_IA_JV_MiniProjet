#include "FollowLeaderGoal_Evaluator.h"
#include "../navigation/Raven_PathPlanner.h"
#include "../Raven_ObjectEnumerations.h"
#include "../lua/Raven_Scriptor.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"

#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include <Debug/DebugConsole.h>




//---------------- CalculateDesirability -------------------------------------
//-----------------------------------------------------------------------------
double FollowLeaderGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
	if (pBot->GetLeaderID() != 0 && pBot->GetLeaderID() != pBot->ID()) {
		debug_con << "OMG ID BOT " << pBot->ID() << " "<< pBot->GetLeaderID() << "";
		return 100;
	}
	else {
		return 0;
	}
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void FollowLeaderGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
	pBot->GetBrain()->AddGoal_MoveToPosition(pBot->GetLeaderBot()->Pos());
	debug_con << "Following leader : " << pBot->GetLeaderBot()->Pos().x << " " << pBot->GetLeaderBot()->Pos().y << "";
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void FollowLeaderGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
	gdi->TextAtPos(Position, "EX: " + ttos(CalculateDesirability(pBot), 2));
}