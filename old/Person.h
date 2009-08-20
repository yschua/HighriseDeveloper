#pragma once
#include "objectbase.h"

class CPerson :
   public CObjectBase
{
protected:
   int m_Level;

public:
   CPerson(void);
   ~CPerson(void);
   void Update( float dt );
   void Draw();
};
