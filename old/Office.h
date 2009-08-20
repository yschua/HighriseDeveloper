#pragma once
#include "FloorSpace.h"
class CAnimation;

class COffice :  public CFloorSpace
{
protected:
   float m_DT;
   float m_CurrentState;
   CAnimation* m_pCurrentAnimation;
   float m_current_duration;
public:
   // CTOR/DTOR
   COffice( CTower* pTower, float x, float level, float x2 );
   ~COffice(void);
   // Properties

   // Implentation
   void UnoccupiedDay( float dt );
   void OccupiedDay( float dt );
};

