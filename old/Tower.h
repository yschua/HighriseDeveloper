#pragma once
#include "Map.h"

class CLevel;
class CPerson;
class CFloorSpace;
class CMap;

using namespace std;

class CTower
{
protected:
   vector <CLevel*> m_Levels;// = {}
   vector <CPerson*> m_People;// = []
   int m_Pop;
   //int m_num_levels = num_levels
   CMap* m_Map; // = None

public:
   // CTOR/DTOR
   CTower(void);
   ~CTower(void);

   //properties
   int get_Pop()
   {
      return m_Pop;
   }
   int get_Levels()
   {
      return (int)m_Levels.size();
   }

   void SetMapCallBack( CLevel* m_Level, float m_X, float m_X2, CObjectBase* pBase )
   {
      m_Map->SetCallback( m_Level, m_X, m_X2, pBase ); // owned here too
   }

   CMap* GetMap()
   {
      return m_Map;
   }
   void SetMap( CMap* pMap ) { m_Map = pMap; };
   // Implementation
   void Update( float dt );
   void Draw();
   void AddFloorSpace( CLevel* pLevel, CFloorSpace* pBuilding );

};

