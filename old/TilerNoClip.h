#pragma once
#include <vector>

class CAnimationSingle;
class CCamera;

using namespace std;

class CTilerNoClip
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
   int m_tiled_num;

   sf::Sprite* m_pSprite;
   CCamera* m_pCamera;
   vector <CAnimationSingle*> m_Sprites;

public:
   CTilerNoClip( sf::Sprite* pFrame, float x, float x2, float y );
   ~CTilerNoClip(void);
   void Resize( float x, float x2 );
   void Draw();
};
