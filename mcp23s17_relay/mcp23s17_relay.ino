#include <SPI.h>
#include <MCP23x17.h>
#include <MCP23S17.h>
#include <OneWire.h>


String incomingByte = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int temperature = 0;
long lastUpdateTime = 0; // last update variable
const int TEMP_UPDATE_TIME = 1000; // update temp pereodically


CMCP23S17 mcp23_1; //Select address of chip "0 0 0"
OneWire ds(9); // Select pin of OneWire

bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

//=== function to print the command list:  ===========================
void printHelp(void){
  Serial.println("--- Command list: ---");
  Serial.println("? -> Print this HELP");
  Serial.println("port * on  -> Activate all ports");
  Serial.println("port * off  -> Deactivate all port");
  Serial.println("port * stat  -> All ports status");
  Serial.println("port # on  -> Port #(1-16) On  \"activate\"");
  Serial.println("port # off  -> Port #(1-16) Off  \"deactivate\"");
  Serial.println("port # stat  -> Port #(1-16) State  \"status\""); 
  Serial.println("reset -> Reset Arduino controller");
  Serial.println("temp -> Show Ambient temperature \"C\"");   
  Serial.println("---");

  }

//=== function to check temperature:  ===========================
int detectTemperature(){

  byte data[2];
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);

  if (millis() - lastUpdateTime > TEMP_UPDATE_TIME)
  {
    lastUpdateTime = millis();
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    data[0] = ds.read();
    data[1] = ds.read();

    // prepare variable
    temperature = (data[1] << 8) + data[0]; temperature = temperature >> 4;
  }
}

//---------------- setup ---------------------------------------------
void setup(){
  SPI.begin();          // Initialize SPI
  detectTemperature();  // Initialize Temp sensor
  Serial.begin(9600);   // Open serial port (9600 bauds).
  Serial.flush();       // Clear receive buffer.
  incomingByte.reserve(200);
  mcp23_1.init(10, 0);

  for (int i=0; i<16; i++) {
    mcp23_1.pinMode(i, OUTPUT);  //Set all ports to OUTPUT
  }
  printHelp();          // Print the command list.
}

//=== RESET board function:  ===========================
void(* resetFunc) (void) = 0; //declare reset function @ address 0

//=== Check serial port function:  ===========================
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    incomingByte += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//--------------- parser ----------------------------------------------- 
void parseCommand(String com)
{
  String  part1;
  String  part2;
  String  part3;

  part1 =  getValue(com,' ',0);
  part1.trim();
  part2 =  getValue(com,' ',1);
  part2.trim();
  part3 =  getValue(com,' ',2);
  part3.trim();
  
     //Serial.println(part1 + " part 1");        //debug
     //Serial.println(part2 + " part 2");        //debug
     //Serial.println(part3 + " part 3");        //debug

  if(part1.equalsIgnoreCase("port"))
    {
         if(inRange(part2.toInt(), 1, 16))
           {
             if (part3.equalsIgnoreCase("on"))
               {
                 mcp23_1.digitalWrite(part2.toInt()-1, HIGH);
                 Serial.println("port=" + part2 + ",status=" + part3);
               }
             else if (part3.equalsIgnoreCase("off"))
               {
                 mcp23_1.digitalWrite(part2.toInt()-1, LOW);
                 Serial.println("port=" + part2 + ",status=" + part3);
               }
             else if (part3.equalsIgnoreCase("stat"))
               {
                 Serial.print("port=" + part2 + ",status=");
                 Serial.println(mcp23_1.digitalRead(4));
               }
             else 
               {
                 Serial.println("syntax erro3r"); // Print syntax error
               }
           }
         else if(part2.equalsIgnoreCase("*"))
           {
             if (part3.equalsIgnoreCase("on"))
               {
                 for (int i=0; i<16; i++) {
                 delay(200); 
                 mcp23_1.digitalWrite(i, HIGH);
                 delay(100);       //little timeout to protect power supply from high load.
                 }
                 Serial.println("ON_ALL=OK");
               }
             else if (part3.equalsIgnoreCase("off"))
               {
                 for (int i=0; i<16; i++) {
                 mcp23_1.digitalWrite(i, LOW);
                 delay(100);      //little timeout
                 }
                 Serial.println("OFF_ALL=OK");
               }
             else if (part3.equalsIgnoreCase("stat"))
               {
                 for (int i=0; i<16; i++) 
                   {
                     Serial.print("port=");
                     Serial.print(i+1);
                     Serial.print(",status=");
                     Serial.println(mcp23_1.digitalRead(i));
                     }
               }
             else 
               {
                 Serial.println("syntax erro2r"); // Print syntax error
               }
           }   
         else
           {
             Serial.println("syntax erro1r"); // Print syntax error
           }
    }
  else if(part1.equalsIgnoreCase("reset"))
    {
         resetFunc();  //call reset
         delay(100);
         Serial.println("this never happens :D");  
    }
  else if(part1.equalsIgnoreCase("temp"))
    {
         detectTemperature(); // call the pope
         Serial.print("temp=");
         Serial.println(temperature); // Print current temp
    }
  else if(part1.equalsIgnoreCase("?"))
    {
         printHelp();
    }
  else
    {
         Serial.println("syntax error"); // Print syntax error
    }

}


//--------------- loop ----------------------------------------------- 
void loop(){
  if (stringComplete) {
   parseCommand(incomingByte);
   //Serial.println(incomingByte); //debug print entered command
   incomingByte = "";
   stringComplete = false;

}}

