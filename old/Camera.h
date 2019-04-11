#pragma once

using namespace sf;

class CAnimationSingle;

using namespace std;
class CCamera //    __shared_state = {}
{
protected:
   int m_X;
   int m_Y;
   int m_PosX;
   int m_PosY;
   int m_WorldX;
   int m_WorldY;
   float m_VX;
   float m_VY;
   float m_AX;
   float m_AY;
   sf::Sprite* m_pSprite;

   sf::RenderWindow* m_pScreen;
public:
   CCamera();
   ~CCamera();

// properties
   int get_WorldX() { return m_WorldX; }
   int get_WorldY() { return m_WorldY; }
   int get_CamX()  { return m_X; }
   int get_CamY()  { return m_Y; }
   int get_CamPosX() { return m_PosX; }
   int get_CamPosY() { return m_PosY; }
   int get_Events ( sf::Event& event );
   int get_Input();
   void set_Velocity( int x, int y );
   void set_Acceleration( int x, int y);

   void MoveV( int x, int y )
   {
      m_VX+= x;
      m_VY+= y;
   }
   void MoveA( int x, int y )
   {
      m_AX+= x;
      m_AY+= y;
   }

// implemtation
   void SetPosition( int x, int y);
   void Center( int new_x, int new_y );
   void DrawTextIgnore ( sf::String text);
   void Clear();
   void Display ();
   void Update( int dt);
   void DrawSprite( sf::Sprite* pSprite );
   void Move( int x, int y );
   void Setup( int cam_x, int cam_y, int world_x, int world_y, string caption);
   void Resize ( int x, int y);
   void DrawSpriteIgnore( sf::Sprite* pSprite ) ;
   void DrawShapeIgnore( sf::Shape& shape);

};