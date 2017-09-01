/*
 * Copyright (C) 2017 iCub Facility - Istituto Italiano di Tecnologia
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


// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "embot_common.h"




// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - pimpl: private implementation (see scott meyers: item 22 of effective modern c++, item 31 of effective c++
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - all the rest
// --------------------------------------------------------------------------------------------------------------------

namespace embot { namespace common {
    

    
}} // namespace embot { namespace common {



namespace embot { namespace common { namespace bit {
    

    // see http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
    static const std::uint8_t s_eocommon_oneBitsInU8[256] = 
    {
    //  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F (<- n)
    //  =====================================================
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, // 0n
        
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 1n (+1)
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 2n (+1)
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 3n (+2)    
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 4n (+1)
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 3n (+2)
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 6n (+2)
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // 7n (+3)
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 8n (+1)
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 9n (+2)
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // An (+2)
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // Bn (+3)
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // Cn (+2)
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // Dn (+3)
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // En (+3)  
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8  // Fn (+4)
    };

    std::uint8_t countU08(const std::uint8_t value)
    {
        return(s_eocommon_oneBitsInU8[value & 0xff]);
    }
    
    std::uint8_t countU16(const std::uint16_t value)
    {
        return(countU08(value&0xff)+countU08((value>>8)&0xff));
    }
    
    std::uint8_t countU32(const std::uint32_t value)
    {
        return(countU16(value&0xffff) + countU16((value>>16)&0xffff));
    }
    
    std::uint8_t countU64(const std::uint64_t value)
    {
        return(countU32(value&0xffffffff) + countU32((value>>32)&0xffffffff));
    }
    
   
} } } // namespace embot { namespace common { namespace bit


namespace embot { namespace common { namespace dsp { namespace q15 {
    
    Q15 convert(const double v, bool &saturated)
    {
        Q15result rr = static_cast<Q15result>(v * 32768.0);    // note: 32768.0 = 2^15
        return saturate(rr, saturated);        
    }
    
    Q15 U16toQ15(const std::uint16_t valU16)
    {
        return valU16-0x8000;
    }

    std::uint16_t Q15toU16(const Q15 valQ15)
    {
        return valQ15+0x8000;
    }
    
    double convert(const Q15 v)
    {
        return static_cast<double>(v) / 32768.0;  // note: 32768.0 = 2^15      
    }
    
    Q15 opposite(const Q15 v)
    {
        if(negOne == v)
        {
            return posOneNearly;
        }
        return -v;
    }
    
    Q15 saturate(const Q15result x, bool &saturated)
    {        
        if (x > 0x7FFF) 
        {
            saturated = true;
            return 0x7FFF;
        }
        else if (x < -0x8000)
        {
            saturated = true;            
            return -0x8000;
        }

        saturated = false;
        return static_cast<Q15>(x);
    }  
    
    Q15 add(const Q15 a, const Q15 b)
    {
        bool saturated = false;
        return add(a, b, saturated);
    }
    
    Q15 add(const Q15 a, const Q15 b, bool &saturated)
    {
        Q15result tmp = static_cast<Q15result>(a) + static_cast<Q15result>(b);
        
        return saturate(tmp, saturated);        
    }
    
    Q15 sub(Q15 &a, Q15 &b)
    {
        return a-b;
    }
    
    Q15 mul(const Q15 a, const Q15 b, bool &saturated)
    {
        Q15result tmp = static_cast<Q15result>(a) * static_cast<Q15result>(b); 
        
        // Rounding; mid values are rounded up
        tmp += (1 << (15 - 1));
        // Correct by dividing by base
        tmp >>= 15;
        // and saturate result
        return saturate(tmp, saturated);      
    }
    
    Q15 mul(const Q15 a, const Q15 b)
    {
        bool saturated = false;
        return mul(a, b, saturated);
    }
    
    Q15 div(const Q15 a, const Q15 b, bool &saturated)
    {
        Q15result n1 = static_cast<Q15result>(a);
        Q15result n2 = static_cast<Q15result>(b);
        Q15result rr = 0;
        std::uint8_t neg = 0;
        
        if(0 == n2)
        {
            saturated = true;
            return 0;
        }
        
        if(n1 < 0)
        {
            neg = !neg;
            n1 = -n1;
        }
        
        if(n2 < 0)
        {
            neg = !neg;
            n2 = -n2;
        }
        
        rr = (n1 << 15) / n2;
        
        if(0 != neg)
        {
            rr = - rr;
        }
        
        return saturate(rr, saturated);
    }
    
    bool add(const matrix &m1, const matrix &m2, matrix &res, bool &saturated)
    {
        if((m1.ncols != m2.ncols) || (m1.ncols != res.ncols))
        {
            return false;
        }        
        if((m1.nrows != m2.nrows) || (m1.nrows != res.nrows))
        {
            return false;
        } 

        saturated =  false;        

        // ok, we do action
        for(int r=0; r<res.nrows; r++)
        {
            for(int c=0; c<res.ncols; c++)
            {
                bool sat1 = false;
                res.data[r*res.ncols+c] = add(m1.data[r*m1.ncols+c], m2.data[r*m2.ncols+c], sat1);
                
                if(sat1)
                {
                    saturated = true;
                }
            }            
        }

        return true;        
    }
    
    bool multiply(const matrix &m1, const matrix &m2, matrix &res, bool &saturated)
    {
        if(m1.ncols != m2.nrows)
        {
            return false;
        }
        
        if(m1.nrows != res.nrows)
        {
            return false;
        }
        
        if(m2.ncols != res.ncols)
        {
            return false;
        } 

        saturated =  false; 
        std::uint32_t nsat = 0;        

        // ok, we do action
        for(int r=0; r<res.nrows; r++)
        {
            for(int c=0; c<res.ncols; c++)
            {
                Q15 v = 0;
                
                const Q15 *row_wise = &m1.data[r*m1.ncols]; // navigo con +1
                const Q15 *col_wise = &m2.data[c];          // navigo con +(m2.ncols)
                for(int i=0; i<m1.ncols; i++)
                {
                    bool sat1 = false;
                    bool sat2 = false;
                    Q15 x = mul(*row_wise, *col_wise, sat1);
                    v = add(v, x, sat2);
                    if(sat1 || sat2)
                    {
                        nsat ++;
                        saturated = true;
                    }
                    row_wise += 1;
                    col_wise += m2.ncols;
                }
                
                res.data[c + r*res.ncols] = v;
            }            
        }

        return true;
    }
   
} } } } // namespace embot { namespace common { namespace dsp { namespace q15 {



// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

