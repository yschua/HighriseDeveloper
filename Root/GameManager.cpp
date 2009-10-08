#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "../Types/String.h"

#include "../xml/tinyxml/tinyxml.h"
#include "Physics.h"
#include "XMLSerializer.h"
#include "../Graphics/Texture.h"

#include "../Tower/Routes.h"
#include "../Tower/Routes.h"
#include "../Tower/FloorBase.h"
#include "../Tower/Level.h"
#include "../Tower/Office.h"
#include "../Tower/Apartment.h"
#include "../Tower/Lobby.h"
#include "../Tower/Tower.h"
#include "../Tower/RouteBase.h"  // Elevators route (levels).
#include "../Tower/ElevatorBase.h"
#include "../Tower/Elevator.h"
#include "../Tower/SkyLobby.h"
#include "../Scene/Scene.h"

#include "GameManager.h"

GameManager::GameManager (Scene& scene)
:  mScene(scene)
{
}

bool GameManager::LoadGame (const char *fileName)
{
   // stuffing the floors with test spaces
   TiXmlDocument* xml = new TiXmlDocument();
   xml->LoadFile(fileName);
   std::cout << "DEBUG: " << xml->Value() << " output: \n";
   xml->Print();

   TiXmlNode* pnGame = xml->FirstChild();
   //std::cout << "DEBUG: Root node: " << nTower->Value() << '\n';
   if ((!xml->Error()) || pnGame)
   {
      TiXmlNode* pnName = pnGame->FirstChild("name");
      TiXmlNode* pnNet = pnGame->FirstChild("net");
      TiXmlNode* pnPop = pnGame->FirstChild("population");
      TiXmlNode* pnTime = pnGame->FirstChild("time");
      // Data needs to be push/pulled through a class attribute
      TiXmlNode* pnTower = pnGame->FirstChild("tower");
      //std::cout << "DEBUG: Root node: " << nTower->Value() << '\n';
      if ((!xml->Error()) || pnTower)
      {
         Scene::TypeTowerIterator it;
         Scene::TypeTowerVector& towers = mScene.GetTowers();
         for( it=towers.begin(); it!=towers.end(); it++ )
         {
            LoadTower(pnTower, (*it));
         }
      }
   }
   else
   {
      std::cout << "WARNING: Failed to load demo tower: " << xml->ErrorDesc() << std::endl
                << " row: " << xml->ErrorRow() << " col: " << xml->ErrorCol()
                << " id: " << xml->ErrorId() << " file: " << xml->Value() << '\n'
                << "DEBUG: File contents (if any): \n";

      xml->Print();
   }
   delete xml;
   return true;
}

void GameManager::Add( TiXmlNode* pnElement, const char* szTag, const char* szText)
{
   TiXmlElement* pnXPos = new TiXmlElement(szTag);
   pnXPos->LinkEndChild (new TiXmlText( szText ));
   pnElement->LinkEndChild(pnXPos);
}

bool GameManager::SaveGame(const char *fileName)
{
   TiXmlDocument* pDoc = new TiXmlDocument( fileName );
   TiXmlNode* pnRoot = new TiXmlElement("highrisetower");
//   mTower->Save(pRoot);
   TiXmlElement* pnTower = new TiXmlElement("tower");

   pDoc->LinkEndChild (pnRoot);

   int net = 100000;
   int pop = 1;
   int time = (int)(12.5*60);  // 12:30

   Add( pnRoot, "name","Tower One");
   Add( pnRoot, "net",ToString (net).c_str());
   Add( pnRoot, "population", ToString (time).c_str());

   pnRoot->LinkEndChild (pnTower);

   Scene::TypeTowerIterator it;
   Scene::TypeTowerVector& towers = mScene.GetTowers();
   for( it=towers.begin(); it!=towers.end(); it++ )
   {
      SaveTower( pnTower, (*it) );
   }

   std::cout << "DEBUG: Output of save attempt: \n";
   pDoc->Print();
   pDoc->SaveFile();
   return true;
}

bool GameManager::LoadTower(TiXmlNode* pnTower, Tower* pTower)
{
   // TODO: move the XML code outside the tower and create an attribute system (class serializer) to move the data
   //       possibly a brige system or visitor patterm
   // Iterate through the levels
   std::cout << "DEBUG: Loading tower...\n" << pnTower->Value() << "  " << pnTower << '\n';
   //TiXmlDocument* nDoc = nTower->Parent()->ToDocument();
   //std::cout << "DEBUG: xml output:\n";
   //nTower->P->Print();
   TiXmlNode* pnLevel = pnTower->FirstChild("level");
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
            pLevel = pTower->GetLevel(levelno);
         }
         else
         {
            // use leveltype here to pick up sky levels etc
            pLevel = pTower->NewLevel(XStart, levelno, XEnd);
         }

         for (TiXmlNode* pnRoom = pnLevel->FirstChild("room"); pnRoom != 0; pnRoom = pnRoom->NextSibling("room"))
         {
            TiXmlNode* pnType = pnRoom->FirstChild("type");
            TiXmlNode* pnXPos = pnRoom->FirstChild("xpos");
            TiXmlNode* pnXEnd = pnRoom->FirstChild("xend");
            TiXmlNode* pnState = pnRoom->FirstChild("state");

            if (pnType && pnXPos && pnState)
            {
               int State = (pnState) ? FromString<int>(pnState->FirstChild()->Value()) : 0;
               std::string Type = pnType->FirstChild()->Value();
               int XPos = FromString<int>(pnXPos->FirstChild()->Value());
               int XEnd = 0;
               std::cout << "Loading room. " << Type << " " << XPos << " " << State << std::endl;
               if( pnXEnd!= NULL)
               {
                  XEnd = FromString<int>(pnXEnd->FirstChild()->Value());
               }
               // Need a better way to do this...
               FloorBase* pRoom = NULL;
               if (Type == "office")
               {
                  pRoom = new Office(XPos, levelno, pTower);
                  pTower->GetLevel(levelno)->AddFloorSpace(pRoom);
               }
               else if (Type == "apartment")
               {
                  pRoom = new Apartment(XPos, levelno, pTower);
                  pTower->GetLevel(levelno)->AddFloorSpace(pRoom);
               }
               else if (Type == "skylobby")
               {
                  pRoom = new SkyLobby(XPos, XEnd, levelno, pTower);
                  pTower->GetLevel(levelno)->AddFloorSpace(pRoom);
               }
               else
               {
                  std::cout << "WARNING: " << Type << " is an invalid room type!\n";
               }
               std::cout << "DEBUG: New " << Type << " on floor " << levelno << " (position " << XPos << ")\n";
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

bool GameManager::SaveTower(TiXmlElement* pnTower, Tower* pTower)
{
   Tower::LevelIterator it;
   Tower::LevelVector& theLevels = pTower->GetLevels();     // Lobby is at mNo_SubLevels not zero

   for (it=theLevels.begin(); it!=theLevels.end(); it++)
   {
      Level* pLevel = (*it);
      TiXmlElement* pnLevel = new TiXmlElement("level");
      XMLSerializer xmlLevel( pnLevel );
      pLevel->Save( xmlLevel );
      pnTower->LinkEndChild(pnLevel);
      Level::FloorMap& fps = pLevel->GetFloorSpaces();
      for (unsigned int i = 0; i < fps.size(); i++)
      {
         TiXmlElement* pnSpace = new TiXmlElement("room");
         XMLSerializer xmlRoom(pnSpace);
         fps[i]->Save( xmlRoom );
         pnLevel->LinkEndChild(pnSpace);
      }
   }
   Routes::RoutesVector& routes = pTower->GetRouteList();
   Routes::RouteIterator iR;
   for (iR=routes.begin(); iR!=routes.end(); iR++)
   {
      TiXmlElement* pnEle = new TiXmlElement("elevator");
      RouteBase* pR = *(iR);
      XMLSerializer xmlEle( pnEle );
      pR->Save( xmlEle );
      pnTower->LinkEndChild(pnEle);
   }
   return true;
}
