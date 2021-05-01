/*
C -Code for running FFt authentication system using  ESP32
Team Id  : DSP_12
Author List: Aravinda Harithsa, Marefat abbas
Filename : FFTAUTHENTICATION.c
*/


#include <Wire.h>
#include <WiFi.h>               //To connect to Wifi network under STA mode 
#include <HTTPClient.h>         //Library file to establish Http connection to google sheets 
#include "arduinoFFT.h"         // FFT library for arudino 
#include "SSD1306.h"            // Display header 
#define SAMPLES 512                 // Bin size for computing FFT     
#define SAMPLING_FREQUENCY 40000   //Our sampling frequency 
        

SSD1306 display(0x3c,SDA,SCL);    // This is to intiate the Display module attached
arduinoFFT FFT = arduinoFFT();    //Create an object of FFT class for Computation
unsigned int sampling_period_us;  
unsigned long microseconds;
double vReal[SAMPLES];            //Real values of the plotted FFT
double vImag[SAMPLES];            //Imaginary values of plotted FFT
unsigned long newTime, oldTime;   //For ADC converison and sampling purpose using this 

int aravinda=0;                   //Flag  to authenticate only once ( 1 or 0)
int sourav=0;                       //Flag  to authenticate only once ( 1 or 0)
const char * ssid = "##########";      //Network credentials
const char * password = "&&&&&&&";  //Network credentials
String GOOGLE_SCRIPT_ID = "AKfycbxR_zSZXTKHCSI4V2tCeCNpGgHTgp3dCH6AQcnQic7WmYv52Ak";    // Id of the goole docs sheet which we are using to store
const int sendInterval = 996 *5; // in millis, 996 instead of 1000 is adjustment, with 1000 it jumps ahead a minute every 3-4 hours


//This is the Network SSL Certificate required to authenticate with google sheets 
const char * root_ca=\
"-----BEGIN CERTIFICATE-----\n" \
"MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n" \
"A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n" \
"Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n" \
"MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n" \
"A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" \
"hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n" \
"v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n" \
"eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n" \
"tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n" \
"C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n" \
"zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n" \
"mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n" \
"V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n" \
"bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n" \
"3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n" \
"J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n" \
"291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n" \
"ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n" \
"AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n" \
"TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n" \
"-----END CERTIFICATE-----\n";


//Start the wifi service
WiFiClientSecure client;

/*
* Function Name:  DrawRect()
* Input     : No parameters passed 
* Output     : Void 
* Logic    : This function will Display rectangular border
* Example Call : DrawRect();
*/
void DrawRect() {
      // Draw a pixel at given position
    for (int i = 0; i < 10; i++) 
    {
      display.setPixel(i, i);
      display.setPixel(10 - i, i);
    }
   
    display.drawRect(12, 12, 20, 20);
     
    // Fill the rectangle
    display.fillRect(14, 14, 17, 17);

    // Draw a line horizontally
    display.drawHorizontalLine(0, 40, 20);

    // Draw a line horizontally
    display.drawVerticalLine(40, 0, 20);
}


/*
* Function Name:  drawSpectrum()
* Input     : No inputs 
* Output     : Void 
* Logic    : This function will Display Eyantra LAB 
* Example Call :  drawSpectrum();
*/
void drawSpectrum()
{
    display.clear();
    display.drawRect(0, 0, 128, 64);      
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 2, "EYANTRA LAB");
           
}

//This will run only once as init ,to set up all hardware interfaces and ports 
void setup() {
  Serial.begin(115200);
  Wire.begin(5,4); // SDA, SCL
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.flipScreenVertically(); // Adjust to suit or remove
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

  WiFi.mode(WIFI_STA); // Work under STA mode of operation 
  WiFi.begin(ssid, password);   //Connect to wifi with following credentials 
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
    Serial.print(".");
  }
  
}


//This is an infinate loop running always 

void loop() {
  display.clear();  //Clear the previous displays 
  drawSpectrum(0,0); // Dray the boundary rectanglt with eyantra logo 
  display.display();  //Update the display screen 
 
  for (int i = 0; i < SAMPLES; i++) 
  {
    newTime = micros()-oldTime;
    oldTime = newTime;
    vReal[i] = analogRead(A0); // A conversion takes about 1uS on an ESP32
    vImag[i] = 0;
    while (micros() < (newTime + sampling_period_us)) { /* do nothing to wait */ }
  }
  //Selection of proper window technique to obtain optimum results
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_BLACKMAN_HARRIS, FFT_FORWARD);

  //Computation of FFt algorithm to obtain Real and imaginary value 
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);  //Convert to mag
  int j=0;
  //$- But system for proof of concept ( max0-max3) 
  int max0=0;
  int max1=0;
  int max2=0;
  int max3=0;

 //This can either be done by calibration or by formula from ( sampling,CHUNK,desired freq) 
for (int i = 150  ; i < 250; i++) // for loop to iterate via all bins

{
    if (vReal[i]>150 && i>170 &&i <180) // this is 16khz
    { 
     
      max1 = 1;   //set the particular bit as high 
    }


    
    if (vReal[i]>150 && i>185 &&i <188) // this is 17khz
    { 
     
      max1 = 1;    //set the particular bit as high 
    }

     if (vReal[i]>50 && i>195 &&i <205)  // this is 18khz
    { 
      
      max2 = 1;    //set the particular bit as high 
    }


 if (vReal[i]>100 && i>210 &&i <230) // this is 19.1khz
    { 
     
      max3 = 1;    //set the particular bit as high 
    }
    
    

}


//To cehck for bits and print relevant user detalils ( in future it might be used with firebase 
if( max0==0 && max1==1 && max2==0 && max3==0 && aravinda == 0 ) 
{
  Serial.println("ARAVINDA HARITHSA");
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "ARAVINDA HARITHSA");//Update the Display module  by calling this URL 
  display.drawString(64, 32, "AUTHENTICATED...");//Update the Display module  by calling this URL 
  display.display();//Dsiplay update 
  delay(1000);    
  display.clear();  
  String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+ "info1=Aravinda&info2=Intern&temp=temp"; //Update the goole sheers by calling this URL 
  http.begin(url, root_ca);    // Begin the HTTP connection with pre stored SSL certificate  and URl link stored in string 
  int httpCode = http.GET();    //Get any error or sucess codes obtained back 
  Serial.println("DONE_");    
  http.end();

  aravinda =1;  //Set the falg that person already entered 
}


if(max0==0 && max1==0 && max2==1 && max3==0 && sourav == 0 ) 
{

Serial.println("SOURAV JENA");
display.setFont(ArialMT_Plain_10);
display.setTextAlignment(TEXT_ALIGN_CENTER);
display.drawString(64, 22, "SOURAV JENA"); //Update the Display by calling this URL 
display.drawString(64, 32, "AUTHENTICATED..."); //Update the Display module  by calling this URL 
display.display();//Dsiplay update
HTTPClient http;
String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+ "info1=Souvrav_Jena&info2=Mentor&temp=Permanent"; //Update the goole sheets by calling this URL 
http.begin(url, root_ca);     // Begin the HTTP connection with pre stored SSL certificate  and URl link stored in string 
int httpCode = http.GET();    //Get any error or sucess codes obtained back 
Serial.println(httpCode);
http.end();
delay(1000); //Wait for some time 
sourav = 1;  //Set the falg that person already entered 
}


}
