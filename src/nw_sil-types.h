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
 *-----------------------------------------------------------------------------*/

#ifndef __INCLUDE_GUARD__NW_SIL_TYPES_H__
#define __INCLUDE_GUARD__NW_SIL_TYPES_H__

#include "nw_sil-configuration.h"

/*_____________________________________________________________________________
 * Mode [ROM]
 *-----------------------------------------------------------------------------
 * An interface can be in different modes that distinguish by the set 
 * of frames that can be sent and received. It is possible, also, to determine
 * for each through what type of 'slot' frames are transmitted and received. 
 *_____________________________________________________________________________*/

typedef struct nw_sil_mode_t_tag { 
    /* For each Rx/Tx type there is a list of frames associated to it. The type
     * names are specified in the global variables "nw_sil_rx_types[]" and 
     * "nw_sil_tx_types[]". The number of rx/tx types are give by the macros  
     * NW_SIL_RX_TYPE_NUMBER and NW_SIL_TX_TYPE_NUMBER.                        */
#   if defined(NW_SIL_OPTION_SET_LOW_LEVEL_TX_FRAME_SLOTS)
    const nw_sil_frame_id_t*  (frame_list_array_tx[NW_SIL_TX_TYPE_NUMBER]);
#   endif
#   if defined(NW_SIL_OPTION_SET_LOW_LEVEL_RX_FRAME_SLOTS)
    const nw_sil_frame_id_t*  (frame_list_array_rx[NW_SIL_RX_TYPE_NUMBER]);
#   endif
     
    /* If the following bit is set in a mode mask, this means that this mode 
     * is active/allowed for the entry.                                        */
    nw_sil_mode_mask_t        bit;

#   if defined(NW_OPTION_DEBUG)
    const char*               name;
#   endif

} nw_sil_mode_t;

/*_____________________________________________________________________________
 * Interface [ROM]
 *-----------------------------------------------------------------------------
 * An object of this type stores information about the current mode, but
 * also a set of function pointers that abstract a controller interface.
 * The function pointers must be set to real functions of the controller
 * driver. One function: user_on_receive_callbacks() is generated and set
 * by the code generator.
 *_____________________________________________________________________________*/
#if defined(NW_SIL_OPTION_SEND_MANAGER)
    struct nw_sil_send_manager_t_tag;
#endif

typedef struct nw_sil_interface_t_tag {
    /* -- The interface itself can reside in ROM. 
     * -- The mode object contains constant data and may reside in ROM.
     * -- The current mode of the interface may change, so some pointer 
     *    must remain in RAM. 
     *
     * THUS:
     *         [ ROM ]        [ RAM ]         [ ROM ]
     *         mode_pp ---->  (pointer)       mode object0
     *                                  `---> mode object1
     *                                        mode object2
     *
     * Changing the mode corresponds to changing the intermediate pointer
     * that resides in RAM.                                                    */
    const nw_sil_mode_t**   mode_pp;

    /* A driver that wants to connect to the SIL needs to provide some of the 
     * following functions in the 'driver' struct. A function pointer that is 
     * set to 0x0 is not going to be used by the SIL. Details about the functions
     * can be found in the documentation.                                      */
    struct { 
        /* Return string representing the current driver version.              */
        const char* (*version)(void);

        /* Send frame via interface.                                           */
        bool        (*send)(nw_sil_frame_id_t        FrameID, 
                            const nw_sil_frame_t*    Frame, 
                            nw_sil_frame_size_t      FrameSize);

        /* Return number of newly received frames.                             */
        /* Access the newly received frame with Index (where Index < N).       */
        size_t      (*get_frame_number)(const struct nw_sil_interface_t_tag* me); 
        void        (*frame_access)(const struct nw_sil_interface_t_tag* me, size_t Index, 
                                    nw_sil_frame_id_t* frame_id, uint8_t** frame_p, 
                                    size_t* frame_size); 
        void        (*frame_access_end)(const struct nw_sil_interface_t_tag* me, 
                                        size_t Index); 

        /* Set Tx/Rx frames for filtering inside the interface. 
         *
         * If filtering is supposed to happen inside the SIL, the function 
         * pointers must be set to zero.                                          
         *
         * Functions receive a zero terminated list of frame identifiers.      */
#       if defined(NW_SIL_OPTION_SET_LOW_LEVEL_TX_FRAME_SLOTS)
        void        (*set_tx_frames)(const struct nw_sil_interface_t_tag* me, 
                                     nw_sil_tx_type_t               tx_type,
                                     const nw_sil_frame_id_t*       frame_list_zero_terminated);    
#       endif
#       if defined(NW_SIL_OPTION_SET_LOW_LEVEL_RX_FRAME_SLOTS)
        void        (*set_rx_frames)(const struct nw_sil_interface_t_tag* me, 
                                     nw_sil_rx_type_t               rx_type,
                                     const nw_sil_frame_id_t*       frame_list_zero_terminated);    
#       endif

    } driver;

    /* The invocation of user callbacks happens by means of the function 
     * pointers which are defined in the structure 'user'.                     */
    struct { 
        void   (*on_send_notification_callbacks)(nw_sil_frame_id_t, bool SuccessF);
        void   (*on_receive_callbacks)(nw_sil_frame_id_t, 
                                       const nw_sil_frame_t*, 
                                       nw_sil_frame_size_t Size);
        bool   (*has_send_notification_callbacks)(nw_sil_frame_id_t);
        bool   (*has_receive_callbacks)(nw_sil_frame_id_t);
    } user;

#   if defined(NW_SIL_OPTION_SEND_MANAGER)
    /* If there is a send manager the following pointer is == 0x0,
     * otherwise it is initialized to 0x0. The function nw_sil_send_manager_init()
     * ensures that the send manager points to its interface and vice versa. */      
    struct nw_sil_send_manager_t_tag**   send_manager_pp;
#   endif

} nw_sil_interface_t;

/*_____________________________________________________________________________
 * Periodic Schedule [RAM and ROM]
 * (Optimized for min. RAM usage)
 *-----------------------------------------------------------------------------
 * This schedule takes care of the periodic sending of signals. It is divided
 * into a constant and a variable part, so that RAM can be spared as much as 
 * possible. Each structure definition relates to 'columns' in a table, i.e.
 *
 *    nw_sil_periodic_schedule_const_t --> columns with constant data
 *
 *    nw_sil_periodic_schedule_entry_t --> columns with variable data
 *
 * Both tables are lined up in paralell. If '__schedule' is the array of 
 * variable entries, and '__const_info' the array of constant infos, then
 *
 *    __schedule + offset  <--(corresponds to)--> __const_info + offset
 *
 * Where 'offset' is of type 'ptrdiff_t' which results on both sides in 
 * corresponding entries. At the same time the 'offset' corresponds 
 * implicitly to a particular transmission frame. 
 *
 * Example: 
 *
 *   __const_info in ROM               __schedule in RAM         Offset (FrameID)
 *   (...periodic_schedule_const_t)    (...periodic_schedule_t)
 *   period_ticks  send_request_bit    tick_n_till_send
 *            64                 4          10                      0     (37E)
 *            63                 7          13                      1     (2FF)
 *            47                 1          11                      2     (7FE)
 *
 * The mapping from frame id/interface to 'offset' happens internally in auto-
 * generated functions. Those functions are then fix at compile time.
 *             
 * The implementation is generated in 'nw_sil_periodic_schedule.c'.
 *_____________________________________________________________________________*/

typedef struct nw_sil_periodic_schedule_const_t_tag {
     /* The 'frame_id' is implicitly specified by the position in the array.   */
     nw_sil_time_tick_t   period_ticks;          /* send period in ticks.      */
     nw_sil_bit_size_t    send_request_bit;      /* send request bit for frame */

} nw_sil_periodic_schedule_const_t;

typedef struct nw_sil_periodic_schedule_entry_t_tag { 
     nw_sil_time_tick_t       tick_n_till_send;  /* ticks until next sending.  */

} nw_sil_periodic_schedule_entry_t;

/*_____________________________________________________________________________
 * Non Periodic Schedule [RAM and ROM]
 * (Optimized for min. RAM usage)
 *-----------------------------------------------------------------------------
 * Some signals can only be sent with a minimum time distance. The 'non
 * periodic schedule' tracks information about recently sent frames to 
 * implement the minimum time distance between signals. As the periodic 
 * schedule it is divided into a constand and a variable part:
 *
 *    nw_sil_non_periodic_schedule_const_entry_t --> columns with constant data
 *
 *    nw_sil_non_periodic_schedule_entry_t --> column with variable data
 *
 * Both tables are lined up in paralell. If '__schedule' is the array of 
 * variable entries, and '__const_info' the array of constant infos, then
 *
 *    __schedule + offset  <--(corresponds to)--> __const_info + offset
 *
 * The implementation is generated in 'nw_sil_non_periodic_schedule.c'.
 * For details about the idea to split into ROM and RAM, review the comment
 * about 'nw_sil_periodic_schedule_t'.
 *_____________________________________________________________________________*/

typedef struct nw_sil_non_periodic_schedule_const_entry_t_tag { 
    /* FrameID/Interface can be concluded from position in the array. */
    nw_sil_time_tick_t    min_send_distance_ticks;

} nw_sil_non_periodic_schedule_const_entry_t; 

typedef struct nw_sil_non_periodic_schedule_entry_t_tag { 
    nw_sil_time_tick_t  tick_n_till_allowed_to_send;

    uint16_t            next_i;
    uint16_t            previous_i;

} nw_sil_non_periodic_schedule_entry_t;

/*_____________________________________________________________________________
 * Frame Databases [ROM]
 *-----------------------------------------------------------------------------
 * Tx Frame Database -- for frames to be transmitted.
 * Rx Frame Database -- for received frames.
 *
 * Both databases share common columns. Those are combined in a common base
 * class 'nw_sil_frame_db_entry_t_tag'. 
 *
 * The signal position database stores information about what signal is 
 * located where in memory and at what bit position.
 *_____________________________________________________________________________*/
typedef struct nw_sil_frame_db_entry_t_tag {
    nw_sil_frame_id_t        id;
    nw_sil_interface_index_t interface_index;
    nw_sil_frame_t*          pointer;
    nw_sil_frame_size_t      size;       /* [byte] */

} nw_sil_frame_db_entry_t;

typedef struct nw_sil_tx_frame_db_entry_t_tag {
    nw_sil_frame_db_entry_t   base;
    /* send bit = (position - schedule base), i.e. pointer offset.             */

    /* The following points to the entry in the non-periodic table which
     * is concerned with the min. time distance between frame transmissions.   */
    ptrdiff_t                 non_periodic_table_index;

    /* List of receive update informations. 
     * List is terminated by 'NW_SIL_SETTING_BIT_VOID'.                        */
    const nw_sil_bit_size_t*  update_bit_list;

    /* Send On Change: 
     *   true  -- if a value is written that changed the value, set the send flag.
     *   false -- do not set the send flag.                                      
     *
     * Send On Write:
     *   true  -- always set the send flag if something is written to the signal.
     *   false -- do not set the send flag.                                      
     *
     * NOTE: If none of both is set, then values are not sent at all (except
     *       by the periodic scheduler, if they are periodic).                 */
    bool                      send_on_change_f;
    bool                      send_on_write_f;

/* #   ifdef NW_SIL_OPTION_SEND_FILTER */
    /* Bit mask of all modes in which the frame is allowed to be transmitted.  */
    nw_sil_mode_mask_t        mode_bit_mask;
/* #   endif */

} nw_sil_tx_frame_db_entry_t;

/* The case to the derived class 'nw_sil_tx_frame_db_entry_t' is only 
 * admissible, if the frame is a tx-frame, i.e. it lies inside the tx-frame-
 * database. All casts shall happen with the macro below!                      
 *
 * RETURNS: NULL    -- if cast is not admissible. 
 *          Pointer -- to an object of class 'nw_sil_tx_frame_db_entry_t'      */
#define nw_sil_tx_frame_db_entry_cast_from_base(X) \
       ((const nw_sil_tx_frame_db_entry_t*)(       \
           (X <  (const nw_sil_frame_db_entry_t*)&nw_sil_tx_frame_db[0])                               ? (void*)0 \
         : (X >= (const nw_sil_frame_db_entry_t*)&nw_sil_tx_frame_db[NW_SIL_SETTING_TX_FRAME_DB_SIZE]) ? (void*)0 \
         : (X)))

/*_____________________________________________________________________________
 * Frame Databases [ROM]
 *-----------------------------------------------------------------------------
 * Tx Frame Database -- for frames to be transmitted.
 * Rx Frame Database -- for received frames.
 *
 * The signal position database stores information about what signal is 
 * located where in memory and at what bit position.
 *_____________________________________________________________________________*/
typedef struct nw_sil_receive_update_info_t_tag { 
    nw_sil_bit_size_t              bit_in_frame;
    nw_sil_receive_update_flag_t   receive_update_flag;

} nw_sil_receive_update_info_t;

typedef struct nw_sil_rx_frame_db_entry_t_tag { 
    nw_sil_frame_db_entry_t              base;

    /* List of receive flags related to the given frame. 
     * List is terminated by 'NW_SIL_SETTING_RECEIVE_FLAG_VOID'.               */
    const nw_sil_receive_flag_t*         receive_flag_list; 

    /* List of receive update informations. 
     * List is terminated by 'NW_SIL_SETTING_RECEIVE_UPDATE_FLAG_VOID'.        */
    const nw_sil_receive_update_info_t*  receive_update_info_list;

    /* Bit mask of all modes in which the frame is allowed to be received.     */
    nw_sil_mode_mask_t                   mode_bit_mask;

} nw_sil_rx_frame_db_entry_t;

/*_____________________________________________________________________________
 * Signal Position Database [ROM]
 *-----------------------------------------------------------------------------
 * The signal position database stores information about what signal is 
 * located where in memory and at what bit position.
 *_____________________________________________________________________________*/
typedef struct nw_sil_signal_position_db_entry_t_tag {
    nw_sil_frame_db_entry_t*      frame_info;
    nw_sil_bit_size_t             bit_offset;
    nw_sil_bit_size_t             length;
#   if    defined(NW_SIL_OPTION_SIGNAL_VALUE_CHECK_ON_READ) \
       || defined(NW_SIL_OPTION_SIGNAL_VALUE_CHECK_ON_WRITE)
    nw_sil_signal_value_t         min_value;
    nw_sil_signal_value_t         max_value;
#   endif

} nw_sil_signal_position_db_entry_t;

/*_____________________________________________________________________________
 * Signal ID = Pointer to a signal position entry. 
 *-----------------------------------------------------------------------------
 * Pointers to the signal position database are used as signal identifier
 * This allows fast access to signal information based on the given id.   
 *_____________________________________________________________________________*/
typedef const struct nw_sil_signal_position_db_entry_t_tag*    nw_sil_signal_id_t;



#endif /* __INCLUDE_GUARD__NW_SIL_TYPES_H__ */
