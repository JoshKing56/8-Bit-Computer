import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class Loader extends PApplet {

/**
 * LoadFile 1
 * 
 * Loads a text file that contains two numbers separated by a tab ('\t').
 * A new pair of numbers is loaded each frame and used to draw a point on the screen.
 */




Serial myPort;  // Create object from Serial class

int SERIAL_BAUD_RATE = 115200;

String[] lines;
int index = 0;

public void setup() {

  
    
  background(0);
  stroke(255);
  fill(0, 255, 0);
  //rect(0, height/3, width*(1/20), (2*height)/3);
  get_file_data();
  
  byte[][] data_byte = new byte[lines.length-2][3];
  convert_to_bytes(data_byte);
  find_serial_port();
  push_data(data_byte);

}

public void draw() {

}


public void get_file_data() {
  StringBuffer path = new StringBuffer(sketchPath(""));
  int path_string_length = path.length();
  path.replace(path_string_length-7, path_string_length, "");
  path.append("hexOutput.hex");
  lines = loadStrings(path.toString());
  println(lines[2]);
}


public void convert_to_bytes(byte[][] data_byte) {

  for (int i = 2; i < lines.length; i++) {
    String data = new String(lines[i].toString());  
    data_byte[i-2][0] = (byte)((hex2byte(data.substring(0, 1))<<4) + hex2byte(data.substring(1, 2)));
    data_byte[i-2][1] = (byte)((hex2byte(data.substring(2, 3))<<4) + hex2byte(data.substring(3, 4)));
    data_byte[i-2][2] = (byte)((hex2byte(data.substring(4, 5))<<4) + hex2byte(data.substring(5, 6)));
  }
}


public void find_serial_port() {
   
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, SERIAL_BAUD_RATE);
  println(portName);
   
}
public void push_data(byte[][] data_byte) {
  
  myPort.write(data_byte.length);  //write length for receiver
  //println(data_byte.length);
  for (int i = 0; i< data_byte.length;i++){
    for(int k =0; k<3;k++){
       //myPort.write(data_byte[i][k]);  //write length for receiver
       delay(3);//short delay between bytes to allow receiver to finish
             
    }
    draw_prog_bar(i, data_byte.length);
  }
}

public void draw_prog_bar(int pos, int max){
  
  print("[");
  int num = (pos*20)/max;
  int i =0;
  for (i =0; i<num;i++)
  print("-");
  for (i = num; i<20; i++){
  print(" ");
  }
  println("]");
  
  //background(0);
  //fill(255, 0, 0);
  //fill(0);
  //rect(0,0, width, height);
  //fill(0,255,0);
  //rect(0, height/3, (pos*width)/max, height/3);
  
}


//lut conversion to byte values
public byte hex2byte(String input) {
  byte output=0;
  switch(input) {
  case "0": 
    output = 0; 
    break;
  case "1": 
    output = 1; 
    break;
  case "2": 
    output = 2; 
    break;
  case "3": 
    output = 3; 
    break;
  case "4": 
    output = 4; 
    break;
  case "5": 
    output = 5; 
    break;
  case "6": 
    output = 6; 
    break;
  case "7": 
    output = 7;   
    break;
  case "8": 
    output = 8; 
    break;
  case "9": 
    output = 9; 
    break;

  case "A": 
    output = 10; 
    break;
  case "B": 
    output = 11;
    break;
  case "C": 
    output = 12; 
    break;
  case "D": 
    output = 13; 
    break;
  case "E": 
    output = 14; 
    break;
  case "F": 
    output = 15;
    break;

  case "a": 
    output = 10; 
    break;
  case "b": 
    output = 11;
    break;
  case "c": 
    output = 12; 
    break;
  case "d": 
    output = 13; 
    break;
  case "e": 
    output = 14; 
    break;
  case "f": 
    output = 15;   
    break;
  }
  return output;
}
  public void settings() {  size(200, 200); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "Loader" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
