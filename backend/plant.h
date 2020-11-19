#ifndef __plant_h__
#define __plant_h__

#include <string>
#include <utility>

class plant {
    public:
	plant(std::string name, std::pair<int, int> location,
	      unsigned int water_needs, std::pair<int, int> light_needs,
	      std::pair<int, int> temperature, std::pair<int, int> soil_needs, int id, int sensor)
		: name{ name }, location{ location },
		  water_needs{ water_needs }, light_needs{ light_needs },
		  temperature{ temperature }, soil_needs{ soil_needs }, id{id}, sensor{sensor} 
	{

	}

	int get_sensor(void) const
	{
		return sensor;
	}

	std::pair<int,int> get_location(void) const 
	{
		return location;
	}

	std::string get_name(void) const 
	{
		return name;
	}

    private:
	std::string name;
	std::pair<int, int> location;
	unsigned int water_needs;
	std::pair<int, int> light_needs;
	std::pair<int, int> temperature;
	std::pair<int, int> soil_needs;
	int id;
	int sensor; // We might need to use a vector here, more sensor 
};

#endif
