
#ifndef __INCLUDE_COMMON_H__
#define __INCLUDE_COMMON_H__

#include <stddef.h>
#include <time.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/neutrino.h>


#define ECSPI_BASE_SIZES             0x100
#define ECSPI_1_BASE_ADDR            0x2008000

#define FILE_PATH_NAME_LEN_MAX		256
#define DATE_TIME_STR_LEN_MAX		32
#define PRINT_MSG_LEN_MAX			120

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

typedef enum tag_MSGLOGLVL
{
	MSG_LOG_DBG = 0,
	MSG_LOG_FILE,

	MSG_LOG_MAX,
}MSG_LOG_LEVEL;

typedef enum tag_MODULE
{
	IPL = 0,
	SERIAL,
	BLOCK,
	NET,
	SCREEN,
	SPI,
	IIC,
}MODULE_DEF;


//may be '__VA_ARGS__' or '##__VA_ARGS__' or '##args'
#define PRINT_SYS_MSG(level, module, fmt, args...)	\
	do{											\
		if (level == MSG_LOG_DBG) {				\
			print_sys_msg(#module, fmt, ##args);\
		}										\
		else {									\
			rel_slogf(fmt, ##args);		\
		}										\
	}while(0)

typedef struct tag_VIPData
{
	uint32_t	index;
	char		desc[100];
	uint32_t	len;		//data len

}VIP_Data;

typedef enum tag_Signal
{
	SBUS_SH_VehicleSpeedIndicated_Data_e = 0,
	SBUS_SH_EngineSpeedIndicated_Data_e,
	SBUS_SH_FuelIndication_Data_e,
	SBUS_SH_EngineCoolantIndicated_Data_e,

	SBUS_SH_ShiftGearReminder_Data_e,
	SBUS_SH_TPMS_Temper_Data_e,

	SBUS_SH_TC_OdometerIndicated_Data_e,
	SBUS_SH_TC_TripAIndicated_Data_e,
	SBUS_SH_TC_TripBIndicated_Data_e,

	// to be continued...

	MAX_VIP_SIGNALL
}VIP_Signal;

extern VIP_Data vip_data[];
extern int file_desc;


void getcurtime(char *dtime, uint32_t len);
int rel_slogf(const char *fmt, ...);
int print_sys_msg(const char *module, const char *fmt, ...);

#endif /* __INCLUDE_COMMON_H__ */
