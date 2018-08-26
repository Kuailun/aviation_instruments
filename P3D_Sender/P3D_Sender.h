#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "SimConnect.h"
#include <strsafe.h>
#include <iostream>

///	\brief	A flag to mark whether quit P3D
///	\details
///			If receiving data from P3D(SIMCONNECT_RECV_ID_QUIT), then quit=1.
//
int     quit = 0;

///	\brief	Handle which represent the P3D
///	\details
///			Need to be initialised by SimConnect_Open().
///			Nearly every function in P3D need this parameter.
///			Need to be closed by SimConnect_Close().
//
HANDLE  hSimConnect = NULL;

///	\brief	Data struct which would be fetched from P3D
///	\details
///			Fetching data from P3D and then build the data which would be sent to 
///			aviation_instrument.
//
struct airplanes_data
{
	///	\brief	Data struct which would be fetched from P3D
	///	\details
	///			Fetching data from P3D and then build the data which would be sent to 
	///			aviation_instrument.
	//
	double  dGeneral_Eng_RPM[2];
	double  dPlan_pitch_deg;
	double  dAirspeed_ind;
	bool    bFlaps_ava;
	double  dPlane_alt;
};

enum EVENT_ID {
	EVENT_SIM_START,
};

enum DATA_DEFINE_ID {
	DEFINITION_1,
};

enum DATA_REQUEST_ID {
	REQUEST_1,
};
int __cdecl _tmain(int argc, _TCHAR* argv[]);
void CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext);
void testDataRequest();