 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Khaled
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohamed Khaled's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (120U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)


#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
  || (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
  || (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port.h does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
  || (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
  || (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port.h does not match the expected version"
#endif


#include "Common_Macros.h"
#include "Std_Types.h"


#define GPIO_COMMIT_UNLOCK_NUMBER 0x4C4F434B

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port Init */
#define PORT_INIT_SID                      (uint8)0x00

/* Service ID for Port Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID         (uint8)0x01

/* Service ID for Refresh Port Direction*/
#define PORT_REFRESH_PORT_DIRECTION_SID    (uint8)0x02

/* Service ID for Port Get Version Info */
#define PORT_GET_VERSION_INFO_SID          (uint8)0x03

/* Service ID for Port Set Pin Mode */
#define PORT_SET_PIN_MODE_SID              (uint8)0x04
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
#define PORT_E_PARAM_PIN                   (uint8)0x0A

#define PORT_E_DIRECTION_UNCHANGEABLE      (uint8)0x0B

#define PORT_E_PARAM_CONFIG                (uint8)0x0C

#define PORT_E_PARAM_INVALID_MODE          (uint8)0x0D

#define PORT_E_MODE_UNCHANGEABLE           (uint8)0x0E

#define PORT_E_UNINIT                      (uint8)0x0F

#define PORT_E_PARAM_POINTER               (uint8)0x10
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef uint8 Port_PortType;

typedef uint8 Port_PinType ;

typedef uint8 Port_PinModeType;

/* Description: Enum to hold initialization state for Port */
typedef enum{
    PORT_NOT_INITIALIZED,PORT_INITIALIZED
}Port_Intialization_State;




/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF_RESISTOR,PULL_UP_RESISTOR,PULL_DOWN_RESISTOR
}Port_PinInternalResistor;

/* Description: Enum to hold PIN direction */
typedef enum
{
  PORT_PIN_IN,PORT_PIN_OUT
} Port_PinDirectionType;

/* Description: Enum to hold changeability of mode for PIN */
typedef enum
{
  PORT_PIN_MODE_UNCHANGEABLE,PORT_PIN_MODE_CHANGEABLE
} Port_PinModeChangeable;

/* Description: Enum to hold changeability of direction for PIN */

typedef enum
{
  PORT_PIN_DIRECTION_UNCHANGEABLE,PORT_PIN_DIRECTION_CHANGEABLE
} Port_PinDirectionChangeable;

/* Description: Enum to hold initial value for PIN */
typedef enum
{
    PORT_PIN_LEVEL_LOW , PORT_PIN_LEVEL_HIGH
}Port_PinInitialValue;


/* Description: Structure to configure each individual PIN:
 *  1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *  2. the number of the pin in the PORT.
 *  3. the direction of pin --> INPUT or OUTPUT
 *  4. the internal resistor --> Disable, Pull up or Pull down
 *  5. the initial value --> PORT_PIN_LEVEL_LOW , PORT_PIN_LEVEL_HIGH
 *  6. the mode --> Range from (PORT_PIN_MODE_ADC) to (PORT_PIN_MODE_DIO)
 *  7. the direction changeable --> PORT_PIN_DIRECTION_UNCHANGEABLE,PORT_PIN_DIRECTION_CHANGEABLE
 *  8. the mode changeable --> PORT_PIN_MODE_UNCHANGEABLE,PORT_PIN_MODE_CHANGEABLE
 */
typedef struct 
{
    Port_PortType port_num;
    Port_PinType pin_num;
    Port_PinDirectionType direction;
    Port_PinInternalResistor resistor;
    Port_PinInitialValue initial_value;
    Port_PinModeType mode;
    Port_PinDirectionChangeable direction_changble;
    Port_PinModeChangeable mode_changble;
}Port_ConfigChannel;


typedef struct{
    Port_ConfigChannel Channels[PORT_CONFIGURED_CHANNLES];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(
 const Port_ConfigType* ConfigPtr
) ;

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin  - Port Pin ID number.
*                  Direction - Port Pin Direction.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
void Port_SetPinDirection(
 Port_PinType Pin,
 Port_PinDirectionType Direction
) ;

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(
 void
) ;

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo(
 Std_VersionInfoType* versioninfo
) ;

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin  - Port Pin ID number.
*                  Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode(
 Port_PinType Pin,
 Port_PinModeType Mode
) ;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType port_configuration;

#endif /* PORT_H */
