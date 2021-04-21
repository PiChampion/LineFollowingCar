#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define YES                     (1)

//Main Definitions

//IOT Definitions
#define ONE_SECOND_RESET        (200)
#define IP_NUM_1                (4)
#define IP_NUM_2                (5)
#define IP_NUM_3                (6)
#define IP_NUM_1_STRING         (10)
#define IP_NUM_2_STRING         (11)
#define IP_NUM_3_STRING         (12)
#define SUBNET_NUM_0            (0)
#define SUBNET_NUM_1            (1)
#define SUBNET_NUM_2            (2)
#define SUBNET_NUM_3            (3)
#define SUBNET_NUM_4            (4)
#define SUBNET_NUM_5            (5)
#define SUBNET_NUM_6            (6)
#define SUBNET_NUM_7            (7)
#define SUBNET_NUM_8            (8)
#define SUBNET_NUM_9            (9)
#define SUBNET_NUM_0_STRING     (16)
#define SUBNET_NUM_1_STRING     (17)
#define SUBNET_NUM_2_STRING     (18)
#define SUBNET_NUM_3_STRING     (20)
#define SUBNET_NUM_4_STRING     (21)
#define SUBNET_NUM_5_STRING     (22)
#define SUBNET_NUM_6_STRING     (24)
#define SUBNET_NUM_7_STRING     (25)
#define SUBNET_NUM_8_STRING     (26)
#define SUBNET_NUM_9_STRING     (28)

//Command Definitions
#define COMMAND_LINES           (3)
#define COMMAND_CHARS           (16)
#define FIFTY_MSEC              (10)
#define DIRECTION_CHAR          (0)
#define HUNDREDS_CHAR           (1)
#define TENS_CHAR               (2)
#define ONES_CHAR               (3)
#define NUMBER_POSITION         (8)

//Startup Definition
#define ONE_SECOND_STARTUP      (200)
#define FIVE_SECOND_STARTUP     (1000)

//Menu Definitions
#define DUMMY_VALUE             (11111)
#define DIVIDE_BY_128           (7)
#define BAUD_SELECTION          (0)
#define TRANSMIT                (1)
#define EVERYTHING              (0)
#define MENU_1                  (1)
#define MENU_2                  (2)
#define MENU_3                  (3)
#define MENU_4                  (4)
#define MENU_5                  (5)
#define MENU_6                  (6)
#define MENU_7                  (7)

//Serial Communication Definitions
#define BEGINNING               (0)
#define SMALL_RING_SIZE         (16)
#define PROC_RING_SIZE          (32)
#define NULL_HEX                (0x00)
#define BAUD_115200             (0)
#define BAUD_460800             (1)
#define BRW_9600                (52)
#define BRW_115200              (4)
#define BRW_460800              (1)
#define MCTLW_9600              (0x4911)
#define MCTLW_115200            (0x5551)
#define MCTLW_460800            (0x4A11)
#define TWENTY_FIVE_MSEC        (5)
#define TWO_SECOND_DELAY        (400)
#define NO_INTERRUPT            (0)
#define RXIFG_CASE              (2)
#define TXIFG_CASE              (4)
#define DISCONNECT_CASE         (100)
#define RECONNECT_CASE          (200)
#define CARRIAGE_RETURN         (0x0D)
#define LINE_FEED               (0x0A)
#define UCA0_PROCESS_BUFFERS    (2)
#define FIRST_CHAR_RECEIVED     (0)
#define PASSWORD_CHAR_1         (1)
#define PASSWORD_CHAR_2         (2)
#define PASSWORD_CHAR_3         (3)
#define PASSWORD_CHAR_4         (4)
#define COMMAND_CHAR            (5)
#define COMMAND_VALUE_1         (6)
#define COMMAND_VALUE_2         (7)
#define COMMAND_VALUE_3         (8)
#define COMMAND                 (0)
#define COMMAND_VALUE_HUNDRED   (1)
#define COMMAND_VALUE_TEN       (2)
#define COMMAND_VALUE_ONE       (3)
#define BUFFER_BUFFER           (1)

//Movement Definitions
#define LINE_THRESHOLD          (300)
#define SENSITIVE_THRESHOLD     (100)
#define TEN_MS                  (2)
#define THIRTY_MS               (6)
#define FORTY_MS                (8)
#define SIXTY_MS                (10)
#define EIGHTY_MS               (12)
#define HALF_SECOND             (5)
#define ONE_SECOND              (10)
#define TWO_SECONDS             (20)
#define THREE_SECONDS           (30)
#define FOUR_SECONDS            (40)
#define FIVE_SECONDS            (50)
#define TEN_SECONDS             (100)
#define TWO_CIRCLES             (290)
#define TURN_90_TIME_CCW        (4)
#define TURN_90_TIME_CW         (5)
#define INITIAL_TURN            (800)
#define INITIAL_TURN_END        (801)
#define WAIT_BUFFER_INITIAL     (802)
#define WAIT_BUFFER_1           (98)
#define FORWARD_AND_SEARCH      (1)
#define BEGIN_MOVEMENT          (2)
#define FORWARD_STOP            (3)
#define WAIT_BUFFER             (4)
#define SPIN_AND_SEARCH         (5)
#define WAIT_BUFFER_2           (6)
#define MOVE_TO_EDGE            (7)
#define TRAVERSE_CIRCLE         (8)
#define WAIT_FOR_R_TURN         (9)
#define WAIT_FOR_L_TURN         (10)
#define WAIT_BUFFER_3           (11)
#define TURN_BACK               (12)
#define WAIT_BUFFER_4           (13)
#define FIND_CENTER             (14)
#define SLIDE_TIME              (2)
#define STATE_0                 (0)
#define STATE_1                 (1)
#define STATE_2                 (2)
#define STATE_3                 (3)
#define STATE_4                 (4)
#define STATE_5                 (5)
#define STATE_6                 (6)
#define STATE_7                 (7)
#define STATE_8                 (8)
#define STATE_9                 (9)
#define STATE_10                (10)
#define STATE_11                (11)
#define STATE_12                (12)
#define STATE_13                (13)

//PWM Definitions
#define WHEEL_PERIOD            (60010)
#define WHEEL_OFF               (0)
#define RIGHT_FORWARD_SPEED     (TB3CCR1)
#define LEFT_FORWARD_SPEED      (TB3CCR2)
#define RIGHT_REVERSE_SPEED     (TB3CCR3)
#define LEFT_REVERSE_SPEED      (TB3CCR4)
#define RIGHT_FULL_SPEED_F      (39000)
#define LEFT_FULL_SPEED_F       (60000)
#define RIGHT_MED_SPEED_F       (32500)
#define LEFT_MED_SPEED_F        (47000)
#define RIGHT_FULL_SPEED_R      (42000)
#define LEFT_FULL_SPEED_R       (60000)
#define RIGHT_MED_SPEED_R       (32500)
#define LEFT_MED_SPEED_R        (55000)
#define RIGHT_SLOW_SPEED_R      (14000)
#define LEFT_SLOW_SPEED_F       (40000)
#define LEFT_SLOW_SPEED_R       (31000)
#define RIGHT_SLOW_SPEED_F      (20000)

//ADC Definitions
#define A2                      (0x00)
#define A3                      (0x01)
#define A5                      (0x02)
#define ASCII_START             ('0')
#define DIVIDE_2                (1)
#define DIVIDE_4                (2)
#define FIRST_NIBBLE_MASK       (0x000F)
#define SECOND_NIBBLE_MASK      (0x00F0)
#define THIRD_NIBBLE_MASK       (0x0F00)
#define FOURTH_NIBBLE_MASK      (0xF000)
#define SECOND_NIBBLE_SHIFT     (4)
#define THIRD_NIBBLE_SHIFT      (8)
#define FOURTH_NIBBLE_SHIFT     (12)
#define THOUSAND                (1000)
#define HUNDRED                 (100)
#define TEN                     (10)
#define ONE                     (1)
#define QUARTER_SECOND          (50)
#define THUMB                   (2)
#define RIGHT_DETECT            (1)
#define LEFT_DETECT             (0)
#define ONES_DIGIT              (7)
#define TENS_DIGIT              (6)
#define HUNDREDS_DIGIT          (5)
#define THOUSANDS_DIGIT         (4)

//Switch Definitions
#define DEBOUNCE_TIME           (10)

//Timer Definitions
#define TIME_SEQ_MAX            (10000)
#define CCR0_CASE               (0)
#define CCR1_CASE               (2)
#define CCR2_CASE               (4)
#define OVERFLOW_CASE           (14)
#define TB0CCR0_INTERVAL        (2500) // 8,000,000 / 2 / 8 / (1 / 5msec)
#define TB0CCR1_INTERVAL        (50000) // 8,000,000 / 2 / 8 / (1 / 100msec)
#define TB0CCR2_INTERVAL        (50000) // 8,000,000 / 2 / 8 / (1 / 100msec)
#define TB1CCR0_INTERVAL        (2500) // 8,000,000 / 2 / 8 / (1 / 5msec)
#define TB1CCR1_INTERVAL        (50000) // 8,000,000 / 2 / 8 / (1 / 100msec)
#define TB1CCR2_INTERVAL        (50000) // 8,000,000 / 2 / 8 / (1 / 100msec)

//Display Definitions
#define DISPLAY_LINE            (11)
#define DISPLAY_SET_TIME        (100)
#define SWITCH_WAIT             (100)
#define UPDATE                  (1)
#define UPDATE_BACKLIGHT        (1)
#define UPDATE_BACKLIGHT_CTR    (100)
#define CHANGE                  (39)
#define TWO_HUNDRED_MS          (2)
#define TIME_DECIMAL_DIGIT      (6)
#define TIME_ONES_DIGIT         (4)
#define TIME_TENS_DIGIT         (3)
#define TIME_HUNDREDS_DIGIT     (2)
#define NULL_CHAR               ('\0')

//String Definitions
#define STRING_ONE              (0)
#define STRING_TWO              (1)
#define STRING_THREE            (2)
#define STRING_FOUR             (3)

//Init Definitions
#define FIRST_CHAR              (0)
#define LAST_CHAR               (10)
#define LINES                   (4)
#define CHAR_SPACES             (11)
#define LINE_ONE                (0)
#define LINE_TWO                (1)
#define LINE_THREE              (2)
#define LINE_FOUR               (3)

//Port Definitions
#define SET_INPUTS              (0x00)
#define SET_OUTPUTS             (0xFF)
#define SET_GPIO		(0x00)
#define SET_LOW                 (0x00)
#define USE_GPIO                (0x00)
#define USE_SMCLK               (0x01)

//Port 1 Pins
#define RED_LED                 (0x01) // 0 RED LED 0
#define A1_SEEED                (0x02) // 1 A1_SEEED
#define V_DETECT_L              (0x04) // 2 V_DETECT_L
#define V_DETECT_R              (0x08) // 3 V_DETECT_R
#define A4_SEEED                (0x10) // 4 A4_ SEEED
#define V_THUMB                 (0x20) // 5 V_THUMB
#define UCA0RXD                 (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD                 (0x80) // 7 Back Channel UCA0TXD

//Port 2 Pins
#define P2_0                    (0x01) // 0
#define P2_1                    (0x02) // 1
#define P2_2                    (0x04) // 2
#define SW2                     (0x08) // 3 SW2
#define P2_4                    (0x10) // 4
#define P2_5                    (0x20) // 5
#define LFXOUT                  (0x40) // 6 XOUTR
#define LFXIN                   (0x80) // 7 XINR

//Port 3 Pins
#define TEST_PROBE              (0x01) // 0 TEST PROBE
#define CHECK_BAT               (0x02) // 1 CHECK_BAT
#define OA2N                    (0x04) // 2 Photodiode Circuit
#define OA2P                    (0x08) // 3 Photodiode Circuit
#define P3_4                    (0x10) // 4 P3_4
#define SMCLK_OUT               (0x10) // 4 SMCLK
#define IR_LED                  (0x20) // 5 IR_LED
#define IOT_LINK                (0x40) // 6 IOT_LINK
#define P3_7                    (0x80) // 7 P3_7

//Port 4 Pins
#define RESET_LCD               (0x01) // 0 LCD Reset
#define SW1                     (0x02) // 1 SW1
#define UCA1RXD                 (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD                 (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD             (0x10) // 4 Chip Select
#define UCB1CLK                 (0x20) // 5 SPI mode clock output UCB1CLK
#define UCB1SIMO                (0x40) // 6 UCB1SIMO
#define UCB1SOMI                (0x80) // 7 UCB1SOMI

//Port 5 Pins
#define IOT_RESET               (0x01) // 0 IOT Reset
#define V_BAT                   (0x02) // 1 Battery Voltage
#define IOT_PROG_SEL            (0x04) // 2 IOT Program Select
#define V_3_3                   (0x08) // 3 V_3_3
#define IOT_PROG_MODE           (0x10) // 4 IOT Program Mode

//Port 6 Pins
#define R_FORWARD               (0x01) // 0 Right Forward
#define L_FORWARD               (0x02) // 1 Left Forward
#define R_REVERSE               (0x04) // 2 Right Reverse
#define L_REVERSE               (0x08) // 3 Left Reverse
#define LCD_BACKLITE            (0x10) // 4 LCD Backlight
#define P6_5                    (0x20) // 5 
#define GRN_LED                 (0x40) // 6 GREEN LED 1      


