#pragma once
#include "FloorSpace.h"

class CLobby : public CFloorSpace
{
public:
   CLobby( CTower* pTower, float x, float x2, float y );
   ~CLobby(void);
   void DoCalcs();
   void Update( float fState );
   void SetPosition( float x, float x2 )
   {
      m_X = x;
      m_X2 = x2;
   }
   void Draw();
};


        