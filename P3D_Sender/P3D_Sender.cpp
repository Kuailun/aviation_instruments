#include "P3D_Sender.h"
using namespace std;

int __cdecl _tmain(int argc, _TCHAR* argv[])
{
	testDataRequest();
	return 0;
}

void CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{
    HRESULT hr;
    
    switch(pData->dwID)
    {
        case SIMCONNECT_RECV_ID_EVENT:
        {
            SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

            switch(evt->uEventID)
            {
                case EVENT_SIM_START:
                    
					// Now the sim is running, request information on the user aircraft
                    hr = SimConnect_RequestDataOnSimObjectType(hSimConnect, REQUEST_1, DEFINITION_1, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
					break;

                default:
                   break;
            }
            break;
        }

        case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE:
        {
            SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*)pData;
            
            switch(pObjData->dwRequestID)
            {
                case REQUEST_1:
                {
                    DWORD ObjectID = pObjData->dwObjectID;
                    airplanes_data *pS = (airplanes_data*)&pObjData->dwData;
                   // if (SUCCEEDED(StringCbLengthA(&pS->title[0], sizeof(pS->title), NULL))) // security check
                    {
						cout << pS->dGeneral_Eng_RPM[0];
                    } 
                    break;
                }

                default:
                   break;
            }
            break;
        }


        case SIMCONNECT_RECV_ID_QUIT:
        {
            quit = 1;
            break;
        }

        default:
            printf("\nReceived:%d",pData->dwID);
            break;
    }
}
void testDataRequest()
{
    HRESULT hr;

    if (SUCCEEDED(SimConnect_Open(&hSimConnect, "Request Data", NULL, 0, 0, 0)))
    {
        printf("\nConnected to Prepar3D!");   
        
        // Set up the data definition, but do not yet do anything with it
        // hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Title", NULL, SIMCONNECT_DATATYPE_STRING256);
        hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Ground Velocity", "Knots");
        hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Pitch Degrees", "degrees");
        hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Airspeed Indicated", "Knots");
        hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Flaps Available", "bool");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Alt Abvoe Ground", "feet");

        // Request an event when the simulation starts
        hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "SimStart");

        while( 0 == quit )
        {
			hr = SimConnect_RequestDataOnSimObjectType(hSimConnect, REQUEST_1, DEFINITION_1, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
			SimConnect_CallDispatch(hSimConnect, MyDispatchProcRD, NULL);
            Sleep(100);
        } 

        hr = SimConnect_Close(hSimConnect);
    }
}