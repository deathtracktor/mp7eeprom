// various system messages

const char msgStartup[] = 
   "Bosch MP7.0H EEPROM rewriter v1.0\n\r"
   "Danila The Blaster (C) 2011\n\r"\
   "Connect Arduino pins A4 and A5 to 24C02 EEPROM pins 5 and 6\n\r"
   "(two pins in top right IC's corner)"
   "Power up the ECU and hit any key to test connection...";
  
const char msgConnectionFailed[] = 
   "Connection to EEPROM failed. Check your wiring and press any key when ready.";
  
const char msgConnectionEstablished[] = 
   "EEPROM connected.";
  
const char msgMenu[] =
   "*** Select an action:\n\r"
   "[1] Read current EEPROM dump\n\r"
   "[2] Write a clean ECU EEPROM dump\n\r"
   "*** Your choice [1-2]:";
  
const char msgInvalidInput[] = 
    "Invalid input, try again";
    
const char msgRewritingData[] =
    "Updating EEPROM image, please wait";
  
const char msgUpdatingAddress[] =
    "Writing to address ";
    
const char msgFinished[] =
    "EEPROM updated, please verify";

  
