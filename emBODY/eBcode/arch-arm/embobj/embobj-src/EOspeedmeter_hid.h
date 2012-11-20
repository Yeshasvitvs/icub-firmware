
// - include guard ----------------------------------------------------------------------------------------------------
#ifndef _EOSPEEDMETER_HID_H_
#define _EOSPEEDMETER_HID_H_

#ifdef __cplusplus
extern "C" {
#endif

/*  @file       EOspeedmeter_hid.h
    @brief      This header file implements hidden interface to speed meter from slow encoder.
    @author     alessandro.scalzo@iit.it
    @date       19/05/2012
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "EoCommon.h"

// - declaration of extern public interface ---------------------------------------------------------------------------
 
#include "EOspeedmeter.h"


// - #define used with hidden struct ----------------------------------------------------------------------------------
// - empty-section

// - definition of the hidden struct implementing the object ----------------------------------------------------------

/** @struct     EOspeedmeter_hid
    @brief      Hidden definition. Implements private data used only internally by the 
                public or private (static) functions of the object and protected data
                used also by its derived objects.
 **/  

struct EOspeedmeter_hid 
{
    int32_t impulse_per_revolution;
    int32_t impulse_per_revolution_by_2;
    
    int32_t time_from_last_change;
    
    int32_t calibration;
    int32_t distance;
    int32_t pos;
    
    int32_t odo_x_freq;
    int32_t speed_filt;
    int32_t speed;
    int32_t dir;
  
    eObool_t first;
}; 


// - declaration of extern hidden functions ---------------------------------------------------------------------------


#ifdef __cplusplus
}       // closing brace for extern "C"
#endif 
 
#endif  // include-guard

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------




