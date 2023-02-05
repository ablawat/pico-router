#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#define PICO_DEBUG_R 17U
#define PICO_DEBUG_G 16U
#define PICO_DEBUG_B 25U

static volatile bool fired = false;

/* set alarm time, match every day at 00:01:00 */
static datetime_t alarm =
{
    .year  = -1,
    .month = -1,
    .day   = -1,
    .dotw  = -1,
    .hour  = 0,
    .min   = 1,
    .sec   = 0
};

static void alarm_callback(void)
{
    alarm.min += 1;

    rtc_set_alarm(&alarm, &alarm_callback);

    if (fired == true)
    {
        /* green LED */
        gpio_put(PICO_DEBUG_G, true);
        fired = false;
    }
    else
    {
        /* green LED */
        gpio_put(PICO_DEBUG_G, false);
        fired = true;
    }
}

int main()
{
    /* start on Wednesday 24th of August 2022 15:30:00 */
    datetime_t time =
    {
        .year  = 2022,
        .month = 8,
        .day   = 24,
        .dotw  = 3,
        .hour  = 15,
        .min   = 30,
        .sec   = 0
    };

    /* start the RTC */
    rtc_init();
    rtc_set_datetime(&time);

    /* 3 RTC clock cycles delay (which is 64 us with the default clock settings) */
    sleep_us(UINT64_C(64));

    rtc_set_alarm(&alarm, &alarm_callback);

    gpio_init(PICO_DEBUG_R);
    gpio_init(PICO_DEBUG_G);
    gpio_init(PICO_DEBUG_B);

    gpio_set_dir(PICO_DEBUG_R, GPIO_OUT);
    gpio_set_dir(PICO_DEBUG_G, GPIO_OUT);
    gpio_set_dir(PICO_DEBUG_B, GPIO_OUT);

    /* turn off RGB LED */
    gpio_put(PICO_DEBUG_R, true);
    gpio_put(PICO_DEBUG_G, true);
    gpio_put(PICO_DEBUG_B, true);

    while (true);

    return 0;
}
