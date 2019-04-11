#pragma once
#include "ObjectBase.h"
class CCamera;
class CTower;
class CAnimation;
class CLevel;

using namespace sf;
using namespace std;

class CFloorSpace: public CObjectBase
{
protected: // so we can use these in extestions of this
   float m_X;
   float m_X2;
   float m_Y;
   int m_NumFrames;
   int m_Level;
   float m_CurrentState;
   float m_current_duration;
   float m_Time;
   float m_ImageSizeX;
   float m_ImageSizeY;
   float m_WorldX;
   float m_WorldY;

   CLevel* m_pLevel;
   CAnimation* m_pCurrentAnimation;
   CTower*  m_pTower;
   CCamera* m_pCamera;
   CAnimationSingle* m_pSprite;
   vector <sf::Image*> m_Frames;
   vector <float> m_Durations;

public:
   CFloorSpace(sf::Sprite* pSprite, CTower* pTower, float x, float x2, float y);
   ~CFloorSpace(void);

   // properties
   float get_X() { return m_X; }
   float get_X2() { return m_X2; }
   float get_Y() { return m_Y; }
   void set_Position( float x, float y )
   {
      m_X = x;
      m_Y = y;
   }
   // implementation
   void Update( float state );
   void Draw();
};

