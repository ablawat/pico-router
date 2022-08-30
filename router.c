/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#define PICO_DEBUG_PIN 2

static volatile bool fired = false;

/* Set alarm */
static datetime_t alarm =
{
    .year  = -1,
    .month = -1,
    .day   = -1,
    .dotw  = -1,
    .hour  = 0,
    .min   = 2,
    .sec   = 0
};


static void alarm_callback(void)
{
    alarm.min += 2;

    rtc_set_alarm(&alarm, &alarm_callback);

    if (fired == true)
    {
        gpio_put(PICO_DEBUG_PIN, 0);
        fired = false;
    }
    else
    {
        gpio_put(PICO_DEBUG_PIN, 1);
        fired = true;
    }
}

int main()
{
    /* Start on Wednesday 24th of August 2022 15:30:00 */
    datetime_t time =
    {
            .year  = 2022,
            .month = 8,
            .day   = 24,
            .dotw  = 3,
            .hour  = 23,
            .min   = 58,
            .sec   = 0
    };

    /* Start the RTC */
    rtc_init();
    rtc_set_datetime(&time);

    /* 3 RTC clock cycles delay (which is 64us with the default clock settings) */
    sleep_us(64);

    rtc_set_alarm(&alarm, &alarm_callback);

    gpio_init(PICO_DEBUG_PIN);
    gpio_set_dir(PICO_DEBUG_PIN, GPIO_OUT);

    gpio_put(PICO_DEBUG_PIN, 0);

    while (true);

    return 0;
}
