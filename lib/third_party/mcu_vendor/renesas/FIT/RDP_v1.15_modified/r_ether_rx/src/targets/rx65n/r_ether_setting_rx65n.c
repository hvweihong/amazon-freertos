/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.    
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_ether_setting_rx65n.c
* Version      : 1.13
* Device       : RX65N
* Description  : Ethernet module device driver
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 01.10.2016 1.00     First Release
*         : 01.10.2017 1.13     Removed ether_clear_icu_source function.
*         :                     Added RX65N-2MB support.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

#include "r_ether_rx_if.h"
#include "src/r_ether_rx_private.h"

#if defined(BSP_MCU_RX65N)
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/* Check the setting values is valid. Please review the setting values in r_ether_rx_config.h if error message is output */
    #if !((ETHER_CFG_AL1_INT_PRIORTY >= 1) && (ETHER_CFG_AL1_INT_PRIORTY <= 15))
        #error "ERROR- ETHER_CFG_AL1_INT_PRIORTY - Interrupt priority level is out of range defined in r_ether_rx_config.h."
    #endif

/***********************************************************************************************************************
* Function Name: ether_enable_icu
* Description  :
* Arguments    : channel -
*                    Ethernet channel number
*                    This is not used in this source file for this MCU group.
* Return Value : none
***********************************************************************************************************************/
void ether_enable_icu(uint32_t channel)
{
    volatile uint32_t   dummy; /* FIXME: Replace this line and last two lines to one "R_INTERNAL_NOT_USED(channel);". */
	bsp_int_ctrl_t int_ctrl;

    ICU.GENAL1.BIT.EN4 = 1;

    int_ctrl.ipl = ETHER_CFG_AL1_INT_PRIORTY;
    R_BSP_InterruptControl(BSP_INT_SRC_AL1_EDMAC0_EINT0, BSP_INT_CMD_GROUP_INTERRUPT_ENABLE, &int_ctrl);

    dummy = channel;
    R_INTERNAL_NOT_USED(&dummy); /* The '&' is for the volatile declaration of the "dummy". */
} /* End of function ether_enable_icu() */

/***********************************************************************************************************************
* Function Name: ether_disable_icu
* Description  :
* Arguments    : channel -
*                    Ethernet channel number
*                    This is not used in this source file for this MCU group.
* Return Value : none
***********************************************************************************************************************/
void ether_disable_icu(uint32_t channel)
{
    volatile uint32_t   dummy; /* FIXME: Replace this line and last two lines to one "R_INTERNAL_NOT_USED(channel);". */

    ICU.GENAL1.BIT.EN4 = 0;

    R_BSP_InterruptControl(BSP_INT_SRC_AL1_EDMAC0_EINT0, BSP_INT_CMD_GROUP_INTERRUPT_DISABLE, FIT_NO_PTR);

    dummy = channel;
    R_INTERNAL_NOT_USED(&dummy); /* The '&' is for the volatile declaration of the "dummy". */
} /* End of function ether_disable_icu() */

/***********************************************************************************************************************
* Function Name: ether_set_phy_mode
* Description  :
* Arguments    : connect -
*                    Ethernet channel number
* Return Value : none
***********************************************************************************************************************/
void ether_set_phy_mode(uint8_t connect)
{
    if (PORT_CONNECT_ET0 == (connect & PORT_CONNECT_ET0))
    {
    #if (ETHER_CFG_MODE_SEL == 0)
        /* MII */
        MPC.PFENET.BIT.PHYMODE0 = 1;
    #elif (ETHER_CFG_MODE_SEL == 1)
        /* RMII */
        MPC.PFENET.BIT.PHYMODE0 = 0;
    #endif
    }

} /* End of function ether_set_phy_mode() */

#endif  /* defined(BSP_MCU_RX65N) */

/* End of File */
