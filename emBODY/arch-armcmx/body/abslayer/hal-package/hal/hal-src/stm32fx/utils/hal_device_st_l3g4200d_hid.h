/*
 * Copyright (C) 2012 iCub Facility - Istituto Italiano di Tecnologia
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
#ifndef _HAL_STM32_SENSOR_GYRO_HID_H_
#define _HAL_STM32_SENSOR_GYRO_HID_H_


/* @file       hal_device_st_l3g4200d_hid.h
    @brief      This header file implements hidden interface to crc
    @author     marco.accame@iit.it
    @date       10/25/2012
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "hal_base.h"



// - declaration of extern public interface ---------------------------------------------------------------------------
 
#include "hal_device_st_l3g4200d.h"



// - #define used with hidden struct ----------------------------------------------------------------------------------
// empty-section


// - definition of the hidden struct implementing the object ----------------------------------------------------------
// empty-section


// - declaration of extern hidden variables ---------------------------------------------------------------------------
// empty-section

// - declaration of extern hidden functions ---------------------------------------------------------------------------

extern uint32_t hal_device_st_l3g4200d_hid_getsize(const hal_cfg_t *cfg);

extern hal_result_t hal_device_st_l3g4200d_hid_setmem(const hal_cfg_t *cfg, uint32_t *memory);


#endif  // include guard

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------




