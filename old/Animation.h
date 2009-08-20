#pragma once

#include <vector>

class CCamera;
class CAnimationSingle;
using namespace std;

class CAnimation //(sf.Sprite) :
{
   int m_X;
   int m_Y;
   int m_NumFrames;
   int m_current_frame_num;
   int m_current_frame;
   float m_current_duration;
   float m_Time;

   CCamera* m_pCamera;
   CAnimationSingle* m_pSprite;
   vector <sf::Image*> m_Frames;
   vector <float> m_Durations;

public:
   CAnimation();
   ~CAnimation();

   void AddFrame( sf::Image* pFrame, float duration );
   void SetPosition( int x, int y )
   {
      m_X = x;
      m_Y = y;

   }
   void Update( float state );
   void Draw();
   void Load( std::string ini_file, std::string section_name );

};
