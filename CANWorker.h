#include <inttypes.h>
#include "stm32f429xx.h"
#include "stm32f4xx_hal.h"


class CANWorker
{

private:
	int sjw = 1;
	int bs1 = 1;
	int bs2 = 1;
	int prescaler = 1;

	bool init_HAL_CAN();
	uint32_t getAPB1Clock();
	void Error_Handler();
public:
	CANWorker();
	void calculateAndInitBaudrate(int baudrate);


};