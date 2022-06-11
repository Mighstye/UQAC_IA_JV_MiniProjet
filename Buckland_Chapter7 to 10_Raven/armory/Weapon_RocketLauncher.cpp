#include "Weapon_RocketLauncher.h"
#include "../Raven_Bot.h"
#include "misc/Cgdi.h"
#include "../Raven_Game.h"
#include "../Raven_Map.h"
#include "../lua/Raven_Scriptor.h"
#include "fuzzy/FuzzyOperators.h"


//--------------------------- ctor --------------------------------------------
//-----------------------------------------------------------------------------
RocketLauncher::RocketLauncher(Raven_Bot*   owner):

                      Raven_Weapon(type_rocket_launcher,
                                   script->GetInt("RocketLauncher_DefaultRounds"),
                                   script->GetInt("RocketLauncher_MaxRoundsCarried"),
                                   script->GetDouble("RocketLauncher_FiringFreq"),
                                   script->GetDouble("RocketLauncher_IdealRange"),
                                   script->GetDouble("Rocket_MaxSpeed"),
                                   owner)
{
    //setup the vertex buffer
  const int NumWeaponVerts = 8;
  const Vector2D weapon[NumWeaponVerts] = {Vector2D(0, -3),
                                           Vector2D(6, -3),
                                           Vector2D(6, -1),
                                           Vector2D(15, -1),
                                           Vector2D(15, 1),
                                           Vector2D(6, 1),
                                           Vector2D(6, 3),
                                           Vector2D(0, 3)
                                           };
  for (int vtx=0; vtx<NumWeaponVerts; ++vtx)
  {
    m_vecWeaponVB.push_back(weapon[vtx]);
  }

  //setup the fuzzy module
  InitializeFuzzyModule();

}


//------------------------------ ShootAt --------------------------------------
//-----------------------------------------------------------------------------
inline void RocketLauncher::ShootAt(Vector2D pos)
{ 
  if (NumRoundsRemaining() > 0 && isReadyForNextShot())
  {
    //fire off a rocket!
    m_pOwner->GetWorld()->AddRocket(m_pOwner, pos);

    m_iNumRoundsLeft--;

    UpdateTimeWeaponIsNextAvailable();

    //add a trigger to the game so that the other bots can hear this shot
    //(provided they are within range)
    m_pOwner->GetWorld()->GetMap()->AddSoundTrigger(m_pOwner, script->GetDouble("RocketLauncher_SoundRange"));
  }
}

//---------------------------- Desirability -----------------------------------
//
//-----------------------------------------------------------------------------
double RocketLauncher::GetDesirability(double DistToTarget)
{
  if (m_iNumRoundsLeft == 0)
  {
    m_dLastDesirabilityScore = 0;
  }
  else
  {
      double botsInFOV = m_pOwner->GetWorld()->GetAllBotsInFOV(m_pOwner).size();
      if (botsInFOV < 1 ) botsInFOV = 0;

    //fuzzify distance and amount of ammo
    m_FuzzyModule.Fuzzify("DistToTarget", DistToTarget);
    m_FuzzyModule.Fuzzify("AmmoStatus", (double)m_iNumRoundsLeft);
    m_FuzzyModule.Fuzzify("NbEnemies", botsInFOV);
    m_FuzzyModule.Fuzzify("EnemyHealth", m_pOwner->GetTargetSys()->GetTarget()->Health());


    m_dLastDesirabilityScore = m_FuzzyModule.DeFuzzify("Desirability", FuzzyModule::max_av);
  }

  return m_dLastDesirabilityScore;
}

//-------------------------  InitializeFuzzyModule ----------------------------
//
//  set up some fuzzy variables and rules
//-----------------------------------------------------------------------------
void RocketLauncher::InitializeFuzzyModule()
{
  FuzzyVariable& DistToTarget = m_FuzzyModule.CreateFLV("DistToTarget");
  FzSet& Target_Close = DistToTarget.AddLeftShoulderSet("Target_Close",0,25,150);
  FzSet& Target_Medium = DistToTarget.AddTriangularSet("Target_Medium",25,150,300);
  FzSet& Target_Far = DistToTarget.AddRightShoulderSet("Target_Far",150,300,1000);

  FuzzyVariable& Desirability = m_FuzzyModule.CreateFLV("Desirability"); 
  FzSet& VeryDesirable = Desirability.AddRightShoulderSet("VeryDesirable", 50, 75, 100);
  FzSet& Desirable = Desirability.AddTriangularSet("Desirable", 25, 50, 75);
  FzSet& Undesirable = Desirability.AddLeftShoulderSet("Undesirable", 0, 25, 50);

  FuzzyVariable& AmmoStatus = m_FuzzyModule.CreateFLV("AmmoStatus");
  FzSet& Ammo_Loads = AmmoStatus.AddRightShoulderSet("Ammo_Loads", 10, 30, 100);
  FzSet& Ammo_Okay = AmmoStatus.AddTriangularSet("Ammo_Okay", 0, 10, 30);
  FzSet& Ammo_Low = AmmoStatus.AddTriangularSet("Ammo_Low", 0, 0, 10);

  FuzzyVariable& NbEnemies = m_FuzzyModule.CreateFLV("NbEnemies");
  FzSet& One_Enemy = NbEnemies.AddLeftShoulderSet("One_Enemy", 0, 1, 2);
  FzSet& Few_Enemies = NbEnemies.AddTriangularSet("Few_Enemies", 1, 2, 3);
  FzSet& Many_Enemies = NbEnemies.AddRightShoulderSet("Many_Enemies", 2, 3, 50);

  FuzzyVariable& EnemyHealth = m_FuzzyModule.CreateFLV("EnemyHealth");
  FzSet& Low_Health = EnemyHealth.AddLeftShoulderSet("Low_Health", 0, 20, 40);
  FzSet& Mid_Health = EnemyHealth.AddTriangularSet("Mid_Health", 40, 50, 60);
  FzSet& High_Health = EnemyHealth.AddRightShoulderSet("High_Health", 60, 80, 100);


  /*
  m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Loads), Undesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Okay), Undesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Low), Undesirable);

  m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Loads), VeryDesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Okay), VeryDesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Low), Desirable);

  m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Loads), Desirable);
  m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Okay), Undesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Low), Undesirable);*/

  m_FuzzyModule.AddRule(Target_Close, Undesirable);
  m_FuzzyModule.AddRule(One_Enemy, Undesirable);

  m_FuzzyModule.AddRule(FzAND(Target_Far, Few_Enemies), Desirable);

  m_FuzzyModule.AddRule(FzAND(Many_Enemies, Target_Far), VeryDesirable);
  m_FuzzyModule.AddRule(FzAND(Many_Enemies, Target_Medium), VeryDesirable);

  m_FuzzyModule.AddRule(FzAND(Low_Health, Target_Medium, Ammo_Loads, Few_Enemies), Desirable);
  m_FuzzyModule.AddRule(FzAND(Low_Health, Target_Medium, Ammo_Okay, Few_Enemies), Desirable);
  m_FuzzyModule.AddRule(FzAND(Low_Health, Target_Medium, Ammo_Low, Few_Enemies), Desirable);

  m_FuzzyModule.AddRule(FzAND(Mid_Health, Target_Medium, Ammo_Loads), VeryDesirable);
  m_FuzzyModule.AddRule(FzAND(Mid_Health, Target_Medium, Ammo_Okay), Desirable);
  m_FuzzyModule.AddRule(FzAND(Mid_Health, Target_Medium, Ammo_Low), Undesirable);

  m_FuzzyModule.AddRule(FzAND(High_Health, Target_Medium, Ammo_Loads), Undesirable);
  m_FuzzyModule.AddRule(FzAND(High_Health, Target_Medium, Ammo_Okay), Undesirable);
  m_FuzzyModule.AddRule(FzAND(High_Health, Target_Medium, Ammo_Low), Undesirable);





}


//-------------------------------- Render -------------------------------------
//-----------------------------------------------------------------------------
void RocketLauncher::Render()
{
    m_vecWeaponVBTrans = WorldTransform(m_vecWeaponVB,
                                   m_pOwner->Pos(),
                                   m_pOwner->Facing(),
                                   m_pOwner->Facing().Perp(),
                                   m_pOwner->Scale());

  gdi->RedPen();

  gdi->ClosedShape(m_vecWeaponVBTrans);
}