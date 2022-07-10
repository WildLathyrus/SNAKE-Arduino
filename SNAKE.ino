# include <FastLED.h>
# define NUMLEDS 64
# define DATAPIN 6

# define RESETPIN 19

# define PINUP 2
# define PINDOWN 3
# define PINLEFT 4
# define PINRIGHT 5

CRGB leds[NUMLEDS];
int fade = 250;

int move_up;
int move_down;
int move_left;
int move_right;

int toggle_up = true;
int toggle_down = true;
int toggle_left = true;
int toggle_right = true;

int snake[NUMLEDS] = { 0 };

int currentloc = 36;
int pastloc = currentloc;
int left_right;

int berry;
int in_play = false;
int run_game = true;

int score = 0;

// COLOR 
// CRGB::DodgerBlue  // blue
// CRGB::FireBrick   // red
// CRGB::DarkGreen   // green

void setup() {
  FastLED.addLeds <NEOPIXEL, DATAPIN> (leds, NUMLEDS);
  for (int i = 0; i < NUMLEDS; i++){
      leds[i] = CRGB::DodgerBlue;
      leds[i].fadeLightBy(fade);
    }
  leds[currentloc] = CRGB::DarkGreen;
  leds[currentloc].fadeLightBy(fade);
  
  pinMode(RESETPIN, OUTPUT);

  pinMode(PINUP,    INPUT_PULLUP);
  pinMode(PINDOWN,  INPUT_PULLUP);
  pinMode(PINLEFT,  INPUT_PULLUP);
  pinMode(PINRIGHT, INPUT_PULLUP);

  randomSeed(analogRead(0));

  Serial.begin(9600);
}

void loop() {
  
  if (run_game){
    if (in_play == false){
      do {
        berry = random(0,NUMLEDS - 1);
        Serial.println(berry);
      }
      while (berry == currentloc);
      in_play = true;
    }
  
    leds[berry] = CRGB::FireBrick;
    leds[berry].fadeLightBy(fade);
    
    move_up = digitalRead(PINUP);
    move_down = digitalRead(PINDOWN);
    move_left = digitalRead(PINLEFT);
    move_right = digitalRead(PINRIGHT);

    Serial.print(move_up);
    
    if (move_up == false && toggle_up == true){
      Serial.println("up");
      toggle_up = false;
      pastloc = currentloc;
      currentloc -= 8;
        if (currentloc >= 0){
          print_led();
        }else{
          currentloc = pastloc;
          //end_game();
        } 
    }else if (move_up == true && toggle_up == false){
      toggle_up = true;
    }
    if (move_down == false && toggle_down == true){
      Serial.println("down");
      toggle_down = false;
      pastloc = currentloc;
      currentloc += 8;
        if (currentloc < 64){
          print_led();
        }else{
          currentloc = pastloc;
          //end_game();
        } 
    }else if (move_down == true && toggle_down == false){
      toggle_down = true;
    }
    if (move_left == false && toggle_left == true){
      Serial.println("left");
      toggle_left = false;
      left_right = (currentloc % 8) - 1;
      pastloc = currentloc;
      currentloc --;
        if (left_right > -1){
          print_led();
        }else{
          currentloc = pastloc;
          //end_game();
        }  
    }else if (move_left == true && toggle_left == false){
      toggle_left = true;
    }
    if (move_right == false && toggle_right == true){
      Serial.println("right");
      toggle_right = false;
      left_right = (currentloc % 8) + 1;
      pastloc = currentloc;
      currentloc ++;
        if (left_right < 8){
          print_led();
        }else{
          currentloc = pastloc;
          //end_game();
        }
    }else if (move_right == true && toggle_right == false){
      toggle_right = true;
    }
  
  
    if (berry == currentloc){
      leds[currentloc] = CRGB::DarkGreen;
      leds[currentloc].fadeLightBy(fade);
      in_play = false;
      score ++;
    }
  }
  
  FastLED.show();
  
  delay(25); // needed to make the button work or it my reconize two push for one
}

int print_led(){
  leds[pastloc] = CRGB::DodgerBlue;
  leds[currentloc] = CRGB::DarkGreen;
  leds[pastloc].fadeLightBy(fade);
  leds[currentloc].fadeLightBy(fade);
  return 0;
  }

int end_game(){
  run_game = false;
  return 0;
  }


  
