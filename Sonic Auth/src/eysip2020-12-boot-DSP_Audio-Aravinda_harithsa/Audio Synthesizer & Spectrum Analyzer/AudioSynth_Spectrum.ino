/*
C -Code for running audio synthesizer and Spectrum analyzer Together by making use of two cores of ESP32
Team Id  : DSP_12
Author List: Aravinda Harithsa, Marefat abbas
Filename : AudioSynth_spectrum.c
Functions  : void displayBand(),void PlayMusic(),void Playbuffer(),void MusicSynth(),void SpectumAnalyzer()
*/
//--------------------------------------------------------------------------------------------------------------------
#include <Wire.h>                // This library is used for serialcommunication
#include "arduinoFFT.h"          // This is arduino FFT implementation where we have all required FFt functions for spectrum analyzer
#include "SSD1306.h"             // This is header file to run the OLED screen 
SSD1306 display(0x3c,SDA,SCL);   // init() for the display module by defining port numbers (SDA,SCL) and the address
#define SAMPLES 512              // This is the number of audio saples taken            
#define SAMPLING_FREQUENCY 40000 // This is our sampling frequency 
#define amplitude 150            // This is our arbitary threshold for amplitude ( scale down factor)          
#include "SoundData.h"           // This contains all the swaras ( sa re ga ma pa da ne sa ) and few notes  stored as 8 bit raw audio data containing numerical vales in array
#include "XT_DAC_Audio.h"        // This is the DAC implementation library which we used to 
#define Num_Samples  112         //  number of dample of signal
#define MaxWaveTypes 4           // types of wave (signal)
         
//--------------------------------------------------------------------------------------------------------------------
  // Create the main player class object. Use GPIO 25, one of the 2 DAC pins and timer 0 will be utilized 
XT_DAC_Audio_Class DacAudio(25,0);        
// Here we will be calling varius instances of the class by passing relevant sound information 
XT_Wav_Class Zero(sa);          
XT_Wav_Class One(re);          
XT_Wav_Class Two(ga);           
XT_Wav_Class Three(ma);           
XT_Wav_Class Four(pa);           
XT_Wav_Class Five(da);       
XT_Wav_Class Six(nee);        
XT_Wav_Class Seven(bsa);          

 // The sequence object, you add your sounds above to this object (see setup below)
XT_Sequence_Class Sequence;              
int count1 = 0;          
arduinoFFT FFT = arduinoFFT();         // Creation of FFT object for arudino     
unsigned int sampling_period_us;       //sampling period   
unsigned long microseconds;          
byte peak[] = {0,0,0,0,0,0,0};        // Creation of 8 different bands required for Spectrum analyzer 
double vReal[SAMPLES];                //Array to store all the real values of the FFt output
double vImag[SAMPLES];                //Array to store all the Imaginary vaues of FFT
unsigned long newTime, oldTime;       //Time variables to help in sampling audio signals  from ADC 
void MusicSynth( void *pvParameters );  
void SpectumAnalyzer( void *pvParameters );

/*
* Function Name: displayBand()
* Input     : band and size 
* Output     : Void 
* Logic    : This function will display the spectrum on OLED screen 
* Example Call : displayBand(band,size);
*/
void displayBand(int band, int dsize){
  int dmax = 50;
  if (dsize > dmax) dsize = dmax;
  if (band == 7) display.drawHorizontalLine(18*6,0, 14);
  for (int s = 0; s <= dsize; s=s+2){display.drawHorizontalLine(18*band,64-s, 14);}
  if (dsize > peak[band]) {peak[band] = dsize;}
}


/*
* Function Name: PlayMusic()
* Input     : Music tone to be played will be added here 
* Output     : Void 
* Logic    : This function will display the spectrum on OLED screen 
* Example Call : displayBand(band,size);
*/

void PlayMusic(char const *Number)
{  
  int NumChars=strlen(Number);              // could lose this line of put strlen in loop below, but bad form to do so
  Sequence.RemoveAllPlayItems();            // Clear out any previous playlist
  for(int i=0;i<NumChars;i++)
  Playbuffer(Number[i]);                 // For each tone/swara  add in the sound for that tune  to the sequence
  DacAudio.Play(&Sequence);                 // Play the sequence, will not wait here to complete, works independently of your code
 
}

/*
* Function Name: Playbuffer()
* Input     : Music tone to be played will be added here 
* Output     : Void 
* Logic    : This function will call the Addplayitem and hence plays the relevent tune 
* Example Call : Playbuffer(Swara);
*/

void Playbuffer(char swara)
{
  // Adds the relevant called swara from 0 to 7 keys press an plays the same tone 

  switch(swara)
  {
    case '0' : Sequence.AddPlayItem(&Zero);break;
    case '1' : Sequence.AddPlayItem(&One);break;
    case '2' : Sequence.AddPlayItem(&Two);break;
    case '3' : Sequence.AddPlayItem(&Three);break;
    case '4' : Sequence.AddPlayItem(&Four);break;
    case '5' : Sequence.AddPlayItem(&Five);break;
    case '6' : Sequence.AddPlayItem(&Six);break;
    case '7' : Sequence.AddPlayItem(&Seven);break;

  }
}


//This will run only once to initialize all the ports and hardware 
void setup() {
  
  // initialize serial communication at 115200 bits per second for laptop to esp32 :
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1,16, 17);    // initialize serial communication at 9600 bits per second from Atmega 2560 to Esp32
  Wire.begin(5,4); // SDA, SCL 
  display.init();  //Initialize the connected display module 
  display.setFont(ArialMT_Plain_10);   // Choose the font to be displayed on oled screen
  display.flipScreenVertically(); // Adjust to suit or remove
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));    //Calculation of sampling frequency 


  // Now Let us set up two tasks to run independently.
  xTaskCreatePinnedToCore(
    MusicSynth
    ,  "MusicSynth"   // Here we will be using this for running music synthesizer 
    ,  1024         // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1            // Priority
    ,  NULL 
    ,  0);        //This process will be running on core 0 of ESP32 

  xTaskCreatePinnedToCore(
    SpectumAnalyzer
    ,  "Spectrum"
    ,  1024  // Stack size
    ,  NULL
    ,  2                // Priority
    ,  NULL 
    ,  1);      // here select the core to which this task will be pinned to core 1 on ESP32

          // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks function defined below , the loop remains empty 
}


 /*
* Function Name: MusicSynth()
* Input     : This is one of the task of RTOS pinned to core 1 
* Output     : Void 
* Logic    : Tasks ( Running Serial monitor and Audio synthesizer) 
* This function will be maintained by RTOS , for loops run on infinate loop 
*/

void MusicSynth(void *pvParameters)  // This is a task.
{
(void) pvParameters;
XT_DAC_Audio_Class DacAudio(25,0);                                            // Create the main player class object. Use GPIO 25 (DAC pin) and timer 0

for (;;)
  { 
   DacAudio.FillBuffer();                   // Fill the buffer with selected sound ( to play the sound on DAC) 
  if(Serial.available())                    // If any key press detected from serial comm from Atmega 2560 
    PlayMusic(Serial.readString().c_str()); // Read the incomming data from serial port and convert it into string format 
     vTaskDelay(10);                        //Each task should be given one tick delay to stop from ending the task 
  }
}
 
 /*
* Function Name: SpectumAnalyzer()
* Input     : This is one of the task of RTOS pinned to core 0 
* Output     : Void 
* Logic    : Tasks ( Running DSP algorithm for FFT generation and Running audio Synthesizer 
* This function will be maintained by RTOS , for loops run on infinate loop 
*/

void SpectumAnalyzer(void *pvParameters)  // This is a task for spectrum analyzer
{
  (void) pvParameters;

  for (;;)
  { 
  display.clear();    //Clear the previous values of display 
  display.drawString(0,0,"0.1 0.2 0.5 1K  2K  4K  8K");  //For various bands write values on screen 
  for (int i = 0; i < SAMPLES; i++)                     //Sampling function which runs for loop to accuire values from ADC until Fixed samples are reached
  {
    newTime = micros()-oldTime;
    oldTime = newTime;
    vReal[i] = analogRead(A0);                              // A conversion takes about 1uS on an ESP32
    vImag[i] = 0;                                           //We don;t require phase so we will be neglecting iaginary values to 0 
    while (micros() < (newTime + sampling_period_us)) { /* do nothing to wait */ }
  }

  //inintially window function will be applied , here we will be using Hamming window ,  FFt forward 
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);

  //This will cpompute  FFT of the given sample and then store the results in vreal and vImag variables 
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  
  //This will Convert the complex imaginary values obtained into magnitude format  
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

 //This loop is used to dynamically plot the whole band of spectrum ( 8 bands ) 
  for (int i = 2; i < (SAMPLES/2); i++){ // Don't use sample 0 and only first SAMPLES/2 are usable. Each array eleement represents a frequency and its value the amplitude.
    if (vReal[i] > 2000) { // Add a crude noise filter, 10 x amplitude or more to filter out ambient noise 
      if (i<=2 )             displayBand(0,(int)vReal[i]/amplitude); // 125Hz
      if (i >3   && i<=5 )   displayBand(1,(int)vReal[i]/amplitude); // 250Hz
      if (i >5   && i<=7 )   displayBand(2,(int)vReal[i]/amplitude); // 500Hz
      if (i >7   && i<=15 )  displayBand(3,(int)vReal[i]/amplitude); // 1000Hz
      if (i >15  && i<=30 )  displayBand(4,(int)vReal[i]/amplitude); // 2000Hz
      if (i >30  && i<=53 )  displayBand(5,(int)vReal[i]/amplitude); // 4000Hz
      if (i >53  && i<=200 ) displayBand(6,(int)vReal[i]/amplitude); // 8000Hz
      if (i >200           ) displayBand(7,(int)vReal[i]/amplitude); // 16000Hz
    
    }
    for (byte band = 0; band <= 6; band++) display.drawHorizontalLine(18*band,64-peak[band],14);
  }
  if (millis()%4 == 0) {for (byte band = 0; band <= 6; band++) {if (peak[band] > 0) peak[band] -= 1;}} // Decay the peak
  display.display();        //This function is called to update the LED screen with new values 
  vTaskDelay(10); 
  }
}






                                      
