#include "Keyboard.h"
#include "Keyboard_de_DE.h"

int time = 0;

int const ROW_COUNT = 6;
int const COLUMN_COUNT = 12;

//Digital Pin numbers of the micro corresponding to each row and column
int ROWS[6] = {0, 1, 2, 3, 4, 5};               
int COLUMNS[12] = {6, 7, 8, 9, 10, 16, 14, 15, 18, 19, 20, 21};

char KEY_MAP_LAYER1[ROW_COUNT][COLUMN_COUNT] = {
                                        {KEY_CIRCUMFLEX, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', KEY_ESZETT},
                                        {KEY_TAB, 'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', KEY_U_UMLAUT},
                                        {KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', KEY_O_UMLAUT, KEY_A_UMLAUT},
                                        {KEY_LEFT_SHIFT, 'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', KEY_RIGHT_SHIFT},
                                        {KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_RETURN, '>', ' ', KEY_F2, KEY_UP_ARROW, KEY_ACUTE, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_RIGHT_CTRL},
                                        {0x00, KEY_BACKSPACE, '<', '#', KEY_RIGHT_ARROW, KEY_F4, KEY_F3, KEY_DOWN_ARROW, '+', KEY_ESC, KEY_DELETE, KEY_LEFT_ARROW},
                                        };

char KEY_MAP_LAYER2[ROW_COUNT][COLUMN_COUNT] = {
                                        {KEY_F12, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11},
                                        {KEY_TAB, 'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', KEY_U_UMLAUT},
                                        {KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', KEY_O_UMLAUT, KEY_A_UMLAUT},
                                        {KEY_LEFT_SHIFT, 'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', KEY_RIGHT_SHIFT},
                                        {KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_RETURN, '>', ' ', KEY_F2, KEY_UP_ARROW, KEY_ACUTE, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_RIGHT_CTRL},
                                        {0x00, KEY_BACKSPACE, '<', '#', KEY_RIGHT_ARROW, KEY_F4, KEY_F3, KEY_DOWN_ARROW, '+', KEY_ESC, KEY_DELETE, KEY_LEFT_ARROW},
                                        };


bool PRESSED_MAP[ROW_COUNT][COLUMN_COUNT];
char (*KEY_MAP)[COLUMN_COUNT] = KEY_MAP_LAYER1;

void setup() {

    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        pinMode(COLUMNS[i], INPUT_PULLUP);
    }
    for (int i = 0; i< ROW_COUNT; i++)
    {
        pinMode(ROWS[i], OUTPUT);
        digitalWrite(ROWS[i], HIGH);
    }
    for (int y = 0; y < ROW_COUNT; y++)
    {
        for (int x = 0; x < COLUMN_COUNT; x++)
        {
            PRESSED_MAP[y][x] = false;
        }
    }

    // put your setup code here, to run once:
    Keyboard.begin(KeyboardLayout_de_DE);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    for (int y = 0; y < ROW_COUNT; y++)
    {
          //Begin scan one row
          digitalWrite(ROWS[y], LOW);

          //Go through column
          for (int x = 0; x < COLUMN_COUNT; x++)
          {
              if (digitalRead(COLUMNS[x]) == LOW && !PRESSED_MAP[y][x])
              {
                  if (KEY_MAP[y][x] == 0x00)
                  {
                      KEY_MAP = KEY_MAP_LAYER2;
                  }
                  else
                  {
                      Keyboard.press(KEY_MAP[y][x]);
                      PRESSED_MAP[y][x] = true;
                  }
              }
              else if (digitalRead(COLUMNS[x]) == HIGH && PRESSED_MAP[y][x])
              {
                  if (KEY_MAP[y][x] == 0x00)
                  {
                      KEY_MAP = KEY_MAP_LAYER1;
                  }
                  else
                  {
                      Keyboard.release(KEY_MAP[y][x]);
                      PRESSED_MAP[y][x] = false;
                  }
              }
          }

          digitalWrite(ROWS[y], HIGH);
      }
}