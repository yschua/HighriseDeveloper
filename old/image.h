#pragma once

using namespace std;
using namespace sf;

class CImage
{
   vector<string> m_ImageManImages;
public:
   CImage();
   ~CImage();
   static sf::Sprite* Load( string name);
};