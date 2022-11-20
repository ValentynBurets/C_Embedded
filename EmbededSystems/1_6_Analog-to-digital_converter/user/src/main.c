#include "stm32f4xx.h"                  // Device header

//---
//typedef struct 
//{
//  uint32_t ADC_Mode;                      
//  uint32_t ADC_Prescaler;                 
//  uint32_t ADC_DMAAccessMode;             
//  uint32_t ADC_TwoSamplingDelay
//}ADC_CommonInitTypeDef,

//---
RCC_ClocksTypeDef RCC_Clocks;

//-------------
static __IO uint32_t TimingDelay;
 
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void){
  if (TimingDelay != 0x00){ 
    TimingDelay--;
  }
}
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}
//--------------

void GPIOInit(){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init( GPIOC, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
}




void adc_init() {
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef adc_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_DeInit();
	ADC_StructInit(&ADC_InitStructure);
	adc_init.ADC_Mode = ADC_Mode_Independent;
	adc_init.ADC_Prescaler = ADC_Prescaler_Div2;
	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	
	ADC_CommonInit(&adc_init);
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
}  

u16 readADC1(u8 channel) {
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_3Cycles);
	ADC_SoftwareStartConv(ADC1);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}


int main(void)
{
	GPIOInit();
	adc_init();
	
	
	while(1){
		
		unsigned int CODEres = readADC1(ADC_Channel_1);
		
		double Vref = 5.0;
		double CODEmax = 0xFFF;
		
		double Vres = Vref*CODEres/CODEmax;
	
	double temperature = (Vres - 0.76)/0.0025 + 25;
		
		if(temperature > 15)
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14); //red
			Delay(1000);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14); //red
		}else{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15); //blue
			Delay(1000);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15); //blue
		}
	}	

}
