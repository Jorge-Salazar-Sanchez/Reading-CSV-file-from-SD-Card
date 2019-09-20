/*
The following code searches for a specific date introduced by the user in a CSV file
logged by different sensors. The code checks if the date exists and if so it prints 
out the reading values associated with that date

Created, edited, and modified Jorge Salazar Sanchez
in June 2019
*/

#include <SPI.h>
#include <SD.h>
#include <string.h>

File myFile;

int arrayPointer = 0;
int q=0;
int n=0;

long month_=0;
long day_=0;
long year_=0;

char* strings[20];

String my_date;



///////////////////////////////////////////////////////////////////
// Setting up Communications (SETUP)
//////////////////////////////////////////////////////////////////

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


///////////////////////////////////////////////////////////////////
// Setting up Serial Port and the SD Card
//////////////////////////////////////////////////////////////////

  Serial.print(F("Initializing SD card..."));
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  

  if (!SD.begin(10)) {
    Serial.println(F("initialization failed!"));
    return;
  }
  Serial.println(F("initialization done."));
  delay(2000);

Serial.println("");



///////////////////////////////////////////////////////////////////
// Searching for the date
//////////////////////////////////////////////////////////////////

// Function that returns the introduced date by the user
my_date = readingsdate();

delay(3000);

Serial.println(F("These are the readings related to the selected date:"));
Serial.println("");




    // re-open the file for reading:
  myFile = SD.open("421pm60.csv");

  if (myFile) {
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {

    // Place the reading value in a String variable
      String line1 = myFile.readStringUntil('\n');
      String line2 = line1;
      
    // Break a string value into tokens
      char* a = (char*) line1.c_str();
      //char* c = a;
      char* b = NULL;
      b = strtok(a, ",");    

     // Place the tokens into a characters array
      while(b != NULL){
        
            strings[arrayPointer] = b;
            arrayPointer++;
            b = strtok(NULL, ",");
     }    

     /////////////////////////////////////////////////////////////////////////
     // Convert each character array value into string values to compare it //
     // with the introduced value (date) by the user //
     /////////////////////////////////////////////////////////////////////////
      
      for (n=0; n<arrayPointer; n++){

        String str(strings[n]);
   
          if (str.equals(my_date)){
              Serial.println(line2);  
          }else{
           }
      }

     ///////////////////////////////////////////
     //// Clear (initialize) existing array ////
     ///////////////////////////////////////////
      memset(strings,0, sizeof(strings));
             arrayPointer = 0;
             n = 0;
   }
}

 
  else {
    // If the file didn't open, print an error:
    Serial.println(F("error opening test.txt"));
  }

    // Close the file
    myFile.close();
    Serial.println("");
    Serial.println(F("finished"));
}




void loop() {

//Nothing to do

}




///////////////////////////////////////////////////////////////////////
// Function that asks for and returns the date introduced by the user 
///////////////////////////////////////////////////////////////////////

String readingsdate () {
  
// Introduce the MONTH:
Serial.println(F("Introduce the MONTH"));

while (Serial.available()==0);
month_ = Serial.parseInt();  
Serial.println(month_);


// Ckeck and validation of the MONTH:
while ((month_>12) || (month_==0)) {

        Serial.println(F("Please, Introduce the MONTH again. This is not a valid MONTH"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        month_ = Serial.parseInt();  

}

        Serial.println("");
        Serial.print(F("You introduced the month = "));
        Serial.println(month_);
        Serial.println("");
        delay(2000);

// Introduce the DAY:
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        Serial.println(F("Introduce the DAY"));
        while (Serial.available()==0);
        day_ = Serial.parseInt();  

Serial.println(day_);


// Ckeck and validation of the DAY:
while ((day_ > 31) || (day_ == 0)) {

        Serial.println(F("Please, Introduce the DAY again. This is not a valid DAY"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        day_ = Serial.parseInt();  

}

        Serial.println("");
        Serial.print(F("You introduced the DAY = "));
        Serial.println(day_);
        Serial.println("");
        delay(2000);

// Introduce the YEAR:
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        Serial.println(F("Introduce the YEAR"));
        while (Serial.available()==0);
        year_ = Serial.parseInt();  

Serial.println(year_);


// Ckeck and validation of the YEAR:
while ((year_ > 2019) || (year_ < 2015) || (year_ == 0)) {

        Serial.println(F("Please, Introduce the YEAR again. This is not a valid YEAR"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        year_ = Serial.parseInt();  

}

        Serial.println("");
        Serial.print(F("You introduced the YEAR = "));
        Serial.println(year_);
        Serial.println("");


delay(2000);


// Print out and return the date introduced by the user:
String mydate = ((String)month_+"/"+day_+"/"+year_);
Serial.print(F("The date to search is: "));
Serial.println(mydate);
Serial.println("");

return mydate;

}


