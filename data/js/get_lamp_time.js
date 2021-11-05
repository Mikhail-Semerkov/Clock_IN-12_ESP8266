function getData() {
    GetSiteTimeLamp = new XMLHttpRequest();
    GetSiteTimeLamp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("result").innerHTML =
                this.responseText;
        }
    };
    GetSiteTimeLamp.open("GET", "adcread", true);
    GetSiteTimeLamp.send();
}


setInterval(function () {
    getData();
}, 1000);