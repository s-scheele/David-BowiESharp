#include <SSD1320_OLED.h>

SSD1320 flexibleOLED(10, 9);

//frequencies from C3 to F#3:
int frequency_array_1[] = {123, 131, 139, 147, 156, 165, 175, 185};
//frequencies from G3 to D4:
int frequency_array_2[] = {196, 208, 220, 233, 247, 261, 277, 294};
//frequencies from D#/Eb4 to A#/Bb4:
int frequency_array_3[] = {311, 330, 349, 370, 392, 415, 440, 466};
//frequencies from B4 to F#/Gb5:
int frequency_array_4[] = {494, 523, 554, 587, 622, 659, 698, 739};

char state;


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(7, OUTPUT);
digitalWrite(7, HIGH);


//print_chord("C E G");
//print_recording();
//print_startscreen();
}


void print_chord(char* chord)
{
  flexibleOLED.begin(160,32);
  flexibleOLED.clearDisplay();
  flexibleOLED.setFontType(1);
  flexibleOLED.setCursor(30, 7);
  flexibleOLED.print(chord);
  flexibleOLED.display();
}

void print_startscreen()
{
  flexibleOLED.begin(160,32);
  flexibleOLED.clearDisplay();

  int sidebar_width = 3;
  int sidebar_height = 15;
  //sidebar on the left side:
  int sidebar0_Y = (flexibleOLED.getDisplayHeight() / 2) - (sidebar_height / 2);
  int sidebar0_X = 2;
  //sidebar on the right side:
  int sidebar1_Y = (flexibleOLED.getDisplayHeight() / 2) - (sidebar_height / 2);
  int sidebar1_X = flexibleOLED.getDisplayWidth() - 3 - sidebar_width;
  //sidebar velocity:
  int sidebar0_velocity = -1;
  int sidebar1_velocity = 1;

  while (!Serial.available())
  //for (int i= 1; i<3000; i++)
  {
    //move sidebars:
    sidebar0_Y += sidebar0_velocity;
    sidebar1_Y += sidebar1_velocity;
    //change direction when they hit a wall:
    if ((sidebar0_Y <= 1) || (sidebar0_Y > flexibleOLED.getDisplayHeight() - 2 - sidebar_height))
    {
      sidebar0_velocity = -sidebar0_velocity;
    }
    if ((sidebar1_Y <= 1) || (sidebar1_Y > flexibleOLED.getDisplayHeight() - 2 - sidebar_height))
    {
      sidebar1_velocity = -sidebar1_velocity;
    }

    flexibleOLED.clearDisplay(CLEAR_BUFFER);
    flexibleOLED.rectFill(sidebar0_X, sidebar0_Y, sidebar_width, sidebar_height);
    flexibleOLED.rectFill(sidebar1_X, sidebar1_Y, sidebar_width, sidebar_height);
  
    flexibleOLED.setFontType(1);
    flexibleOLED.setCursor(15, 12);
    flexibleOLED.print("David BowiE#");
    flexibleOLED.setFontType(0); 
    flexibleOLED.setCursor(35, 0);
    flexibleOLED.print("Press a Button");
    flexibleOLED.display();
  }
}

void print_recording()
{
  flexibleOLED.begin(160,32);
  flexibleOLED.clearDisplay();
  flexibleOLED.setFontType(1);

  int dot_rad = 2;
  int dot_X = 110;
  int dot_X_max = 135;
  int dot_X_min = 110;
  int dot_Y = 13;
  int dot_velocity = 1;
  int one = 1;
  int two = 1;
  int three = 1;
/*
  while (three < 20)
  {
    flexibleOLED.setCursor(78, 7);
    flexibleOLED.print("3");
    flexibleOLED.display();
    three++;
  }

  if (three >= 20)
  {
    flexibleOLED.clearDisplay();
    while (two < 20)
    {
      flexibleOLED.setCursor(78, 7);
      flexibleOLED.print("2");
      flexibleOLED.display();
      two++;
    }
  }

  if ((three >= 20) && (two >= 20))
  {
    flexibleOLED.clearDisplay();
    while (one < 20)
    {
      flexibleOLED.setCursor(78, 7);
      flexibleOLED.print("1");
      flexibleOLED.display();
      one++;
    }
  }
  */

  while (!Serial.available())
  //for (int i = 1; i<3000; i++)
  {
    dot_X += dot_velocity;
    if ((dot_X >= dot_X_max) || (dot_X <= dot_X_min))
    {
      dot_velocity = -dot_velocity;
    }
    flexibleOLED.clearDisplay(CLEAR_BUFFER);
    flexibleOLED.circleFill(dot_X, dot_Y, dot_rad);
    flexibleOLED.setCursor(25, 7);
    flexibleOLED.print("Recording");
    flexibleOLED.display();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0)
{
  state = Serial.read();

  switch (state)
  {
    case 'A':
    print_startscreen();
    break;

    case 'B':
    print_recording();
    break;

    case 'C':
    print_chord("C - E - G"); // c
    break;

    case 'D':
    print_chord("C# - F - G#"); // c sharp
    break;

    case 'E':
    print_chord("D - F# - A"); // d
    break;

    case 'F':
    print_chord("D# - G - A#"); // d sharp
    break;

    case 'G':
    print_chord("E - G# - B"); // e
    break;

    case 'H':
    print_chord("F - A - C"); // f
    break;

    case 'I':
    print_chord("F# - A# - C"); //f sharp
    break;

    case 'J':
    print_chord("G - B - D"); // g
    break;

    case 'K':
    print_chord("G# - C - D#"); //g sharp
    break;

    case 'L':
    print_chord("A - C# - E"); //a
    break;

    case 'M':
    print_chord("A - C - E"); //a sharp
    break;
    
    case 'N':
    print_chord("B - D# - F#"); //b
    break;

    case 'O':
    print_chord("Pause"); //b
    break;

    default:
    break;
  }
}
}
