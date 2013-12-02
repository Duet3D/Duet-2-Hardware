/**
 * \file
 *
 * \brief Timer management for lwIP example.
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include "board.h"
#include "timer_mgt_sam.h"
#include "tc.h"
#include "pmc.h"
#include "sysclk.h"
#include "lwip/sys.h"
/** Clock tick count */
static volatile uint32_t gs_ul_clk_tick;

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	/* Remove warnings */
	volatile uint32_t ul_dummy;

	/* Clear status bit to acknowledge interrupt */
	ul_dummy = TC0->TC_CHANNEL[0].TC_SR;

	/* Increase tick */
	gs_ul_clk_tick++;
}

/**
 * \brief Initialize for timing operation.
 */
void sys_init_timing(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;

	/* Clear tick value */
	gs_ul_clk_tick = 0;

	/* Configure PMC */
	pmc_enable_periph_clk(ID_TC0);

	/** Configure TC for a 4Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(1000,
			sysclk_get_main_hz(), &ul_div, &ul_tcclks,
			sysclk_get_main_hz());
	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC0, 0, (sysclk_get_main_hz() / ul_div) / 1000);

	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type)ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);

	/* Start timer */
	tc_start(TC0, 0);
}

/**
 * \brief Read for clock time (ms).
 */
uint32_t sys_get_ms(void)
{
	return gs_ul_clk_tick;
}

#if (THIRDPARTY_LWIP_VERSION != 132)

/* See lwip/sys.h for more information
   Returns number of milliseconds expired
   since lwip is initialized
*/
u32_t sys_now(void)
{
	return (sys_get_ms());
}

#endif
