
int default_bool_autoantiotravlenie_lamp = 0;
int default_bool_auto_brights = 1;
int default_bool_auto_sunch_time = 1;

int default_int_bright_led_basic = 0;
int default_int_effects_led_basic = 12;
int default_int_speed_led_basic = 20;

int default_int_bright_led_front = 0;
int default_int_effects_led_front = 2;
int default_int_speed_led_front = 20;

const char *settingsFilename = "/8266.cfg";

struct settings_t
{
    char string_name_ssid_AP[32];
    char string_name_ssid[32];
    char string_password[32];

    char string_color_front[32];
    char string_color_basic[32];

    unsigned long bool_autoantiotravlenie_lamp;
    unsigned long bool_auto_brights;
    unsigned long bool_auto_sunch_time;

    unsigned long int_bright_led_basic;

    unsigned long int_effects_led_basic;

    unsigned long int_speed_led_basic;

    unsigned long int_bright_led_front;

    unsigned long int_effects_led_front;

    unsigned long int_speed_led_front;
};

extern settings_t settings{
    "IN-12 Clock AP",
    "CODE_0x",  //SSID Default
    "46684668", //Password Default
    "255,0,0",
    "255,0,0",
    default_bool_autoantiotravlenie_lamp,
    default_bool_auto_brights,
    default_bool_auto_sunch_time,

    default_int_bright_led_basic,
    default_int_effects_led_basic,
    default_int_speed_led_basic,

    default_int_bright_led_front,
    default_int_effects_led_front,
    default_int_speed_led_front

};

bool settings_save()
{
    if (!SPIFFS.begin())
    {
#ifdef DEBUG
        Serial.println("SPIFFS mount failed");
#endif
        return false;
    }
    File config = SPIFFS.open(settingsFilename, "w");
    if (!config)
    {
#ifdef DEBUG
        Serial.println("File open failed");
#endif
        return false;
    }
    uint16_t bytesWrited = config.write((byte *)&settings, sizeof(settings));
    config.close();
    if (bytesWrited != sizeof(settings))
    {
#ifdef DEBUG
        Serial.println("writen != settings");
#endif
        return false;
    }
    else
    {
        return true;
    }
}

bool settings_read()
{
    if (!SPIFFS.begin())
    {
#ifdef DEBUG
        Serial.println("SPIFFS mount failed");
#endif
        return false;
    }
    if (!SPIFFS.exists(settingsFilename))
    {
#ifdef DEBUG
        Serial.println("Config file not exsist");
#endif
        if (!settings_save())
        {
            return false;
        }
    }
    File config = SPIFFS.open(settingsFilename, "r");
    if (!config)
    {
        return false;
    }
    uint16_t bytesRead = config.read((byte *)&settings, sizeof(settings));
    config.close();
    if (bytesRead != sizeof(settings))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void settings_default()
{

    strncpy(settings.string_name_ssid_AP, "IN-12 Clock AP", sizeof(settings.string_name_ssid_AP));
    strncpy(settings.string_name_ssid, "CODE_0x", sizeof(settings.string_name_ssid));
    strncpy(settings.string_password, "46684668", sizeof(settings.string_password));

    strncpy(settings.string_color_front, "255,0,0", sizeof(settings.string_color_front));
    strncpy(settings.string_color_basic, "255,0,0", sizeof(settings.string_color_basic));

    settings.bool_autoantiotravlenie_lamp = default_bool_autoantiotravlenie_lamp;
    settings.bool_auto_brights = default_bool_auto_brights;
    settings.bool_auto_sunch_time = default_bool_auto_sunch_time;

    settings.int_bright_led_basic = default_int_bright_led_basic;
    settings.int_effects_led_basic = default_int_effects_led_basic;
    settings.int_speed_led_basic = default_int_speed_led_basic;

    settings.int_bright_led_front = default_int_bright_led_front;
    settings.int_effects_led_front = default_int_effects_led_front;
    settings.int_speed_led_front = default_int_speed_led_front;

    settings_save();
}