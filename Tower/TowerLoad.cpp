#include "../xml/tinyxml/tinyxml.h"
#include "tower.h"
#include "level.h"
#include "../Types/String.h"
#include "office.h"
#include <iostream>

bool Tower::Load(TiXmlNode* nTower)
{
   int level = 1;

   // Iterate through the levels
   for (TiXmlNode* nLevel = nTower->FirstChild("level"); nLevel != 0; nLevel = nLevel->NextSibling("level"))
   {
      std::cout << "Loading level " << level << '\n';
      TiXmlNode* nStart = nLevel->FirstChild("xstart");
      TiXmlNode* nEnd = nLevel->FirstChild("xend");
      if (nStart || nEnd) {
         int XStart = ToInt(nStart->FirstChild()->ValueStr());
         int XEnd = ToInt(nEnd->FirstChild()->ValueStr());
         NewLevel(XStart, level, XEnd);

         for (TiXmlNode* nRoom = nLevel->FirstChild("room"); nRoom != 0; nRoom = nRoom->NextSibling("room")) {
            TiXmlNode* nType = nRoom->FirstChild("type");
            TiXmlNode* nXPos = nRoom->FirstChild("xpos");
            if (nType || nXPos) {
               std::string Type = nType->FirstChild()->ValueStr();
               int XPos = ToInt(nXPos->FirstChild()->ValueStr());
               // Need a better way to do this...
               FloorBase* pRoom;
               if (Type == "office") {
                  pRoom = new office(XPos, level, this);
                  GetLevel(level)->AddFloorSpace(pRoom);
               } else {
                  std::cout << "WARNING: " << Type << " is an invalid room type!\n";
               }
               std::cout << "DEBUG: New " << Type << " on floor " << level << " (position " << XPos << ")\n";

            }
         }
      } else {
         std::cout << "WARNING: Failed to load level " << level << ", could not find xstart or xend node.\n";
      }
      std::cout << "Loaded level " << level << '\n';
      level++;
   }
}
