#include <vector>
#include <iostream>
// these are for Randomization used for testing
#include <math.h>
#include <stdlib.h>
//
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Image.h"
#include "Level.h"
#include "Camera.h"
#include "Tower.h"
#include "AnimationSingle.h"
#include "Office.h"
#include "Map.h"
#include "ot.h"

//from PySFML import sf
//from rfsm import rfsm
//from tower import tower
//from animation import animation
//from background import background
//from buildings import *
//from camera import camera
//from interface import interface
//from map import map

//import psyco
//psyco.full ()
using namespace sf;
int Run()
{
   CCamera* cam = new CCamera();
   cam->Setup( 800, 600, 1200, 1080, "Test" );
   //cam->Sset_max_framerate(60);
   CImage* image_man = new CImage();
   CTower Tower;
   sf::Event event;
   COffice my_office( &Tower, 400, 1, 72 );
   COffice my_office2( &Tower, 400, 2, 72 );
   COffice my_office3( &Tower, 472, 1, 72 );
   COffice my_office4( &Tower, 472, 2, 72 );
   COffice my_office5( &Tower, 544, 1, 72 );
   COffice my_office6( &Tower, 544, 2, 72 );
   COffice my_office7( &Tower, 450, 3, 72 );
   COffice my_office8( &Tower, 522, 3, 72 );
   CLevel level_1( 1, cam,  &Tower );
   CLevel level_2( 2, cam,  &Tower );
   CLevel level_3( 3, cam,  &Tower );
   level_1.AddFloor( &my_office );
   level_1.AddFloor( &my_office3 );
   level_1.AddFloor( &my_office5 );
   level_2.AddFloor( &my_office2 );
   level_2.AddFloor( &my_office4 );
   level_2.AddFloor( &my_office6 );
   level_3.AddFloor( &my_office7 );
   level_3.AddFloor( &my_office8 );
   while (1)
   {
      while (cam->get_Events(event))
      {
         if (event.Type == sf::Event::Closed)
         {
            exit (0);
         }
         if (event.Type == sf::Event::KeyPressed) {
            if (event.Key.Code == sf::Key::A)
            {
               cam->MoveV( -200, 0 );
               cam->MoveA( 150, 0 );
            }
            if (event.Key.Code == sf::Key::S)
            {
               cam->MoveV( 200, 0 );
               cam->MoveA( -150, 0 );
            }
            if (event.Key.Code == sf::Key::D)
            {
               cam->MoveV( 0, 200 );
               cam->MoveA( 0, -150 );
            }
            if (event.Key.Code == sf::Key::W)
            {
               cam->MoveV( 0, -200 );
               cam->MoveA( 0, 150 );
            }
            if (event.Key.Code == sf::Key::E)
            {
               cam->set_Velocity( 0, 0 );
            }
         }
      }
      cam->Clear ();
//      cam->Integrate (60);
      level_1.Update (60);
      level_1.Draw ();
      level_2.Update (60);
      level_2.Draw ();
      level_3.Update (60);
      level_3.Draw ();
      cam->Display ();
   }
   delete cam;
   return 0;
}
