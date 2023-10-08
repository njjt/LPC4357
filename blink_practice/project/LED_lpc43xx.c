/*-----------------------------------------------------------------------------
 * Copyright (c) 2013 - 2019 Arm Limited (or its affiliates). All
 * rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   1.Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   2.Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   3.Neither the name of Arm nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *-----------------------------------------------------------------------------
 * Name:    LED_MCB4300.c
 * Purpose: LED interface for MCB4300 evaluation board
 * Rev.:    1.0.1
   ---------------------------------------------------------------------------*/

#include "SCU_LPC43xx.h"
#include "GPIO_LPC43xx.h"
#include "Board_LED.h"

#define LED_COUNT                      (8U)

/* LED pins:
   - LED0: PD_10 = GPIO6[24]
   - LED1: PD_11 = GPIO6[25]
   - LED2: PD_12 = GPIO6[26]
   - LED3: PD_13 = GPIO6[27]
   - LED4: PD_14 = GPIO6[28]
   - LED5: P9_0  = GPIO4[12]
   - LED6: P9_1  = GPIO4[13]
   - LED7: P9_2  = GPIO4[14] */

/* LED GPIO definitions */
static const GPIO_ID LED_GPIO[] = {
  { 6U, 24U },
  { 6U, 25U },
  { 6U, 26U },
  { 6U, 27U },
  { 6U, 28U },
  { 4U, 12U },
  { 4U, 13u },
  { 4U, 14U }
};

/* LED pin definitions */
static const PIN_ID LED_PIN[] = {
  { 13U, 10U, (SCU_CFG_MODE_FUNC4 | SCU_PIN_CFG_PULLDOWN_EN)},
  { 13U, 11U, (SCU_CFG_MODE_FUNC4 | SCU_PIN_CFG_PULLDOWN_EN)},
  { 13U, 12U, (SCU_CFG_MODE_FUNC4 | SCU_PIN_CFG_PULLDOWN_EN)},
  { 13U, 13U, (SCU_CFG_MODE_FUNC4 | SCU_PIN_CFG_PULLDOWN_EN)},
  { 13U, 14U, (SCU_CFG_MODE_FUNC4 | SCU_PIN_CFG_PULLDOWN_EN)},
  {  9U,  0u, (SCU_CFG_MODE_FUNC0 | SCU_PIN_CFG_PULLDOWN_EN)},
  {  9U,  1u, (SCU_CFG_MODE_FUNC0 | SCU_PIN_CFG_PULLDOWN_EN)},
  {  9U,  2U, (SCU_CFG_MODE_FUNC0 | SCU_PIN_CFG_PULLDOWN_EN)}
};


/**
  \fn          int32_t LED_Initialize (void)
  \brief       Initialize LEDs
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_Initialize (void) {
  uint32_t n;

  /* Enable GPIO clock */
  GPIO_PortClock     (1);

  /* Configure pins: Output Mode with Pull-down resistors */
  for (n = 0U; n < LED_COUNT; n++) {
    SCU_PinConfigure (LED_PIN[n].port,  LED_PIN[n].num,  LED_PIN[n].config_val);
    GPIO_SetDir      (LED_GPIO[n].port, LED_GPIO[n].num, GPIO_DIR_OUTPUT);
    GPIO_PinWrite    (LED_GPIO[n].port, LED_GPIO[n].num, 0);
  }
  return 0;
}

/**
  \fn          int32_t LED_Uninitialize (void)
  \brief       De-initialize LEDs
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_Uninitialize (void) {
  uint32_t n;

  /* Unconfigure pins: turn off Pull-up/down resistors */
  for (n = 0U; n < LED_COUNT; n++) {
    SCU_PinConfigure (LED_PIN[n].port,  LED_PIN[n].num,  0);
  }
  return 0;
}

/**
  \fn          int32_t LED_On (uint32_t num)
  \brief       Turn on requested LED
  \param[in]   num  LED number
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_On (uint32_t num) {
  int32_t retCode = 0;

  if (num < LED_COUNT) {
    GPIO_PinWrite     (LED_GPIO[num].port, LED_GPIO[num].num, 1);
  }
  else {
    retCode = -1;
  }

  return retCode;
}

/**
  \fn          int32_t LED_Off (uint32_t num)
  \brief       Turn off requested LED
  \param[in]   num  LED number
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_Off (uint32_t num) {
  int32_t retCode = 0;

  if (num < LED_COUNT) {
    GPIO_PinWrite     (LED_GPIO[num].port, LED_GPIO [num].num, 0);
  }
  else {
    retCode = -1;
  }

  return retCode;
}

/**
  \fn          int32_t LED_SetOut (uint32_t val)
  \brief       Write value to LEDs
  \param[in]   val  value to be displayed on LEDs
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_SetOut (uint32_t val) {
  uint32_t n;

  for (n = 0U; n < LED_COUNT; n++) {
    if (val & (1 << n)) LED_On (n);
    else                LED_Off(n);
  }

  return 0;
}

/**
  \fn          uint32_t LED_GetCount (void)
  \brief       Get number of LEDs
  \return      Number of available LEDs
*/
uint32_t LED_GetCount (void) {

  return LED_COUNT;
}
