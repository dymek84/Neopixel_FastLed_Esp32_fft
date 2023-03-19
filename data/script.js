

function SendData() {
    console.log("save button was clicked!");

    var xmessage = document.getElementById("data_form").Message.value;
    var xbrightness = document.getElementById("myRange").value;

    var data = { brightness: xbrightness, message: xmessage };

    var xhr = new XMLHttpRequest();
    var url = "/message";

    xhr.addEventListener("load", transferComplete);
    xhr.addEventListener("error", transferFailed);

    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            // Typical action to be performed when the document is ready:
            if (xhr.responseText != null) {
                console.log(xhr.responseText);
                //? alert(xhr.responseText);
            }
        }
    };

    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.send(JSON.stringify(data));
    return true;
}
function test() {
    var mySnack = document.getElementById("snackbar");
    mySnack.textContent = "Data successfully sent";
    mySnack.className = "show";
    setTimeout(function () { mySnack.className = mySnack.className.replace("show", ""); }, 3000);
}
function transferComplete(evt) {
    var mySnack = document.getElementById("snackbar");
    mySnack.textContent = "Data successfully sent";
    mySnack.className = "show";
    setTimeout(function () { mySnack.className = mySnack.className.replace("show", ""); }, 3000);
}

function transferFailed(evt) {
    var mySnack = document.getElementById("snackbar");
    mySnack.textContent = "Oops, something went wrong..";
    mySnack.className = "show";
    setTimeout(function () { mySnack.className = mySnack.className.replace("show", ""); }, 3000);
}

function rangeSlideRW(value) {
    document.getElementById('rangeValueRW').innerHTML = value;
}
var updateDropdown = function updateDropdown() {
    var selects = document.querySelectorAll('select');

    for (i = 0; i <= selects.length - 1; i++) {
        selects[i].addEventListener('change', onChangeUpdate);
    }

    function onChangeUpdate() {
        var label = this.parentNode.querySelector('label');
        label.innerText = this.options[this.selectedIndex].text
    }
}
addEventListener('input', e => {
    let _t = e.target;

    _t.parentNode.style.setProperty(`--val`, +_t.value)
}, false);

function submitMessage() {
    alert("Restarting ESP");
    setTimeout(function () { document.location.reload(false); }, 500);
}
function openCity(evt, cityName) {
    // Declare all variables
    var i, tabcontent, tablinks;

    // Get all elements with class="tabcontent" and hide them
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }

    // Get all elements with class="tablinks" and remove the class "active"
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }

    // Show the current tab, and add an "active" class to the button that opened the tab
    document.getElementById(cityName).style.display = "block";
    evt.currentTarget.className += " active";
}