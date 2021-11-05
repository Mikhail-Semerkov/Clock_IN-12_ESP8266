#include <Arduino.h>

#include <site.h>

void setup()
{
  setup_site();

  setup_ws2812();

  setup_in_12_lamp();
  setup_synch_clock_udp();
}

void loop()
{
  loop_site();

  loop_ws2812();

  SYNCH_CLOCK();

  //LAMP_WRITE();

  Anti_Perebor_All_Lamp();
}
