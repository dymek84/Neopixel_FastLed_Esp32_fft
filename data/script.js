var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

window.addEventListener('load', onLoad);

function onLoad(event) {
    initWebSocket();
}

// ----------------------------------------------------------------------------
// WebSocket handling
// ----------------------------------------------------------------------------

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
    let data = JSON.parse(event.data);
    //document.getElementById('led').className = data.status;
    //document.getElementById('led' + data.rank).className = data.status;

    if (data.rank == "1") {
        if (data.status == "on") {
            document.getElementById('toggle1').style.backgroundColor = "#F9E79F";
            document.getElementById('toggle1').style.color = "#1B2E3C";
        } else {
            document.getElementById('toggle1').style.backgroundColor = "#1B2E3C";
            document.getElementById('toggle1').style.color = "#Fff";
        }
    }

    if (data.rank == "2") {
        if (data.status == "on") {
            document.getElementById('toggle2').style.backgroundColor = "#F9E79F";
            document.getElementById('toggle2').style.color = "#1B2E3C";
        } else {
            document.getElementById('toggle2').style.backgroundColor = "#1B2E3C";
            document.getElementById('toggle2').style.color = "#Fff";
        }
    }
    if (data.rank == "3") {
        if (data.status == "on") {
            document.getElementById('toggle3').style.backgroundColor = "#F9E79F";
            document.getElementById('toggle3').style.color = "#1B2E3C";
        } else {
            document.getElementById('toggle3').style.backgroundColor = "#1B2E3C";
            document.getElementById('toggle3').style.color = "#Fff";
        }
    }
    if (data.rank == "4") {
        if (data.status == "on") {
            document.getElementById('toggle4').style.backgroundColor = "#F9E79F";
            document.getElementById('toggle4').style.color = "#1B2E3C";
        } else {
            document.getElementById('toggle4').style.backgroundColor = "#1B2E3C";
            document.getElementById('toggle4').style.color = "#Fff";
        }
    }
    if (data.rank == "5") {
        if (data.status == "on") {
            document.getElementById('toggle5').style.backgroundColor = "#F9E79F";
            document.getElementById('toggle5').style.color = "#1B2E3C";
        } else {
            document.getElementById('toggle5').style.backgroundColor = "#1B2E3C";
            document.getElementById('toggle5').style.color = "#Fff";
        }
    }
    if (data.rank == "6") {
        if (data.status == "on") {
            document.getElementById('toggle6').style.backgroundColor = "#F9E79F";
            document.getElementById('toggle6').style.color = "#1B2E3C";
        } else {
            document.getElementById('toggle6').style.backgroundColor = "#1B2E3C";
            document.getElementById('toggle6').style.color = "#Fff";
        }
    }
    if (data.rank == "8") {
        if (data.status == "on") {
            document.getElementById('rank8').style.backgroundColor = "#fff";
            document.getElementById('rank8').style.color = "#000";

        } else {
            document.getElementById('rank8').style.backgroundColor = "#ff0000";
            document.getElementById('rank8').style.color = "#00ff00";

        }
    }
    if (data.patternNumber != "") {
        var patternNumber = data.patternNumber;
        document.getElementById('rank8info').innerHTML = patternNumber;
    }


}



// ----------------------------------------------------------------------------
// Button handling
// ----------------------------------------------------------------------------
function nextPattern() {
    websocket.send(JSON.stringify({ 'action': 'nextPattern' }));
}

function initButton1() {
    document.getElementById('toggle1').addEventListener('click', onToggle1);
    console.log("Button 1 initialized");
}

function initButton2() {
    document.getElementById('toggle2').addEventListener('click', onToggle2);
}

function initButton3() {
    document.getElementById('toggle3').addEventListener('click', onToggle3);
}

function initButton4() {
    document.getElementById('toggle4').addEventListener('click', onToggle4);
}

function initButton5() {
    document.getElementById('toggle5').addEventListener('click', onToggle5);
}

function initButton6() {
    document.getElementById('toggle6').addEventListener('click', onToggle6);
}

function myFunction() {
    websocket.send(JSON.stringify({ 'action': 'rank8' }));
    console.log("Button rank8 pressed");
}

function onToggle1(event) {
    websocket.send(JSON.stringify({ 'action': 'toggle1' }));
    console.log("Button 1 pressed");
}

function onToggle2(event) {
    websocket.send(JSON.stringify({ 'action': 'toggle2' }));
}

function onToggle3(event) {
    websocket.send(JSON.stringify({ 'action': 'toggle3' }));
}

function onToggle4(event) {
    websocket.send(JSON.stringify({ 'action': 'toggle4' }));
}

function onToggle5(event) {
    websocket.send(JSON.stringify({ 'action': 'toggle5' }));
}

function onToggle6(event) {
    websocket.send(JSON.stringify({ 'action': 'toggle6' }));
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