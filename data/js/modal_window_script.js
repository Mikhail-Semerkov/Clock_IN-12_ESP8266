
/////////////MODAL WINDOWS////////////////////////////////////////////////////
var modal = document.querySelector(".modal_save_settings_connect");
// var closeButton = document.querySelector(".close-button");

function toggleModal_save_settings_connect() {
    modal.classList.toggle("show-modal");
}

function windowOnClick(event) {
    if (event.target === modal) {
        toggleModal_save_settings_connect();
    }
}

