/*
 * SPI.h
 *
 *  Created on: Sep 21, 2024
 *      Author: nemad
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32F103C6.h"
#include "GPIO.h"

struct S_IRQ_SRC
{
	uint8_t     TXE:1      ;
	uint8_t     RXNE:1     ;
	uint8_t     ERRI:1     ;
	uint8_t     Reserved:5 ;

};

typedef struct
{
	uint16_t         Device_MDOE   ;      //Specifies if master or slave @ref SPI Device mode

	uint16_t         COMM_MODE     ;      //Specifies the SPI bi directional mode @ref SPI Commuinication Mode

	uint16_t         Frame_Format  ;      //Specifies LSB or MSB @ ref SPI Frame Format

	uint16_t         Data_Size     ;      //Specifies Data size 8 or 16 bits @ref SPI Data Size

	uint16_t         CLK_POL       ;      //@ref SPI Clock Polarity

	uint16_t         CLK_PHA       ;      //@ref SPI CLock Phase

	uint16_t         NSS           ;      //@ref SPI NSS

	uint16_t         SPI_BRPRE     ;      //Specifies the Baud Rate @ref SPI Baud Rate PreScaler

	uint16_t         IRQ_Enable    ;      //@ref SPI IRQ Enable

	void(* P_IRQ_CallBack)(struct S_IRQ_SRC IRQ_SRC)       ;

}SPI_Config;


enum  Polling_MECH {
	polling_disable ,
	polling_enable
};







//=============================================================
//================MACROS CONFIG REFERENCE======================
//=============================================================
//@ref SPI Device mode
#define SPI_Device_Mode_SLAVE                    (0x00000000U)
#define SPI_Device_Mode_MASTER                   (0x1U << 2)  //CR1

//@ref SPI Commuinication Mode
#define SPII_Direction_2Lines                    (0x00000000U)
#define SPII_Direction_2Lines_RX                 (0x1U << 10 )  //CR1
#define SPII_Direction_1Line_RX                  (0x1U << 15 )  //CR1
#define SPII_Direction_1Line_TX                  ((0x1U << 15) | (0X1U << 14))  //CR1

//@ ref SPI Frame Format
#define SPI_Frame_Format_MSB                     (0x00000000U)  //CR1
#define SPI_Frame_Format_LSB                     (0x1U << 7 )  //CR1

//@ref SPI Data Size
#define SPI_DataSize_8Bits                       (0x00000000U)  //CR1
#define SPI_DataSize_16Bits                      (0x1U << 11 )  //CR1

//@ref SPI Clock Polarity
#define SPI_CLK_POL_LOW_IDLE                     (0x00000000U)  //CR1
#define SPI_CLK_POL_HIGH_IDLE                    (0x1U << 1)   //CR1

//@ref SPI CLock Phase
#define SPI_CLK_PHA_FirstEdge                    (0x00000000U) //CR1
#define SPI_CLK_POL_SecondEdge                   (0x1U << 0)  //CR1

//@ref SPI NSS
//HW
#define SPI_NSS_HW_SLAVE                          (0x00000000U)
#define SPI_NSS_HW_MASTER_OP_EN                   (0x1U << 2) //CR2
#define SPI_NSS_HW_MASTER_OP_DIS                  ~(0x1U << 2) //CR2

//SW (MAster or Slave)
#define SPI_NSS_SW_Internal_RESET                 (0x1U << 9)
#define SPI_NSS_SW_Internal_SET                   ((0x1U << 9) | (0x1U << 8))

//@ref SPI Baud Rate PreScaler
#define SPI_BaudRate_PRE_2                        (0x00000000U)
#define SPI_BaudRate_PRE_4                        (0b001U << 3)
#define SPI_BaudRate_PRE_8                        (0b010U << 3)
#define SPI_BaudRate_PRE_16                       (0b011U << 3)
#define SPI_BaudRate_PRE_32                       (0b100U << 3)
#define SPI_BaudRate_PRE_64                       (0b101U << 3)
#define SPI_BaudRate_PRE_128                      (0b110U << 3)
#define SPI_BaudRate_PRE_256                      (0b111U << 3)

//@ref SPI IRQ Enable
#define SPI_IRQ_Enable_NONE                       (uint32_t)(0)
#define SPI_IRQ_Enable_TXIE                       (uint32_t)(1 << 7)
#define SPI_IRQ_Enable_RXNEIE                     (uint32_t)(1 << 6)
#define SPI_IRQ_Enable_ERRIE                      (uint32_t)(1 << 5)


//=============================================================
//===========APIs Supported by MCAL SPI Driver=================
//=============================================================
void MCAL_SPI_INIT(SPI_TypeDef * SPIx , SPI_Config* SPI_CFG );
void MCAL_SPI_DeINIT(SPI_TypeDef * SPIx );

void MCAL_SPI_Set_PINS(SPI_TypeDef * SPIx );

void MCAL_SPI_TX(SPI_TypeDef * SPIx , uint16_t * pTX_Buff , enum Polling_MECH POLLING);

void MCAL_SPI_RX(SPI_TypeDef * SPIx , uint16_t * pRX_Buff , enum Polling_MECH POLLING);

void MCAL_SPI_RX_TX(SPI_TypeDef * SPIx , uint16_t * p_TX_RX_Buff , enum Polling_MECH POLLING);


#endif /* INC_SPI_H_ */
