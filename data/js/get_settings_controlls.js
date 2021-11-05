var SettingRead = false;

function getSetting_checkbox_antiotravlenie() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            if (this.responseText == 0) {
                Checkbox_anti_otravlenie_El.checked = false;
            }

            if (this.responseText == 1) {
                Checkbox_anti_otravlenie_El.checked = true;
            };
        };

    }
    reqvest.open("GET", "Set_Setting_Controll_bool_autoantiotravlenie_lamp", true);
    reqvest.send();
};


function getSetting_checkbox_auto_brightnes() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            if (this.responseText == 0) {
                Checkbox_auto_brightnes_El.checked = false;
            }

            if (this.responseText == 1) {
                Checkbox_auto_brightnes_El.checked = true;
            };
        };

    }
    reqvest.open("GET", "Set_Setting_Controll_bool_auto_brights", true);
    reqvest.send();
};

function getSetting_checkbox_auto_synch_time() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            if (this.responseText == 0) {
                Checkbox_auto_synch_time_El.checked = false;
            }

            if (this.responseText == 1) {
                Checkbox_auto_synch_time_El.checked = true;
            };
        };

    }
    reqvest.open("GET", "Set_Setting_Controll_bool_auto_sunch_time", true);
    reqvest.send();
};



function getSetting_int_int_effects_led_front() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            console.log("Save_effects_front: " + this.responseText)
            select_effects_front.value = this.responseText

        };

    }
    reqvest.open("GET", "Set_Setting_Controll_int_effects_led_front", true);
    reqvest.send();
};



function getSetting_int_int_effects_led_basic() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            console.log("Save_effects_basic: " + this.responseText)
            select_effects_basic.value = this.responseText;

        };

    }
    reqvest.open("GET", "Set_Setting_Controll_int_effects_led_basic", true);
    reqvest.send();
};


function getSetting_int_brightness_led_front() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            console.log("Save_brightness_front: " + this.responseText)
            Brightnes_Front.value = this.responseText;

            let top_front = parseFloat(rangeInput_front.value) / step_basic * -40;
            rangeValue_front.style.marginTop = top_front + "px";

        };

    }
    reqvest.open("GET", "Set_Setting_Controll_int_brights_led_front", true);
    reqvest.send();
};



function getSetting_int_brightness_led_basic() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            console.log("Save_brightness_basic: " + this.responseText)
            Brightnes_Basic.value = this.responseText;

            let top_basic = parseFloat(rangeInput_basic.value) / step_basic * -40;
            rangeValue_basic.style.marginTop = top_basic + "px";

        };

    }
    reqvest.open("GET", "Set_Setting_Controll_int_brights_led_basic", true);
    reqvest.send();
};



function getSetting_int_speed_led_front() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            console.log("Save_speed_front: " + this.responseText)
            Speed_Front.value = this.responseText;

            let top_speed_front = parseFloat(rangeInput_speed_front.value) / step_speed_front * -40;
            rangeValue_speed_front.style.marginTop = top_speed_front + "px";

        };

    }
    reqvest.open("GET", "Set_Setting_Controll_int_speed_led_front", true);
    reqvest.send();
};



function getSetting_int_speed_led_basic() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            console.log("Save_speed_basic: " + this.responseText)
            Speed_Basic.value = this.responseText;

            let top_speed_basic = parseFloat(rangeInput_speed_basic.value) / step_speed_basic * -40;
            rangeValue_speed_basic.style.marginTop = top_speed_basic + "px";

        };

    }
    reqvest.open("GET", "Set_Setting_Controll_int_speed_led_basic", true);
    reqvest.send();
};


function getSetting_string_color_front() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            console.log("Save_Color_Front: " + this.responseText)

            function rgb2hex(rgb) {
                var rgb = rgb.match(/^rgba?[\s+]?\([\s+]?(\d+)[\s+]?,[\s+]?(\d+)[\s+]?,[\s+]?(\d+)[\s+]?/i);

                return (rgb && rgb.length === 4) ? "#" +
                    ("0" + parseInt(rgb[1], 10).toString(16)).slice(-2) +
                    ("0" + parseInt(rgb[2], 10).toString(16)).slice(-2) +
                    ("0" + parseInt(rgb[3], 10).toString(16)).slice(-2) : '';
            };

            //alert(rgbToHex(0, 51, 255)); // #0033ff

            var Color = this.responseText;

            let arr = Color.split(',', 3);

            var Result_Color = "rgb(" + arr[1] + "," + arr[0] + "," + arr[2] + ")";


            Color_Front.value = rgb2hex(Result_Color);

        };

    }
    reqvest.open("GET", "Set_Setting_Controll_string_color_front", true);
    reqvest.send();
};



function getSetting_string_color_basic() {

    reqvest = new XMLHttpRequest();
    reqvest.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {

            console.log("Save_Color_Basic: " + this.responseText)

            function rgb2hex(rgb) {
                var rgb = rgb.match(/^rgba?[\s+]?\([\s+]?(\d+)[\s+]?,[\s+]?(\d+)[\s+]?,[\s+]?(\d+)[\s+]?/i);

                return (rgb && rgb.length === 4) ? "#" +
                    ("0" + parseInt(rgb[1], 10).toString(16)).slice(-2) +
                    ("0" + parseInt(rgb[2], 10).toString(16)).slice(-2) +
                    ("0" + parseInt(rgb[3], 10).toString(16)).slice(-2) : '';
            };

            //alert(rgbToHex(0, 51, 255)); // #0033ff

            var Color = this.responseText;

            let arr = Color.split(',', 3);

            var Result_Color = "rgb(" + arr[1] + "," + arr[0] + "," + arr[2] + ")";


            Color_Basic.value = rgb2hex(Result_Color);

        };

    }
    reqvest.open("GET", "Set_Setting_Controll_string_color_basic", true);
    reqvest.send();
};











if (SettingRead == false) {
    console.log("getSettings");
    getSetting_checkbox_antiotravlenie();
    getSetting_checkbox_auto_brightnes();
    getSetting_checkbox_auto_synch_time();

    getSetting_int_int_effects_led_front();
    getSetting_int_int_effects_led_basic();

    getSetting_int_brightness_led_front();
    getSetting_int_brightness_led_basic();

    getSetting_int_speed_led_front();
    getSetting_int_speed_led_basic();


    getSetting_string_color_front();
    getSetting_string_color_basic();


    SettingRead = true;
}

