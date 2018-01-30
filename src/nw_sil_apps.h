/*============================================================================
**
**                     CONFIDENTIAL VISTEON CORPORATION
**
** This is an unpublished work of authorship, which contains trade secrets,
** created in 2010. Visteon Corporation owns all rights to this work and
** intends to maintain it in confidence to preserve its trade secret status.
** Visteon Corporation reserves the right, under the copyright laws of the
** United States or those of any other country that may have jurisdiction,
** to protect this work as an unpublished work, in the event of an
** inadvertent or deliberate unauthorized publication. Visteon Corporation
** also reserves its rights under all copyright laws to protect this work as
** a published work, when appropriate. Those having access to this work may
** not copy it, use it, modify it or disclose the information contained in
** it without the written authorization of Visteon Corporation.
**
**============================================================================
**
** Name:           sbus_apps.h
**
** Description:    NW_SIL/SBUS interface layer public header file
**
**
** Organization:   Paul Morris
**
**============================================================================
**
**==========================================================================*/
#ifndef SIL_APPS_H
#define SIL_APPS_H


/*============================================================================
** I N C L U D E   F I L E S
**==========================================================================*/
//#include "hmi_common.h"
#include "nw_sil-types.h"
#include "nw_sil.h"
#include <semaphore.h>

/*============================================================================
** T Y P E   D E F I N I T I O N S
**==========================================================================*/
/*
** HMI is using these interfaces per Aananth's direction.
** These should be changed to the following in the next release:
**
** #define HMI_NETWORK_SIGNAL_READ(SIGNAL_NAME)                 nw_sil_signal_read(SIGNAL_NAME)
** #define HMI_NEWTORK_SIGNAL_WRITE(SIGNAL_NAME, VALUE)         nw_sil_signal_write(SIGNAL_NAME, VALUE)
**
*/
//#define HMI_NETWORK_SIGNAL_READ(FRAME_P, SIGNAL_NAME)           nw_sil_read_in_frame(FRAME_P, SIGNAL_NAME)
//#define HMI_NEWTORK_SIGNAL_WRITE(FRAME_P, SIGNAL_NAME, VALUE)   nw_sil_write_in_frame(FRAME_P, SIGNAL_NAME, VALUE)

#define HMI_NETWORK_SIGNAL_READ(SIGNAL_NAME)                 nw_sil_read(SIGNAL_NAME)
#define HMI_NEWTORK_SIGNAL_WRITE(FRAME_ID,SignalID, DataP)   	nw_sil_apps_vSendMessageQueue(FRAME_ID, SignalID, DataP)// nw_sil_frame_write(FRAME_P,VALUE,SIZE)//nw_sil_write(SIGNAL_NAME, VALUE)



#define SIL_MSG_ID_MASK         (0xC000)
#define SIL_TX_DISPLAY          (0x0000)
#define SIL_RX_DISPLAY          (0x8000)
#define SIL_TX_DATA_MSG_MASK    ((0x4000) | SIL_TX_DISPLAY )
#define SIL_TX_ACTION_MSG_MASK  ((0x0000) | SIL_TX_DISPLAY )
#define SIL_RX_DATA_MSG_MASK    ((0x4000) | SIL_RX_DISPLAY )
#define SIL_RX_ACTION_MSG_MASK  ((0x0000) | SIL_RX_DISPLAY )

extern read_sil_callback sbus_apps_SBUS_DATA_Callback;
extern sem_t nw_sil_sem;

typedef enum
{
	NW_SIL_MIN_DATA = 0u,
	/*ACTION*/
	NW_SIL_INIT_DATA = NW_SIL_MIN_DATA,
	NW_SIL_FATAL_ERROR_VIP_DATA,
	NW_SIL_PULSE_GIP_DATA,
	NW_SIL_REQ_POWEROFF_DATA,
	NW_SIL_PULSE_SWITCH_DATA,
	NW_SIL_REQ_UPGRADE_DATA,
	/*DATA*/
	NW_SIL_DATA_BASE,
	NW_SIL_REP_SW_VERSION_DATA = NW_SIL_DATA_BASE,
	NW_SIL_REP_SCREENSHOT_DATA,
	NW_SIL_REP_MENU_SETUP_DATA,
	NW_SIL_MAX_DATA,
}NW_SIL_enMessageID;

typedef struct
{
	NW_SIL_enMessageID enMessage_ID;
	uint8_t* MessageData;
	uint8_t* MessageData_original;
	uint8_t u8Period;
	const uint8_t u8Period_reload;
	uint8_t u8Priority;
	bool boUpdate;
	bool boSend_Immediately;
	uint8_t u8MessageSize;
}NW_SIL_tAPP_LIST;

extern uint8_t NW_SIL_REP_SW_VERSION_FrmPtr[16];
extern uint8_t NW_SIL_INIT_DATA_FrmPtr[1];
extern uint8_t NW_SIL_FATAL_ERROR_VIP_FrmPtr[1];
extern uint8_t NW_SIL_PULSE_GIP_FrmPtr[1];
extern uint8_t NW_SIL_REQ_POWEROFF_FrmPtr[1];
extern uint8_t NW_SIL_PULSE_SWITCH_FrmPtr[1];
extern uint8_t NW_SIL_REQ_UPGRADE_FrmPtr[1];
extern void nw_sil_apps_vSendMessageQueue(NW_SIL_enMessageID FrameID, nw_sil_signal_id_t SignalID, uint32_t DataP);
extern void nw_sil_callback_init(read_sil_callback * callback);
extern void nw_sil_apps_SendMessageQueue(NW_SIL_enMessageID FrameID, nw_sil_signal_id_t SignalID, uint32_t DataP);
extern void nw_sil_apps_Main(void);
extern bool nw_sil_apps_LockMutex(void);
extern bool nw_sil_apps_UnlockMutex(void);
extern bool nw_sil_apps_tx( uint16_t FrameID, uint8_t* DataP );
extern bool sil_sbus_transmit(nw_sil_frame_id_t FrameID, const nw_sil_frame_t* Frame, nw_sil_frame_size_t FrameSize);
extern void nw_sil_apps_init (void);
extern void sbus_apps_StartTask(void);
extern void nw_sil_apps_thread(void);
extern void nw_sil_apps_StartTask(void);
extern uint8_t SBUS_CurrentState(void);

/* end of file =============================================================*/

#endif
