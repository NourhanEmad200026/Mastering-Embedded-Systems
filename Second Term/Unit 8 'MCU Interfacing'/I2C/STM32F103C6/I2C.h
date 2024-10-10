/*
 * I2C.h
 *
 *  Created on: Oct 6, 2024
 *      Author: nemad
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stm32F103C6.h"
#include "RCC.h"
#include "GPIO.h"


#define I2C_EVENT_MASTER_BYTE_TRANSMITTING        ((uint32_t)00070008)        //TRA , BUSY ,MSL in SR2 , TXE flags

struct S_I2C_Slave_Address{
	uint16_t       DUAL_EN                  ;
	uint16_t       Primary_slave_Address    ;
	uint16_t       Secondary_slave_Address  ;
	uint32_t       I2C_Address_slave_mode   ;   //@ref I2C_Address_slave
};

typedef enum{
	I2C_ERROR_AF     ,
	I2C_EV_Stop      ,
	I2C_EV_ADD_Match ,
	I2C_EV_Data_REQ  , //the APP layer should send data
	I2C_EV_Data_RCV  , //the APP layer should receive data
}Slave_State;

typedef enum{
	with_stop ,
	without_stop
}Stop_Condition;

typedef enum{
	Disable = 0 ,
	Enable = 1
}Functional_State;

typedef enum{
	start ,
	repeated_Start
}Start_Condition;


typedef enum{Reset = 0 , Set = 1 }Flag_Status ;

typedef enum{
	I2C_Flag_Busy  = 0 ,
	EV5 ,
	EV6 ,
	MASTER_BYTE_TRANSMITTING =  ((uint32_t)0x00070080UL) ,
	EV8 ,
	EV8_1 ,
	EV7
}Flag;

typedef enum
{
	I2C_Write = 0 ,
	I2C_Read = 1
}I2C_Direction;




typedef struct{

	 uint32_t                       Clk_Speed             ;    //Specifies the clk frequency @ref I2C_Clk_Speed

	 uint32_t                       Stretch_Mode          ;   //@ref I2C_STRETCH_MODE

	 uint32_t                       I2C_MODE              ;  //@ref I2C_Mode specifies whether I2C mode or SMBus mode

	 struct S_I2C_Slave_Address     I2C_Device_ADD        ;

	 uint32_t                       I2C_ACK_CTRL          ;  //@ref I2C_ACK_CTRL

	 uint32_t                       I2C_GeneralCallback   ;

	 void(*P_Slave_Event_CallBack)(Slave_State state)     ;
}I2C_Init_T;








//=============================================================
//================MACROS CONFIG REFERENCE======================
//=============================================================

//@ref I2C_Clk_Speed
    //– Standard Speed (up to 100 kHz)
    //– Fast Speed (up to 400 kHz)
    //to configure clk
    //I2C_CR2 FREQ Bit[5:0]
    //• Program the peripheral input clock in I2C_CR2 Register in order to generate co
    //timings
    //• Configure the clock control registers
    //            Thigh = CCR * T PCLK1
    //            SM or FM
    //• Configure the rise time register
    //• Program the I2C_CR1 register to enable the peripheral
    //• Set the START bit in the I2C_CR1 register to generate a Start condition

#define I2C_SCLK_STD_50KHz           (0x50000U)
#define I2C_SCLK_STD_100KHz          (100000U)


//@ref I2C_STRETCH_MODE
//CR1 Bit 7
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_Stretch_Mode_EN           0x00000000U
#define I2C_Stretch_Mode_Dis          I2C_CR1_NOSTRETCH

//@ref I2C_Mode
//SMBus in CR1
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_MODE_I2C                  0x00000000U
#define I2C_MODE_SMBus                I2C_CR1_SMBUS

//@ref I2C_Address_slave
//I2C_OAR1
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Slave_7Bit                0x00000000U
#define I2C_Slave_10Bit               (uint16_t)(1 << 15)

//@ref I2C_ACK_CTRL
#define I2C_ACK_EN                    (I2C_CR1_ACK)
#define I2C_ACK_DIS                   ((uint16_t)0x0000)

//@ref I2C_ENGC
#define I2C_ENGC_EN                    (I2C_CR1_ACK)
#define I2C_ENGC_DIS                   ((uint16_t)0x0000)



//=============================================================
//===========APIs Supported by MCAL I2C Driver=================
//=============================================================

void MCAL_I2C_Init(I2C_TypeDef * I2Cx , I2C_Init_T * I2C_CFG) ;
void MCAL_I2C_DeInit(I2C_TypeDef * I2Cx) ;

void MCAL_I2C_GPIO_SetPINS (I2C_TypeDef * I2Cx) ;

//Master Polling
void MCAL_I2C_MASTER_TX(I2C_TypeDef* I2Cx , uint16_t dvc_ADD , uint8_t * dataTX ,uint32_t data_lenght , Stop_Condition Stop , Start_Condition Start ) ;

void MCAL_I2C_MASTER_RX(I2C_TypeDef* I2Cx , uint16_t dvc_ADD , uint8_t * dataRX ,uint32_t data_lenght , Stop_Condition Stop , Start_Condition Start ) ;

//Slave Interrupt Mechanism

void MCAL_I2C_SLAVE_SEND(I2C_TypeDef* I2Cx , uint8_t data) ;
uint8_t MCAL_I2C_SLAVE_RECEIVE(I2C_TypeDef* I2Cx ) ;


//Generic APIs

void I2C_Generate_Start(I2C_TypeDef * I2Cx ,Functional_State State , Start_Condition Start) ;

Flag_Status I2C_Get_Flag_Status(I2C_TypeDef * I2Cx , Flag Status );

void I2C_SendAddress(I2C_TypeDef * I2Cx  , uint16_t Address , I2C_Direction Direction) ;\

void I2C_Generate_Stop(I2C_TypeDef * I2Cx , Functional_State State);

void I2C_ACK_CFG(I2C_TypeDef * I2Cx , Functional_State State);

void Slave_Status(I2C_TypeDef * I2Cx , Slave_State state) ;

#endif /* INC_I2C_H_ */
