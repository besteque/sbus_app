/*-----------------------------------------------------------------------------
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
 *-----------------------------------------------------------------------------*/

#ifndef __INCLUDE_GUARD__NW_SIL_H__
#define __INCLUDE_GUARD__NW_SIL_H__

#include "nw_sil-configuration.h"
#include "nw_sil-types.h"
#include "nw_sil-core.h"

typedef int (*read_sil_callback)(uint16_t frame_id);

/* Initialization _____________________________________________________________*/
extern void      nw_sil_init(read_sil_callback arg);

/*_____________________________________________________________________________
 * Send Control
 *
 * The SIL Send Control is designed to work in different usage scenarios:
 *
 *    (1) The SIL calls the interfaces' send functions as a reaction
 *        to a call to 'nw_sil_transmit()'.
 *
 *    (2) The SIL is asked for the next frame to be sent. 
 *
 * Scenario (1) can still be divided into two usage patterns: calls at
 * fixed and dynamic time intervals, therefore
 *
 *      nw_sil_transmit()       -- is to be called in fixed time intervals.
 *      nw_sil_transmit(DeltaT) -- is to be called in dynamic time intervals.
 *
 * The latter function returns the time distance in future when it wants to 
 * be called next time. It is then the task of the user to provide the function
 * call in the given time frame. 
 *
 * In both cases of scenario (1), the update of SIL's schedules happens 
 * on a call to the transmit functions. 
 *
 * In scenario (2) the update of schedules takes place in a separate function. 
 * This comes from the practical experience that when a new message is required
 * by the low-level driver, the current time is not necessarily available. The
 * function 
 *
 *               nw_sil_hear_beat(DeltaT)
 *
 * though, requires an argument that tells how much time has passed and returns
 * the time distance in future when it wants to be called next. This function 
 * is to be called from something like a timer event handler.
 *_____________________________________________________________________________*/
#if defined(NW_SIL_OPTION_DYNAMIC_TIME_TRIGGER) 
    extern size_t    nw_sil_heart_beat(size_t  DeltaT_ms);
#else
    extern void      nw_sil_heart_beat(void);
#endif

/*_____________________________________________________________________________
 * Receive Control
 * 
 * The following function polls frames from interfaces into SIL's frame buffer. 
 * Alternatively, frames may be received through pre-defined call-backs. See
 * also: 'nw_sil-types.h': struct 'nw_sil_interface_t' nested struct 'user'.
 *_____________________________________________________________________________*/
extern void      nw_sil_receive();

/*_____________________________________________________________________________
 * Flush
 * 
 * Iterate over all frames that have their send flag being raised and 
 * send them out. The function 'flush_this()' allows 
 *_____________________________________________________________________________*/
extern bool      nw_sil_flush();
extern bool      nw_sil_flush_this(const nw_sil_interface_t* interface_p, 
                                   nw_sil_frame_id_t         FrameID, 
                                   const uint8_t*            source_p);

/*_____________________________________________________________________________
 * Flush-Get
 *
 * Actively require a frame to be sent. This is only available if 
 * 'NW_SIL_OPTION_TRANSMIT_ON_REQUEST' is defined.
 *_____________________________________________________________________________*/
#if defined(NW_SIL_OPTION_TRANSMIT_ON_REQUEST)
extern void      nw_sil_flush_get(const nw_sil_interface_t*  interface_p, 
                                  nw_sil_frame_id_t*         frame_id, 
                                  nw_sil_frame_t**           frame_pp, 
                                  size_t*                    frame_size);
#endif

/*_____________________________________________________________________________
 * Mode Change for Interface
 *_____________________________________________________________________________*/
extern void      nw_sil_mode_set(const nw_sil_interface_t*  me, 
                                 const nw_sil_mode_t* const Mode);

/*_____________________________________________________________________________
 * Write to Signals and Frames    
 *_____________________________________________________________________________*/
extern const nw_sil_tx_frame_db_entry_t*      
                 nw_sil_frame_write(nw_sil_frame_id_t   FrameID, 
                                    const uint8_t*      source_p, 
                                    nw_sil_frame_size_t ByteN);
extern void      nw_sil_write(nw_sil_signal_id_t    SignalID, 
                              nw_sil_signal_value_t Value);
extern void      nw_sil_write_bytes(nw_sil_signal_id_t SignalID, 
                                    uint8_t            ByteOffset, 
                                    size_t             ByteN, 
                                    uint8_t*           source_p);
#if ! defined(NW_SIL_OPTION_DIRECT_SIGNAL_ACCESS_IN_FRAME)
extern void      nw_sil_write_in_frame(uint8_t*              FrameP, 
                                       nw_sil_signal_id_t    SignalID, 
                                       nw_sil_signal_value_t Value);
#else
/*               nw_sil_write_in_frame(...) is a macro.                        */
#endif
/*_____________________________________________________________________________
 * Read from Signals and Frames    
 *_____________________________________________________________________________*/
extern nw_sil_signal_value_t  nw_sil_read(nw_sil_signal_id_t SignalID);
extern void                   nw_sil_read_bytes(nw_sil_signal_id_t  SignalID, 
                                                uint8_t             ByteOffset, 
                                                size_t              ByteN, 
                                                uint8_t*            drain_p);
extern void                   nw_sil_frame_read(nw_sil_frame_id_t   FrameID, 
                                                uint8_t*            drain_p, 
                                                nw_sil_frame_size_t ByteN);
#if ! defined(NW_SIL_OPTION_DIRECT_SIGNAL_ACCESS_IN_FRAME)
extern nw_sil_signal_value_t  nw_sil_read_in_frame(uint8_t*           FrameP, 
                                                   nw_sil_signal_id_t SignalID);
#else
/*                            nw_sil_read_in_frame(...) is a macro.            */
#endif

/*_____________________________________________________________________________
 * Flags: Receive, Receive Update, and Send Flags
 *
 * Receive Flag:        whenever a frame arrives.                             
 * Receive Updata Flag: the signal's update flag is set in received frame.    
 * Send Flag:           whenever a frame is to be sent out.
 *_____________________________________________________________________________*/
extern bool   nw_sil_receive_flag_get_and_clear(nw_sil_receive_flag_t);
extern bool   nw_sil_receive_update_flag_get_and_clear(nw_sil_receive_flag_t);

extern void   nw_sil_send_request_set(nw_sil_send_flag_t);
extern bool   nw_sil_send_request_get(nw_sil_send_flag_t);
extern void   nw_sil_send_request_reset(nw_sil_frame_id_t          FrameID, 
                                        const nw_sil_interface_t*  InterfaceP);

#endif /* __INCLUDE_GUARD__NW_SIL_H__ */
