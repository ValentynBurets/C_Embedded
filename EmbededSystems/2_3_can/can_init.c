#include "can_init.h"

CAN_InitTypeDef CAN_InitStructure;
CAN_FilterInitTypeDef CAN_FilterInitStructure;
void CAN1_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
/* CAN GPIOs configuration */
RCC_AHB1PeriphClockCmd(CAN1_GPIO_CLK, ENABLE);
GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_RX_SOURCE, GPIO_AF_CAN1);
GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_TX_SOURCE, GPIO_AF_CAN1);
/* Налаштування RX і TX */
GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN | CAN1_TX_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(CAN1_GPIO_PORT, &GPIO_InitStructure);
/* Налаштування CAN */
/* Тактування */
RCC_APB1PeriphClockCmd(CAN1_GPIO_CLK, ENABLE);
CAN_DeInit(CAN1);
/* ініціалізація структури CAN */
CAN_InitStructure.CAN_TTCM = DISABLE;
CAN_InitStructure.CAN_ABOM = DISABLE;
CAN_InitStructure.CAN_AWUM = DISABLE;
CAN_InitStructure.CAN_NART = ENABLE;
CAN_InitStructure.CAN_RFLM = DISABLE;
CAN_InitStructure.CAN_TXFP = DISABLE;
CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
CAN_InitStructure.CAN_Prescaler = 12;
CAN_Init(CAN1, &CAN_InitStructure);

CAN_FilterInitStructure.CAN_FilterNumber = 0;
CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
CAN_FilterInit(&CAN_FilterInitStructure);

/* Вмикаємо переривання */
CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
CAN_ITConfig(CAN1, CAN_IT_FMP1, ENABLE);
CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
}
