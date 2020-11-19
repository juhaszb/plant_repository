#ifndef __plants_h__
#define __plants_h__

#include <memory>

#include <vector>
#include <string>

#include "plant.h"

class plants {
    public:
	static std::shared_ptr<plants> get_instance()
	{
		static std::shared_ptr<plants> instance(new plants());

		return instance;
	}
	
	void add_plant(const plant& p)
	{
		plant_list.push_back(p);
	}

	std::vector<plant>& get_plants(void)
	{
		return plant_list;
	}

    private:
	plants() = default;
	plants(const plants &) = delete;
	plants(plants &&) = delete;
	plants &operator=(const plants &) = delete;
	std::vector<plant> plant_list;
};
// std::shared_ptr<plants> plants::instance = nullptr;
#endif
