//from PySFML import sf
//from camera import camera
//import ConfigParser
//import sys, os
//import image

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Frame.h"
#include "Camera.h"
#include "AnimationSingle.h"
#include "Animation.h"

CAnimation::CAnimation()
{
   m_NumFrames = 0;
   m_X = 0;
   m_Y = 0;
   m_current_duration = 0.0;
   m_current_frame_num = 0;
   m_current_frame = 0;//None;
   m_Time = 0.0;
   m_pCamera = new CCamera();
}

CAnimation::~CAnimation()
{
   try
   {
      delete m_pSprite;
      delete m_pCamera;
   }
   catch( ... )
   {
      std::cout << "CAnimation DTOR: Error freeing local members!";
      // aler
   }
}

void CAnimation::AddFrame( sf::Image* pFrame, float duration )
{
   if( this->m_Frames.size() == 0 )
   {
      //      sf::Sprite::__init__ (this, pFrame); no compiley
   }
   m_Frames.push_back( pFrame );
   m_Durations.push_back( duration );
   //   m_num_frames += 1  the m_Frames collection does this for you
   m_current_frame = (int)m_Frames.size() -1; //m_frames[0]
   m_current_duration = (float)m_Durations.size();
}

void CAnimation::Update( float dt)
{
   m_Time += dt;
   if( m_Time >= m_current_duration )
   {
      m_current_frame_num += 1;
      m_Time = 0;
      if( m_current_frame_num >= (int)m_Frames.size() ) // m_num_frames
      {
         m_current_frame_num = 0;
      }
      m_pSprite->SetImage( *m_Frames[m_current_frame_num] );
      m_current_duration = m_Durations[m_current_frame_num];
   }
}

void CAnimation::Draw( ) 
{
   m_pCamera->DrawSprite( m_pSprite->GetSprite() );
}

void CAnimation::Load( string ini_file, string section_name) 
{
   //float ini = ConfigParser.ConfigParser();         got owned here, need to learn about this Parser
   //ini.read (os.path.join ('data', ini_file))
   //for im, duration in ini.items (section_name) :
   //{
   //   m_add_frame (image.load (im), int (duration))
   //}
}


