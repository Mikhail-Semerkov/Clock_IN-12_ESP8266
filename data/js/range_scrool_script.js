let rangeInput_speed_front = document.querySelector(".range_input_speed_front input");
let rangeValue_speed_front = document.querySelector(".range_input_speed_front .value div");
var Speed_Front = document.getElementById("range_speed_front");


let start_speed_front = parseFloat(rangeInput_speed_front.min);
let end_speed_front = parseFloat(rangeInput_speed_front.max);
let step_speed_front = parseFloat(rangeInput_speed_front.step);

for (let i = start_speed_front; i <= end_speed_front; i += step_speed_front) {
    rangeValue_speed_front.innerHTML += '<div>' + i + '</div>';
}

rangeInput_speed_front.addEventListener("input", function () {
    let top_speed_front = parseFloat(rangeInput_speed_front.value) / step_speed_front * -40;
    rangeValue_speed_front.style.marginTop = top_speed_front + "px";
});


Speed_Front.addEventListener("change", function () {


    Speed_Front.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            Speed_Front.innerHTML = this.responseText;
        }
    };

    request.open("GET", "speed_front_set?text_speed_front=" + Speed_Front.value, true);
    request.send();
    console.log("Speed_Front: " + Speed_Front.value);
});










let rangeInput_speed_basic = document.querySelector(".range_input_speed_basic input");
let rangeValue_speed_basic = document.querySelector(".range_input_speed_basic .value div");
var Speed_Basic = document.getElementById("range_speed_basic");


let start_speed_basic = parseFloat(rangeInput_speed_basic.min);
let end_speed_basic = parseFloat(rangeInput_speed_basic.max);
let step_speed_basic = parseFloat(rangeInput_speed_basic.step);

for (let i = start_speed_basic; i <= end_speed_basic; i += step_speed_basic) {
    rangeValue_speed_basic.innerHTML += '<div>' + i + '</div>';
}

rangeInput_speed_basic.addEventListener("input", function () {
    let top_speed_basic = parseFloat(rangeInput_speed_basic.value) / step_speed_basic * -40;
    rangeValue_speed_basic.style.marginTop = top_speed_basic + "px";
});



Speed_Basic.addEventListener("change", function () {


    Speed_Basic.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            Speed_Basic.innerHTML = this.responseText;
        }
    };


    request.open("GET", "speed_basic_set?text_speed_basic=" + Speed_Basic.value, true);
    request.send();
    console.log("Speed_Basic: " + Speed_Basic.value);
});









let rangeInput_front = document.querySelector(".range_input_bright_ws2812_front input");
let rangeValue_front = document.querySelector(".range_input_bright_ws2812_front .value div");
var Brightnes_Front = document.getElementById("range_brightnes_front");


let start_front = parseFloat(rangeInput_front.min);
let end_front = parseFloat(rangeInput_front.max);
let step_front = parseFloat(rangeInput_front.step);

for (let i = start_front; i <= end_front; i += step_front) {
    rangeValue_front.innerHTML += '<div>' + i + '</div>';
}

rangeInput_front.addEventListener("input", function () {
    let top_front = parseFloat(rangeInput_front.value) / step_front * -40;
    rangeValue_front.style.marginTop = top_front + "px";
});


Brightnes_Front.addEventListener("change", function () {
    Brightnes_Front.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            Brightnes_Front.innerHTML = this.responseText;
        }
    };
    request.open("GET", "brightnes_front_set?text_brightnes_front=" + Brightnes_Front.value, true);
    request.send();
    console.log("Brightnes_Front: " + Brightnes_Front.value);
});







let rangeInput_basic = document.querySelector(".range_input_bright_ws2812_basic input");
let rangeValue_basic = document.querySelector(".range_input_bright_ws2812_basic .value div");
var Brightnes_Basic = document.getElementById("range_brightnes_basic");


let start_basic = parseFloat(rangeInput_basic.min);
let end_basic = parseFloat(rangeInput_basic.max);
let step_basic = parseFloat(rangeInput_basic.step);

for (let i = start_basic; i <= end_basic; i += step_basic) {
    rangeValue_basic.innerHTML += '<div>' + i + '</div>';
}

rangeInput_basic.addEventListener("input", function () {
    let top_basic = parseFloat(rangeInput_basic.value) / step_basic * -40;
    rangeValue_basic.style.marginTop = top_basic + "px";
});


Brightnes_Basic.addEventListener("change", function () {


    Brightnes_Basic.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            Brightnes_Basic.innerHTML = this.responseText;
        }
    };
    request.open("GET", "brightnes_basic_set?text_brightnes_basic=" + Brightnes_Basic.value, true);
    request.send();
    console.log("Brightnes_Basic: " + Brightnes_Basic.value);
});








let rangeInput_brightnes_lamp = document.querySelector(".range_input_bright_lamp input");
let rangeValue_brightnes_lamp = document.querySelector(".range_input_bright_lamp .value div");
var Brightnes_Lamp = document.getElementById("range_brightnes_lamp");


let start_brightnes_lamp = parseFloat(rangeInput_brightnes_lamp.min);
let end_brightnes_lamp = parseFloat(rangeInput_brightnes_lamp.max);
let step_brightnes_lamp = parseFloat(rangeInput_brightnes_lamp.step);

for (let i = start_brightnes_lamp; i <= end_brightnes_lamp; i += step_brightnes_lamp) {
    rangeValue_brightnes_lamp.innerHTML += '<div>' + i + '</div>';
}

rangeInput_brightnes_lamp.addEventListener("input", function () {
    let top_brightnes_lamp = parseFloat(rangeInput_brightnes_lamp.value) / step_brightnes_lamp * -40;
    rangeValue_brightnes_lamp.style.marginTop = top_brightnes_lamp + "px";
});


Brightnes_Lamp.addEventListener("change", function () {


    Brightnes_Lamp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            Brightnes_Lamp.innerHTML = this.responseText;
        }
    };
    request.open("GET", "brightnes_lamp_set?text_brightnes_lamp=" + Brightnes_Lamp.value, true);
    request.send();
    console.log("Brightnes_Lamp: " + Brightnes_Lamp.value);
});




