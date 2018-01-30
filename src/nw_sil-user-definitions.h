
#ifndef __INCLUDE_GUARD__NW_SIL_USER_DEFINITIONS_H__
#define __INCLUDE_GUARD__NW_SIL_USER_DEFINITIONS_H__
/* User definitions _____________________________________________________________
 *
 * CONTENT: -- Definition of types to be used by the libSIL and its interface
 *             functions.
 *
 *          -- Any other content (included headers) which are to be available 
 *             in any other part of the code.
 *
 * NOTE: The content of this file is completely reconfigurable. In cases that 
 *       there is no access to 'inttypes.h', 'stdbool.h', and/or 'stddef.h' then
 *       the following types need to be defined explicitly:
 *
 *       uint8_t   --> as the type that carries 1 byte.
 *       uint16_t  --> ...         that carries 2 bytes.
 *       uint32_t  --> ...         that carries 4 bytes.
 *       uint64_t  --> ...         that carries 8 bytes.
 *       bool      --> ...         that can carry a truth value
 *       true      --> as a value that casts to 'condition true', i.e. integer 1
 *       false     --> as a value that casts to 'condition true', i.e. integer 0
 *
 * (C) 2010 Visteon Deutschland GmbH
 *
 * ABSOLUTELY NO WARRANTY 
 *_____________________________________________________________________________*/

#ifdef __cplusplus
extern "C" { 
#endif

#include <inttypes.h>   /* C99 Standard */
#include <stdbool.h>    /* C99 Standard */
#include <stddef.h>     /* C99 Standard */

#ifdef __cplusplus
}
#endif

//#include "sv_sbus.h"

/* Convert SBUS signal name from XML definition into name used in SIL */
#define SBUS_SIGNAL(name)   SBUS_SH_##name
#define SBUS_FRAME(name)	nw_sil_frame_id_##name

/* Types ______________________________________________________________________*/
/* Control of memory consumption of the SIL by defining the below types.       */
typedef uint16_t  nw_sil_time_tick_t;
typedef uint8_t   nw_sil_frame_t;       
typedef uint16_t  nw_sil_frame_id_t;    /* NW_SIL_SETTING_FRAME_ID_INVALID     */
typedef uint32_t  nw_sil_signal_value_t;/* NW_SIL_SETTING_SIGNAL_VALUE_INVALID */

typedef uint16_t  nw_sil_frame_size_t;  /* NW_SIL_SETTING_FRAME_SIZE_INVALID   */
typedef uint16_t  nw_sil_bit_size_t;    /* NW_SIL_SETTING_BIT_SIZE_INVALID     */
/*                                       * NW_SIL_SETTING_BIT_VOID             */

typedef uint8_t   nw_sil_interface_index_t; /* ... _INTERFACE_INDEX_INVALID    */

#define NW_SIL_SETTING_FRAME_ID_INVALID     (0xFFFF)
#define NW_SIL_SETTING_FRAME_SIZE_INVALID   (0xFFFF)
#define NW_SIL_SETTING_SIGNAL_VALUE_INVALID (0xFFFFFFFFu)
#define NW_SIL_SETTING_BIT_SIZE_INVALID     (0xFFFF)
#define NW_SIL_SETTING_BIT_VOID             (0xFFFE)

#define NW_SIL_SETTING_INTERFACE_INDEX_INVALID (0xFF)
#define NW_SIL_SETTING_TIME_TICK_INVALID       (0xFFFF) 

/* All sub-systems have been setup to use nw_sil_signal_write() but SIL
** is changed to nw_sil_write() to link them here or use nw_sil_write_dummy()
** to disconnect s/s for testing, etc. */
#if defined (SBUS_APPS_TEST)
  #define nw_sil_signal_write nw_sil_write_dummy
#else
  #define nw_sil_signal_write nw_sil_write
#endif

/* The error frame as defined in the XML message catalog */
#define NW_SIL_SETTING_FRAME_ID_SBUS_FATAL_ERROR     SBUS_FRAME(SBUS_FATAL_ERROR_VIP)

#define NW_SIL_OPTION_SEND_FILTER
#define NW_SIL_OPTION_TRANSMIT_ON_REQUEST
#define NW_SIL_OPTION_DYNAMIC_TIME_TRIGGER
#define NW_SIL_OPTION_SEND_MANAGER
//#define NW_SIL_OPTION_SEND_MANAGER_INTERFACE_SBUS_BACK

/* Timings ____________________________________________________________________*/
#if defined(NW_SIL_OPTION_DYNAMIC_TIME_TRIGGER)
#   define NW_SIL_SETTING_MIN_TRANSMIT_INTERVAL_MS  (10)
#   define NW_SIL_SETTING_MAX_TRANSMIT_INTERVAL_MS  (1000)
#endif
#define NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS     (4)

/* Send Manager _______________________________________________________________*/
#if defined(NW_SIL_OPTION_SEND_MANAGER)
#   define NW_SIL_SETTING_SEND_MANAGER_TIMEOUT_WAIT_SEND_NOTIFICATION_MS (1000)
#   define NW_SIL_SETTING_SEND_MANAGER_MAX_SEND_ATTEMPT_NUMBER           (4)
#   define NW_SIL_OPTION_SEND_MANAGER_INTERFACE_SBUS_FORTH
#endif

/* Mutex Definitions __________________________________________________________*/

/* #define NW_SIL_OPTION_MUTEX */
/* #define NW_SIL_TYPE_MUTEX_VARIABLE *//* Example: pthread_mutex_t            */
/*                                  * (empty if no variable to be defined)     */
#define NW_SIL_MUTEX_INIT(MUTEX)   /* Example: pthread_mutex_init(MUTEX, NULL) */
#define NW_SIL_MUTEX_LOCK(MUTEX)   /* Example: pthread_mutex_lock(MUTEX)       */
#define NW_SIL_MUTEX_UNLOCK(MUTEX) /* Example: pthread_mutex_unlock(MUTEX)     */

/* SIL Interface Callback Declerations ________________________________________*/
/* Interface User's Receive Callbacks */
extern void   sbus_apps_Rx_Callback(nw_sil_frame_id_t, const nw_sil_frame_t*, nw_sil_frame_size_t Size);
/* Interface User's Transmit Callbacks */


/* Routing to Process Context: ________________________________________________
 *
 * The following events can be raised into process context from interrupt 
 * context: 
 *
 *     -- nw_sil_heart_beat(...)            (possibly from a timer interrupt)
 *     -- nw_sil_flush(...)
 *
 * For this to happen macros must initiate the delayed call to a delayed function.
 * The function that must be called is mentioned along with the macro. If a
 * macro is not defined, it means that the call is not delayed.                
 *
 *
 * The following functions may be raised into the 'hear beat' context. Their
 * calls are implemented via queues.
 *
 *     -- nw_sil_on_receive_interrupt(...)        
 *     -- nw_sil_on_send_notification(...)        
 *                                                                             */

/* #define NW_SIL_OPTION_ROUTE_SEND_NOTIFICATION_TO_HEART_BEAT_CONTEXT          */
/* #define NW_SIL_SETTING_ON_SEND_NOTIFICATION_QUEUE_SIZE          (10)        */

/* #define NW_SIL_OPTION_ROUTE_RECEIVE_INTERRUPT_TO_HEART_BEAT_CONTEXT          */
/* #define NW_SIL_SETTING_ON_RECEIVE_INTERRUPT_QUEUE_SIZE          (10)        */

/* #define NW_SIL_ACTION_ROUTE_TO_PROCESS_CONTEXT_HEART_BEAT()                 */
/*   --> void nw_sil_in_process_context_heart_beat(void)                       */

/* #define NW_SIL_ACTION_ROUTE_TO_PROCESS_CONTEXT_FLUSH()                      */
/*   --> void nw_sil_in_process_context_flush(void)                            */

/* Tracing SIL: ________________________________________________________________
 *
 * Following Macros allow a tracing of SIL's sending, receiving and mode
 * change behavior. For tracing the following macros **must** be defined:      
 *
 * MANDATORY MACROS (may be defined empty, though):                            
 *
 * For explanatory purposes those macros are defined to work together
 * with a low level macro 'NW_SIL_FLUSH_BYTES'. If this macro is defined
 * empty, then nothing is sent, not trace channel is required.                 */

#define NW_SIL_DEBUG_SEND_TRY(INTERFACE, FRAME_ID, FRAME_SIZE, FRAME_P)     NW_SIL_DEBUG_FRAME(0x4F0, (INTERFACE), (FRAME_ID), (FRAME_SIZE), (FRAME_P))
#define NW_SIL_DEBUG_RECEIVE_TRY(INTERFACE, FRAME_ID, FRAME_SIZE, FRAME_P)  NW_SIL_DEBUG_FRAME(0x4F1, (INTERFACE), (FRAME_ID), (FRAME_SIZE), (FRAME_P))
#define NW_SIL_DEBUG_SEND_OK(INTERFACE, FRAME_ID)                           NW_SIL_DEBUG_FLUSH_BYTES(0x4F2,                                                                                                                                       (INTERFACE),                                                                                                                                 ((FRAME_ID) >> 8), ((FRAME_ID) & 0xFF),                                                                                                      0, 0, 0, 0, 0)
#define NW_SIL_DEBUG_RECEIVE_OK(INTERFACE, FRAME_ID)                        NW_SIL_DEBUG_FLUSH_BYTES(0x4F3,                                                                                                                                       (INTERFACE),                                                                                                                                 ((FRAME_ID) >> 8), ((FRAME_ID) & 0xFF),                                                                                                      0, 0, 0, 0, 0)
#define NW_SIL_DEBUG_SEND_NOTIFICATION(INTERFACE, FRAME_ID, SUCCESS_F)      NW_SIL_DEBUG_FLUSH_BYTES(0x4F4,                                                                                                                                       (INTERFACE),                                                                                                                                 ((FRAME_ID) >> 8), ((FRAME_ID) & 0xFF),                                                                                                      (SUCCESS_F),                                                                                                                                 0, 0, 0, 0)
#define NW_SIL_DEBUG_SEND_MANAGER_INIT()                                    NW_SIL_DEBUG_FLUSH_BYTES(0x4FC, 0, 0, 0, 0, 0, 0, 0, 0)
#define NW_SIL_DEBUG_MODE_SET(INTERFACE, MODE)                              NW_SIL_DEBUG_FLUSH_BYTES(0x4FD, (INTERFACE),                                                                                                                                 ((MODE) >> 8), ((MODE) & 0xFF), 0, 0, 0, 0, 0)
#define NW_SIL_DEBUG_MODE_MISMATCH(INTERFACE_P, SEND_F, FRAME_ID)           NW_SIL_DEBUG_FLUSH_BYTES(0x4FE,                                                                                                                           (INTERFACE_P - (const nw_sil_interface_t*)nw_sil_interface_list),                                                                                   (((*(INTERFACE_P->mode_pp))->bit) >> 8),                                                                                                            (((*(INTERFACE_P->mode_pp))->bit)  & 0xFF),                                                                                                         (SEND_F),                                                                                                                                           ((FRAME_ID) >> 8), ((FRAME_ID) & 0xFF), 0, 0)
#define NW_SIL_DEBUG_ERROR_MESSAGE_SIZE(INTERFACE, SEND_F, FRAME_ID, EXPECTED, REAL)  NW_SIL_DEBUG_FLUSH_BYTES(0x4FF,                                                                                                                    (INTERFACE - (const nw_sil_interface_t*)nw_sil_interface_list),                                                                                   (SEND_F),                                                                                                                 ((FRAME_ID) >> 8), ((FRAME_ID) & 0xFF),                                                                                   (EXPECTED) & 0xFF,                                                                                                        (REAL) & 0xFF,                                                                                                            0, 0)

/* Helper Macros (not required to be defined, in general):
 *
 * Flush a frame through the tracer interface:                                 */
#define NW_SIL_DEBUG_FRAME(MSG_ID, INTERFACE, FRAME_ID, SIZE, P)                         do {                                                                                  /* Filter Frame IDs as desired. */                                               if( 1 || ((FRAME_ID) & 0xFF) < 0x04 ) {                                             /* Display at max. 5 first bytes of frame */                                     NW_SIL_DEBUG_FLUSH_BYTES((MSG_ID),                                                                        (INTERFACE),                                                                     ((FRAME_ID) >> 8), ((FRAME_ID) & 0x0F),                                          (SIZE),                                                                          (((SIZE) > 0) ? (P)[0] : 0),                                                     (((SIZE) > 1) ? (P)[1] : 0),                                                     (((SIZE) > 2) ? (P)[2] : 0),                                                     (((SIZE) > 3) ? (P)[3] : 0));                        }                                                                            } while(0)


/* The tracer's bottleneck. The function below should be linked to s function 
 * that flushes bytes X0, ... X7 through some interface.                       */
#define NW_SIL_DEBUG_FLUSH_BYTES(ID, X0, X1, X2, X3, X4, X5, X6, X7)         /* empty */

#endif /* __INCLUDE_GUARD__NW_SIL_USER_DEFINITIONS_H__ */
