var acc = document.getElementsByClassName("accordion");
var i;

for (i = 0; i < acc.length; i++) {
    acc[i].addEventListener("click", function () {
        resetAccordian(this);
        var panel = this.nextElementSibling;
        if (panel.style.display === "block") {
            panel.style.display = "none";
            this.classList.remove("active");
        } else {
            panel.style.display = "block";
        }
    });
}


resetAccordian = (originalTarget) => {
    let accordians = Object.values(acc);
    accordians.forEach(data => {
        if (data != originalTarget) {
            let target = data.nextElementSibling;
            data.classList.remove("active");
            if (target.style.display === "block") {

                target.style.display = "none";
            }
        } else {
            data.classList.add("active");
        }
    }, originalTarget);
}