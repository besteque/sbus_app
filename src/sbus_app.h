#ifndef _INCLUDE_SBUS_APP_H
#define _INCLUDE_SBUS_APP_H


#ifdef __QNXNTO__
#include <sys/neutrino.h>
#include <hw/inout.h>
#endif

//#include "nw_sil-user-definitions.h"
//#include "nw_sil-types.h"
//#include "nw_sil-configuration.h"
//#include "nw_sil-core.h"
//#include "nw_sil-encoder-decoder.h"
#include "nw_sil.h"
#include "nw_sil_apps.h"

#include "common.h"
#include "file_parser.h"

#define SND_PULS_INTERVAL		2	/* send pulse signal time interval */

#define SAVE_SIGNAL_INFO(datatype)				\
inline void save_signal_##datatype(void)		\
{												\
	int value;									\
	int len = vip_data[datatype##_e].len;		\
	value = HMI_NETWORK_SIGNAL_READ(datatype);	\
	printf(#datatype" value:%#x\n", value);		\
	write_data(datatype##_e, &value, len);		\
}


/**
 *  signal data persist function definition
 *  */
SAVE_SIGNAL_INFO(SBUS_SH_VehicleSpeedIndicated_Data);
SAVE_SIGNAL_INFO(SBUS_SH_EngineSpeedIndicated_Data);
SAVE_SIGNAL_INFO(SBUS_SH_FuelIndication_Data);
SAVE_SIGNAL_INFO(SBUS_SH_EngineCoolantIndicated_Data);
SAVE_SIGNAL_INFO(SBUS_SH_ShiftGearReminder_Data);
SAVE_SIGNAL_INFO(SBUS_SH_TPMS_Temper_Data);
SAVE_SIGNAL_INFO(SBUS_SH_TC_OdometerIndicated_Data);
SAVE_SIGNAL_INFO(SBUS_SH_TC_TripAIndicated_Data);
SAVE_SIGNAL_INFO(SBUS_SH_TC_TripBIndicated_Data);
//to be continued...

#endif	/* _INCLUDE_SBUS_APP_H */
