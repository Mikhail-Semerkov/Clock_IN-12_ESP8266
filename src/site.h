#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#include <FS.h>

#include <setting_controlls.h>

#include <in_12_lamp.h>
#include <synch_clock_udp.h>
#include <functions.h>
#include <ws2812.h>

bool load_settings;
int сonnect_count;

const char *htmlfile = "/index.html";

String SSID_SAVE;
String PASSWORD_SAVE;

int Brightnes_WS2812_Front;
int Brightnes_WS2812_Basic;

String Effects_WS2812_Front;

ESP8266WebServer server(80);

ESP8266HTTPUpdateServer httpUpdater;

bool loadFromSpiffs(String path)
{
  String dataType = "text/plain";
  if (path.endsWith("/"))
    path += "index.htm";

  if (path.endsWith(".src"))
    path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".html"))
    dataType = "text/html";
  else if (path.endsWith(".htm"))
    dataType = "text/html";
  else if (path.endsWith(".css"))
    dataType = "text/css";
  else if (path.endsWith(".js"))
    dataType = "application/javascript";
  else if (path.endsWith(".png"))
    dataType = "image/png";
  else if (path.endsWith(".gif"))
    dataType = "image/gif";
  else if (path.endsWith(".jpg"))
    dataType = "image/jpeg";
  else if (path.endsWith(".ico"))
    dataType = "image/x-icon";
  else if (path.endsWith(".xml"))
    dataType = "text/xml";
  else if (path.endsWith(".pdf"))
    dataType = "application/pdf";
  else if (path.endsWith(".zip"))
    dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download"))
    dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size())
  {
  }

  dataFile.close();
  return true;
}

void handleWebRequests()
{
  if (loadFromSpiffs(server.uri()))
    return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void ssid_save_setting_control()
{

  SSID_SAVE = server.arg("Text_SSID");

  Serial.println(SSID_SAVE);
  server.send(200, "text/plane", SSID_SAVE);
}

void password_save_setting_control()
{

  PASSWORD_SAVE = server.arg("Text_PASSWORD");

  Serial.println(PASSWORD_SAVE);
  server.send(200, "text/plane", PASSWORD_SAVE);
}

void button_save_setting_connect_control() // кнопка подключения к wifi
{
  Serial.println("button_save_setting_connect click");
  server.send(200, "text/html", ""); //посылка ответа сервера

  strncpy(settings.string_name_ssid, SSID_SAVE.c_str(), sizeof(settings.string_name_ssid));
  strncpy(settings.string_password, PASSWORD_SAVE.c_str(), sizeof(settings.string_password));
  settings_save();
}

void checkbox_antiotravlenie_control() // checkbox антиотравление
{
  String state;

  String act_state = server.arg("checkbox_antiotravlenie");

  if (act_state == "1")
  {
    state = "Сheckbox Antiotravlenie true";
    Antiotravlenie_Lamp = true;
    Count_Time_Anti_Otravlenie = 0;
  }
  else
  {
    state = "Сheckbox Antiotravlenie false";
    Antiotravlenie_Lamp = false;
  }

  Serial.println(state);
  server.send(200, "text/plane", state);

  settings.bool_autoantiotravlenie_lamp = act_state.toInt();
  settings_save();

  Serial.println("Save AntiOtravlenie: " + String(settings.bool_autoantiotravlenie_lamp));
  Serial.println();
}

void checkbox_auto_brightnes_control() //checkbox автоматической яркости ленты
{
  String state;

  String act_state = server.arg("checkbox_auto_brightnes");

  if (act_state == "1")
  {
    state = "checkbox_auto_brightnes true";
  }
  else
  {
    state = "checkbox_auto_brightnes false";
  }

  Serial.println(state);
  server.send(200, "text/plane", state);

  settings.bool_auto_brights = act_state.toInt();
  settings_save();

  Serial.println("Save Auto Brightnes: " + String(settings.bool_auto_brights));
  Serial.println();
}

void checkbox_auto_synch_time_control() // checkbox автоматической синхронизации времени
{
  String state;
  String act_state = server.arg("checkbox_auto_synch_time");

  if (act_state == "1")
  {
    state = "checkbox_auto_synch_time true";
  }
  else
  {
    state = "checkbox_auto_synch_time false";
  }

  Serial.println(state);
  server.send(200, "text/plane", state);

  settings.bool_auto_sunch_time = act_state.toInt();
  settings_save();

  Serial.println("Save Auto Synch Time: " + String(settings.bool_auto_sunch_time));
  Serial.println();
}

void button_synch_time_control() // кнопка синхронизации времени с ntp сервера
{
  Serial.println("button_synch_time click");
  server.send(200, "text/html", ""); //посылка ответа сервера

  UDP_SYNCH();
}

void handleRoot()
{
  server.sendHeader("Location", "/index.html", true);
  server.send(302, "text/plane", "");
}

void Set_Site_Time_Lamp_Current()
{
  server.send(200, "text/plane", Lamp_Time_Current);
}

void Set_Setting_Controll_bool_autoantiotravlenie_lamp()
{
  server.send(200, "text/plane", String(settings.bool_autoantiotravlenie_lamp));
}

void Set_Setting_Controll_bool_auto_brights()
{
  server.send(200, "text/plane", String(settings.bool_auto_brights));
}

void Set_Setting_Controll_bool_auto_sunch_time()
{
  server.send(200, "text/plane", String(settings.bool_auto_sunch_time));
}

void Set_Setting_Controll_int_effects_led_front()
{
  server.send(200, "text/plane", String(settings.int_effects_led_front));
}

void Set_Setting_Controll_int_effects_led_basic()
{
  server.send(200, "text/plane", String(settings.int_effects_led_basic));
}

void Set_Setting_Controll_int_brights_led_front()
{
  server.send(200, "text/plane", String(settings.int_bright_led_front));
}

void Set_Setting_Controll_int_brights_led_basic()
{
  server.send(200, "text/plane", String(settings.int_bright_led_basic));
}

void Set_Setting_Controll_int_speed_led_front()
{
  server.send(200, "text/plane", String(settings.int_speed_led_front));
}

void Set_Setting_Controll_int_speed_led_basic()
{
  server.send(200, "text/plane", String(settings.int_speed_led_basic));
}

void Set_Setting_Controll_string_color_front()
{
  server.send(200, "text/plane", String(settings.string_color_front));
}

void Set_Setting_Controll_string_color_basic()
{
  server.send(200, "text/plane", String(settings.string_color_basic));
}

void default_esp8266_control()
{
  Serial.println("ESP Settings Default");
  delay(1000);
  server.stop();
  WiFi.disconnect();
  Serial.end();
  delay(1000);

  settings_default();
  ESP.restart();
}

void reboot_esp8266_control()
{
  ws2812fx_FRONT.stop();
  ws2812fx_BASIC.stop();
  Serial.println("ESP restart");
  delay(1000);
  server.stop();
  WiFi.disconnect();
  Serial.end();
  delay(1000);
  Serial.println("ESP GoodBay");
  delay(1000);
  ESP.restart();
}

void select_effects_front_control()
{
  String act_state = server.arg("text_sellect_effects_front");
  Serial.println("Select Effect Front:" + act_state);
  server.send(200, "text/plane", act_state);

  settings.int_effects_led_front = act_state.toInt();
  settings_save();

  ws2812fx_FRONT.setMode(act_state.toInt());
}

void select_effects_basic_control()
{
  String act_state = server.arg("text_sellect_effects_basic");

  Serial.println("Select Effect Basic:" + act_state);

  server.send(200, "text/plane", act_state);

  settings.int_effects_led_basic = act_state.toInt();
  settings_save();

  ws2812fx_BASIC.setMode(act_state.toInt());
}

void select_time_anti_otravlenie()
{
  String act_state = server.arg("text_time_antiotravlenie");
  Serial.println("Select Time Anti Otravlrnie: " + act_state);
  server.send(200, "text/plane", act_state);

  Time_Anti_Otravlenie = act_state.toInt();
}

void range_brightnes_front_control()
{
  String act_state = server.arg("text_brightnes_front");
  Serial.println("Range Brightnes Front: " + act_state);
  server.send(200, "text/plane", act_state);

  settings.int_bright_led_front = act_state.toInt();
  settings_save();

  ws2812fx_FRONT.setBrightness(act_state.toInt());
}

void range_brightnes_basic_control()
{
  String act_state = server.arg("text_brightnes_basic");
  Serial.println("Range Brightnes Basic: " + act_state);
  server.send(200, "text/plane", act_state);

  settings.int_bright_led_basic = act_state.toInt();
  settings_save();

  ws2812fx_BASIC.setBrightness(act_state.toInt());
}

void select_color_front_control()
{
  String act_state = server.arg("text_sellect_color_front");
  Serial.println("Select Color Front:" + act_state);
  server.send(200, "text/plane", act_state);

  String R = getValue(act_state, ',', 1);
  String G = getValue(act_state, ',', 0);
  String B = getValue(act_state, ',', 2);

  ws2812fx_FRONT.setColor(R.toInt(), G.toInt(), B.toInt());

  B.replace(",", "");
  String Color_Led = R + "," + G + "," + B;

  strncpy(settings.string_color_front, Color_Led.c_str(), sizeof(settings.string_color_front));
  settings_save();

  Serial.println("Save Color Led Front: " + Color_Led);
}

void select_color_basic_control()
{
  String act_state = server.arg("text_sellect_color_basic");
  Serial.println("Select Color Basic:" + act_state);
  server.send(200, "text/plane", act_state);

  String R = getValue(act_state, ',', 1);
  String G = getValue(act_state, ',', 0);
  String B = getValue(act_state, ',', 2);

  ws2812fx_BASIC.setColor(R.toInt(), G.toInt(), B.toInt());

  B.replace(",", "");
  String Color_Led = R + "," + G + "," + B;

  strncpy(settings.string_color_basic, Color_Led.c_str(), sizeof(settings.string_color_basic));
  settings_save();
  Serial.println("Save Color Led Basic: " + Color_Led);
}

void range_speed_front_control()
{
  String act_state = server.arg("text_speed_front");

  Serial.println("Select Speed Front:" + act_state);

  server.send(200, "text/plane", act_state);

  settings.int_speed_led_front = act_state.toInt();
  settings_save();

  ws2812fx_FRONT.setSpeed(act_state.toInt() * 50);
}

void range_speed_basic_control()
{

  String act_state = server.arg("text_speed_basic");

  Serial.println("Select Speed Basic:" + act_state);

  server.send(200, "text/plane", act_state);

  settings.int_speed_led_basic = act_state.toInt();
  settings_save();

  ws2812fx_BASIC.setSpeed(act_state.toInt() * 50);
}

void range_brightnes_lamp_control()
{
  String act_state = server.arg("text_brightnes_lamp");
  Serial.println("Range Brightnes Lamp: " + act_state);
  server.send(200, "text/plane", act_state);

  // settings.int_bright_led_front = act_state.toInt();
  // settings_save();
  Brightness_Lamp = act_state.toInt();
  // ws2812fx_FRONT.setBrightness(act_state.toInt());
}

/////////////////////////////////////////////////////////////////////////////////////////////
void setup_site()
{
  SPIFFS.begin();

  settings_read();

  Serial.begin(115200);
  Serial.println();

  String SSID_CONNECT = settings.string_name_ssid;

  if (SSID_CONNECT == "")
  {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(settings.string_name_ssid_AP);

    Serial.println();
    Serial.println("MODE connected to WiFi_AP");
    Serial.println("Name AP: " + String(settings.string_name_ssid_AP));
  }

  if (SSID_CONNECT != "")
  {
    WiFi.mode(WIFI_STA);
    WiFi.begin(settings.string_name_ssid, settings.string_password);

    Serial.println();
    Serial.println("MODE connected to WiFi_STA");
    Serial.println("Name SSID: " + String(settings.string_name_ssid));
    Serial.println("Password: " + String(settings.string_password));

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
      сonnect_count++;

      if (сonnect_count > 30)
      {
        strncpy(settings.string_name_ssid, "", sizeof(settings.string_name_ssid));
        strncpy(settings.string_password, "", sizeof(settings.string_password));
        settings_save();
        delay(500);
        ESP.restart();
      }
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(String(settings.string_name_ssid));
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  server.on("/", handleRoot);

  server.onNotFound(handleWebRequests);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////Загрузка настроек с контроллера на сервер//////////////////////////////////////////
  server.on("/Set_Setting_Controll_bool_autoantiotravlenie_lamp", Set_Setting_Controll_bool_autoantiotravlenie_lamp);
  server.on("/Set_Setting_Controll_bool_auto_brights", Set_Setting_Controll_bool_auto_brights);
  server.on("/Set_Setting_Controll_bool_auto_sunch_time", Set_Setting_Controll_bool_auto_sunch_time);
  server.on("/Set_Setting_Controll_int_effects_led_front", Set_Setting_Controll_int_effects_led_front);
  server.on("/Set_Setting_Controll_int_effects_led_basic", Set_Setting_Controll_int_effects_led_basic);
  server.on("/Set_Setting_Controll_int_brights_led_front", Set_Setting_Controll_int_brights_led_front);
  server.on("/Set_Setting_Controll_int_brights_led_basic", Set_Setting_Controll_int_brights_led_basic);
  server.on("/Set_Setting_Controll_int_speed_led_front", Set_Setting_Controll_int_speed_led_front);
  server.on("/Set_Setting_Controll_int_speed_led_basic", Set_Setting_Controll_int_speed_led_basic);
  server.on("/Set_Setting_Controll_string_color_front", Set_Setting_Controll_string_color_front);
  server.on("/Set_Setting_Controll_string_color_basic", Set_Setting_Controll_string_color_basic);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //Мои контроллы сервера
  server.on("/adcread", Set_Site_Time_Lamp_Current);

  server.on("/save_setting_connect_set", button_save_setting_connect_control);
  server.on("/parrametrs_ssid_set", ssid_save_setting_control);
  server.on("/parrametrs_password_set", password_save_setting_control);

  server.on("/checkbox_antiotravlenie_set", checkbox_antiotravlenie_control);
  server.on("/checkbox_auto_brightnes_set", checkbox_auto_brightnes_control);
  server.on("/checkbox_auto_synch_time_set", checkbox_auto_synch_time_control);
  server.on("/button_synch_time_set", button_synch_time_control);

  server.on("/select_effects_front_set", select_effects_front_control);
  server.on("/select_effects_basic_set", select_effects_basic_control);
  server.on("/brightnes_front_set", range_brightnes_front_control);
  server.on("/brightnes_basic_set", range_brightnes_basic_control);

  server.on("/speed_front_set", range_speed_front_control);
  server.on("/speed_basic_set", range_speed_basic_control);

  server.on("/select_time_antiotravlenie_set", select_time_anti_otravlenie);

  server.on("/select_color_front_set", select_color_front_control);
  server.on("/select_color_basic_set", select_color_basic_control);

  server.on("/default_esp8266_set", default_esp8266_control);
  server.on("/reboot_esp8266_set", reboot_esp8266_control);

  server.on("/brightnes_lamp_set", range_brightnes_lamp_control);

  load_settings = false;

  httpUpdater.setup(&server, "/ota");

  server.begin();
}

void load_settings_site()
{
  if (load_settings == false)
  {
    Set_Setting_Controll_bool_autoantiotravlenie_lamp();
    Set_Setting_Controll_bool_auto_brights();
    Set_Setting_Controll_bool_auto_sunch_time();

    Set_Setting_Controll_int_effects_led_front();
    Set_Setting_Controll_int_effects_led_basic();

    Set_Setting_Controll_int_brights_led_front();
    Set_Setting_Controll_int_brights_led_basic();

    Set_Setting_Controll_int_speed_led_front();
    Set_Setting_Controll_int_speed_led_front();

    Set_Setting_Controll_string_color_front();
    Set_Setting_Controll_string_color_basic();

    Serial.println();

    Serial.println("Load Settings SPIFFS:");

    Serial.println("Param SSID: " + String(settings.string_name_ssid));
    Serial.println("Param PASSWORD: " + String(settings.string_password));

    Serial.println("CheckBox Anti Otravlenie: " + String(settings.bool_autoantiotravlenie_lamp));
    Serial.println("CheckBox Auto Brights: " + String(settings.bool_auto_brights));
    Serial.println("CheckBox Auto Synch Time: " + String(settings.bool_auto_sunch_time));

    Serial.println("Select Effect Front: " + String(settings.int_effects_led_front));
    Serial.println("Select Effect Basic: " + String(settings.int_effects_led_basic));

    Serial.println("Select Brights Front: " + String(settings.int_bright_led_front));
    Serial.println("Select Brights Basic: " + String(settings.int_bright_led_basic));

    Serial.println("Select Speed Front: " + String(settings.int_speed_led_front));
    Serial.println("Select Speed Basic: " + String(settings.int_speed_led_basic));

    Serial.println("Select Color Front: " + String(settings.string_color_front));
    Serial.println("Select Color Basic: " + String(settings.string_color_basic));

    Serial.println();

    load_settings = true;
  }
}

void loop_site()
{
  load_settings_site();
  server.handleClient();
}
