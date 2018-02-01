/*
 * common.c
 *
 *  Created on: 2018-1-29
 *      Author: xuyang
 */
#include "sbus_app.h"



VIP_Data vip_data[] =
{
	/* index     								desc                  len */
	{SBUS_SH_VehicleSpeedIndicated_Data_e,    	"VehicleSpeed",       	2	},
	{SBUS_SH_EngineSpeedIndicated_Data_e,     	"EngineSpeed",      	2	},

	{SBUS_SH_FuelIndication_Data_e,     		"Fuel",      			2	},
	{SBUS_SH_EngineCoolantIndicated_Data_e,  	"EngineCoolant",      	2	},

	{SBUS_SH_ShiftGearReminder_Data_e,			"ShiftGear",			2   },
	{SBUS_SH_TPMS_Temper_Data_e,				"Temperature",			2   },

	{SBUS_SH_TC_OdometerIndicated_Data_e,		"Odometer",				4   },
	{SBUS_SH_TC_TripAIndicated_Data_e,			"TripA",				4   },
	{SBUS_SH_TC_TripBIndicated_Data_e,			"TripB",				4   },

	// to be continued...
};



/**
 * 待增加字节序转换处理
 */
void record_vip_data(uint16_t frame_id)
{
	//uint16_t double_bytes;
	//uint32_t four_bytes;

	switch (frame_id)
	{
		case nw_sil_frame_id_SBUS_Vehicle_Engine_Speed_DATA:
		{
			// fetch VehicleSpeed
			//double_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_VehicleSpeedIndicated_Data);
			//write_data(SBUS_SH_VehicleSpeedIndicated_Data_e, (void*)&double_bytes, sizeof(double_bytes));
			//printf("VehicleSpeed:%#x\n", double_bytes);
			save_signal_SBUS_SH_VehicleSpeedIndicated_Data();

			// fetch EngineSpeed
			//double_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_EngineSpeedIndicated_Data);
			//write_data(SBUS_SH_VehicleSpeedIndicated_Data_e, (void*)&double_bytes, sizeof(double_bytes));
			//printf("EngineSpeed:%#x\n", double_bytes);
			save_signal_SBUS_SH_EngineSpeedIndicated_Data();

			break;
		}

		case nw_sil_frame_id_SBUS_FUEL_EngineCoolant_DATA:
		{
			// fetch Fuel
			//double_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_FuelIndication_Data);
			//write_data(SBUS_SH_FuelIndication_Data_e, (void*)&double_bytes, sizeof(double_bytes));
			//printf("Fuel:%#x\n", double_bytes);
			save_signal_SBUS_SH_FuelIndication_Data();

			// fetch EngineCoolant
			//double_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_EngineCoolantIndicated_Data);
			//write_data(SBUS_SH_EngineCoolantIndicated_Data_e, (void*)&double_bytes, sizeof(double_bytes));
			//printf("EngineCoolant:%#x\n", double_bytes);
			save_signal_SBUS_SH_EngineCoolantIndicated_Data();

			break;
		}

		case nw_sil_frame_id_SBUS_ShiftGearReminder_DATA:
		{
			// fetch ShiftGear
			//double_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_ShiftGearReminder_Data);
			//write_data(SBUS_SH_ShiftGearReminder_Data_e, (void*)&double_bytes, sizeof(double_bytes));

			save_signal_SBUS_SH_ShiftGearReminder_Data();

			break;
		}

		case nw_sil_frame_id_SBUS_TemperatureDisplay_DATA:
		{
			//double_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_TPMS_Temper_Data);
			//write_data(SBUS_SH_TPMS_Temper_Data_e, (void*)&double_bytes, sizeof(double_bytes));

			save_signal_SBUS_SH_TPMS_Temper_Data();

			break;
		}

		case nw_sil_frame_id_SBUS_Odometer_DATA:
		{
			//four_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_TC_OdometerIndicated_Data);
			//write_data(SBUS_SH_TC_OdometerIndicated_Data_e, (void*)&four_bytes, sizeof(four_bytes));
			save_signal_SBUS_SH_TC_OdometerIndicated_Data();

			//four_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_TC_TripAIndicated_Data);
			//write_data(SBUS_SH_TC_TripAIndicated_Data_e, (void*)&four_bytes, sizeof(four_bytes));
			save_signal_SBUS_SH_TC_TripAIndicated_Data();

			//four_bytes = HMI_NETWORK_SIGNAL_READ(SBUS_SH_TC_TripBIndicated_Data);
			//write_data(SBUS_SH_TC_TripBIndicated_Data_e, (void*)&four_bytes, sizeof(four_bytes));
			save_signal_SBUS_SH_TC_TripBIndicated_Data();

			break;
		}

		// to be continued...

		default:break;
	}

}


int app_sil_callback(uint16_t frame_id)
{

	PRINT_SYS_MSG(MSG_LOG_DBG, SPI, "receive msg,frame_id:0x%x\n", frame_id);

	record_vip_data(frame_id);

	return 0;
}

/*
 * global param:file_desc
 */
int main(int argc, char *argv[])
{
	//int i = 0;
	uint8_t u8PulseSignal[1] ={ 0xaa};
	struct timespec t;
	uint64_t begin, nsec;
	//char now_tm[DATE_TIME_STR_LEN_MAX] = {0};

	PRINT_SYS_MSG(MSG_LOG_DBG, SPI, "1111111111111\n");

	/* for test */
	int j = 0, dbg_q = 0;
	if (argc >= 2 )
	{
		dbg_q = strtoul(argv[1], 0, 0);
	}

	if (ThreadCtl(_NTO_TCTL_IO, 0) == -1) {
		perror("ThreadCtl");
		return (!EOK);
	}

	/* file that exchange data with kanzi */
	file_desc = create_fle(NULL,NULL);


	/* initialize */
	//HMI_NEWTORK_SIGNAL_WRITE(NW_SIL_INIT_DATA, SBUS_SH_INIT_STATUS,
	//		NW_SIL_SBUS_INIT_DATA_INIT_STATUS_INIT_START);
	HMI_NEWTORK_SIGNAL_WRITE(NW_SIL_INIT_DATA, SBUS_SH_INIT_STATUS,
			NW_SIL_SBUS_INIT_DATA_INIT_STATUS_INIT_START);

	// invoke for the 2st times will lead to memory fault,WHY?
	nw_sil_init(app_sil_callback);

	HMI_NEWTORK_SIGNAL_WRITE(NW_SIL_INIT_DATA, SBUS_SH_INIT_STATUS,
		NW_SIL_SBUS_INIT_DATA_INIT_STATUS_INIT_END);


	clock_gettime (CLOCK_REALTIME, &t);
	begin = t.tv_sec;


	for (;;) {

		clock_gettime (CLOCK_REALTIME, &t);
		nsec = t.tv_sec;
		if ((nsec-begin) >= SND_PULS_INTERVAL)
		{
			//i = 0;
			begin = nsec;

			/* send pulse to keep alive */
			HMI_NEWTORK_SIGNAL_WRITE(NW_SIL_PULSE_GIP_DATA, SBUS_SH_PULSENUM_GIP, (uint32_t)u8PulseSignal[0]);
			PRINT_SYS_MSG(MSG_LOG_DBG, SPI, "send msg,frame_id:%#x\n", nw_sil_frame_id_SBUS_PULSE_GIP);


			/* for test */
			j++;
			if ((argc >= 2) && (j >= dbg_q))
			{
				printf("dbginfo:threshold(%d), value(%d)\n", dbg_q, j);
				goto cleanup;
			}

			//printf("now is :%s\n", now_tm);
			/* end for test */
		}
	}

/* release resources */
cleanup:
	close_file(file_desc);

	return EXIT_SUCCESS;
}
