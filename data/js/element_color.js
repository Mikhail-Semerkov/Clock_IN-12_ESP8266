var Color_Front = document.getElementById("color_led_front");
var Color_Basic = document.getElementById("color_led_basic");


function HEXtoRGB(hex) {
    hex = hex.replace(/#/g, '');
    if (hex.length === 3) {
        hex = hex.split('').map(function (hex) {
            return hex + hex;
        }).join('');
    }
    // validate hex format
    var result = /^([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})[\da-z]{0,0}$/i.exec(hex);
    if (result) {
        var red = parseInt(result[1], 16);
        var green = parseInt(result[2], 16);
        var blue = parseInt(result[3], 16);

        return [red, green, blue];
    } else {
        // invalid color
        return null;
    }
}







Color_Front.addEventListener('change', () => {
    Color_Front.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            Color_Front.innerHTML = this.responseText;
        }
    };

    var RGB = HEXtoRGB(Color_Front.value) + ",";
    request.open("GET", "select_color_front_set?text_sellect_color_front=" + RGB, true);
    request.send();
    //console.log("Select Color Front: " + Color_Front.value.slice(1));
    console.log("COLOR Value - " + RGB);

});


Color_Basic.addEventListener('change', () => {
    Color_Basic.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            Color_Basic.innerHTML = this.responseText;
        }
    };
    var RGB = HEXtoRGB(Color_Basic.value) + ",";
    request.open("GET", "select_color_basic_set?text_sellect_color_basic=" + RGB, true);
    request.send();
    console.log("Select Color Basic: " + RGB);



});






