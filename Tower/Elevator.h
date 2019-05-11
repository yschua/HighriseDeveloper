/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Highrise Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ELEVATOR_H
#define _ELEVATOR_H

// Elevator class, this is the elevator carrige.
// Handles the car movement and operations.
// Elevator is the overhead cable machine.
// LiftShaft is the evelator shaft.
// ListPit is the crash landing pit below in the event of a break failure.
// This three parts build the shaft for the elevator/lift to run in.

// class RouteBase;
struct RoutingRequest;
class AnimationSingle;
class ElevatorMachine; // mover above
class ElevatorShaft;   // holds the tiler to show the shaft
class Person;
class PersonQueue;
class Tower;
class SerializerBase;

#include "../Graphics/ModelObject.h"
#include "../Root/Physics.h"
#include "RouteBase.h"

#include <vector>

struct CallButton
{
    CallButton() : m_callUp(false), m_callDown(false) {}
    bool m_callUp;
    bool m_callDown;
};

struct FloorButton
{
    FloorButton(bool enabled=true) : m_stopping(false), m_enabled(enabled) {}
    bool m_stopping;
    bool m_enabled;
};

struct Rider
{
    Person* m_person;
    int m_destLevel;
};

class Elevator : public Body, public RouteBase, public Gfx::ModelObject // Quad morphic
{
public:
    enum LiftStyle {
        LS_Small = 0,
        LS_Standard,
        LS_HighCapacity,
        LS_Freight,
        LS_Express
    };

    Elevator(LiftStyle style, int x, short BottLevel, short TopLevel, Tower* TowerParent);
    Elevator(SerializerBase& ser, short TopLevel, Tower* TowerParent);
    virtual ~Elevator();

    static BaseType GetBaseType() { return BaseElevator; }
    static const char* GetTypeString() { return "elevator"; }

    virtual void DrawFramework() {} // later we do lifts to

    // RouteBase overrides
    bool SetCallButton(RoutingRequest& req) override;
    void SetFloorButton(RoutingRequest& req) override;
    int LoadPerson(Person* person, RoutingRequest& req) override; // return space remaining
    void Update(float dt, int tod) override;
    void Update(float dt) override;
    void Draw() override;
    void Save(SerializerBase& ser) override;
    PersonQueue* FindQueue(int level) override;
    bool StopsOnLevel(int level) override;
    int FindLobby() override;

private:
    void LoadImages();
    void PosCalc();
    Person* UnloadPerson();
    void Motion();
    void SetQueues();
    void SetStopLevels();
    void SetMinMax();
    int FindNearestCall() const; // parent
    bool KeepMovingInCurrentDirection() const;
    int GetNumLevels() const;
    int GetCurrentLevel() const;
    bool CanStop() const;
    int GetNumRiders() const;

private:
    static int gElevatorsNumber;
    static const int mStandingPositions[];

    AnimationSingle* mElevatorImage;
    AnimationSingle* mLiftPit;
    AnimationSingle* mRiderImage;
    ElevatorMachine* mLiftMachine;
    ElevatorShaft* mElevatorShaft;

    // Serializer attributes
    int mNumber; // number of this lift
    int mX;
    int mY;
    float mZ;
    short mTopLevel;
    short mBottomLevel;
    short mPosition;
    short mDirection;
    short mIdleTime;
    short mEnd2; // unused
    short mOffset; // adjust for starting floor.
    short mRidersOnBoard;
    short mMaxCap;

    // calculated values
    short mMaxFloorY;
    short mMinFloorY;

    LiftStyle mLiftStyle;
    std::vector<PersonQueue*>* mRouteQueues; // person queue for elevators that stop on this level

    Tower* mTowerParent;

    // TODO lobby should be level value of 0, consistent with the rest

    std::map<int, FloorButton> m_floorButtons;
    std::map<int, CallButton> m_callButtons; // parent, should also check if there are people queuing
    bool m_idle;
    bool m_dirUp;
    std::vector<Rider> m_riders;
};

#endif
