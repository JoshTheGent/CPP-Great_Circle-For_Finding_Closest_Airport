#include <string>
#include <iostream>
#include <math.h>
#include "Coordinates.hpp"

class GreatCircle
{
public:
	// constructor //
	GreatCircle()
	{
	}
	GreatCircle(InputCoordinates input, FileCoordinates airport)
	{
		InputName = input.Name;
		InputLat = input.Latitude;
		InputLon = input.Longitude;

		FileName = airport.Name;
		FileLat = airport.Latitude;
		FileLon = airport.Longitude;
	}

	GreatCircle(std::string IName, std::string FName, double miles) 
				: InputName(IName), FileName(FName), Miles(miles) 
				{
				}

	// attributes from input //
	std::string InputName;
	double InputLat;
	double InputLon;
	double InputLatR;
	double InputLonR;

	// attributes from file //
	std::string FileName;
	double FileLat;
	double FileLon;
	double FileLatR;
	double FileLonR;

	double Kilometres;
	double Miles;
	double AngleRadians;
	double AngleDegrees;
	bool check;
	

	// Methods //
	void GreatCircleCalculations()
	{
		CheckDegrees();
		if(check)
		{
			Radians();
        	CentralAngle();
        	Distance();
		}

	}

	void CheckDegrees()
	{
	    check = true;

	    if(InputLat < -90.0 || InputLat > 90.0)
	    {
	        check = false;
	    }

	    if(InputLon < -180.0 || InputLon > 180.0)
	    {
	        check = false;
	    }

	    if(FileLat < -90.0 || FileLat > 90.0)
	    {
	        check = false;
	    }

	    if(FileLon < -180.0 || FileLon > 180.0)
	    {
	        check = false;
	    }
	}

	void Radians()
	{
		double DegreesInRadian = 57.29577951;
	    InputLatR = InputLat / DegreesInRadian;
	    InputLonR = InputLon / DegreesInRadian;

	    FileLatR = FileLat / DegreesInRadian;
	    FileLonR = FileLon / DegreesInRadian;
	}

	void CentralAngle()
	{
	    double LongitudesDifference;
	    double DegreesInRadian = 57.29577951;

	    if(InputLonR > FileLonR)
	    {
	        LongitudesDifference = InputLonR - FileLonR;
	    }
	    else
	    {
	        LongitudesDifference = FileLonR - InputLonR;
	    }

	    AngleRadians = acos(sin(InputLatR) * sin(FileLatR) + cos(InputLatR) * cos(FileLatR) * cos(LongitudesDifference));

	    AngleDegrees = AngleRadians * DegreesInRadian;
	}

	void Distance()
	{
		double EarthRadiusKm = 6371;
		double KmPerMile = 1.60934;
	    Kilometres = EarthRadiusKm * AngleRadians;

	    Miles = Kilometres / KmPerMile;
	}
};