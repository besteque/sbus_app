#ifndef __INCLUDE_GUARD__NW_SIL_CONFIGURATION_H__
#define __INCLUDE_GUARD__NW_SIL_CONFIGURATION_H__
struct nw_sil_interface_t_tag;
#include "nw_sil-user-definitions.h"


/* Settings */
#define NW_SIL_MAX_FRAME_SIZE_IN_BYTES                   16 /**/
#define NW_SIL_MAX_RX_FRAME_SIZE_IN_BYTES                12 /**/
#define NW_SIL_MAX_TX_FRAME_SIZE_IN_BYTES                16 /**/
#define NW_SIL_OPTION_NON_PERIODIC_SCHEDULE              true /**/
#define NW_SIL_SETTING_FRAME_ID_LIST_TERMINATOR          NW_SIL_SETTING_FRAME_ID_INVALID /**/
#define NW_SIL_SETTING_FRAME_MEMORY_SIZE__Display        0 /**/
#define NW_SIL_SETTING_INTERFACE_LIST_SIZE               1 /**/
#define NW_SIL_SETTING_NON_PERIODIC_SCHEDULE_SIZE        9 /**/
#define NW_SIL_SETTING_NON_PERIODIC_SCHEDULE_TIME_BEYOND (NW_SIL_CONVERT_TIME_MILLISEC_TO_TICK(0) + 1) /**/
#define NW_SIL_SETTING_PERIODIC_SCHEDULE_SIZE            0 /**/
#define NW_SIL_SETTING_RX_AND_RX_UPDATE_FLAG_BYTE_N      1 /**/
#define NW_SIL_SETTING_RX_FRAME_DB_SIZE                  16 /**/
#define NW_SIL_SETTING_SEND_FLAG_MASK_BYTE_N             2 /**/
#define NW_SIL_SETTING_TX_FRAME_DB_SIZE                  9 /**/

/* Mode Declarations */
struct nw_sil_mode_t_tag;
extern const struct   nw_sil_mode_t_tag* const nw_sil__InterfaceDisplay_Mode_default_FmdHandle;
extern const struct   nw_sil_mode_t_tag* const nw_sil__InterfaceDisplay_Mode_disabled_FmdHandle;
extern const struct   nw_sil_mode_t_tag* const nw_sil__InterfaceDisplay_Mode_init_FmdHandle;
extern const struct   nw_sil_mode_t_tag* const nw_sil__InterfaceDisplay_Mode_mini_spi_FmdHandle;
extern const struct   nw_sil_mode_t_tag* const nw_sil__InterfaceDisplay_Mode_normal_FmdHandle;
extern const struct   nw_sil_mode_t_tag* const nw_sil__Interface_Mode_Null_FmdHandle;
extern const struct   nw_sil_mode_t_tag* const nw_sil__Interface_Mode_SelfCannonade_FmdHandle;


/* Null Mode */
/* extern */ nw_sil_frame_t*          nw_sil_NullMode_on_receive(nw_sil_frame_id_t x, uint8_t* y);

/* SelfCannonade Mode */
/* extern */ nw_sil_frame_t*          nw_sil_SelfCannonadeMode_on_receive(nw_sil_frame_id_t x, uint8_t* y);

#define  NW_SIL_TX_TYPE_NUMBER  (1)
#define  NW_SIL_RX_TYPE_NUMBER  (1)
typedef enum {
    NW_SIL_TX_TYPE_NORMAL = 0
} nw_sil_tx_type_t;

typedef enum {
    NW_SIL_RX_TYPE_NORMAL = 0
} nw_sil_rx_type_t;


typedef uint8_t nw_sil_mode_mask_t;



/* Interface Pointers */
#define Display_CNetHandle   (&(nw_sil_interface_list[0]))

/* Interface Drivers */
/* Interface: Display */
/* extern */ bool        sil_sbus_transmit(nw_sil_frame_id_t, const nw_sil_frame_t*, nw_sil_frame_size_t);

typedef void nw_sil_interface_parameter_Display_t;
extern const uint8_t  nw_sil_interface_parameter_Display;
/* Receive Flags */

/* Traditional Immediate Frame Flags (which are actually normal receive flags) */
#define NW_SIL_SETTING_RECEIVE_FLAG_VOID  ((nw_sil_receive_flag_t)0)
typedef uint8_t nw_sil_receive_flag_t;


/* Receive Update Flags */
#define NW_SIL_SETTING_RECEIVE_UPDATE_FLAG_VOID  ((nw_sil_receive_update_flag_t)0)
typedef uint8_t nw_sil_receive_update_flag_t;


/* Frame Memory for Interfaces */
extern const uint8_t  nw_sil_const_signal_frame_memory[];
/* NOT: extern const nw_sil_frame_t * const         __nw_sil_not_implemented_frame_p;
 *      Because, we need something that can be used in constant initialization.
 *      Let us assume that there is not frame stored at address '1'.                 */
#define __nw_sil_not_implemented_frame_p  ((const nw_sil_frame_t * const)0x1)

/* Frame Pointers: Display */
extern uint8_t       SBUS_Vehicle_Engine_Speed_DATA_FrmPtr[4];
extern const uint8_t SBUS_Vehicle_Engine_Speed_DATA_FrmPtr_backup[4];
extern uint8_t       SBUS_FUEL_EngineCoolant_DATA_FrmPtr[4];
extern const uint8_t SBUS_FUEL_EngineCoolant_DATA_FrmPtr_backup[4];
extern uint8_t       SBUS_ShiftGearReminder_DATA_FrmPtr[4];
extern const uint8_t SBUS_ShiftGearReminder_DATA_FrmPtr_backup[4];
extern uint8_t       SBUS_TemperatureDisplay_DATA_FrmPtr[2];
extern const uint8_t SBUS_TemperatureDisplay_DATA_FrmPtr_backup[2];
extern uint8_t       SBUS_Odometer_DATA_FrmPtr[12];
extern const uint8_t SBUS_Odometer_DATA_FrmPtr_backup[12];
extern uint8_t       SBUS_TC_DATA_FrmPtr[12];
extern const uint8_t SBUS_TC_DATA_FrmPtr_backup[12];
extern uint8_t       SUBS_TelltaleCtrl_DATA_FrmPtr[10];
extern const uint8_t SUBS_TelltaleCtrl_DATA_FrmPtr_backup[10];
extern uint8_t       SBUS_KeyCtrl_DATA_FrmPtr[2];
extern const uint8_t SBUS_KeyCtrl_DATA_FrmPtr_backup[2];
extern uint8_t       SBUS_TPMS_DATA_FrmPtr[12];
extern const uint8_t SBUS_TPMS_DATA_FrmPtr_backup[12];
extern uint8_t       SBUS_PULSE_VIP_FrmPtr[1];
extern const uint8_t SBUS_PULSE_VIP_FrmPtr_backup[1];
extern uint8_t       SBUS_WarningID_DATA_FrmPtr[8];
extern const uint8_t SBUS_WarningID_DATA_FrmPtr_backup[8];
extern uint8_t       SBUS_BatteryStatus_DATA_FrmPtr[1];
extern const uint8_t SBUS_BatteryStatus_DATA_FrmPtr_backup[1];
extern uint8_t       SBUS_APAStatus_DATA_FrmPtr[2];
extern const uint8_t SBUS_APAStatus_DATA_FrmPtr_backup[2];
extern uint8_t       SBUS_REQ_SW_VERSION_FrmPtr[4];
extern const uint8_t SBUS_REQ_SW_VERSION_FrmPtr_backup[4];
extern uint8_t       SBUS_POWEROFF_FrmPtr[1];
extern const uint8_t SBUS_POWEROFF_FrmPtr_backup[1];
extern uint8_t       SBUS_REQ_SCREENSHOT_FrmPtr[9];
extern const uint8_t SBUS_REQ_SCREENSHOT_FrmPtr_backup[9];
extern uint8_t       SBUS_REP_SW_VERSION_FrmPtr[16];
extern const uint8_t SBUS_REP_SW_VERSION_FrmPtr_backup[16];
extern uint8_t       SBUS_REP_SCREENSHOT_FrmPtr[1];
extern const uint8_t SBUS_REP_SCREENSHOT_FrmPtr_backup[1];
extern uint8_t       SBUS_REP_MENU_SETUP_FrmPtr[3];
extern const uint8_t SBUS_REP_MENU_SETUP_FrmPtr_backup[3];
extern uint8_t       SBUS_INIT_DATA_FrmPtr[1];
extern const uint8_t SBUS_INIT_DATA_FrmPtr_backup[1];
extern uint8_t       SBUS_FATAL_ERROR_VIP_FrmPtr[1];
extern const uint8_t SBUS_FATAL_ERROR_VIP_FrmPtr_backup[1];
extern uint8_t       SBUS_PULSE_GIP_FrmPtr[1];
extern const uint8_t SBUS_PULSE_GIP_FrmPtr_backup[1];
extern uint8_t       SBUS_REQ_POWEROFF_FrmPtr[1];
extern const uint8_t SBUS_REQ_POWEROFF_FrmPtr_backup[1];
extern uint8_t       SBUS_PULSE_SWITCH_FrmPtr[1];
extern const uint8_t SBUS_PULSE_SWITCH_FrmPtr_backup[1];
extern uint8_t       SBUS_REQ_UPGRADE_FrmPtr[1];
extern const uint8_t SBUS_REQ_UPGRADE_FrmPtr_backup[1];


/* Constant Signal Database (Each Signal One Frame) */


typedef enum {
    Display_SBUS_INIT_DATA_TxImfHandle = 0,
    Display_SBUS_FATAL_ERROR_VIP_TxImfHandle = 1,
    Display_SBUS_PULSE_GIP_TxImfHandle = 2,
    Display_SBUS_REQ_POWEROFF_TxImfHandle = 3,
    Display_SBUS_PULSE_SWITCH_TxImfHandle = 4,
    Display_SBUS_REQ_UPGRADE_TxImfHandle = 5,
    Display_SBUS_REP_SW_VERSION_TxImfHandle = 6,
    Display_SBUS_REP_SCREENSHOT_TxImfHandle = 7,
    Display_SBUS_REP_MENU_SETUP_TxImfHandle = 8,
    SendVoid_TxImfHandle = 9
} nw_sil_send_flag_t;


#define nw_sil_frame_id_SBUS_APAStatus_DATA            0x400C
#define nw_sil_frame_id_SBUS_BatteryStatus_DATA        0x400B
#define nw_sil_frame_id_SBUS_FATAL_ERROR_VIP           0x8001
#define nw_sil_frame_id_SBUS_FUEL_EngineCoolant_DATA   0x4001
#define nw_sil_frame_id_SBUS_INIT_DATA                 0x8000
#define nw_sil_frame_id_SBUS_KeyCtrl_DATA              0x4007
#define nw_sil_frame_id_SBUS_Odometer_DATA             0x4004
#define nw_sil_frame_id_SBUS_POWEROFF                  0x0001
#define nw_sil_frame_id_SBUS_PULSE_GIP                 0x8002
#define nw_sil_frame_id_SBUS_PULSE_SWITCH              0x8004
#define nw_sil_frame_id_SBUS_PULSE_VIP                 0x4009
#define nw_sil_frame_id_SBUS_REP_MENU_SETUP            0xC002
#define nw_sil_frame_id_SBUS_REP_SCREENSHOT            0xC001
#define nw_sil_frame_id_SBUS_REP_SW_VERSION            0xC000
#define nw_sil_frame_id_SBUS_REQ_POWEROFF              0x8003
#define nw_sil_frame_id_SBUS_REQ_SCREENSHOT            0x0002
#define nw_sil_frame_id_SBUS_REQ_SW_VERSION            0x0000
#define nw_sil_frame_id_SBUS_REQ_UPGRADE               0x8005
#define nw_sil_frame_id_SBUS_ShiftGearReminder_DATA    0x4002
#define nw_sil_frame_id_SBUS_TC_DATA                   0x4005
#define nw_sil_frame_id_SBUS_TPMS_DATA                 0x4008
#define nw_sil_frame_id_SBUS_TemperatureDisplay_DATA   0x4003
#define nw_sil_frame_id_SBUS_Vehicle_Engine_Speed_DATA 0x4000
#define nw_sil_frame_id_SBUS_WarningID_DATA            0x400A
#define nw_sil_frame_id_SUBS_TelltaleCtrl_DATA         0x4006

/* Signal Definitions */
/* #if ! defined(NW_SIL_OPTION_DIRECT_SIGNAL_ACCESS_IN_FRAME) */
#define SBUS_SH_APA_DisplayInfo             ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[0]))
#define SBUS_SH_APA_Status                  ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[1]))
#define SBUS_SH_BSP_VERSION                 ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[2]))
#define SBUS_SH_BatterySystemStatus         ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[3]))
#define SBUS_SH_EngineCoolantIndicated_Data ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[4]))
#define SBUS_SH_EngineSpeedIndicated_Data   ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[5]))
#define SBUS_SH_FATAL_ERROR_TO_VIP          ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[6]))
#define SBUS_SH_FuelIndication_Data         ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[7]))
#define SBUS_SH_HMI_VERSION                 ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[8]))
#define SBUS_SH_INIT_STATUS                 ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[9]))
#define SBUS_SH_InsiderTempDisplay_Data     ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[10]))
#define SBUS_SH_KANZI_VERSION               ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[11]))
#define SBUS_SH_MIDWARE_VERSION             ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[12]))
#define SBUS_SH_Menu_Language               ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[13]))
#define SBUS_SH_Menu_OverSpeed              ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[14]))
#define SBUS_SH_Menu_TiredDriveTime         ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[15]))
#define SBUS_SH_OutsiderTempDisplay_Data    ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[16]))
#define SBUS_SH_POWEROFFCMD                 ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[17]))
#define SBUS_SH_POWEROFF_STATE              ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[18]))
#define SBUS_SH_PULSENUM_GIP                ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[19]))
#define SBUS_SH_PULSENUM_VIP                ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[20]))
#define SBUS_SH_PULSE_SWITCH                ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[21]))
#define SBUS_SH_REQ_UPGRADE                 ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[22]))
#define SBUS_SH_SCREENSHOTCMD               ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[23]))
#define SBUS_SH_SCREENSHOTDOWN              ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[24]))
#define SBUS_SH_SCREENSHOTPARAMHW           ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[25]))
#define SBUS_SH_SCREENSHOTPARAMXY           ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[26]))
#define SBUS_SH_ShiftGearReminder_Data      ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[27]))
#define SBUS_SH_TC_AverageFuel_Data         ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[28]))
#define SBUS_SH_TC_AverageVehicleSpeed_Data ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[29]))
#define SBUS_SH_TC_CuurentVehicleSpeed_Data ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[30]))
#define SBUS_SH_TC_DTEIndication_Data       ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[31]))
#define SBUS_SH_TC_DriveTime_Data           ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[32]))
#define SBUS_SH_TC_InstantFuel_Data         ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[33]))
#define SBUS_SH_TC_OdometerIndicated_Data   ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[34]))
#define SBUS_SH_TC_TripAIndicated_Data      ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[35]))
#define SBUS_SH_TC_TripBIndicated_Data      ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[36]))
#define SBUS_SH_TPMS_Press_Data             ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[37]))
#define SBUS_SH_TPMS_Temper_Data            ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[38]))
#define SBUS_SH_TPMS_TireSts_Data           ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[39]))
#define SBUS_SH_Telltale_H_Data             ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[40]))
#define SBUS_SH_Telltale_L_Data             ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[41]))
#define SBUS_SH_Telltale_M_Data             ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[42]))
#define SBUS_SH_VIP_REQ_SW_VERSION          ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[43]))
#define SBUS_SH_VehicleSpeedIndicated_Data  ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[44]))
#define SBUS_SH_WarningInfo_H_Data          ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[45]))
#define SBUS_SH_WarningInfo_L_Data          ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[46]))
#define SBUS_SH_Wheel_Key_Data              ((nw_sil_signal_id_t)(&nw_sil_signal_position_db[47]))
/* #endif /+ ! defined(NW_SIL_OPTION_DIRECT_SIGNAL_ACCESS_IN_FRAME) */

/* Controller Init Function Declarations */
struct nw_sil_interface_t_tag;
/* extern */ void nw_sil_interface_send_manager_SBUS_init(const struct nw_sil_interface_t_tag*, const nw_sil_interface_parameter_Display_t*);



/* Named Values */
#define NW_SIL_SBUS_INIT_DATA_INIT_STATUS_INIT_END       0xAA
#define NW_SIL_SBUS_INIT_DATA_INIT_STATUS_INIT_START     0x00
#define NW_SIL_SBUS_KeyCtrl_DATA_Wheel_Key_Data_Down     0x02
#define NW_SIL_SBUS_KeyCtrl_DATA_Wheel_Key_Data_Left     0x03
#define NW_SIL_SBUS_KeyCtrl_DATA_Wheel_Key_Data_None     0x00
#define NW_SIL_SBUS_KeyCtrl_DATA_Wheel_Key_Data_Ok_Long  0x06
#define NW_SIL_SBUS_KeyCtrl_DATA_Wheel_Key_Data_Ok_Short 0x05
#define NW_SIL_SBUS_KeyCtrl_DATA_Wheel_Key_Data_Return   0x07
#define NW_SIL_SBUS_KeyCtrl_DATA_Wheel_Key_Data_Right    0x04
#define NW_SIL_SBUS_KeyCtrl_DATA_Wheel_Key_Data_Up       0x01
#define NW_SIL_SBUS_PULSE_SWITCH_PULSE_SWITCH_NOTREADY   0x00
#define NW_SIL_SBUS_PULSE_SWITCH_PULSE_SWITCH_READY      0x01
#define NW_SIL_SBUS_REQ_POWEROFF_POWEROFF_STATE_NOTREADY 0x00
#define NW_SIL_SBUS_REQ_POWEROFF_POWEROFF_STATE_READY    0x01
#define NW_SIL_SBUS_REQ_UPGRADE_REQ_UPGRADE_NOTREADY     0x00
#define NW_SIL_SBUS_REQ_UPGRADE_REQ_UPGRADE_READY        0x01
#define NW_SIL_SBUS_TPMS_DATA_TPMS_TireSts_Data_CmnWarn  0x01
#define NW_SIL_SBUS_TPMS_DATA_TPMS_TireSts_Data_NoWarn   0x00
#define NW_SIL_SBUS_TPMS_DATA_TPMS_TireSts_Data_SysErr   0x06
#define NW_SIL_SBUS_TPMS_DATA_TPMS_TireSts_Data_WarnFL   0x02
#define NW_SIL_SBUS_TPMS_DATA_TPMS_TireSts_Data_WarnFR   0x03
#define NW_SIL_SBUS_TPMS_DATA_TPMS_TireSts_Data_WarnRL   0x04
#define NW_SIL_SBUS_TPMS_DATA_TPMS_TireSts_Data_WarnRR   0x05


#endif /* __INCLUDE_GUARD__NW_SIL_CONFIGURATION_H__ */
