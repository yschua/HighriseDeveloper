#pragma once

#include "ObjectBase.h"
class CAnimationSingle;
class CTilerNoClip;
class CTilerNoClip;

class CBackground : public CObjectBase
{
   float m_X;
   float m_Y;
   CAnimationSingle* m_pBackground;
   CTilerNoClip* m_pGround;
   CTilerNoClip* m_pBuildings;

public:
   CBackground( float x, float y );
   ~CBackground();
   void Draw();
};
