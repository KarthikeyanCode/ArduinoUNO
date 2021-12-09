// C++ code
#include<Wire.h>
float gas = 0.00;
float tmp = 0.00;
int crates[3];
float gas_values[3];
float tmp_values[3];
float core[3];
//String gas_string[4];
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  int temp1, temp2, temp;
  for(int j=0; j<3; j++)
  {
    delay(200);
    String gas_string = "";
    String tmp_string = "";
    int i=0;
    Wire.requestFrom(j+1, 14);
    delayMicroseconds(20);
    while(Wire.available())
    {
      if(i<7)
      {
          char g = Wire.read();
          gas_string += g;
      }
      else
      {
          char t = Wire.read();
          tmp_string += t;
      }
      //Serial.println(g);
      //Serial.println(gas);
      i++;
    }
    gas = gas_string.toFloat();
    gas_values[j] = gas;
    tmp = tmp_string.toFloat();
    tmp_values[j] = tmp;
    Serial.print("Gas value ");
    Serial.println(j+1);
    Serial.println(gas);
    Serial.print("tmp value ");
    Serial.println(j+1);
    Serial.println(tmp);
  }//after getting the values over a cycle we can start sorting
  for(int i=0;i<3;i++)
  {
    core[i] = 2*gas_values[i] + tmp_values[i];
  }
  crates[0] = 1;
  crates[1] = 2;
  crates[2] = 3;
  for(int p=0;p<3;p++)
  {
  	 for(int q=p+1; q<3; q++)
     {
     	if(core[q] > core[p])
        {
          temp1 = core[p];
          core[p] = core[q];
          core[q] = temp1;
          temp = crates[p];
          crates[p] = crates[q];
          crates[q] = temp;
        }    
     }
  }
  //now we can transmit the values back to the crates using I2C
  //protocol
  byte rank=0;
  Serial.println();
  Serial.println("Ranks:");
  for(byte k=0;k<3;k++)
  {
    rank = k+1;
    Serial.print(crates[k]);
    Serial.print(" - ");
    Serial.println(rank);
    Wire.beginTransmission(crates[k]);
    delayMicroseconds(20);
    Wire.write(rank);
    Wire.endTransmission();
  }
  delay(100);
}