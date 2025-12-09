#pragma once

#include "cmos.hpp"





class Debug
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		uint16 m_revisionID;
		uint16 m_deviceID;
		
		
		//	Constructor and Destructor
		constexpr inline Debug();
		Debug(const Debug& debug) = delete;
		inline ~Debug();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		constexpr inline uint16 get_revisionID() const;
		constexpr inline uint16 get_deviceID() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Debug::Debug()
	:	m_revisionID(0),
		m_deviceID(0)
{
	
}


inline Debug::~Debug()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

constexpr inline uint16 Debug::get_revisionID() const
{
	return(m_revisionID);
}


constexpr inline uint16 Debug::get_deviceID() const
{
	return(m_deviceID);
}