/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#define PICO_LED_PIN 2

int main()
{
    /* Start on Friday 24th of August 2022 11:00:00 */
    datetime_t time = {
            .year  = 2022,
            .month = 8,
            .day   = 24,
            .dotw  = 3,       /* 0 is Sunday */
            .hour  = 15,
            .min   = 30,
            .sec   = 0
    };

    /* Start the RTC */
    rtc_init();
    rtc_set_datetime(&time);

    /* 3 RTC clock cycles delay (which is 64us with the default clock settings) */
    sleep_us(64);

    const uint LED_PIN = PICO_LED_PIN;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true)
    {
        rtc_get_datetime(&time);

	if (((time.hour >= 15) && (time.hour < 16)) ||
            ((time.hour >= 17) && (time.hour < 18)))
	{
            gpio_put(LED_PIN, 1);
	}
	else
	{
            gpio_put(LED_PIN, 0);
	}

        sleep_ms(1000);
    }
}
