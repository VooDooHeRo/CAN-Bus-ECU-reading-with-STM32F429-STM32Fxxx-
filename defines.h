/* User can use this section to tailor CANx instance used and associated 
   resources */
/* Definition for CANx clock resources */
#define CANx                            CAN1
#define CANx_CLK_ENABLE()               __HAL_RCC_CAN1_CLK_ENABLE()
#define CANx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
     
#define CANx_FORCE_RESET()              __HAL_RCC_CAN1_FORCE_RESET()
#define CANx_RELEASE_RESET()            __HAL_RCC_CAN1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define CANx_TX_PIN                    GPIO_PIN_12
#define CANx_TX_GPIO_PORT              GPIOA  
#define CANx_TX_AF                     GPIO_AF9_CAN1
#define CANx_RX_PIN                    GPIO_PIN_11
#define CANx_RX_GPIO_PORT              GPIOA 
#define CANx_RX_AF                     GPIO_AF9_CAN1

/* Definition for USARTx's NVIC */
//#define CANx_RX_IRQn                   CAN2_RX0_IRQn
//#define CANx_RX_IRQHandler             CAN2_RX0_IRQHandler

#define CANx_RX_IRQn1                   CAN1_RX0_IRQn
#define CANx_RX_IRQHandler1             CAN1_RX0_IRQHandler