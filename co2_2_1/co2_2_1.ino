#define anologIn            (6)
#define Tcm                 (3)
#define Time_interval       (50)
#define Sample_no           (5)

#define         ZERO_POINT_VOLTAGE           (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         REACTION_VOLTGAE             (0.020) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

/*****************************Globals***********************************************/
float           CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602-3))};   
                                                     //two points are taken from the curve. 
                                                     //with these two points, a line is formed which is
                                                     //"approximately equivalent" to the original curve.
                                                     //data format:{ x, y, slope}; point1: (lg400, 0.324), point2: (lg4000, 0.280) 
                                                     //slope = ( reaction voltage ) / (log400 –log1000) 
void setup()
{
    Serial.begin(9600);                              //UART setup, baudrate = 9600bps           
}

void loop()
{
    int percentage;
    float volts;
    
   
    volts = MGRead(anologIn);
    Serial.print( "SEN0159:" );
    Serial.print(volts); 
    Serial.print( "V           " );
    
    percentage = MGGetPercentage(volts,CO2Curve);
    Serial.print("CO2:");
    if (percentage == -1) {
        Serial.print( "<400" );
    } else {
        Serial.print(percentage);
    }
    Serial.print( "ppm" );  
    Serial.print( "       Time point:" );
    Serial.print(millis());
    Serial.print("\n");
    
    delay(200);
}



/*****************************  MGRead *********************************************
Input:   mg_pin - analog channel
Output:  output of SEN0159
Remarks: This function reads the output of SEN0159
************************************************************************************/ 
float MGRead(int mg_pin)
{
    int i;
    float v=0;

    for (i=0;i<Sample_no;i++) {
        v += analogRead(mg_pin);
        delay(Time_interval);
    }
    v = v/Sample_no ;

    return v;  
}

/*****************************  MQGetPercentage **********************************
Input:   volts   - SEN-000007 output measured in volts
         pcurve  - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm) 
         of the line could be derived if y(MG-811 output) is provided. As it is a 
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic 
         value.
************************************************************************************/ 
int  MGGetPercentage(float volts, float *pcurve)
{
   //if ((volts )>=ZERO_POINT_VOLTAGE) {
     // return -1;
 //  } else { 
      return pow(10, ((volts)-pcurve[1])/pcurve[2]+pcurve[0]);
  // }
}
