#ifndef USCI_SPI_H
#define USCI_SPI_H

#include <msp432.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI B0 Master-In-Slave-Out (MISO)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.6
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIB0_MISO_BIT                 BIT6
#define USCIB0_MISO_PORT                P1IN
#define USCIB0_MISO_DDR                 P1DIR
#define SET_USCIB0_MISO_AS_AN_INPUT     USCIB0_MISO_DDR &= ~USCIB0_MISO_BIT

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI B0 Master-Out-Slave-In (MOSI)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.7
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIB0_MOSI_BIT                 BIT7
#define USCIB0_MOSI_PORT                P1OUT
#define USCIB0_MOSI_DDR                 P1DIR
#define SET_USCIB0_MOSI_AS_AN_OUTPUT    USCIB0_MOSI_DDR |= USCIB0_MOSI_BIT

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Slave Clock for GPIO Flash Memory Board
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.5
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SPI_SCK_BIT                 BIT5
#define SPI_SCK_PORT                P1OUT // SPI Slave Clock output
#define SPI_SCK_DDR                 P1DIR // SPI Slave Clock direction
#define SET_SPI_SCK_AS_AN_OUTPUT    SPI_SCK_DDR |= SPI_SCK_BIT

void InitializeSPI();
void SPISendByte(unsigned char SendValue);
unsigned char SPIReceiveByte();

#endif
