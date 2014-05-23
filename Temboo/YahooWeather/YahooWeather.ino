#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int numRuns = 1;   // Execution count, so this doesn't run forever
int maxRuns = 10;   // Maximum number of times the Choreo should be executed

  // For debugging, wait until the Console console is connected.
void setup() {
    Bridge.begin();
    Console.begin();
    while(!Console);
}

void loop() {
  if (numRuns <= maxRuns) {
    Console.println("Running GetWeatherByAddress - Run #" + String(numRuns++));
    
    TembooChoreo GetWeatherByAddressChoreo;

    // Invoke the Temboo client
    GetWeatherByAddressChoreo.begin();
    
    // Set Temboo account credentials
    GetWeatherByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetWeatherByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetWeatherByAddressChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    GetWeatherByAddressChoreo.addInput("Units", "c");
    GetWeatherByAddressChoreo.addInput("Address", "Lincoln Uk");
    
    // Identify the Choreo to run
    GetWeatherByAddressChoreo.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");
    
    // Run the Choreo; when results are available, print them to Console
    GetWeatherByAddressChoreo.run();
    
    while(GetWeatherByAddressChoreo.available()) {
      char c = GetWeatherByAddressChoreo.read();
      Console.print(c);
    }
    GetWeatherByAddressChoreo.close();
  }

  Console.println("Waiting...");
  delay(30000); // wait 30 seconds between GetWeatherByAddress calls
}
