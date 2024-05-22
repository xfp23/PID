#include "pins.h"
#include "screen_conf.h"
#include "PID_config.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pwm_conf.h"


extern volatile MUPD mpu_data;
extern volatile struct PIDCTROL M1_A;
extern volatile struct MOTORSPEED Speed;
extern volatile MUPD mpu_data;
extern volatile PIDCTROL M1_A;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

// 主页面
INTERFACE front_page = {
    .top_x = 46,
    .top_y = 8,
    .top_text = "PID",
    .first_text_x = TEXT_X,
    .first_text_y=17,
    .first_text = "M1 OUTPUT:",
    .second_text_x = TEXT_X,
    .second_text_y = 27,
    .second_text = "M2 OUTPUT:",
    .third_text_x = TEXT_X,
    .third_text_y = 37,
    .third_text = "Accgle:",
    .fourth_text_x = TEXT_X,
    .fourth_text_y = 47,
    .fourth_text = "Angle:"
};

void init_screen() {
    Wire.begin(3, 2);
    Serial.println("Start init screen");
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F(" initialization failed"));
       // while (1); // Stop execution if initialization fails
    }
    //Serial.println(F("SSD1306 initialized"));
    display.display(); // Show initial buffer content
    DELAY_MS(200);       // Pause for 2 seconds to show the initial screen
    display.clearDisplay();
    display.display();
}

void displayout(const char *pt, int x, int y) {
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(x, y);
    display.print(pt);
}

void display_battery() {
    int points[][2] = {
        {4, -1}, {3, 0}, {2, 1}, {1, 2}, {0, 3},
        {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3},
        {5, 3}, {4, 4}, {3, 5}, {2, 6}, {1, 7}
    };

    for (int i = 0; i < sizeof(points) / sizeof(points[0]); ++i) {
        displayout(".", points[i][0], points[i][1]);
    }
   // display.display();
}

void display_bar() {
    displayout("PID...", 45, 39);
    for (int x = 10; x < 100; x++) {
        for (int y = 28; y < 40; y++) {
            displayout(".", x, y);
        }
        if (x % 2 == 0) {
            DELAY_MS(22); // Delay to simulate loading
            display.display();
        }
    }
}

void dispaly_num(float num, int x, int y) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.print(num);
}

void display_speed(INTERFACE *menu) {
    displayout(menu->top_text,menu->top_x,menu->top_y);
    displayout(menu->first_text, menu->first_text_x, menu->first_text_y);
    displayout(menu->second_text, menu->second_text_x, menu->second_text_y);
    displayout(menu->third_text, menu->third_text_x, menu->third_text_y);
    displayout(menu->fourth_text, menu->fourth_text_x, menu->fourth_text_y);

    dispaly_num(Speed.M1_PWM_OUT*100/MAX1_DUTY, 80, 17);
    displayout("%",110,27);
    displayout("%",110,17);
    dispaly_num(Speed.M2_PWM_OUT*100/MAX2_DUTY, 80, 27);
    dispaly_num(mpu_data.accgle, 80, 37);
    dispaly_num(mpu_data.angle, 80, 47);
    //display.display();
}

void screen_loop() {
    static bool initialized = false;
    if (!initialized) {
       // init_screen();
        display_bar();
        display_battery();
        DELAY_MS(500); // Delay to show the battery and bar initialization
        initialized = true;
    }

    display.clearDisplay();
    display_speed(&front_page);
    display_battery();
    display.display();
}

void screen_Application(void *param) {
    while (true) {
        screen_loop();
         DELAY_MS(10);
    }
}
