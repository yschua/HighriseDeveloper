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

class Tower;

// these are hard coded now but will be modifiable
class BuildStategyBase
{
protected:
   std::string mType;  // Office, Apt, Condo
   // subtype maybe, reception, cubes, datacente, boardroom (offices) or luxury/studio apt.
   int mWidth;    // in units of 9 pixels
   int mHeight;   // Levels (1,2 or 3)

public:
   BuildStategyBase()
   {
   }
   // get/set properties
   int GetWidth() { return mWidth; };
   int GetHeight() { return mHeight; };
public:
   virtual bool PlacingRoom() { return false; }
   virtual bool BuildHere (Tower* pTowwer, int x, int y);
   virtual void ShowGhostBuild (Tower* pTower, int x, int level);
};
// Offices
class BuildOfficeStategy : public BuildStategyBase
{
public:
   BuildOfficeStategy()
   {
      mType = "Office"; // May not always be the class name
      mWidth = 8;       // 72/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower, int x, int level);
};

// Apartments
class BuildApartmentStategy : public BuildStategyBase
{
public:
   BuildApartmentStategy()
   {
      mType = "Apartment"; // May not always be the class name
      mWidth = 8;       // 72/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower, int x, int level);
};

//stairs
class BuildStairStategy : public BuildStategyBase
{
public:
   BuildStairStategy()
   {
      mType = "Stairs"; // May not always be the class name
      mWidth = 2;       // 18/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return false; }
   virtual void ShowGhostBuild (Tower* pTower, int x, int level);
};

// Condos
class BuildCondoStategy : public BuildStategyBase
{
public:
   BuildCondoStategy()
   {
      mType = "Condo"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Tower* pTowwer, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Tower* pTower, int x, int level);
};

// select and drag
// build lobby
// build elevator
// build other

#endif // _BUILDSTRATEGIES_H
