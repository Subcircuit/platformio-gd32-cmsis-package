/*!
    \file    gd32f403_exti.c
    \brief   EXTI driver
    
    \version 2017-02-10, V1.0.0, firmware for GD32F403
    \version 2018-12-25, V2.0.0, firmware for GD32F403
    \version 2020-09-30, V2.1.0, firmware for GD32F403
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f403_exti.h"

/*!
    \brief      deinitialize the EXTI
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exti_deinit(void)
{
    /* reset the value of all the EXTI registers */
    EXTI_INTEN = (uint32_t)0x00000000U;
    EXTI_EVEN  = (uint32_t)0x00000000U;
    EXTI_RTEN  = (uint32_t)0x00000000U;
    EXTI_FTEN  = (uint32_t)0x00000000U;
    EXTI_SWIEV = (uint32_t)0x00000000U;
}

/*!
    \brief      initialize the EXTI
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[in]  mode: interrupt or event mode, refer to exti_mode_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_INTERRUPT: interrupt mode
      \arg        EXTI_EVENT: event mode
    \param[in]  trig_type: interrupt trigger type, refer to exti_trig_type_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_TRIG_RISING: rising edge trigger
      \arg        EXTI_TRIG_FALLING: falling trigger
      \arg        EXTI_TRIG_BOTH: rising and falling trigger
    \param[out] none
    \retval     none
*/
void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type)
{
    /* reset the EXTI line x */
    EXTI_INTEN &= ~(uint32_t)linex;
    EXTI_EVEN &= ~(uint32_t)linex;
    EXTI_RTEN &= ~(uint32_t)linex;
    EXTI_FTEN &= ~(uint32_t)linex;
    
    /* set the EXTI mode and enable the interrupts or events from EXTI line x */
    switch(mode){
    case EXTI_INTERRUPT:
        EXTI_INTEN |= (uint32_t)linex;
        break;
    case EXTI_EVENT:
        EXTI_EVEN |= (uint32_t)linex;
        break;
    default:
        break;
    }
    
    /* set the EXTI trigger type */
    switch(trig_type){
    case EXTI_TRIG_RISING:
        EXTI_RTEN |= (uint32_t)linex;
        EXTI_FTEN &= ~(uint32_t)linex;
        break;
    case EXTI_TRIG_FALLING:
        EXTI_RTEN &= ~(uint32_t)linex;
        EXTI_FTEN |= (uint32_t)linex;
        break;
    case EXTI_TRIG_BOTH:
        EXTI_RTEN |= (uint32_t)linex;
        EXTI_FTEN |= (uint32_t)linex;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable the interrupts from EXTI line x
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     none
*/
void exti_interrupt_enable(exti_line_enum linex)
{
    EXTI_INTEN |= (uint32_t)linex;
}

/*!
    \brief      enable the events from EXTI line x
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     none
*/
void exti_event_enable(exti_line_enum linex)
{
    EXTI_EVEN |= (uint32_t)linex;
}

/*!
    \brief      disable the interrupt from EXTI line x
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     none
*/
void exti_interrupt_disable(exti_line_enum linex)
{
    EXTI_INTEN &= ~(uint32_t)linex;
}

/*!
    \brief      disable the events from EXTI line x
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     none
*/
void exti_event_disable(exti_line_enum linex)
{
    EXTI_EVEN &= ~(uint32_t)linex;
}

/*!
    \brief      get EXTI lines flag
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus exti_flag_get(exti_line_enum linex)
{
    if(RESET != (EXTI_PD & (uint32_t)linex)){
        return SET;
    }else{
        return RESET;
    } 
}

/*!
    \brief      clear EXTI lines pending flag
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     none
*/
void exti_flag_clear(exti_line_enum linex)
{
    EXTI_PD = (uint32_t)linex;
}

/*!
    \brief      get EXTI lines flag when the interrupt flag is set
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus exti_interrupt_flag_get(exti_line_enum linex)
{
    uint32_t flag_left, flag_right;
    
    flag_left = EXTI_PD & (uint32_t)linex;
    flag_right = EXTI_INTEN & (uint32_t)linex;
    
    if((RESET != flag_left) && (RESET != flag_right)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear EXTI lines pending flag
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     none
*/
void exti_interrupt_flag_clear(exti_line_enum linex)
{
    EXTI_PD = (uint32_t)linex;
}

/*!
    \brief      enable EXTI software interrupt event
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     none
*/
void exti_software_interrupt_enable(exti_line_enum linex)
{
    EXTI_SWIEV |= (uint32_t)linex;
}

/*!
    \brief      disable EXTI software interrupt event
    \param[in]  linex: EXTI line number, refer to exti_line_enum
                only one parameter can be selected which is shown as below:
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] none
    \retval     none
*/
void exti_software_interrupt_disable(exti_line_enum linex)
{
    EXTI_SWIEV &= ~(uint32_t)linex;
}
