#pragma once
#include <vector>
class CFrame;
class CAnimationSingle;
class CCamera;

using namespace std;

class CTiler
{
   float m_X;
   float m_X2;
   float m_Y;
   int m_NumFrames;
   int m_current_frame_num;
   int m_current_frame;
   float m_current_duration;
   float m_Time;
   float m_ImageSizeX;
   float m_ImageSizeY;

   CCamera* m_pCamera;
   sf::Sprite* m_pSprite;
   vector <CAnimationSingle*>::iterator m_Iter;
   vector <CAnimationSingle*> m_Sprites;
public:
   CTiler( sf::Sprite* pSprite, float x, float x2, float y );
   ~CTiler(void);
   void Draw();   
};

