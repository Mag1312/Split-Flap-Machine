#include <WiFi.h>
#include <time.h>
#include <WiFiClientSecure.h>
#include <variables.h>
#include <WebServer.h>

String month = setOfMonths[months];

void handleTimeNow()
{
  displayTime();
}

void handleDateNow()
{
  displayDayInfo();
  delay(5000);
  displayWeekDay();
  delay(5000);
  displayWeahter();
}

void handleDisplayWord()
{
  if(server.hasArg("word"))
  {
    wordToBeDisplayed = server.arg("word");
  }
  displayWord();
  server.send(200, "text/plain", "OK");
} 

void handlePlayNow()
{
  Serial2.println("PLAY");
}

void handleStopNow()
{
  Serial2.println("STOP");
}
void handlePreviousNow()
{
  Serial2.println("PREV");
}
void handleNextNow()
{
  Serial2.println("NEXT");
}


void handleRoot()
{
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  "<style>

body{
    background-color:#fffcf2;
    font-family:Arial, Helvetica, sans-serif;
    margin:0;
    display:flex;
    justify-content:center;
}

#box{
    background-color:#252422;
    border-radius:50px;
    padding:50px 40px;
    margin:50px;
    width:90%;
    max-width:900px;
    text-align:center;
}

#header{
    background-color:#fffcf2;
    border-radius:50px;
    padding:15px 30px;
    margin-bottom:50px;
}

h1{
    color:#fca311;
    font-size:clamp(40px,5vw,75px);
    margin:0;
}

.row{
    display:grid;
    grid-template-columns:1fr 1fr;
    align-items:center;
    gap:40px;
    margin:25px 0;
}

.box{
    font-size:clamp(35px,4vw,60px);
    font-weight:700;
    background-color:#fca311;
    border-radius:30px;
    padding:10px;
}

button{
    background-color:#fffcf2;
    font-size:clamp(18px,2.5vw,35px);
    font-weight:700;
    color:#fca311;
    border-radius:30px;
    border:none;
    height:65px;
    cursor:pointer;
}

input{
    height:45px;
    font-size:22px;
    text-align:center;
    border-radius:15px;
    border:none;
    width:100%;
}

/* wide input spanning both columns */
.fullInput{
    grid-column:1 / span 2;
}

/* play stop row */
.controlRow{
    grid-column:1 / span 2;
    display:flex;
    justify-content:space-between;
}

.controlRow{
    grid-column:1 / span 2;
    display:flex;
    justify-content:space-between;
    gap:20px;
}

.controlRow button{
    flex:1;
}

</style>"
  
  html += "<body> <div id=\"box\"> <div id=\"header\"> <h1>Slit Flap Web Server</h1> </div>";
  html += "<div class=\"row\">
<div class=\"box\">";
  html += "<p>" + hour1 + hour2 + ":" + minute4 + minute5 + "</p>";
  html += "</div>";
  html += "<button onclick=\"timeNow()\">Display Time Now</button>";
  html += "</div>";

  html += "<div class=\"row\">
<div class=\"box\">";
  html += "<p id=\"date\>" + days + " " + month + " " + years + "</p>";
  html += "</div>";
  html += "<button onclick=\"infoNow()\">Display Todays Info</button>";
  html += "</div>";


  
  html += "<div class=\"row\">";
  html += "<input type=\"text\" id=\"word\" maxlength=\"7\" placeholder=\"Enter word here\">";
  html += "<button onclick=\"sendWord()\">Display Word</button>";
  html += "</div>";
  

"<div class="row">
<div class="controlRow">
<button onclick="play()">Play</button>
<button onclick="previous()">Previous</button>
<button onclick="next()">Next</button>
<button onclick="stop()">Stop</button>
</div>
</div>";

  html += "<script>";
  html += "function timeNow(){";
  html += "fetch(\"/time/now\");}";
  html += "function infoNow(){";
  html += "fetch(\"/info/now\");}";
  html += "function play(){";
  html += "fetch(\"/play/now\");}";
  html += "function stop(){";
  html += "fetch(\"/stop/now\");}";
  html += "function next(){";
  html += "fetch(\"/next/now\");}";
  html += "function previous(){";
  html += "fetch(\"/previous/now\");}";
  html += "function sendWord(){";
  html += "let w = document.getElementById(\"word\").value;";
  html += "fetch(\"/displayWord?word=\" +w);}";
  html += "</script>";

  html += "</body></html>";
  server.send(200, "text/html", html);
}