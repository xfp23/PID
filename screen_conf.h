#include <Arduino.h>
typedef struct {
    uint8_t top_x;
    uint8_t top_y;
    char * top_text;
    uint8_t first_text_x;
    uint8_t  first_text_y;
    char *first_text;
    uint8_t second_text_x;
    uint8_t second_text_y;
    char *second_text;
    uint8_t third_text_x;
    uint8_t third_text_y;
    char *third_text;
    uint8_t fourth_text_x;
    uint8_t fourth_text_y;
    char *fourth_text;
}INTERFACE;

#define TEXT_X 10
