//////////////////////////////////////////Глобальные переменные//////////////////////////////////////////////////////
request = new XMLHttpRequest();


const Button_save_setting_coonnect_El = document.getElementById("save_setting_coonnect");
const Checkbox_anti_otravlenie_El = document.getElementById("checkbox_antiotravlenie");
const Checkbox_auto_brightnes_El = document.getElementById("checkbox_auto_brightnes");
const Checkbox_auto_synch_time_El = document.getElementById("checkbox_auto_synch_time");


var select_effects_front = document.getElementById("select_void_option_ws2812_front");
var select_effects_basic = document.getElementById("select_void_option_ws2812_basic");
var select_time_antiotravlenie = document.getElementById("select_time_antiotravlenie");


const TextBox_SSID_El = document.getElementById("Text_SSID");
const TextBox_PASSWORD_El = document.getElementById("Text_PASSWORD");






const Button_Default_Settings_ESP8266_El = document.getElementById("button_default_settings_esp8266");
const Button_Reboot_ESP8266_El = document.getElementById("button_reboot_esp8266");



////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Page 1////////////////////////////////////

//TextBox SSID

//TextBox_SSID_El.addEventListener('input', function () {
function TextBox_SSID() {

    TextBox_SSID_Request = new XMLHttpRequest();
    console.log("Click TextBox SSID: " + TextBox_SSID_El.value)
    TextBox_SSID_Request.open("GET", "parrametrs_ssid_set?Text_SSID=" + TextBox_SSID_El.value, true);
    TextBox_SSID_Request.send();

};

//TextBox PASSWORD
//
//TextBox_PASSWORD_El.addEventListener('input', function () {
function TextBox_PASSWORD() {
    TextBox_SSID_Password = new XMLHttpRequest();
    console.log("Click TextBox PASSWORD: " + TextBox_PASSWORD_El.value)
    TextBox_SSID_Password.open("GET", "parrametrs_password_set?Text_PASSWORD=" + TextBox_PASSWORD_El.value, true);
    TextBox_SSID_Password.send();
};





var button_click_save_modal = document.getElementById("button_click_save_modal");
var button_click_ok_modal = document.getElementById("button_click_ok_modal");

button_click_save_modal.addEventListener('click', function () {
    TextBox_SSID();
    TextBox_PASSWORD();
    console.log("Click Save Settings Connect");
    request.open('GET', '/save_setting_connect_set', true);
    request.send();
    toggleModal_save_settings_connect();

});

button_click_ok_modal.addEventListener('click', function () {

    toggleModal_save_settings_connect();

});


//Button СОХРАНИТЬ
Button_save_setting_coonnect_El.addEventListener('click', function () {

    if (TextBox_PASSWORD_El.value.length >= 8) {

        button_click_save_modal.style = "";
        button_click_ok_modal.style = "display:none";



        toggleModal_save_settings_connect();

        var Text_Window = document.getElementById("modal_text_window");
        var Text_SSID = document.getElementById("modal_text_ssid");
        var Text_PASSWORD = document.getElementById("modal_text_password");

        Text_Window.style.fontSize = "16px";
        Text_Window.style.textAlign = "center";
        Text_Window.textContent = "Сохранить данные?";

        Text_SSID.style.fontSize = "14px";
        Text_SSID.textContent = "SSID: " + TextBox_SSID_El.value;

        Text_PASSWORD.style.fontSize = "14px";
        Text_PASSWORD.textContent = "PASSWORD: " + TextBox_PASSWORD_El.value;

        // closeButton.addEventListener("click", toggleModal_save_settings_connect);
        window.addEventListener("click", windowOnClick);
    }

    else if (TextBox_PASSWORD_El.value.length < 8) {

        button_click_save_modal.style = "display:none";
        button_click_ok_modal.style = "";


        toggleModal_save_settings_connect();

        var Text_Window = document.getElementById("modal_text_window");
        var Text_SSID = document.getElementById("modal_text_ssid");
        var Text_PASSWORD = document.getElementById("modal_text_password");

        Text_Window.style.fontSize = "16px";
        Text_Window.style.textAlign = "center";
        Text_Window.textContent = "Пароль не может быть менее 8 символов";

        Text_SSID.style.fontSize = "14px";
        Text_SSID.textContent = "";

        Text_PASSWORD.style.fontSize = "14px";
        Text_PASSWORD.textContent = "";

        // closeButton.addEventListener("click", toggleModal_save_settings_connect);
        window.addEventListener("click", windowOnClick);

    }

});


///////////////////////////////////////////////////////////////////////////


/////////////////////////////////Page 2////////////////////////////////////


////////////////////////////////Чекбокс Антиотравление//////////////////////////////////////////////////////////////
Checkbox_anti_otravlenie_El.addEventListener('change', function () {
    if (this.checked) {
        console.log("Антиотравление включено")
        checkbox_antiotravlenie_function(1);
    } else {
        console.log("Антиотравление выключено")
        checkbox_antiotravlenie_function(0);
    }
});

function checkbox_antiotravlenie_function(sostoyanie) {

    request.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("checkbox_antiotravlenie").innerHTML = this.responseText;
        }
    };
    request.open("GET", "checkbox_antiotravlenie_set?checkbox_antiotravlenie=" + sostoyanie, true);
    request.send();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








//Кнопка синхронизация времени
const Button_Synch_Time = document.getElementById("button_synch_time");
Button_Synch_Time.addEventListener("click", () => {

    console.log("Click Synch Time");

    request.open('GET', '/button_synch_time_set', true);
    request.send();

});






// чекбокс автояркость

Checkbox_auto_brightnes_El.addEventListener("click", () => {
    if (Checkbox_auto_brightnes_El.checked == true) {
        console.log("Автояркость включена");
        checkbox_autobrightnes_function(1);
    }
    if (Checkbox_auto_brightnes_El.checked == false) {
        console.log("Автояркость выключена");
        checkbox_autobrightnes_function(0);
    }
});
//Функция чекбокс автояркость
function checkbox_autobrightnes_function(sostoyanie) {

    request.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("checkbox_auto_brightnes").innerHTML = this.responseText;
        }
    };
    request.open("GET", "checkbox_auto_brightnes_set?checkbox_auto_brightnes=" + sostoyanie, true);
    request.send();
}
// чекбокс автосинхронизации времени

Checkbox_auto_synch_time_El.addEventListener("click", () => {
    if (Checkbox_auto_synch_time_El.checked == true) {
        console.log("Автосинхронизация включена");
        checkbox_auto_synch_time_function(1);
    }
    if (Checkbox_auto_synch_time_El.checked == false) {
        console.log("Автосинхронизация выключена");
        checkbox_auto_synch_time_function(0);
    }
});
//Функция автосинхронизации времени
function checkbox_auto_synch_time_function(sostoyanie) {

    request.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("checkbox_auto_synch_time").innerHTML = this.responseText;
        }
    };
    request.open("GET", "checkbox_auto_synch_time_set?checkbox_auto_synch_time=" + sostoyanie, true);
    request.send();
}


//Button настройки по умолчанию
Button_Default_Settings_ESP8266_El.addEventListener("click", () => {
    var isAdmin = confirm("Подтвердите сброс настроек?");

    if (isAdmin == true) {
        console.log("Click Default ESP8266");
        request.open('GET', '/default_esp8266_set', true);
        request.send();
    }
});

//Button ПЕРЕЗАГРУЗИТЬ
Button_Reboot_ESP8266_El.addEventListener("click", () => {
    var isAdmin = confirm("Подтвердите перезагрузку?");

    if (isAdmin == true) {
        console.log("Click Reboot ESP8266");
        request.open('GET', '/reboot_esp8266_set', true);
        request.send();
    }
});


//Элемент select front

select_effects_front.addEventListener('change', () => {
    select_effects_front.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            select_effects_front.innerHTML = this.responseText;
        }
    };
    request.open("GET", "select_effects_front_set?text_sellect_effects_front=" + select_effects_front.value, true);
    request.send();
    console.log("Select Effect Front: " + select_effects_front.value);

});

//Элемент select basic

select_effects_basic.addEventListener('change', () => {
    select_effects_basic.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            select_effects_basic.innerHTML = this.responseText;
        }
    };
    request.open("GET", "select_effects_basic_set?text_sellect_effects_basic=" + select_effects_basic.value, true);
    request.send();
    console.log("Select Effect Basic: " + select_effects_basic.value);

});




var info_wifi_conteiner = document.getElementById("info_wifi_conteiner_id");
var connect_wifi_conteiner = document.getElementById("connect_wifi_conteiner_id");

function radactor_setting_coonnect_fnc() {

    if (info_wifi_conteiner.style.display != "none") {
        info_wifi_conteiner.style.display = "none";
        connect_wifi_conteiner.style.display = "";
    }



}

function return_setting_coonnect_fnc() {

    if (info_wifi_conteiner.style.display == "none") {
        info_wifi_conteiner.style.display = "";
        connect_wifi_conteiner.style.display = "none";
    }

}




select_time_antiotravlenie.addEventListener('change', () => {
    select_time_antiotravlenie.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            select_time_antiotravlenie.innerHTML = this.responseText;
        }
    };
    request.open("GET", "select_time_antiotravlenie_set?text_time_antiotravlenie=" + select_time_antiotravlenie.value, true);
    request.send();
    console.log("Select Time Anti Otravlrnie: " + select_time_antiotravlenie.value);

});

