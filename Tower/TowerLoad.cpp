#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "../xml/tinyxml/tinyxml.h"
#include "../Types/String.h"
#include "Level.h"
#include "Office.h"
#include "Apartment.h"
#include "Tower.h"

/*bool Tower::Load(TiXmlNode* nTower)
{
   // TODO: move the XML code outside the tower and create an attribute system (class serializer) to move the data
   //       possibly a brige system or visitor patterm
   // Iterate through the levels
   std::cout << "DEBUG: Loading tower...\n" << nTower->Value() << "  " << nTower << '\n';
   //TiXmlDocument* nDoc = nTower->Parent()->ToDocument();
   //std::cout << "DEBUG: xml output:\n";
   //nTower->P->Print();
   TiXmlNode* pnLevel = nTower->FirstChild("level");
   std::cout << "DEBUG: Level node is " << pnLevel << std::endl;
   if (!pnLevel) return false;

   for (; pnLevel; pnLevel = pnLevel->NextSibling("level"))
   {
      std::cout << "DEBUG: Loading level... (" << pnLevel << ")\n";
      TiXmlNode* pnLevelType = pnLevel->FirstChild("type");
      TiXmlNode* pnStart = pnLevel->FirstChild("xstart");
      TiXmlNode* pnEnd = pnLevel->FirstChild("xend");
      TiXmlNode* pnLevelNo = pnLevel->FirstChild("level");
      std::cout << "DEBUG: Loaded basic nodes..." << std::endl;
      int levelno;
      if (pnStart && pnEnd && pnLevelNo && pnLevelType)
      {
         std::string LevelType = pnLevelType->FirstChild()->Value();
         int XStart = FromString<int>(pnStart->FirstChild()->Value());
         int XEnd = FromString<int>(pnEnd->FirstChild()->Value());
         levelno = FromString<int>(pnLevelNo->FirstChild()->Value());
         Level* pLevel = NULL;
         if( levelno < 1 )
         {
            pLevel = this->GetLevel(levelno);
         }
         else
         {
            // use leveltype here to pick up sky levels etc
            pLevel = NewLevel(XStart, levelno, XEnd);
         }

         for (TiXmlNode* pnRoom = pnLevel->FirstChild("room"); pnRoom != 0; pnRoom = pnRoom->NextSibling("room"))
         {
            TiXmlNode* pnType = pnRoom->FirstChild("type");
            TiXmlNode* pnXPos = pnRoom->FirstChild("xpos");
            TiXmlNode* pnState = pnRoom->FirstChild("state");

            std::cout << "Loading room. " << pnType << " " << pnXPos << " " << pnState << std::endl;
            if (pnType && pnXPos && pnState)
            {
               int State = (pnState) ? FromString<int>(pnState->FirstChild()->Value()) : 0;
               std::string Type = pnType->FirstChild()->Value();
               int XPos = FromString<int>(pnXPos->FirstChild()->Value());
               // Need a better way to do this...
               FloorBase* pRoom;
               if (Type == "office")
               {
                  pRoom = new Office(XPos, levelno, this);
                  //pRoom->SetState(State);
               }
               else if (Type == "apartment")
               {
                  pRoom = new Apartment(XPos, levelno, this);
                  //pRoom->SetState(State);
               }
               else
               {
                  std::cout << "WARNING: " << Type << " is an invalid room type!\n";
               }
               std::cout << "DEBUG: New " << Type << " on floor " << levelno << " (position " << XPos << ")\n";
               GetLevel(levelno)->AddFloorSpace(pRoom);
            }
         }
      }
      else
      {
         std::cout << "WARNING: Failed to load level " << levelno << ", could not find xstart or xend node.\n";
      }
      std::cout << "DEBUG: finished loading level " << levelno << '\n';
   }
   std::cout << "DEBUG: finished loading tower...\n";
   return true;
}

bool Tower::Save(TiXmlElement* Parent) {
   for (unsigned int i = 0; i < mLevels.size(); i++) {
      TiXmlElement* pnLevel = new TiXmlElement("level");
      mLevels[i]->Save(pnLevel);
      Parent->LinkEndChild(pnLevel);
   }
   return true;
}*/
