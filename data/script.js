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
    
   
    if (data.patternName != "") {
        var patternName = data.patternName;
        document.getElementById('patternName').innerHTML = patternName;
    }
    if(data.patternNumber != "")
    {
        var patternNumber = data.patternNumber;
        document.getElementById('patternNumber').innerHTML = patternNumber;
    }
    if(data.StripePatternsAmount!= "")
    {
        var StripePatternsAmount = data.StripePatternsAmount;
        document.getElementById('StripePatternsAmount').innerHTML = StripePatternsAmount;
    }
    if(data.paletteName!= "")
    {
        var paletteName = data.paletteName;
        document.getElementById('paletteName').innerHTML = paletteName;
    }  
    if(data.speed!= "")
    {
        var speed = data.speed;
        document.getElementById('speed').innerHTML = speed;
    }
 

}



// ----------------------------------------------------------------------------
// Button handling
// ----------------------------------------------------------------------------
function nextPattern() {
    websocket.send(JSON.stringify({ 'action': 'nextPattern' }));
}
function prevPattern() {
    websocket.send(JSON.stringify({ 'action': 'prevPattern' }));
}
function prevPalette() {
    websocket.send(JSON.stringify({ 'action': 'prevPalette' }));
}
function nextPalette() {
    websocket.send(JSON.stringify({ 'action': 'nextPalette' }));
}
function speedDown() {
    websocket.send(JSON.stringify({ 'action': 'speedDown' }));
}
function speedUp() {
    websocket.send(JSON.stringify({ 'action': 'speedUp' }));
}
function prevMatrix(){
    websocket.send(JSON.stringify({ 'action': 'prevMatrix' }));
}
function nextMatrix(){
    websocket.send(JSON.stringify({ 'action': 'nextMatrix' }));
}
function updateSliderSpeed(element) {
    var sliderNumber = element.id.charAt(element.id.length-1);
    var sliderValue = document.getElementById(element.id).value;
    document.getElementById("speedSliderVal").innerHTML = sliderValue;
    console.log(sliderValue);
    websocket.send(JSON.stringify({ 'action': 'speedSlider', 'sliderValue': sliderValue.toString()})
    );
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