#include "defines.h"


extern CAN_HandleTypeDef _canHandle;


/**
* @brief  This function handles CAN1 RX0 interrupt request.
* @param  None
* @retval None
*/
void CAN1_RX0_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&_canHandle);
}


/**
* @brief  This function handles CAN2 RX0 interrupt request.
* @param  None
* @retval None
*/
void CAN2_RX0_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&_canHandle);
}

/**
* @brief  This function handles CAN1 RX1 interrupt request.
* @param  None
* @retval None
*/
void CAN1_RX1_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&_canHandle);
}

/**
* @brief  This function handles CAN2 RX1 interrupt request.
* @param  None
* @retval None
*/
void CAN2_RX1_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&_canHandle);
}

/**
* @brief  This function handles CAN1 TX interrupt request.
* @param  None
* @retval None
*/
void CAN1_TX_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&_canHandle);
}


/**
* @brief  This function handles CAN2 TX interrupt request.
* @param  None
* @retval None
*/
void CAN2_TX_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&_canHandle);
}
