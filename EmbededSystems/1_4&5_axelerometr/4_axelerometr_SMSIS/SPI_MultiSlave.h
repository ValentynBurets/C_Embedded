#define SPI_DRIVER //specifies the underlying SPI CMSIS-Driver, which actually controls the SPI peripheral and the accesses the bus. The wrapper will connect to that driver.
#define SPI_ENABLE_SLAVE_x //enables each SPI bus connected slave. This basically means that the driver control block Driver_SPIn will be exported by the wrapper for each particular slave.
#define SPI_DRIVER_SLAVE_x //sets the exported control block number n, for example Driver_SPIn. The application connects to this driver.
