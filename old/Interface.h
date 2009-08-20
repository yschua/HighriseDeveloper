#pragma once
#include "ObjectBase.h"
class CTower;
class CCamera;
class CAnimationSingle;

class CInterface : CObjectBase
{
   //CTower* m_pTower;
   CCamera* m_pCamera;
   CAnimationSingle* m_Clock;
   vector<CAnimationSingle*> m_Stars;
   sf::Font m_Font;
   sf::String m_Text;

   CInterface();
   ~CInterface();
   void SetStar( int star );
   void Update( float dt);
   void Draw();
};
