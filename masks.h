#define RED (0x02)
#define BLUE (0x04)
#define LIGHT (0x10)
#define MOTION (0x20)
#define LCD_DATA_DATA (GPIO_PORTB_DATA_R)
#define LCD_CTRL_DATA (GPIO_PORTA_DATA_R)
#define SW1 (0x10)
#define SW2 (0x01)
#define RS (0X04)
#define RW (0x08)
#define EN (0x10)

void timer(float time);
void wait(int time);
void PORT_INIT(void);
void GPTM_D_ONESHOT(void);
void LCD_START(void);
void LCD_command(unsigned char command);
void LCD_data(unsigned char command);