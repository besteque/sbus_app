/*------------------------------------------------------------------------------
 * PURPOSE:
 * 
 * AUTHOR:  Frank-Rene Schaefer
 *          Visteon Deutschland GmbH, Kerpen, Germany
 * 
 * DATE:    Juli, 2010
 * 
 * (C) 2010 Visteon GmbH
 * 
 * ABSOLUTELY NO WARRANTY
 *------------------------------------------------------------------------------*/
#ifndef __INCLUDE_GUARD__NW_SIL_CORE_H__
#define __INCLUDE_GUARD__NW_SIL_CORE_H__

#include "nw_sil-types.h"
#include "nw_sil-configuration.h"

/*_____________________________________________________________________________
 * Global Objects (Singletons) of the SIL
 *_____________________________________________________________________________*/
extern const nw_sil_interface_t                 nw_sil_interface_list[NW_SIL_SETTING_INTERFACE_LIST_SIZE];
extern nw_sil_non_periodic_schedule_entry_t     nw_sil_non_periodic_schedule[NW_SIL_SETTING_NON_PERIODIC_SCHEDULE_SIZE];
extern const nw_sil_signal_position_db_entry_t  nw_sil_signal_position_db[];
extern const nw_sil_tx_frame_db_entry_t         nw_sil_tx_frame_db[NW_SIL_SETTING_TX_FRAME_DB_SIZE];
extern uint8_t                                  nw_sil_send_flags[NW_SIL_SETTING_SEND_FLAG_MASK_BYTE_N];
extern uint8_t                                  nw_sil_receive_and_receive_update_flags[NW_SIL_SETTING_RX_AND_RX_UPDATE_FLAG_BYTE_N];
extern bool                                     nw_sil_mode_match(const nw_sil_interface_t* const, nw_sil_mode_mask_t);

#   ifdef  NW_SIL_TYPE_MUTEX_VARIABLE
    extern NW_SIL_TYPE_MUTEX_VARIABLE  nw_sil_global_frame_buffer_mutex_f;
    extern NW_SIL_TYPE_MUTEX_VARIABLE  nw_sil_global_flag_mutex_f;
    extern NW_SIL_TYPE_MUTEX_VARIABLE  nw_sil_global_interfaces_mutex_f;
#   endif

/*_____________________________________________________________________________
 * Frame Buffer                
 *
 * Storage to maintain values of signals in frames.
 *_____________________________________________________________________________*/
extern bool            nw_sil_frame_db_flush(void);
extern void            nw_sil_frame_db_clear(void);

/*_____________________________________________________________________________
 * Periodic Schedule
 *
 * Management of perdiodic frame sending. The schedule is updated either via
 * a function call to 
 *
 *   -- nw_sil_periodic_schedule_on_timer_tick    (fixed time intervals)
 *   -- nw_sil_periodic_schedule_on_timer_trigger (dynamic time intervals)
 *
 * depending on whether the SIL is triggered in fixed time slots, or via 
 * dynamically varrying time intervals. In the latter case, the SIL returns
 * the time distance in future when it wants to be called next.
 *_____________________________________________________________________________*/
#if defined(NW_SIL_OPTION_DYNAMIC_TIME_TRIGGER) || defined(NW_SIL_OPTION_TRANSMIT_ON_REQUEST)
extern size_t  nw_sil_periodic_schedule_on_timer_trigger(size_t DeltaT);
#else
extern void    nw_sil_periodic_schedule_on_timer_tick(void);
#endif

#if defined(NW_SIL_OPTION_TRANSMIT_ON_REQUEST)
extern size_t  nw_sil_periodic_schedule_update_on_timer_trigger(size_t DeltaT);
extern void    nw_sil_periodic_schedule_register_sent(nw_sil_frame_id_t    FrameID, 
                                                      const nw_sil_interface_t*  interface_p);
extern void    nw_sil_periodic_schedule_register_unsent(nw_sil_frame_id_t    FrameID, 
                                                        const nw_sil_interface_t*  interface_p);
#endif
extern void    nw_sil_periodic_schedule_print(void);

/*_____________________________________________________________________________
 * Non-Periodic Schedule
 *
 * Keeping track of minimum time distance between frame transmissions.
 *_____________________________________________________________________________*/
#if defined(NW_SIL_OPTION_DYNAMIC_TIME_TRIGGER) || defined(NW_SIL_OPTION_TRANSMIT_ON_REQUEST)
extern size_t          nw_sil_non_periodic_schedule_on_timer_trigger(size_t DeltaT_ms);
#endif
extern void            nw_sil_non_periodic_schedule_on_timer_tick(void);
extern void            nw_sil_non_periodic_schedule_print(void);
extern void            nw_sil_non_periodic_schedule_register_sent(nw_sil_frame_id_t    ID, 
                                                                  const nw_sil_interface_t*  InterfaceP);
extern void            nw_sil_non_periodic_schedule_register_by_pointer(nw_sil_non_periodic_schedule_entry_t*);
extern nw_sil_non_periodic_schedule_entry_t*
                       nw_sil_non_periodic_schedule_permission_to_send(const nw_sil_frame_id_t    FrameID, 
                                                                       const nw_sil_interface_t*  InterfaceP);

/*_____________________________________________________________________________
 * Direct Notifications from the Low Level Driver
 *_____________________________________________________________________________*/
extern void            nw_sil_on_receive_interrupt(const nw_sil_interface_t*  interface_p,
                                                   nw_sil_frame_id_t          FrameID,
                                                   nw_sil_frame_t*            MemoryFramePointer,
                                                   size_t                     MemoryFrameSize);
extern void            nw_sil_on_send_notification(const nw_sil_interface_t*  interface_p, 
                                                   bool                       SuccessF,
                                                   nw_sil_frame_id_t          FrameID);

/*_____________________________________________________________________________
 * Misc Service Functions
 *_____________________________________________________________________________*/
#if defined(NW_SIL_OPTION_UNIT_TEST)
extern void   nw_sil_flags_send_print();
extern void   nw_sil_flags_receive_print();
#endif

extern void   nw_sil_flags_send_clear();
extern void   nw_sil_flags_receive_clear();

/* Access to Transmission frame information.                                   */
extern const nw_sil_tx_frame_db_entry_t*   nw_sil_tx_frame_db_entry_get(nw_sil_frame_id_t          FrameID, 
                                                                        const nw_sil_interface_t*  InterfaceP /* 0x0 */);
extern const nw_sil_rx_frame_db_entry_t*   nw_sil_rx_frame_db_entry_get(nw_sil_frame_id_t          FrameID, 
                                                                        const nw_sil_interface_t*  InterfaceP /* 0x0 */);



/* Transmission Bottleneck: All sending must pass this function.               */
extern bool   __nw_sil_send(const nw_sil_interface_t*  Interface,
                            nw_sil_frame_id_t          FrameID, 
                            const nw_sil_frame_t*      Frame, 
                            size_t                     FrameSize);

/* Receive and Receive Update Flags                                            */
extern void  nw_sil_receive_flag_set(nw_sil_receive_flag_t BitIndex);
extern void  nw_sil_receive_flag_unset(nw_sil_receive_flag_t BitIndex);
extern bool  nw_sil_receive_flag_get(nw_sil_receive_flag_t BitIndex);
extern void  nw_sil_receive_update_flag_set(nw_sil_receive_update_flag_t BitIndex);
extern bool  nw_sil_receive_update_flag_get(nw_sil_receive_update_flag_t BitIndex);

/* Macros: Bit Accesss in Byte Arrays. 
 *
 * Use following 'speed ups':
 *    integer division by 8:      byte_offset = BitIndex >> 3;  
 *    remainder of div. by 8:     bit_offset  = BitIndex & 0x7;                */
#ifndef WIN32
extern void nw_sil_flag_set(uint8_t* flag_memory, size_t BitIndex);
extern void nw_sil_flag_unset(uint8_t* flag_memory, size_t BitIndex);
extern bool nw_sil_flag_get(uint8_t* flag_memory, size_t BitIndex);
#endif
/* The macros above **cannot** be used for bit access in frames, since the 
 * alignment is reversed! Use the following:                                   */
extern bool nw_sil_frame_get_bit(nw_sil_frame_t* frame_p, size_t FrameSize, nw_sil_bit_size_t BitIndex);
extern void nw_sil_frame_set_bit(nw_sil_frame_t* frame_p, size_t FrameSize, nw_sil_bit_size_t BitIndex);
extern void nw_sil_frame_unset_bit(nw_sil_frame_t* frame_p, size_t FrameSize, nw_sil_bit_size_t BitIndex);

/* Access to signals/values in frames. These functions incorporate the 
 * secrets of 'byte offset direction' and 'byte alignment'.                    */
extern nw_sil_signal_value_t nw_sil_frame_read_value(uint8_t* frame_p,   size_t FrameSize, 
                                                     size_t   BitOffset, size_t BitNumber);
extern nw_sil_signal_value_t nw_sil_frame_write_value(uint8_t* frame_p,   size_t FrameSize, 
                                                      size_t   BitOffset, size_t BitNumber,  
                                                      nw_sil_signal_value_t Value);
extern bool                  nw_sil_frame_write_bytes(uint8_t* frame_p,    size_t FrameSize, size_t FieldByteN,
                                                      ptrdiff_t BitOffset, uint8_t  ByteOffsetN, size_t ByteN, 
                                                      uint8_t* source_p);
extern void                  nw_sil_frame_read_bytes(uint8_t*  frame_p,   size_t  FrameSize, size_t FieldByteN,
                                                     ptrdiff_t BitOffset, uint8_t ByteOffsetN, size_t ByteN, 
                                                     uint8_t*  drain_p);
/* Delayed Function Call Queues Init */
extern void                  nw_sil_context_router_queues_init(void);

/* Convert a time in millseconds into a time in ticks. 
 *
 * The time tick's size is determined by 'NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS'. 
 * The converter function rounds up or down. It is NOT a simple floor-integer 
 * division. If the result is '0' it is set automatically to '1' so that zero 
 * periods are avoided.                                                          
 *
 * NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS is supposed to be defined in 
 * "nw_sil-user-definitions.h"                                                   */
#if 0
#define NW_SIL_CONVERT_TIME_MILLISEC_TO_TICK(X)                                                                    \
        (   ((X + (NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS/2)) / NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS == 0) ? 1 \
          :  (X + (NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS/2)) / NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS )
#endif
#define NW_SIL_CONVERT_TIME_MILLISEC_TO_TICK(X)                                                     \
        (    (X) == -1                                           ? NW_SIL_SETTING_TIME_TICK_INVALID \
          : ((X) / NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS) == 0 ? 1 \
          : ((X) / NW_SIL_SETTING_TIME_TICK_GRANULARITY_MS)) 

/* Lift to process context functions (optional) */
#if defined(NW_SIL_ACTION_ROUTE_TO_PROCESS_CONTEXT_HEART_BEAT) 
    extern void nw_sil_in_process_context_heart_beat(void);
#endif
#if defined(NW_SIL_ACTION_ROUTE_TO_PROCESS_CONTEXT_RECEIVE_INTERRUPT)
    extern void nw_sil_in_process_context_on_receive_interrupt(void);
#endif

#if defined(NW_SIL_ACTION_ROUTE_TO_PROCESS_CONTEXT_SEND_NOTIFICATION_INTERRUPT)
    extern void nw_sil_in_process_context_on_send_notification_interrupt(void);
#endif

#if defined(NW_SIL_ACTION_ROUTE_TO_PROCESS_CONTEXT_FLUSH)
    extern void nw_sil_in_process_context_flush(void);
#endif

#endif /* __INCLUDE_GUARD__NW_SIL_CORE_H__ */
