#include <common.h>
#include <clock.h>
#include <malloc.h>
#include <spi.h>

/*
 * Handler to get access to the driver specific slave data structure
 * @param c		generic slave
 * @returns		driver specific slave
 */
static inline struct lpc_spi_slave *to_lpc_spi(struct spi_slave *slave)
{

}

/*
 * Initialization of the entire driver
 */
void spi_init()
{

}

/*
 * Prepare to use an SPI slave
 * @param b		SPI controller
 * @param cs		slave Chip Select
 * @param hz		max freq this slave can run at
 * @param m		slave access mode
 * @returns		driver specific slave
 */
struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
				  unsigned int hz, unsigned int mode)
{
	struct spi_slave *slave = NULL;

	return slave;
}

/*
 * Done with an an SPI slave
 * @param slv		SPI slave
 */
void spi_free_slave(struct spi_slave *slv)
{

}

/*
 * Set up the SPI controller
 * @param slv		SPI slave
 * @returns		0->success; !0->failure
 */
int spi_claim_bus(struct spi_slave *slv)
{
	return 0;
}

/*
 * Shut down the SPI controller
 * @param slv		SPI slave
 */
void spi_release_bus(struct spi_slave *slv)
{

}

/*
 * Perform an SPI transfer
 * @param slv		SPI slave
 * @param bl		transfer length (in bits)
 * @param dout		data out
 * @param din		data in
 * @param fl		transfer flags
 * @returns		0->success; !0->failure
 */
int spi_xfer(struct spi_slave *slv, unsigned int bl,
	     const void *dout, void *din, unsigned long fl)
{
	int ret = 0;

	return ret;
}
