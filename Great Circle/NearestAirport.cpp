#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "GreatCircle.hpp"

int main()
{

	int count = 0;
	
	// READ IN FILE airport.dat //
	std::ifstream AirportFile;
	AirportFile.open("airports.dat");
	if(!AirportFile.is_open())
	{
		std::cout << "Could not open the file, Exiting" << std::endl;
		return 1;
	}
	// get the number of inputs we need to allocate for //
	std::string lineCount;
	while(std::getline(AirportFile,lineCount))
	{
		count++;
	}
	AirportFile.close();

	// doing the read in again, because errors if i dont //
	// READ IN FILE airport.dat //
	AirportFile.open("airports.dat");
	if(!AirportFile.is_open())
	{
		std::cout << "Could not open the file, Exiting" << std::endl;
		return 1;
	}
	// TO STORE OUR AIRPORTS //
	FileCoordinates Airports[count];
	
	std::string line;
	int i = 0;
	while(std::getline(AirportFile,line))
	{
		std::stringstream ss(line);

		// everything on a line in order //
		std::string AirportId, 
					Name, City, Country, IATA, ICAO,
					latS, lonS, altS,
					Timezone, DST, Tz, Type, Source;
		std::string buffer;

		// getting everything from the file line //
		std::getline(ss,AirportId,'\"');
		std::getline(ss,Name,'\"'); // need this
		std::getline(ss,buffer,','); //helps with commas in the name
		std::getline(ss,buffer,'\"'); //helps with commas in the name
		std::getline(ss,City,'\"');
		std::getline(ss,buffer,','); //helps with commas in the name
		std::getline(ss,Country,',');
		std::getline(ss,IATA,',');
		std::getline(ss,ICAO,',');
		std::getline(ss,latS,','); // need this
		std::getline(ss,lonS,','); // need this
		std::getline(ss,altS,','); // need this
		std::getline(ss,Timezone,',');
		std::getline(ss,DST,',');
		std::getline(ss,Tz,',');
		std::getline(ss,Type,',');
		std::getline(ss,Source,',');

		double lat = std::stod(latS);
		double lon = std::stod(lonS);
		double alt = std::stod(altS);

		FileCoordinates Airport(Name, lat, lon, alt);
		
		Airports[i].Name = Airport.Name;
		Airports[i].Latitude = Airport.Latitude;
		Airports[i].Longitude = Airport.Longitude;
		Airports[i].Altitude = Airport.Altitude;
		
		i++;
	}

	AirportFile.close();


	// Getting User Input //
	while(1)
	{
		// USER INPUT VARS //
	    double InputLongitude;
	    double InputLatitude;
	    double InputAltitude;
	    std::string InputName = "User Input";

	    // PROMPT USER //
	    std::cout << "Enter coordinates Latitude Longitude Altitude" << std::endl;
	    std::cin >> InputLatitude >> InputLongitude >> InputAltitude;
	    
	    // Leave Program if all input == -1 //
	    if(InputLatitude == -1 && InputLongitude == -1 && InputAltitude == -1)
	    {
	    	break;
	    }
	    // construct input //
	    InputCoordinates Input(InputName, InputLatitude, InputLongitude, InputAltitude);
	
	    GreatCircle GreatCircles[count];

	    for(int i = 0; i < count; i++)
	    {
	    	// taking two coordinates and running calculations //
	    	GreatCircle greatcircle(Input, Airports[i]);
	    	greatcircle.GreatCircleCalculations();
	    	GreatCircles[i].InputName = greatcircle.InputName;
	    	GreatCircles[i].FileName = greatcircle.FileName;
	    	GreatCircles[i].Miles = greatcircle.Miles;
	    }

	    // this object will be used to check for the closest //
	    // setting object to initialize //
	    GreatCircle Closest[5]
	    {
	    	{GreatCircles[0].InputName , GreatCircles[0].FileName, GreatCircles[0].Miles},
	    	{GreatCircles[1].InputName , GreatCircles[1].FileName, GreatCircles[1].Miles},
	    	{GreatCircles[2].InputName , GreatCircles[2].FileName, GreatCircles[2].Miles},
	    	{GreatCircles[3].InputName , GreatCircles[3].FileName, GreatCircles[3].Miles},
	    	{GreatCircles[4].InputName , GreatCircles[4].FileName, GreatCircles[4].Miles},
	    };
	    for(int j = 0; j < count; j++)
	    {
	    	if(GreatCircles[j].Miles < Closest[0].Miles)
	    	{
	    		//update last element
	    		Closest[4].InputName = Closest[3].InputName;
	    		Closest[4].FileName = Closest[3].FileName;
	    		Closest[4].Miles = Closest[3].Miles;
	    		
	    		//update 4th element
	    		Closest[3].InputName = Closest[2].InputName;
	    		Closest[3].FileName = Closest[2].FileName;
	    		Closest[3].Miles = Closest[2].Miles;

	    		//update 3rd element
	    		Closest[2].InputName = Closest[1].InputName;
	    		Closest[2].FileName = Closest[1].FileName;
	    		Closest[2].Miles = Closest[1].Miles;

	    		//update 2nd element
	    		Closest[1].InputName = Closest[0].InputName;
	    		Closest[1].FileName = Closest[0].FileName;
	    		Closest[1].Miles = Closest[0].Miles;

	    		// update the first element //
	    		Closest[0].InputName = GreatCircles[j].InputName;
	    		Closest[0].FileName = GreatCircles[j].FileName;
	    		Closest[0].Miles = GreatCircles[j].Miles;
	    	}
	    	else if(GreatCircles[j].Miles < Closest[1].Miles || GreatCircles[j].Miles == Closest[0].Miles)
	    	{
	    		//update last element
	    		Closest[4].InputName = Closest[3].InputName;
	    		Closest[4].FileName = Closest[3].FileName;
	    		Closest[4].Miles = Closest[3].Miles;
	    		
	    		//update 4th element
	    		Closest[3].InputName = Closest[2].InputName;
	    		Closest[3].FileName = Closest[2].FileName;
	    		Closest[3].Miles = Closest[2].Miles;

	    		//update 3rd element
	    		Closest[2].InputName = Closest[1].InputName;
	    		Closest[2].FileName = Closest[1].FileName;
	    		Closest[2].Miles = Closest[1].Miles;

	    		//update 2nd element
	    		Closest[1].InputName = GreatCircles[j].InputName;
	    		Closest[1].FileName = GreatCircles[j].FileName;
	    		Closest[1].Miles = GreatCircles[j].Miles;
	    	}
	    	else if(GreatCircles[j].Miles < Closest[2].Miles || GreatCircles[j].Miles == Closest[1].Miles)
	    	{
	    		//update last element
	    		Closest[4].InputName = Closest[3].InputName;
	    		Closest[4].FileName = Closest[3].FileName;
	    		Closest[4].Miles = Closest[3].Miles;
	    		
	    		//update 4th element
	    		Closest[3].InputName = Closest[2].InputName;
	    		Closest[3].FileName = Closest[2].FileName;
	    		Closest[3].Miles = Closest[2].Miles;

	    		//update 3rd element
	    		Closest[2].InputName = GreatCircles[j].InputName;
	    		Closest[2].FileName = GreatCircles[j].FileName;
	    		Closest[2].Miles = GreatCircles[j].Miles;
	    	}
	    	else if(GreatCircles[j].Miles < Closest[3].Miles || GreatCircles[j].Miles == Closest[2].Miles)
	    	{
	    		//update last element
	    		Closest[4].InputName = Closest[3].InputName;
	    		Closest[4].FileName = Closest[3].FileName;
	    		Closest[4].Miles = Closest[3].Miles;
	    		
	    		//update 4th element
	    		Closest[3].InputName = GreatCircles[j].InputName;
	    		Closest[3].FileName = GreatCircles[j].FileName;
	    		Closest[3].Miles = GreatCircles[j].Miles;
	    	}
	    	else if(GreatCircles[j].Miles < Closest[4].Miles || GreatCircles[j].Miles == Closest[3].Miles)
	    	{
	    		//update last element
	    		Closest[4].InputName = GreatCircles[j].InputName;
	    		Closest[4].FileName = GreatCircles[j].FileName;
	    		Closest[4].Miles = GreatCircles[j].Miles;
	    	}
	    }
		// Display result //
	    std::cout << "The closest 5 airports are:" << std::endl;
	    std::cout << "1st: " << "from " << Closest[0].InputName << " to " << Closest[0].FileName << " with a distance: " << Closest[0].Miles << " Miles" << std::endl; 
		std::cout << "2nd: " << "from " << Closest[1].InputName << " to " << Closest[1].FileName << " with a distance: " << Closest[1].Miles << " Miles" << std::endl; 
		std::cout << "3rd: " << "from " << Closest[2].InputName << " to " << Closest[2].FileName << " with a distance: " << Closest[2].Miles << " Miles" << std::endl; 
		std::cout << "4th: " << "from " << Closest[3].InputName << " to " << Closest[3].FileName << " with a distance: " << Closest[3].Miles << " Miles" << std::endl; 
		std::cout << "5th: " << "from " << Closest[4].InputName << " to " << Closest[4].FileName << " with a distance: " << Closest[4].Miles << " Miles" << std::endl << std::endl; 
	}
}