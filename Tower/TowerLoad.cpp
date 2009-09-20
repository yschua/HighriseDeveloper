#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "../xml/tinyxml/tinyxml.h"
#include "../Types/String.h"
#include "level.h"
#include "office.h"
#include "apartment.h"
#include "tower.h"

bool Tower::Load(TiXmlNode* nTower)
{
   // TODO: move the XML code outside the tower and create an attribute system (class serializer) to move the data
   //       possibly a brige system or visitor patterm
   // Iterate through the levels
   std::cout << "DEBUG: Loading tower...\n";
   //TiXmlDocument* nDoc = nTower->Parent()->ToDocument();
   //std::cout << "DEBUG: xml output:\n";
   //nTower->P->Print();
   for (TiXmlNode* pnLevel = nTower->FirstChild("level"); pnLevel != 0; pnLevel = pnLevel->NextSibling("level"))
   {
      std::cout << "DEBUG: Loading level...\n";
      TiXmlNode* pnLevelType = pnLevel->FirstChild("type");
      TiXmlNode* pnStart = pnLevel->FirstChild("xstart");
      TiXmlNode* pnEnd = pnLevel->FirstChild("xend");
      TiXmlNode* pnLevelNo = pnLevel->FirstChild("number");
      int levelno = FromString<int>(pnLevelNo->FirstChild()->Value());
      if (pnStart || pnEnd)
      {
         std::string LevelType = pnLevelType->FirstChild()->Value();
         int XStart = FromString<int>(pnStart->FirstChild()->Value());
         int XEnd = FromString<int>(pnEnd->FirstChild()->Value());
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
            int State = (pnState) ? FromString<int>(pnState->FirstChild()->Value()) : 0;
            if (pnType || pnXPos)
            {
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
