#include <ShiftRegister74HC595.h>
#include <GyverTimer.h>

ShiftRegister74HC595<2> sr(13, 14, 15);
uint8 Key_Lamp[4] = {11, 12, 13, 14};

GTimer Timer_Brightness_Lamp(US);

int Brightness_Lamp = 20;
//int Brightness_Сycle = 0;
int Count_Dots;

uint8 LAMP1_TIME;
uint8 LAMP2_TIME;
uint8 LAMP3_TIME;
uint8 LAMP4_TIME;

int Perebor;

bool Antiotravlenie_Lamp;
unsigned long Time_Anti_Otravlenie;
unsigned long Count_Time_Anti_Otravlenie;

void setup_in_12_lamp()
{
    Timer_Brightness_Lamp.setInterval(3300);
    Time_Anti_Otravlenie = 60;
}

void LAMP_WRITE(int Count_Lamp_1, int Count_Lamp_2, int Count_Lamp_3, int Count_Lamp_4, int Brightness_Lamp) //int Count_Lamp_1, int Count_Lamp_2, int Count_Lamp_3, int Count_Lamp_4
{
    if (Timer_Brightness_Lamp.isReady())
    {
        for (int i = 0; i < 5; i++)
        {
            if (i == 0)
            {

                sr.set(Key_Lamp[i], HIGH);

                switch (Brightness_Lamp)
                {
                case 20:

                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);

                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    sr.set(LAMP1_TIME, HIGH);
                    break;

                default:
                    break;
                }
            }

            if (i == 1)
            {

                sr.set(Key_Lamp[i], HIGH);

                switch (Brightness_Lamp)
                {
                case 20:

                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);

                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    sr.set(LAMP2_TIME, HIGH);
                    break;

                default:
                    break;
                }
            }

            if (i == 2)
            {

                sr.set(Key_Lamp[i], HIGH);

                switch (Brightness_Lamp)
                {
                case 20:

                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);

                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    sr.set(LAMP3_TIME, HIGH);
                    break;

                default:
                    break;
                }
            }

            if (i == 3)
            {
                sr.set(Key_Lamp[i], HIGH);

                switch (Brightness_Lamp)
                {
                case 20:

                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);

                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    sr.set(LAMP4_TIME, HIGH);
                    break;

                default:
                    break;
                }
            }

            sr.setAllLow();

            if (i == 4)
            {
                if (Count_Dots == 0)
                {
                    sr.set(10, LOW);
                    //sr.set(10, HIGH);
                }
                if (Count_Dots == 1)
                {
                    sr.set(10, HIGH);
                    sr.set(10, HIGH);
                    sr.set(10, HIGH);
                    sr.set(10, HIGH);
                    sr.set(10, HIGH);
                    sr.set(10, HIGH);
                }
                else if (Count_Dots == 2)
                {
                    Count_Dots = 0;
                }
            }
            sr.setAllLow();
        }
    }
}

void Anti_Perebor_All_Lamp()
{
    if (Antiotravlenie_Lamp == true && Time_Anti_Otravlenie > Count_Time_Anti_Otravlenie)
    {
        Serial.println(Time_Anti_Otravlenie);
        Serial.println();
        Serial.println(Count_Time_Anti_Otravlenie);

        Perebor++;
        sr.setNoUpdate(Perebor, HIGH);
        sr.setNoUpdate(11, HIGH);
        sr.setNoUpdate(12, HIGH);
        sr.setNoUpdate(13, HIGH);
        sr.setNoUpdate(14, HIGH);
        sr.updateRegisters();
        delay(100);

        sr.setNoUpdate(Perebor, LOW);
        sr.updateRegisters();

        if (Perebor >= 9)
        {
            Perebor = -1;
        }
    }
    else if (Antiotravlenie_Lamp == true && Time_Anti_Otravlenie == 0)
    {
        Serial.println(Time_Anti_Otravlenie);
        Serial.println();
        Serial.println(Count_Time_Anti_Otravlenie);

        Perebor++;
        sr.setNoUpdate(Perebor, HIGH);
        sr.setNoUpdate(11, HIGH);
        sr.setNoUpdate(12, HIGH);
        sr.setNoUpdate(13, HIGH);
        sr.setNoUpdate(14, HIGH);
        sr.updateRegisters();
        delay(100);

        sr.setNoUpdate(Perebor, LOW);
        sr.updateRegisters();

        if (Perebor >= 9)
        {
            Perebor = -1;
        }

        Count_Time_Anti_Otravlenie = 0;
    }
}
