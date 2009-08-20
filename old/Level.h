#pragma once
#include "ObjectBase.h"
class CFloorSpace;
class CCamera;
class CTower;
using namespace std;

class CLevel : public CObjectBase
{
   int m_X;
   int m_Y;
   int m_X2;
   int m_Level;

   int m_WorldX;
   int m_WorldY;
   CCamera* m_pCamera;
   CTower*  m_pTower;
   vector<CFloorSpace*> m_FloorSpaces;

public:
   CLevel( int levelNo, CCamera* pCam, CTower* pTower );
   ~CLevel();
   void AddFloor( CFloorSpace* pFloor );
   void Update( float dt );
   void Draw();

};
