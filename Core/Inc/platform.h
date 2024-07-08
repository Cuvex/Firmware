
/******************************************************************************
  * @attention
  *
  * Portion Copyright (C) 2024 Semilla3 OÜ.  All Rights Reserved.
  *
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
******************************************************************************/
/*! \file
 *
 *  \author 
 *
 *  \brief Platform header file. Defining platform independent functionality.
 *
 */


/*
 *      PROJECT: ST25R95  
 *      $Revision: $
 *      LANGUAGE:  ISO C99
 */

/*! \file platform.h
 *
 *  \author 
 *
 *  \brief Platform specific definition layer  
 *  
 *  This should contain all platform and hardware specifics such as 
 *  GPIO assignment, system resources, locks, IRQs, etc
 *  
 *  Each distinct platform/system/board must provide this definitions 
 *  for all SW layers to use
 *  
 */

#ifndef PLATFORM_H
#define PLATFORM_H

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
#include "stm32u5xx_hal.h"
#include "main.h"
#include "stdbool.h"

#include "logger.h"
#include "timer.h"
#include "st_errno.h"

/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

#define ST25R95_INTERFACE_UART	1

#define ST25R95_N_SS_PIN             		GPIO_PIN_0		//nSPI_SS_Pin           /*!< GPIO pin used for ST25R95 SPI SS              */
#define ST25R95_N_SS_PORT            		GPIOB			//nSPI_SS_GPIO_Port     /*!< GPIO port used for ST25R95 SPI SS port        */

#define ST25R95_TAGDETECT_DEF_CALIBRATION 	0x7C             /*!< Tag Detection Calibration default value                    */
#define ST25R95_TAGDETECT_CALIBRATE       	true             /*!< False: use default value, True: call calibration procedure */
/*
******************************************************************************
* GLOBAL MACROS
******************************************************************************
*/

#define platformProtectWorker()                            /* Protect RFAL Worker/Task/Process from concurrent execution on multi thread platforms   */
#define platformUnprotectWorker()                          /* Unprotect RFAL Worker/Task/Process from concurrent execution on multi thread platforms */

#define platformLedsInitialize()                                                                                         /*!< Initializes the pins used as LEDs to outputs*/

#define platformLedOff( port, pin )                   platformGpioClear(port, pin)                                       /*!< Turns the given LED Off                     */
#define platformLedOn( port, pin )                    platformGpioSet(port, pin)                                         /*!< Turns the given LED On                      */
#define platformLedToogle( port, pin )                platformGpioToogle(port, pin)                                      /*!< Toogle the given LED                        */

#define platformGpioSet(port, pin)                    HAL_GPIO_WritePin((port), (pin), GPIO_PIN_SET)                     /*!< Turns the given GPIO High                   */
#define platformGpioClear(port, pin)                  HAL_GPIO_WritePin((port), (pin), GPIO_PIN_RESET)                   /*!< Turns the given GPIO Low                    */
#define platformGpioToogle(port, pin)                 HAL_GPIO_TogglePin((port), (pin))                                  /*!< Toogles the given GPIO                      */
#define platformGpioIsHigh(port, pin)                 (HAL_GPIO_ReadPin((port), (pin)) == GPIO_PIN_SET)                  /*!< Checks if the given LED is High             */
#define platformGpioIsLow(port, pin)                  (!platformGpioIsHigh((port), (pin)))                               /*!< Checks if the given LED is Low              */

#define platformTimerCreate(t)                        timerCalculateTimer(t)                                             /*!< Create a timer with the given time (ms)     */
#define platformTimerIsExpired(timer)                 timerIsExpired(timer)                                              /*!< Checks if the given timer is expired        */
#define platformDelay(t)                              HAL_Delay(t)                                                       /*!< Performs a delay for the given time (ms)    */
//#define platformDelay(t)                              osDelay(t)                                                       /*!< Performs a delay for the given time (ms)    */

#define platformGetSysTick()                          HAL_GetTick()                                                      /*!< Get System Tick ( 1 tick = 1 ms)            */

#if !(ST25R95_INTERFACE_UART) /* ST25R95_INTERFACE_SPI */
#define platformSpiSelect()                           platformGpioClear(ST25R95_N_SS_PORT, ST25R95_N_SS_PIN)             /*!< SPI SS\CS: Chip|Slave Select                */
#define platformSpiDeselect()                         platformGpioSet(ST25R95_N_SS_PORT, ST25R95_N_SS_PIN)               /*!< SPI SS\CS: Chip|Slave Deselect              */
#define platformSpiTxRx(txBuf, rxBuf, len)            HAL_SPI_TransmitReceive((&hspi1), (txBuf), (rxBuf), (len), 1000)   /*!< SPI transceive                              */
#define platformUartTx(TxBuf, len)                                                                                       /*!< UART transceive                             */
#define platformUartRx(RxBuf, len)                                                                                       /*!< UART transceive                             */
#else /* !ST25R95_INTERFACE_SPI */
#define platformSpiSelect()                                                                                              /*!< SPI SS\CS: Chip|Slave Select                */
#define platformSpiDeselect()                                                                                            /*!< SPI SS\CS: Chip|Slave Deselect              */
#define platformSpiTxRx(txBuf, rxBuf, len)                                                                               /*!< SPI transceive                              */
#define platformUartTx(TxBuf, len)                     HAL_UART_Transmit(&huart3, (TxBuf), (len), 50)                    /*!< UART transceive                             */
#define platformUartRx(RxBuf, len)                     HAL_UART_Receive(&huart3, (RxBuf), (len), 50)                     /*!< UART transceive                             */
#define platformUartTxIT(TxBuf, len)                   HAL_UART_Transmit_IT(&huart3, (TxBuf), (len))                     /*!< UART transceive                             */
#define platformUartRxIT(RxBuf, len)                   HAL_UART_Receive_IT(&huart3, (RxBuf), (len))                      /*!< UART transceive                             */
#define platformUartReset()                            HAL_UART_Abort(&huart3)                                           /*!< UART abort Tx/Rx and reset uart             */
#endif /* ST25R95_INTERFACE_SPI */

#define platformLog(...)                              logUsart(__VA_ARGS__)                                              /*!< Log  method                                 */

/*
******************************************************************************
* RFAL FEATURES CONFIGURATION
******************************************************************************
*/
#define RFAL_FEATURE_LISTEN_MODE               false      /*!< Enable/Disable RFAL support for Listen Mode                               */
#define RFAL_FEATURE_WAKEUP_MODE               true       /*!< Enable/Disable RFAL support for the Wake-Up mode                          */
#define RFAL_FEATURE_NFCA                      true       /*!< Enable/Disable RFAL support for NFC-A (ISO14443A)                         */
#define RFAL_FEATURE_NFCB                      true       /*!< Enable/Disable RFAL support for NFC-B (ISO14443B)                         */
#define RFAL_FEATURE_NFCF                      true       /*!< Enable/Disable RFAL support for NFC-F (FeliCa)                            */
#define RFAL_FEATURE_NFCV                      true       /*!< Enable/Disable RFAL support for NFC-V (ISO15693)                          */
#define RFAL_FEATURE_T1T                       true       /*!< Enable/Disable RFAL support for T1T (Topaz)                               */
#define RFAL_FEATURE_T2T                       true       /*!< Enable/Disable RFAL support for T2T                                       */
#define RFAL_FEATURE_T4T                       true       /*!< Enable/Disable RFAL support for T4T                                       */
#define RFAL_FEATURE_ST25TB                    true       /*!< Enable/Disable RFAL support for ST25TB                                    */
#define RFAL_FEATURE_ST25xV                    true       /*!< Enable/Disable RFAL support for ST25TV/ST25DV                             */
#define RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG     false      /*!< Enable/Disable Analog Configs to be dynamically updated (RAM)             */
#define RFAL_FEATURE_DYNAMIC_POWER             false      /*!< Enable/Disable RFAL dynamic power support                                 */
#define RFAL_FEATURE_ISO_DEP                   true       /*!< Enable/Disable RFAL support for ISO-DEP (ISO14443-4)                      */
#define RFAL_FEATURE_ISO_DEP_POLL              true       /*!< Enable/Disable RFAL support for Poller mode (PCD) ISO-DEP (ISO14443-4)    */
#define RFAL_FEATURE_ISO_DEP_LISTEN            false      /*!< Enable/Disable RFAL support for Listen mode (PICC) ISO-DEP (ISO14443-4)   */
#define RFAL_FEATURE_NFC_DEP                   true       /*!< Enable/Disable RFAL support for NFC-DEP (NFCIP1/P2P)                      */

#define RFAL_FEATURE_ISO_DEP_IBLOCK_MAX_LEN    256U       /*!< ISO-DEP I-Block max length. Please use values as defined by rfalIsoDepFSx */
#define RFAL_FEATURE_NFC_DEP_BLOCK_MAX_LEN     254U       /*!< NFC-DEP Block/Payload length. Allowed values: 64, 128, 192, 254           */
#define RFAL_FEATURE_NFC_RF_BUF_LEN            258U       /*!< RF buffer length used by RFAL NFC layer                                   */

#define RFAL_FEATURE_ISO_DEP_APDU_MAX_LEN      512U       /*!< ISO-DEP APDU max length.                                                  */
#define RFAL_FEATURE_NFC_DEP_PDU_MAX_LEN       512U       /*!< NFC-DEP PDU max length.                                                   */

/*
******************************************************************************
* GLOBAL VARIABLE
******************************************************************************
*/
#if !(ST25R95_INTERFACE_UART) /* ST25R95_INTERFACE_SPI */
extern SPI_HandleTypeDef hspi1;
#else /* !ST25R95_INTERFACE_SPI */
extern UART_HandleTypeDef huart3;
#endif /* ST25R95_INTERFACE_SPI */

#endif /* PLATFORM_H */



