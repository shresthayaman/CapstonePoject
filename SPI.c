#include "spi.h"

void InitializeSPI()
{
    // Software reset enabled. USCI logic held in reset state.
    UCB0CTL1 = UCSWRST;

    // Initialize all USCI registers with UCSWRST = 1 (including UCxCTL1)

    // Select USCI SPI functionality.
    UCB0CTL0 = UCCKPH + UCMSB + UCMST + UCSYNC;
    UCB0CTL1 |= UCSSEL_2;       // SMCLK as source
    UCB0BR1 = 0; UCB0BR0 = 0x1; // divide clock by 1
    UCB0TXBUF = 0;              // initialize transmit buffer to 0

    // Configure port pin to receive output from USCI B0 clock.
    SET_SPI_SCK_AS_AN_OUTPUT;
    P1SEL2 |= SPI_SCK_BIT; P1SEL |= SPI_SCK_BIT;

    // Configure port pin to receive output from USCI B0 MOSI.
    SET_USCIB0_MOSI_AS_AN_OUTPUT;
    P1SEL2 |= USCIB0_MOSI_BIT; P1SEL |= USCIB0_MOSI_BIT;

    // Configure port pin to receive output from USCI B0 MISO.
    SET_USCIB0_MISO_AS_AN_INPUT;
    P1SEL2 |= USCIB0_MISO_BIT; P1SEL |= USCIB0_MISO_BIT;

    // Software reset disabled. USCI logic released for operation.
    UCB0CTL1 &= ~UCSWRST;
}


void SPISendByte(unsigned char SendValue)
{
    UCB0TXBUF = SendValue;
    while (UCB0STAT & UCBUSY);
}

unsigned char SPIReceiveByte()
{
    unsigned char ReceiveValue = 0;

    IFG2 &= ~UCB0RXIFG; // Clear interrupt flag.

    /* To receive data into the USCI in master mode, data must be written
     * to UCxTXBUF because receive and transmit operations operate concurrently.
     * See bottom of page 439 of Users Guide.
     */
    UCB0TXBUF = 0x00;

    while (!(IFG2 & UCB0RXIFG));
    ReceiveValue = UCB0RXBUF;

    return ReceiveValue;
}





