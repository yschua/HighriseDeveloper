#pragma once

class CFrame
{
public:
   int m_Width;
   int m_Height;
   CFrame(void);
   ~CFrame(void);
   int GetHeight() { return m_Height; };
   int GetWidth() { return m_Width; };
};
