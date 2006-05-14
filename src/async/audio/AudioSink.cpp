/**
@file	 AudioSink.cpp
@brief   A_brief_description_for_this_file
@author  Tobias Blomberg / SM0SVX
@date	 2005-04-17

A_detailed_description_for_this_file

\verbatim
<A brief description of the program or library this file belongs to>
Copyright (C) 2003 Tobias Blomberg / SM0SVX

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
\endverbatim
*/



/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/

#include "AudioSink.h"
#include "AudioSource.h"



/****************************************************************************
 *
 * Namespaces to use
 *
 ****************************************************************************/

using namespace Async;



/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Local class definitions
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Prototypes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/




/****************************************************************************
 *
 * Local Global Variables
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Public member functions
 *
 ****************************************************************************/


/*
 *------------------------------------------------------------------------
 * Method:    
 * Purpose:   
 * Input:     
 * Output:    
 * Author:    
 * Created:   
 * Remarks:   
 * Bugs:      
 *------------------------------------------------------------------------
 */
bool AudioSink::registerSource(AudioSource *source, bool reg_sink)
{
  if (m_source != 0)
  {
    return m_source == source;
  }
  
  m_source = source;
  if (reg_sink)
  {
    if (!m_source->registerSink(this))
    {
      m_source = 0;
      return false;
    }
  }
  
  if (m_handler != 0)
  {
    if (!m_handler->registerSource(source, false))
    {
      if (reg_sink)
      {
      	m_source->unregisterSink();
      }
      m_source = 0;
      return false;
    }
  }
  
  return true;
  
} /* AudioSink::registerSource */


void AudioSink::unregisterSource(bool unreg_sink)
{
  if (m_source == 0)
  {
    return;
  }
  
  AudioSource *source = m_source;
  m_source = 0;
  
  if (unreg_sink)
  {
    source->unregisterSink();
  }
  
} /* AudioSink::unregisterSource */



/****************************************************************************
 *
 * Protected member functions
 *
 ****************************************************************************/


/*
 *------------------------------------------------------------------------
 * Method:    
 * Purpose:   
 * Input:     
 * Output:    
 * Author:    
 * Created:   
 * Remarks:   
 * Bugs:      
 *------------------------------------------------------------------------
 */
void AudioSink::sourceResumeOutput(void)
{
  if (m_source != 0)
  {
    m_source->resumeOutput();
  }
} /* AudioSink::sourceResumeOutput */


void AudioSink::sourceAllSamplesFlushed(void)
{
  if (m_source != 0)
  {
    m_source->allSamplesFlushed();
  }
} /* AudioSink::sourceAllSamplesFlushed */


bool AudioSink::setHandler(AudioSink *handler)
{
  clearHandler();
  
  if (handler == 0)
  {
    return true;
  }
  
  if (m_source != 0)
  {
    if (!m_handler->registerSource(m_source, false))
    {
      return false;
    }
  }
  
  m_handler = handler;
  
  return true;
    
} /* AudioSink::setHandler */


void AudioSink::clearHandler(void)
{
  if (m_handler == 0)
  {
    return;
  }
  
  if (m_source != 0)
  {
    m_handler->unregisterSource(false);
  }
  
  m_handler = 0;
} /* AudioSink::clearHandler */



/****************************************************************************
 *
 * Private member functions
 *
 ****************************************************************************/


/*
 *----------------------------------------------------------------------------
 * Method:    
 * Purpose:   
 * Input:     
 * Output:    
 * Author:    
 * Created:   
 * Remarks:   
 * Bugs:      
 *----------------------------------------------------------------------------
 */







/*
 * This file has not been truncated
 */
