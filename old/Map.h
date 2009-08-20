#pragma once
#include "ObjectBase.h"

class CObjectBase;
class CTower;
class CLevel;

class CMap : public CObjectBase
{
protected:
   CCamera* m_pCamera;
   CTower* m_pTower;
   int m_WorldX;
   int m_WorldY;
   float m_World_prop;
   float m_Aspect;
   int m_LevelHeight;
   sf::Image* m_MiniMap;
   sf::Sprite* m_MiniMapSprite;
   int cam_x;
   int cam_y;
   int m_X;
   int m_Y;
   int m_cambox_x;
   int m_cambox_y; 
   CAnimationSingle* m_pGround;
   CAnimationSingle* m_pSky;
   int m_GroundSize;
//   int m_Ground;
//   int m_Sky;
   sf::Shape m_pMiniBorder;
   sf::Shape m_pCambox;
   vector<CLevel*> m_ClickMap;
public:
   CMap( CTower* pTower, int world_x, int world_y );
   ~CMap();
   void DrawMap();
   void SetCallback( CLevel* level, float x, float x2, CObjectBase* object );
   CLevel* WorldClick( int x, int y, long cargo_2);
   void Click(int x, int y);
   void Resize ( int x, int y);
   void DrawMinimap( );
};

