/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

// - include guard ----------------------------------------------------------------------------------------------------
#ifndef _EODEQUE_HID_H_
#define _EODEQUE_HID_H_

#ifdef __cplusplus
extern "C" {
#endif

/* @file       EOdeque_hid.h
    @brief      This header file implements hidden interface to a EOdeque object.
    @author     marco.accame@iit.it
    @date       10/06/2009
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "EoCommon.h"

// - declaration of extern public interface ---------------------------------------------------------------------------
 
#include "EOdeque.h"


// - #define used with hidden struct ----------------------------------------------------------------------------------
// empty-section


// - definition of the hidden struct implementing the object ----------------------------------------------------------

/* @struct     EOdeque_hid
    @brief      Hidden definition. Implements private data used only internally by the 
                public or private (static) functions of the object and protected data
                used also by its derived objects.
 **/  
 
struct EOdeque_hid 
{
    /* @private                number of items in the deque. used only by the deque. */                
    eOsizecntnr_t               size;                                                            
    /* @private                index to the item in front of the deque. used only by the deque. */
    eOsizecntnr_t               first;                    
    /* @private                index to the item that will be next at the back of the deque. used only by the deque.*/
    eOsizecntnr_t               next;                    
    /* @private                size in bytes of the item object. */
    eOsizeitem_t                item_size;                
    /* @private                number of item object in the array. */
    eOsizecntnr_t               max_items;         
    /* @private                array of item object. */
    void                        *item_array_data;        
    /* @private                specialised copy for a single item object. It is called upon copy into the deque*/
    eOres_fp_voidp_voidp_t      item_copy_fn;
    /* @private                specialised remove for a single item object. It is called upon removal from the deque*/
    eOres_fp_voidp_t            item_clear_fn;
};


// - declaration of extern hidden functions ---------------------------------------------------------------------------

extern void eo_deque_hid_QuickPopFront(EOdeque * deque);


#ifdef __cplusplus
}       // closing brace for extern "C"
#endif 
 
#endif  // include-guard

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------



