
#include <SPI.h>
#include <MCP23x17.h>
#include <MCP23S17.h>
#include <OneWire.h>


String incomingByte; 
int temperature = 0;
long lastUpdateTime = 0; // last update variable
const int TEMP_UPDATE_TIME = 1000; // update temp pereodically


CMCP23S17 mcp23_1; //Select address of chip "0 0 0"
OneWire ds(9); // Select pin of OneWire



//=== function to print the command list:  ===========================
void printHelp(void){
  Serial.println("--- Command list: ---");
  Serial.println("? -> Print this HELP");
  Serial.println("STATUS -> All ports status");
  Serial.println("ON_ALL -> Activate all ports");
  Serial.println("OFF_ALL -> Deactivate all port");
  Serial.println("port_#_on -> Port #(1-16) On  \"activate\"");
  Serial.println("port_#_off -> Port #(1-16) Off  \"deactivate\"");
  Serial.println("port_#_stat -> Port #(1-16) State  \"status\""); 
  Serial.println("RESET -> Reset Arduino controller");
  Serial.println("TEMP -> Show Ambient temperature \"°C\"");   
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
  mcp23_1.init(10, 0);

  for (int i=0; i<16; i++) {
    mcp23_1.pinMode(i, OUTPUT);  //Set all ports to OUTPUT
  }
  printHelp();          // Print the command list.
}

//=== RESET board function:  ===========================
void(* resetFunc) (void) = 0; //declare reset function @ address 0


//--------------- loop ----------------------------------------------- 
void loop(){
 if (Serial.available() > 0) { 
   incomingByte = Serial.readString(); //Read data from UART to string
   Serial.flush();                     //Flush data in serial port
   //Serial.println(incomingByte);     //Print entered command
   if (incomingByte == "?")
    {
         printHelp();
    }
   if (incomingByte == "RESET")
    {
         resetFunc();  //call reset
         delay(100);
         Serial.println("this never happens :D");    
    }
   if (incomingByte == "TEMP")
    {
         detectTemperature(); // call the pope
         Serial.print("temp=");
         Serial.println(temperature); // Print current temp
    }
   if (incomingByte == "STATUS")
    {
        Serial.println("--- STATUS: ---");
         for (int i=0; i<16; i++) 
          {
            Serial.print("port=");
            Serial.print(i+1);
            Serial.print(",status=");
            Serial.println(mcp23_1.digitalRead(i));
            
          }
    }    
   if (incomingByte == "ON_ALL")
    {
            for (int i=0; i<16; i++) {
              mcp23_1.digitalWrite(i, HIGH);
              delay(100);       //little timeout to protect power supply from high load.
            }
            Serial.println("OK");
    }    
   if (incomingByte == "OFF_ALL")
    {
            for (int i=0; i<16; i++) {
              mcp23_1.digitalWrite(i, LOW);
              delay(100);      //little timeout
            }
            Serial.println("OK");
    }    

   if (incomingByte == "port_1_on")
    {
            mcp23_1.digitalWrite(0, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_2_on")
    {
            mcp23_1.digitalWrite(1, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_3_on")
    {
            mcp23_1.digitalWrite(2, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_4_on")
    {
            mcp23_1.digitalWrite(3, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_5_on")
    {
            mcp23_1.digitalWrite(4, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_6_on")
    {
            mcp23_1.digitalWrite(5, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_7_on")
    {
            mcp23_1.digitalWrite(6, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_8_on")
    {
            mcp23_1.digitalWrite(7, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_9_on")
    {
            mcp23_1.digitalWrite(8, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_10_on")
    {
            mcp23_1.digitalWrite(9, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_11_on")
    {
            mcp23_1.digitalWrite(10, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_12_on")
    {
            mcp23_1.digitalWrite(11, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_13_on")
    {
            mcp23_1.digitalWrite(12, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_14_on")
    {
            mcp23_1.digitalWrite(13, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_15_on")
    {
            mcp23_1.digitalWrite(14, HIGH);
            Serial.println("OK");
    }
   if (incomingByte == "port_16_on")
    {
            mcp23_1.digitalWrite(15, HIGH);
            Serial.println("OK");
    }
    //Set LOW state per port block
   if (incomingByte == "port_1_off")
    {
            mcp23_1.digitalWrite(0, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_2_off")
    {
            mcp23_1.digitalWrite(1, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_3_off")
    {
            mcp23_1.digitalWrite(2, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_4_off")
    {
            mcp23_1.digitalWrite(3, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_5_off")
    {
            mcp23_1.digitalWrite(4, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_6_off")
    {
            mcp23_1.digitalWrite(5, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_7_off")
    {
            mcp23_1.digitalWrite(6, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_8_off")
    {
            mcp23_1.digitalWrite(7, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_9_off")
    {
            mcp23_1.digitalWrite(8, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_10_off")
    {
            mcp23_1.digitalWrite(9, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_11_off")
    {
            mcp23_1.digitalWrite(10, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_12_off")
    {
            mcp23_1.digitalWrite(11, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_13_off")
    {
            mcp23_1.digitalWrite(12, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_14_off")
    {
            mcp23_1.digitalWrite(13, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_15_off")
    {
            mcp23_1.digitalWrite(14, LOW);
            Serial.println("OK");
    }
   if (incomingByte == "port_16_off")
    {
            mcp23_1.digitalWrite(15, LOW);
            Serial.println("OK");
    }
    //Read status per port block
   if (incomingByte == "port_1_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(0));
    }
   if (incomingByte == "port_2_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(1));
    }
   if (incomingByte == "port_3_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(2));
    }
   if (incomingByte == "port_4_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(3));
    }
   if (incomingByte == "port_5_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(4));
    }
   if (incomingByte == "port_6_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(5));
    }
   if (incomingByte == "port_7_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(6));
    }
   if (incomingByte == "port_8_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(7));
    }
   if (incomingByte == "port_9_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(8));
    }
   if (incomingByte == "port_10_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(9));
    }
   if (incomingByte == "port_11_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(10));
    }
   if (incomingByte == "port_12_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(11));
    }
   if (incomingByte == "port_13_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(12));
    }
   if (incomingByte == "port_14_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(13));
    }
   if (incomingByte == "port_15_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(14));
    }
   if (incomingByte == "port_16_stat")
    {
            Serial.print("status=");
            Serial.println(mcp23_1.digitalRead(15));
    }


}}
