#pragma once


//	Version of DeviceDriver (Major.Minor), the same for all Microcontrollers: this Header is identical in every Microcontroller Folder
//	1.0 until the first Release Package, then incremented with every Release Package
#define DEVICEDRIVER_VERSION_MAJOR									1
#define DEVICEDRIVER_VERSION_MINOR									0


//	This DeviceDriver is built for CMOS 1.x: another Major Version of CMOS has a different Interface
#if !defined(CMOS_VERSION_MAJOR)
	#error "DeviceDriver needs CMOS 1.x: CMOS_VERSION_MAJOR is missing (include cmos.hpp first, or the CMOS Headers are too old)"
#elif CMOS_VERSION_MAJOR != 1
	#error "DeviceDriver needs CMOS 1.x: the CMOS Headers (CMOS/API/Inc) do not belong to this DeviceDriver"
#endif
