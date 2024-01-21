/*
 * Controlling 28BYJ-48 Stepper Motor over WiFi using ESP32   
 * usng 2 push buttons: CW and CCW
 * 
 * Watch Video instrution for this code:https://youtu.be/n2oeT6RcU5Q
 * 
 * Full explanation of this code and wiring diagram is available at
 * my Arduino Course at Udemy.com here: http://robojax.com/L/?id=62

 * Written by Ahmad Shamshiri on April 19, 2020 at 17:58
 * in Ajax, Ontario, Canada. www.robojax.com
 * 

 * Get this code and other Arduino codes from Robojax.com
Learn Arduino step by step in structured course with all material, wiring diagram and library
all in once place. Purchase My course on Udemy.com http://robojax.com/L/?id=62

If you found this tutorial helpful, please support me so I can continue creating 
content like this. You can support me on Patreon http://robojax.com/L/?id=63

or make donation using PayPal http://robojax.com/L/?id=64

 *  * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

int Pin1 = 13;//IN1 is connected to 13 
int Pin2 = 12;//IN2 is connected to 12  
int Pin3 = 14;//IN3 is connected to 14 
int Pin4 = 27;//IN4 is connected to 27 

 
int pole1[] ={0,0,0,0, 0,1,1,1, 0};//pole1, 8 step values
int pole2[] ={0,0,0,1, 1,1,0,0, 0};//pole2, 8 step values
int pole3[] ={0,1,1,1, 0,0,0,0, 0};//pole3, 8 step values
int pole4[] ={1,1,0,0, 0,0,0,1, 0};//pole4, 8 step values


int poleStep = 0; 
int  dirStatus = 3;// stores direction status 3= stop (do not change)


String buttonTitle1[] ={"CCW", "CW"};
String buttonTitle2[] ={"CCW", "CW"};
String argId[] ={"ccw", "cw"};


#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "Galaxy A12 2DF3";
const char *password = "khnq9920";

WebServer server(80);

void handleRoot() {
   //Robojax.com ESP32 Relay Motor Control
 String HTML ="<!DOCTYPE html>\
  <html>\
  <head>\
  	
<title>Robojax 28BYJ-48 Motor Control</title>\
  	
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  
<style>\
 
html,body{	
width:100%\;
height:100%\;
margin:0}
*{box-sizing:border-box}
.colorAll{
	background-color:#90ee90}
.colorBtn{
	background-color:#add8e6}
.angleButtdon,a{
	font-size:30px\;
border:1px solid #ccc\;
display:table-caption\;
padding:7px 10px\;
text-decoration:none\;
cursor:pointer\;
padding:5px 6px 7px 10px}a{
	display:block}
.btn{
	margin:5px\;
border:none\;
display:inline-block\;
vertical-align:middle\;
text-align:center\;
white-space:nowrap}
";
   
  HTML +="</style>

</head>

<body>
<h1>Robojax 28BYJ-48 Stepper Motor Control </h1>
";

   if(dirStatus ==2){
    HTML +="
	<h2><span style=\"background-color: #FFFF00\">Motor Running in CW</span></h2>
";    
   }else if(dirStatus ==1){
    HTML +="
	<h2><span style=\"background-color: #FFFF00\">Motor Running in CCW</span></h2>
";      
   }else{
    HTML +="
	<h2><span style=\"background-color: #FFFF00\">Motor OFF</span></h2>
";    
   }
      if(dirStatus ==1){
        HTML +="	<div class=\"btn\">
		<a class=\"angleButton\" style=\"background-color:#f56464\"  href=\"/motor?";
        HTML += argId[0];
        HTML += "=off\">";
        HTML +=buttonTitle1[0]; //motor ON title
      }else{
        HTML +="	<div class=\"btn\">
		<a class=\"angleButton \" style=\"background-color:#90ee90\"  href=\"/motor?";  
         HTML += argId[0];
        HTML += "=on\">";       
        HTML +=buttonTitle2[0];//motor OFF title   
      }   
     HTML +="</a>	
	</div>

";  
           
      if(dirStatus ==2){
        HTML +="	<div class=\"btn\">
		<a class=\"angleButton\" style=\"background-color:#f56464\"  href=\"/motor?";
        HTML += argId[1];
        HTML += "=off\">";
        HTML +=buttonTitle1[1]; //motor ON title
      }else{
        HTML +="	<div class=\"btn\">
		<a class=\"angleButton \" style=\"background-color:#90ee90\"  href=\"/motor?";  
         HTML += argId[1];
        HTML += "=on\">";       
        HTML +=buttonTitle2[1];//motor OFF title   
      }   
     HTML +="</a>	
	</div>

";     

   
   

  HTML +="	
</body>
</html>
";
  server.send(200, "text/html", HTML);  
}//handleRoot()

void handleNotFound() {
  //Robojax.com 28BYJ-48 Steper Motor Control
  String message = "File Not Found

";
  message += "URI: ";
  message += server.uri();
  message += "
Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "
Arguments: ";
  message += server.args();
  message += "
";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "
";
  }

  server.send(404, "text/plain", message);
  //Robojax.com 28BYJ-48 Steper Motor Control
}//end of handleNotFound()

void setup(void) {
  //Robojax.com 28BYJ-48 Steper Motor Control
 
 pinMode(Pin1, OUTPUT);//define pin for ULN2003 in1 
 pinMode(Pin2, OUTPUT);//define pin for ULN2003 in2   
 pinMode(Pin3, OUTPUT);//define pin for ULN2003 in3   
 pinMode(Pin4, OUTPUT);//define pin for ULN2003 in4   

 
  Serial.begin(115200);//initialize the serial monitor
  Serial.println("Robojax 28BYJ-48 Stepper Motor Control");

  //Robojax.com 28BYJ-48 Steper Motor Control
    
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: http://");
  Serial.println(WiFi.localIP());

//multicast DNS   //Robojax.com 28BYJ-48 Steper Motor Control
  if (MDNS.begin("robojaxESP32")) {
    Serial.println("MDNS responder started");
    Serial.println("access via http://robojaxESP32");
  }

  server.on("/", handleRoot);
  server.on("/motor", HTTP_GET, motorControl);           
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}//end of setup

void loop(void) {
    //Robojax.com 28BYJ-48 Steper Motor Control
  server.handleClient();
if(dirStatus ==1){ 
   poleStep++; 
    driveStepper(poleStep);    
 }else if(dirStatus ==2){ 
   poleStep--; 
    driveStepper(poleStep);    
 }else{
  driveStepper(8);   
 }
 if(poleStep>7){ 
   poleStep=0; 
 } 
 if(poleStep<0){ 
   poleStep=7; 
 } 

   delay(1);
   //Robojax.com 28BYJ-48 Steper Motor Control
}//end of loop

/*
 * motorControl()
 * updates the value of "dirStatus" varible to 1, 2 or 3
 * returns nothing
 * written by Ahmad Shamshiri
 * on Wednesday April 19, 2020 at 18:03 in Ajax, Ontario, Canada
 * www.robojax.com
 */
void motorControl() {


    if(server.arg(argId[0]) == "on")
    {
      dirStatus = 1;// CCW 
               
    }else if(server.arg(argId[0]) == "off"){
      dirStatus = 3;  // motor OFF 
          
    }else if(server.arg(argId[1]) == "on"){
      dirStatus = 2;  // CW  
          
    }else if(server.arg(argId[1]) == "off"){
      dirStatus = 3;  // motor OFF
          
    }  

  

  handleRoot();
}//motorControl end



/*
 * @brief sends signal to the motor
 * @param "c" is integer representing the pol of motor
 * @return does not return anything
 * 
 * www.Robojax.com code June 2019
 */
void driveStepper(int c)
{
     digitalWrite(Pin1, pole1[c]);  
     digitalWrite(Pin2, pole2[c]); 
     digitalWrite(Pin3, pole3[c]); 
     digitalWrite(Pin4, pole4[c]);   
}//driveStepper end here