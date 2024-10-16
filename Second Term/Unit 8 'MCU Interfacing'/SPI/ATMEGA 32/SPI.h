/*
 * SPI.h
 *
 * Created: 10/16/2024 12:47:26 AM
 *  Author: nemad
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../DIO/DIO.h"
#include "stdint.h"
#include "../../utils.h"

#define SS   4
#define MOSI 5
#define MISO 6
#define SCK  7

#define Default_Stop '\r'

typedef enum{
	SPI_Polling_DIS ,
	SPI_Polling_EN
}SPI_Polling_Mech;

typedef struct{
	uint8_t mode           ; //@ref SPI_mode
	uint8_t IRQ_EN         ; //@ref Interrupt Enable
	uint8_t Data_Order     ; //@ref Data Order 
	uint8_t Clock_Polarity ; //@ref SPI Clk Polarity 
	uint8_t Clock_Phase    ; //@ref SPI Clk Phase
	uint8_t Clock_Rate     ; //@ref SPI Clk Rate 
	void(* P_IRQ_CallBack)(void) ;

}S_SPI_CFG;



/*=====================================================================
======================MACROS CONFIGURATION=============================
=======================================================================
*/


//@ref SPI_mode
#define SPI_MASTER             ((0b1) << MSTR)
#define SPI_SLAVE              ((0b0) << MSTR)

//@ref Interrupt Enable
#define SPI_IRQ_None           ((0b0) << SPIE)
#define SPI_IRQ_EN             ((0b1) << SPIE)

//@ref Data Order 
#define SPI_MSB_First          ((0b0) << DORD)
#define SPI_LSB_First          ((0b1) << DORD)

//@ref SPI Clk Polarity 
#define SPI_CPOL_Rising        ((0b0) << CPOL)
#define SPI_CPOL_Falling       ((0b1) << CPOL)

//@ref SPI Clk Phase
#define SPI_CPHA_Sample        ((0b0) << CPHA)
#define SPI_CPHA_Setup         ((0b1) << CPHA)

//@ref SPI Clk Rate 
#define SPI_CLK_F_2            ((0b00) << SPR0)
#define SPI_CLK_F_4            ((0b00) << SPR0)
#define SPI_CLK_F_8            ((0b01) << SPR0)
#define SPI_CLK_F_16           ((0b01) << SPR0)
#define SPI_CLK_F_32           ((0b10) << SPR0)
#define SPI_CLK_F_64           ((0b10) << SPR0)     
#define SPI_CLK_F_128          ((0b11) << SPR0)



/*=====================================================================
=================================APIS==================================
=======================================================================
*/

void SPI_INIT (S_SPI_CFG * SPI_CFG) ;

void SPI_MASTER_TX_char(uint8_t data , SPI_Polling_Mech Polling) ;
void SPI_MASTER_TX_String(uint8_t * str , SPI_Polling_Mech Polling) ;
uint8_t SPI_MASTER_RX_char(SPI_Polling_Mech Polling) ;
void SPI_MASTER_RX_String(uint8_t * str , SPI_Polling_Mech Polling) ;


void SPI_Slave_TX_char(uint8_t data, SPI_Polling_Mech Polling) ;
void SPI_SLAVE_TX_String(uint8_t * str , SPI_Polling_Mech Polling) ;
uint8_t SPI_SLAVE_RX_Char(SPI_Polling_Mech Polling) ;
void SPI_Slave_RX_String(uint8_t * str , SPI_Polling_Mech Polling) ;


#endif /* SPI_H_ */