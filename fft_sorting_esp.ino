#include "driver/i2s.h"
#include <arduinoFFT.h>
arduinoFFT FFT = arduinoFFT();
#include "variables.h"

void setup_mic()
{
  pinMode(27, INPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  i2s_driver_install((i2s_port_t)i2s_num, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)i2s_num, &pin_config);
  i2s_start((i2s_port_t)i2s_num);
}


int findMostFrequentElement()
{
  int n = 19;
    for (int i = 0; i < n; i++)    //Sort the array
    {    
        int temp;
        for (int j = i+1; j < n; j++) 
        {     
           if(array_of_notes_running[i] > array_of_notes_running[j]) 
           {    
               temp = array_of_notes_running[i];    
               array_of_notes_running[i] = array_of_notes_running[j];    
               array_of_notes_running[j] = temp;    
           }     
        }     
    }        
    //find the most occuring element
    int max_count = 1;
    int res = array_of_notes_running[0];
    int count = 1; 
    for (int i = 1; i < n; i++) { 
        if (array_of_notes_running[i] == array_of_notes_running[i - 1])
        {
            count++; 
        }
        else { 
            if (count > max_count) 
            { 
                max_count = count; 
                res = array_of_notes_running[i - 1]; 
            } 
            count = 1; 
        } 
    }   
    // If last element is most frequent 
    if (count > max_count) 
    { 
        max_count = count; 
        res = array_of_notes_running[n - 1]; 
    }   
    return find_chord(res); //return the most repeating element
}


int find_chord(int frequent_value)
{
    if (frequent_value == 123)
    {
      array_of_chords[chord_cnt++] = 'N';
    }
    if (frequent_value == 131)
    {
      array_of_chords[chord_cnt++] = 'C';
    }
    if (frequent_value == 139)
    {
      array_of_chords[chord_cnt++] = 'D';
    }
    if (frequent_value == 147)
    {
      array_of_chords[chord_cnt++] = 'E';
    }
    if (frequent_value == 156)
    {
       array_of_chords[chord_cnt++] = 'F';
    }
    if (frequent_value == 165)
    {
      array_of_chords[chord_cnt++] = 'G';    
    }
    if (frequent_value == 175)
    {
      array_of_chords[chord_cnt++] = 'H';
    }
    if (frequent_value == 185)
    {
      array_of_chords[chord_cnt++] = 'I';
    }
    if (frequent_value == 196)
    {
      array_of_chords[chord_cnt++] = 'J';
    }
    if (frequent_value == 208)
    {
       array_of_chords[chord_cnt++] = 'K';
    }
    if (frequent_value == 220)
    {
      array_of_chords[chord_cnt++] = 'L';
    }
    if (frequent_value == 233)
    {
      array_of_chords[chord_cnt++] = 'M';
    }
    if (frequent_value == 247)
    {
      array_of_chords[chord_cnt++] = 'N';
    }
    if (frequent_value == 261)
    {
      array_of_chords[chord_cnt++] = 'C';
    }
    if (frequent_value == 277)
    {
      array_of_chords[chord_cnt++] = 'D';
    }
    if (frequent_value == 294)
    {
      array_of_chords[chord_cnt++] = 'E';
    }
    if (frequent_value == 311)
    {
      array_of_chords[chord_cnt++] = 'F';
    }
    if (frequent_value == 330)
    {
      array_of_chords[chord_cnt++] = 'G';
    }
    if (frequent_value == 349)
    {
      array_of_chords[chord_cnt++] = 'H';
    }
    if (frequent_value == 370)
    {
      array_of_chords[chord_cnt++] = 'I';
    }
    if (frequent_value == 392)
    {
      array_of_chords[chord_cnt++] = 'J';
    }
    if (frequent_value == 415)
    {
      array_of_chords[chord_cnt++] = 'K';
    }
    if (frequent_value == 440)
    {
      array_of_chords[chord_cnt++] = 'L';
    } 
    if (frequent_value == 466)
    {
      array_of_chords[chord_cnt++] = 'M';
    }
    if (frequent_value == 494)
    {
      array_of_chords[chord_cnt++] = 'N';
    }
    if (frequent_value == 523)
    {
      array_of_chords[chord_cnt++] = 'C';
    }
    if (frequent_value == 554)
    {
      array_of_chords[chord_cnt++] = 'D';
    }
    if (frequent_value == 587)
    {
      array_of_chords[chord_cnt++] = 'E';
    }
    if (frequent_value == 622)
    {
      array_of_chords[chord_cnt++] = 'F';
    }
    if (frequent_value == 659)
    {
      array_of_chords[chord_cnt++] = 'G';
    }
    if (frequent_value == 698)
    {
      array_of_chords[chord_cnt++] = 'H';
    }
    if (frequent_value == 739)
    {
      array_of_chords[chord_cnt++] = 'I';
    }
    if (frequent_value == 0)
    {
      array_of_chords[chord_cnt++] = 'O';
    }
  }



void setup_buttons()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
}


int find_array(int n, int target)
{
  //figure out what frequency array we should use:
  if (target < 191)
  {
    return find_note(n, target, frequency_array_1);
  }
  else if ((target < 302) && (target > 190))
  {
    return find_note(n, target, frequency_array_2);
  }
  else if ((target > 301) && (target < 481))
  {
    return find_note(n, target, frequency_array_3);
  }
  else if (target > 480)
  {
    return find_note(n, target, frequency_array_4);
  }
}


int find_note(int n, int target, int frequency_array[])
{
  if (target >= frequency_array[n-1])
  {
    return frequency_array[n-1];
  }
  else if (target == 0)
  {
    array_of_notes_running[running_cnt++] = 0;
    if (running_cnt == 19)
    {
      findMostFrequentElement();
      running_cnt = 0;
      memset(array_of_notes_running, 0, 19);
    }
  }

  int i = 0;
  int j = n;
  int middle = 0;

  while (i < j)
  {
    middle = (i + j) / 2;

    //lower half:
    if (target < frequency_array[middle])
    {
      if ((middle > 0) && (target > frequency_array[middle - 1]))
      {
        return get_Closest(frequency_array[middle - 1], frequency_array[middle], target);
      }
      j = middle;
    }
    //upper half:
    else
    {
      if ((middle < n - 1) && (target < frequency_array[middle + 1]))
      {
        return get_Closest(frequency_array[middle], frequency_array[middle + 1], target);
      }
      i = middle + 1;
    }
  } 
}


int get_Closest(int val1, int val2, int target)
{
  if ((target - val1) >= (val2 - target))
  {
    array_of_notes_running[running_cnt++] = val2;
  }
  else
  {
    array_of_notes_running[running_cnt++] = val1;
  }
  if (running_cnt == 19)
  {
   findMostFrequentElement();
   running_cnt = 0;
   memset(array_of_notes_running, 0, 19);

  }
}


int check_buttons(int button)
{
  int reading = digitalRead(button);
  
  if (((millis() - lastDebounceTime) > debounceDelay)) 
  {
    buttonState = reading;
    if (buttonState == LOW) 
    {
      if (button == 2)
      {
        buttonState = HIGH;
        start_recording();
      }
      else if (button == 4)
      {
        buttonState = HIGH;
        stop_recording = 1;
      }
      else if (button == 17)
      {
        buttonState = HIGH;
        start_playback();
      }
    }
  }
}


void start_recording()
{
  Serial.write("B");
  array_cnt = 0;
  memset(array_of_hz, 0, 5000);
  while (stop_recording == 0)
  {
    sampleIn = 0;
    for (uint16_t i = 0; i < BLOCK_SIZE; i++)
    {
      i2s_pop_sample((i2s_port_t)i2s_num, (char*)&sampleIn, portMAX_DELAY);
      sampleIn >>= 14;
      vReal[i] = sampleIn;
      vImag[i] = 0.0;
    }
    FFT.Windowing(vReal, BLOCK_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, BLOCK_SIZE, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, BLOCK_SIZE);
    FFT.MajorPeak(vReal, BLOCK_SIZE, samplingFrequency, &freq, &ampli);
    if (freq < 1000 && ampli > 10000)
    {
      hz = round(freq);
      array_of_hz[array_cnt++] = hz;
    }
    else
    {
      array_of_hz[array_cnt++] = 0;
    }
  
    if (array_cnt == 5000)
    {
      stop_recording = 1;
    }
    delay(99);
    check_buttons(4);
  }
  stop_recording = 0;
  stop_record();
}


void stop_record()
{
  chord_cnt = 0;
  memset(array_of_chords, 0, 250);
  for (int k = 0; k < array_cnt; k++)
  {
    find_array(lenght_frequency_array, array_of_hz[k]);
  }  
  Serial.write("A");
}


void start_playback()
{
  int z = 0;
  delay(1000);
  while (z < chord_cnt)
  {
    Serial.print(array_of_chords[z]);
    delay(2000);
    z++;
  }
  delay(2000);
  Serial.write("A");
}


void setup()
{
  Serial.begin(115200);
  Serial.write("A");
  setup_mic();
  setup_buttons();
}


void loop()
{
  check_buttons(2);
  check_buttons(17);
}
