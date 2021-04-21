//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

#include "macros.h"

void main(void);
// IOT
void IOT_Process(void);
void find_ip_address(char string[PROC_RING_SIZE]);
void find_subnet(char string[PROC_RING_SIZE]);
void Command_Process(void);

// Serial
void Init_Serial_UCA0(unsigned int baud);
void Init_Serial_UCA1(unsigned int baud);
void Serial_Process(void);
void out_character_UCA0(char character);
void out_character_UCA1(char character);

// Movement
void Movement_Process(void);
void Stop_Movement(void);
void Forward_Movement(void);
void Forward_Movement_Medium(void);
void Forward_Movement_Slow(void);
void Reverse_Movement(void);
void Spin_CW(void);
void Spin_CW_SLOW(void);
void Spin_CCW(void);
void Spin_CCW_SLOW(void);
void Turn_R_Five_Degrees(void);
void Turn_L_Five_Degrees(void);

// Display
void Update_Display_Process(void);
void set_display(const char line1[DISPLAY_LINE], const char line2[DISPLAY_LINE], 
                 const char line3[DISPLAY_LINE], char const line4[DISPLAY_LINE]);
void set_display_line(char data[DISPLAY_LINE], unsigned int line);
void Backlight_Update(void);

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);
__interrupt void ADC_ISR(void);

// Analog to Digital Converter
void ADC_Process(void);
void Init_ADC(void);
unsigned int HEXtoBCD(unsigned int data);
void adc_line4(unsigned int data, int x);
void HEXtoASCII(char string[DISPLAY_LINE], unsigned int data);

// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

// LCD
void update_changed_display(void);

void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);
void Startup_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char MODE);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);




