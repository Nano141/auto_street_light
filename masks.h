#define RED (0x02)
#define BLUE (0x04)
#define LIGHT (0x02)
#define MOTION (0x01)

void wait(int time);
void PORT_INIT(void);
void GPTM_D_ONESHOT(void);