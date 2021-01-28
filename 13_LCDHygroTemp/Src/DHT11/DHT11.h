GPIO_InitTypeDef gpio;

void DHT11_setup();
uint8_t DHT11_check_response();
uint8_t DHT11_read_data();
void set_pin_input(GPIO_TypeDef *gpio, uint16_t pin);
void set_pin_output(GPIO_TypeDef *gpio, uint16_t pin);
