/**
 * @file main.c
 * @version 1.0
 * @date 2021-04-18
 * 
 */

#include "Rath_HAL.h"

static void AG_GPIO_init(void);
static void AG_ADC0_init(void);
static void AG_USART0_init(void);

int main(void) {

  AG_GPIO_init();
  AG_ADC0_init();
  AG_USART0_init();

  uint32_t counter = 0;

  while (1) {
    /* read the converted data from ADC */
    uint16_t buffer[4];
    
    ADC_ChannelInitTypeDef adc0_channel_init_struct;

    adc0_channel_init_struct.channel = ADC_CHANNEL_0;
    adc0_channel_init_struct.rank = ADC_RANK_0;
    adc0_channel_init_struct.sample_time = ADC_SAMPLETIME_1POINT5;
    HAL_ADC_initChannel(ADC0, &adc0_channel_init_struct);

    HAL_ADC_startConversion(ADC0, 0);
    buffer[0] = HAL_ADC_read(ADC0);
    
    adc0_channel_init_struct.channel = ADC_CHANNEL_1;
    adc0_channel_init_struct.rank = ADC_RANK_0;
    adc0_channel_init_struct.sample_time = ADC_SAMPLETIME_1POINT5;
    HAL_ADC_initChannel(ADC0, &adc0_channel_init_struct);
    
    HAL_ADC_startConversion(ADC0, 0);
    buffer[1] = HAL_ADC_read(ADC0);
    
    adc0_channel_init_struct.channel = ADC_CHANNEL_2;
    adc0_channel_init_struct.rank = ADC_RANK_0;
    adc0_channel_init_struct.sample_time = ADC_SAMPLETIME_1POINT5;
    HAL_ADC_initChannel(ADC0, &adc0_channel_init_struct);
    
    HAL_ADC_startConversion(ADC0, 0);
    buffer[2] = HAL_ADC_read(ADC0);

    /* the signal will be active low */
    buffer[3] = HAL_GPIO_readPin(GPIOA, GPIO_PIN_4);

    /* send the data to PC */
    HAL_USART_transmit(USART0, buffer, sizeof(uint16_t) * 4, 0);
    printf("\n", 0);

    /* delay for 0.01 seconds */
    HAL_delay(10);
  }
}

static void AG_GPIO_init(void) {
  HAL_RCU_enablePeriphClock(RCU_GPIOA);
  HAL_RCU_enablePeriphClock(RCU_GPIOC);
  HAL_RCU_enablePeriphClock(RCU_GPIOD);
  HAL_RCU_enablePeriphClock(RCU_GPIOE);
  
  GPIO_InitTypeDef gpio_init_struct;
  
  /* USART pins */
  gpio_init_struct.pin = GPIO_PIN_9;
  gpio_init_struct.mode = GPIO_MODE_AF_PP;
  gpio_init_struct.speed = GPIO_SPEED_50MHZ;
  gpio_init_struct.pull = 0;
  HAL_GPIO_init(GPIOA, &gpio_init_struct);
  
  gpio_init_struct.pin = GPIO_PIN_10;
  gpio_init_struct.mode = GPIO_MODE_INPUT;
  gpio_init_struct.speed = 0;
  gpio_init_struct.pull = GPIO_PULL_NONE;
  HAL_GPIO_init(GPIOA, &gpio_init_struct);

  /* Analog pins */
  gpio_init_struct.pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
  gpio_init_struct.mode = GPIO_MODE_ANALOG;
  gpio_init_struct.speed = GPIO_SPEED_50MHZ;
  gpio_init_struct.pull = GPIO_PULL_NONE;
  HAL_GPIO_init(GPIOA, &gpio_init_struct);
  
  /* button pin */
  gpio_init_struct.pin = GPIO_PIN_4;
  gpio_init_struct.mode = GPIO_MODE_INPUT;
  gpio_init_struct.speed = GPIO_SPEED_50MHZ;
  gpio_init_struct.pull = GPIO_PULL_UP;
  HAL_GPIO_init(GPIOA, &gpio_init_struct);
  
  gpio_init_struct.pin = GPIO_PIN_11;
  gpio_init_struct.mode = GPIO_MODE_INPUT;
  gpio_init_struct.speed = GPIO_SPEED_50MHZ;
  gpio_init_struct.pull = GPIO_PULL_DOWN;
  HAL_GPIO_init(GPIOD, &gpio_init_struct);
  
  gpio_init_struct.pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
  gpio_init_struct.mode = GPIO_MODE_INPUT;
  gpio_init_struct.speed = GPIO_SPEED_50MHZ;
  gpio_init_struct.pull = GPIO_PULL_DOWN;
  HAL_GPIO_init(GPIOE, &gpio_init_struct);
}

static void AG_ADC0_init(void) {
  HAL_RCU_enablePeriphClock(RCU_ADC0);
  HAL_RCU_setADCClock(RCU_CKADC_CKAPB2_DIV8);

  ADC_InitTypeDef adc0_init_struct;
  adc0_init_struct.mode = ADC_MODE_FREE;
  adc0_init_struct.data_align = ADC_DATAALIGN_RIGHT;
  adc0_init_struct.scan_mode = DISABLE;
  adc0_init_struct.continuous_mode = DISABLE;
  adc0_init_struct.discontinuous_mode = DISABLE;
  adc0_init_struct.trigger_source = ADC_TRIGGERSOURCE_REGULAR_SOFTWARE;
  adc0_init_struct.conversion_length = 1;

  adc0_init_struct.inserted_discontinuous_mode = DISABLE;
  adc0_init_struct.inserted_trigger_source = 0;
  adc0_init_struct.inserted_conversion_length = 1;
  adc0_init_struct.auto_insertion_mode = DISABLE;
  HAL_ADC_init(ADC0, &adc0_init_struct);

  ADC_ChannelInitTypeDef adc0_channel_init_struct;
  adc0_channel_init_struct.channel = ADC_CHANNEL_0;
  adc0_channel_init_struct.rank = ADC_RANK_0;
  adc0_channel_init_struct.sample_time = ADC_SAMPLETIME_1POINT5;
  adc0_channel_init_struct.insersion_offset = 0;
  HAL_ADC_initChannel(ADC0, &adc0_channel_init_struct);
  
  HAL_ADC_enable(ADC0);
}

static void AG_USART0_init(void) {
  HAL_RCU_enablePeriphClock(RCU_USART0);

  USART_InitTypeDef usart0_init_struct;
  usart0_init_struct.mode = USART_MODE_TX_RX;
  usart0_init_struct.baudrate = 115200UL;         // set the baudrate to 115200
  usart0_init_struct.word_length = USART_WORDLENGTH_8BIT;
  usart0_init_struct.stop_bits = USART_STOPBITS_1BIT;
  usart0_init_struct.parity = USART_PARITY_NONE;
  usart0_init_struct.hw_control = USART_HWCONTROL_NONE;
  HAL_USART_init(USART0, &usart0_init_struct);

  HAL_USART_enable(USART0);
}

