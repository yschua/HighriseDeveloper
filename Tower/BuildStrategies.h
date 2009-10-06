/*   This file is part of Highrise Developer.
 *
 *   Highrise Developer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Highrise Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Highrise Developer.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _BUILDSTRATEGIES_H
#define _BUILDSTRATEGIES_H
#include <string>
#include <map>

class Tower;

// these are hard coded now but will be modifiable
class BuildStrategyBase
{
protected:
   std::string mType;  // Office, Apt, Condo
   // subtype maybe, reception, cubes, datacente, boardroom (offices) or luxury/studio apt.
   int mWidth;    // in units of 9 pixels
   int mHeight;   // Levels (1,2 or 3)

public:
   BuildStrategyBase()
   {
   }
   // get/set properties
   int GetWidth() { return mWidth; };
   int GetHeight() { return mHeight; };
public:
   virtual bool PlacingRoom() { return false; }
   virtual bool BuildHere (Tower* pTowwer, int x, int y);
   virtual void ShowGhostBuild (Tower* pTower);
};

class BuildStrategyFactory
{
   BuildStrategyFactory();
//   BuildStrategyBase* MakeStrategy (const char* type );
   BuildStrategyBase* MakeStrategy (int type );
};

// Offices
class BuildOfficeStrategy : public BuildStrategyBase
{
public:
   BuildOfficeStrategy()
   {
      mType = "Office"; // May not always be the class name
      mWidth = 8;       // 72/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// Apartments
class BuildApartmentStrategy : public BuildStrategyBase
{
public:
   BuildApartmentStrategy()
   {
      mType = "Apartment"; // May not always be the class name
      mWidth = 8;       // 72/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

class BuildHotelStrategy : public BuildStrategyBase
{
public:
   BuildHotelStrategy(int units)
   {
      mType = "Hotel"; // May not always be the class name
      mWidth = units;       // 72/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

//stairs
class BuildStairStrategy : public BuildStrategyBase
{
public:
   BuildStairStrategy()
   {
      mType = "Stairs"; // May not always be the class name
      mWidth = 2;       // 18/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return false; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// Condos
class BuildCondoStrategy : public BuildStrategyBase
{
public:
   BuildCondoStrategy()
   {
      mType = "Condo"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// 
class BuildHousekeepingStrategy : public BuildStrategyBase
{
public:
   BuildHousekeepingStrategy()
   {
      mType = "Housekeeping"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// 
class BuildServiceStrategy : public BuildStrategyBase
{
public:
   BuildServiceStrategy()
   {
      mType = "Services"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// 
class BuildSecurityStrategy : public BuildStrategyBase
{
public:
   BuildSecurityStrategy()
   {
      mType = "Security"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// 
class BuildClinicStrategy : public BuildStrategyBase
{
public:
   BuildClinicStrategy()
   {
      mType = "Clinic"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// 
class BuildWasteManagementStrategy : public BuildStrategyBase
{
public:
   BuildWasteManagementStrategy()
   {
      mType = "WasteManagement"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// 
class BuildRetailStrategy : public BuildStrategyBase
{
public:
   BuildRetailStrategy()
   {
      mType = "RetailShop"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

class BuildRestaurantStrategy : public BuildStrategyBase
{
public:
   BuildRestaurantStrategy()
   {
      mType = "Restaurant"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower);
};

// select and drag
// build lobby
// build elevator
// build other

#endif // _BUILDSTRATEGIES_H
