#include <Arduino.h>
#include <GyverTimer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <microDS3231.h>
///////////////////////////////////////

GTimer TimerSecond(MS);

// Time UDP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedDate;
String dayStamp;
String timeStamp;
int timeZone = 3;
bool Synch_UDP;
bool UDP_Error;

// RTC Time
MicroDS3231 RTC_Clock;

String Lamp_Time_Current;

void UDP_SYNCH()
{
  if (WiFi.status() == WL_CONNECTED && Synch_UDP == false)
  {
    Serial.println("WiFi Connect!");
    timeClient.begin();
    timeClient.setTimeOffset(3600 * timeZone);

    if (!timeClient.update())
    {
      Serial.println("UDP Error!");
      timeClient.forceUpdate();
      UDP_Error = true;
    }
    else
    {
      UDP_Error = false;
    }

    if (UDP_Error == false && UDP_Error == false)
    {

      formattedDate = timeClient.getFormattedDate();
      int splitT = formattedDate.indexOf("T");
      dayStamp = formattedDate.substring(0, splitT);
      Serial.print("UDP DATE: ");
      Serial.println(dayStamp);

      timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
      Serial.print("UDP TIME: ");
      Serial.println(timeStamp);

      RTC_Clock.setHMSDMY(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(), dayStamp.substring(8, 10).toInt(), dayStamp.substring(5, 7).toInt(), dayStamp.substring(0, 4).toInt());

      if (UDP_Error == false)
      {
        Synch_UDP = true;
      }
    }
  }
}

void SYNCH_CLOCK()
{
  if (TimerSecond.isReady())
  {
    char time[8];

    RTC_Clock.getTimeChar(time);

    LAMP1_TIME = String(time[0]).toInt();
    LAMP2_TIME = String(time[1]).toInt();
    LAMP3_TIME = String(time[3]).toInt();
    LAMP4_TIME = String(time[4]).toInt();

    Lamp_Time_Current = time;

    Count_Dots++;

    if (Antiotravlenie_Lamp == true)
    {
      Count_Time_Anti_Otravlenie++;
    }
  }

  LAMP_WRITE(LAMP1_TIME, LAMP2_TIME, LAMP3_TIME, LAMP4_TIME, Brightness_Lamp);
}

void setup_synch_clock_udp()
{
  Synch_UDP = false;
  UDP_Error = false;

  TimerSecond.setInterval(1000);
}