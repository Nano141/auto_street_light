int main()
{
  volatile int value = 0;
  PORT_INIT();
  LCD_START();
  value = Set_Delay(value);
  Check_Move(value);
  return 0;
}
