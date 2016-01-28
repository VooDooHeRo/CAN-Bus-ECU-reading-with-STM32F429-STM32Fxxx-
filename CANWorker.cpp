#include "CANWorker.h"

#define CAN_BAUDRATE_TEST_TIMEOUT   10000 //ms

CAN_HandleTypeDef _canHandle;

bool receivedAnyCANFrame = false;
bool flag = false;
bool busy = false;

CANWorker::CANWorker ()
{
  // I used STM32F429-Discovery blue button for jumping to next baudrate solution, use another GPIO (or another method) 
  //that suits you.
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
  
  /*##- Start the Reception process and enable reception interrupt #########*/
  if(HAL_CAN_Receive_IT(&_canHandle, CAN_FIFO0) != HAL_OK)
	{
		/* Reception Error */
		Error_Handler();
	}
	
	int counter = 0;
	while (true)
	{
	  // check if the External interrupt of USER_KEY is occured (by checking the flag)
		if (counter >= (CAN_BAUDRATE_TEST_TIMEOUT / 300) && !receivedAnyCANFrame && flag)
		{ 
		  
			INFO("CAN BAUDRATE TEST timed out, trying another baudrate\r\n");
			flag = false;
			counter = 0;
			receivedAnyCANFrame = false;
			if (!busy)
				calculateAndInitBaudrate(250000);  // change to your desired baudrate (typically 250kbs or 500kbs)
		}
		else
		{
			HAL_Delay(300);
			counter++;
		}
	}
	
	bool CANWorker::init_HAL_CAN()
{
	CAN_FilterConfTypeDef sFilterConfig;
	static CanTxMsgTypeDef TxMessage;
	static CanRxMsgTypeDef RxMessage;

	/*##-1- Configure the CAN peripheral #######################################*/
	_canHandle.Instance = CAN1;
	_canHandle.pTxMsg = &TxMessage;
	_canHandle.pRxMsg = &RxMessage;

	_canHandle.Init.TTCM = DISABLE; //Non time trigger communication mode //
	_canHandle.Init.ABOM = DISABLE;  //The software automatically Bus-off management     //
	_canHandle.Init.AWUM = DISABLE; //Sleep mode wake by software (clear CAN-> MCR SLEEP) (automatic wake-up mode)//
	_canHandle.Init.NART = DISABLE;  //Disable automatic transfer message (non-automatic retransmission mode)//
	_canHandle.Init.RFLM = DISABLE; //The message is not locked, the new cover the old // 
	_canHandle.Init.TXFP = DISABLE; // Priority is determined by the message identifier //
	
	_canHandle.Init.Mode = CAN_MODE_NORMAL;
	_canHandle.Init.SJW = CAN_SJW_2TQ;
	_canHandle.Init.BS1 = CAN_BS1_3TQ;
	_canHandle.Init.BS2 = CAN_BS2_3TQ;
	_canHandle.Init.Prescaler = 16;

	if(HAL_CAN_Init(&_canHandle) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
		return false;
	}

// The below CAN filter does not actually filer any CAN frame, and this is what we want right now!
/*##-2- Configure the CAN Filter ###########################################*/
	sFilterConfig.FilterNumber = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = 0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 14;

	if(HAL_CAN_ConfigFilter(&_canHandle, &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
		return false;
	}
	
		return true;
}

void CANWorker::Error_Handler()
{
	while(1)
	{
		BSP_LED_Toggle(LED3);
		HAL_Delay(100);
	}
}

void CANWorker::calculateAndInitBaudrate(int baudrate)
{
	busy = true;
	bool shouldBrake = false;
	uint32_t frequency = getAPB1Clock();
	for (; sjw <= 4 && !shouldBrake; )
	{
		for (; bs1 <= 16 && !shouldBrake; )
		{
			for (; bs2 <= 8 && !shouldBrake; )
			{
				for (; prescaler <= 1024 && !shouldBrake; )
				{
					int calcBaudrate = (int)(frequency / (prescaler * (sjw + bs1 + bs2)));
					if (calcBaudrate == baudrate)
					{
						if (sjw == 1)
							_canHandle.Init.SJW = CAN_SJW_1TQ;
						else if (sjw == 2)
							_canHandle.Init.SJW = CAN_SJW_2TQ;
						else if (sjw == 3)
							_canHandle.Init.SJW = CAN_SJW_3TQ;
						else if (sjw == 4)
							_canHandle.Init.SJW = CAN_SJW_4TQ;

						if (bs1 == 1)
							_canHandle.Init.BS1 = CAN_BS1_1TQ;
						else if (bs1 == 2)
							_canHandle.Init.BS1 = CAN_BS1_2TQ;
						else if (bs1 == 3)
							_canHandle.Init.BS1 = CAN_BS1_3TQ;
						else if (bs1 == 4)
							_canHandle.Init.BS1 = CAN_BS1_4TQ;
						else if (bs1 == 5)
							_canHandle.Init.BS1 = CAN_BS1_5TQ;
						else if (bs1 == 6)
							_canHandle.Init.BS1 = CAN_BS1_6TQ;
						else if (bs1 == 7)
							_canHandle.Init.BS1 = CAN_BS1_7TQ;
						else if (bs1 == 8)
							_canHandle.Init.BS1 = CAN_BS1_8TQ;
						else if (bs1 == 9)
							_canHandle.Init.BS1 = CAN_BS1_9TQ;
						else if (bs1 == 10)
							_canHandle.Init.BS1 = CAN_BS1_10TQ;
						else if (bs1 == 11)
							_canHandle.Init.BS1 = CAN_BS1_11TQ;
						else if (bs1 == 12)
							_canHandle.Init.BS1 = CAN_BS1_12TQ;
						else if (bs1 == 13)
							_canHandle.Init.BS1 = CAN_BS1_13TQ;
						else if (bs1 == 14)
							_canHandle.Init.BS1 = CAN_BS1_14TQ;
						else if (bs1 == 15)
							_canHandle.Init.BS1 = CAN_BS1_15TQ;
						else if (bs1 == 16)
							_canHandle.Init.BS1 = CAN_BS1_16TQ;

						if (bs2 == 1)
							_canHandle.Init.BS2 = CAN_BS2_1TQ;
						else if (bs2 == 2)
							_canHandle.Init.BS2 = CAN_BS2_2TQ;
						else if (bs2 == 3)
							_canHandle.Init.BS2 = CAN_BS2_2TQ;
						else if (bs2 == 4)
							_canHandle.Init.BS2 = CAN_BS2_2TQ;


						_canHandle.Init.Prescaler = prescaler;

						shouldBrake = true;

            // below lines are my own serial class, replace them with yours
						//serial->puts("new config applied\r\n");
						//serial->puts("sjw: ");
						//serial->print(sjw);
						//serial->puts("  bs1: ");
						//serial->print(bs1);
						//serial->puts("  bs2: ");
						//serial->print(bs2);
						//serial->puts(" prescaler: ");
						//serial->print(prescaler);
						//serial->puts("\r\n");
					}

					prescaler++;
				}
				if (!shouldBrake)
				{
					prescaler = 1;
					bs2++;
				}
			}
			if (!shouldBrake)
			{
				bs2 = 1;
				bs1++;
			}
		}
		if (!shouldBrake)
		{
			bs1 = 1;
			sjw++;
		}
	}

	busy = false;

	if (HAL_CAN_Init(&_canHandle) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* CanHandle)
{

	receivedAnyCANFrame = true;

  // below lines are my own serial class, replace them with yours
	serial->print("StdId:");
	serial->print((int)CanHandle->pRxMsg->StdId);
	serial->print(",");
	serial->print((int)CanHandle->pRxMsg->ExtId);
	serial->print(",");
	serial->print((int)CanHandle->pRxMsg->DLC);
	serial->print(",");
	serial->print((int)CanHandle->pRxMsg->Data[0]);
	serial->putc(' ');
	serial->print((int)CanHandle->pRxMsg->Data[1]);
	serial->putc(' ');
	serial->print((int)CanHandle->pRxMsg->Data[2]);
	serial->putc(' ');
	serial->print((int)CanHandle->pRxMsg->Data[3]);
	serial->putc(' ');
	serial->print((int)CanHandle->pRxMsg->Data[4]);
	serial->putc(' ');
	serial->print((int)CanHandle->pRxMsg->Data[5]);
	serial->putc(' ');
	serial->print((int)CanHandle->pRxMsg->Data[6]);
	serial->putc(' ');
	serial->print((int)CanHandle->pRxMsg->Data[7]);
	serial->print("\r\n");

	BSP_LED_Toggle(LED3);
	
	
	/* Receive the next CAN Frame*/
	if(HAL_CAN_Receive_IT(CanHandle, CAN_FIFO0) != HAL_OK)
	{
		/* Reception Error */
		//Error_Handler();
	}
}
