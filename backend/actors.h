#ifndef __actors_h__
#define __actors_h__

#include <memory>
#include <pistache/net.h>
#include <vector>
#include <string>

#include "actor.h"

class actors {
    public:
	static std::shared_ptr<actors> get_instance()
	{
		static std::shared_ptr<actors> instance(new actors());

		return instance;
	}

	void add_actor(int id, Pistache::Address addr, int port)
	{
		actor_list.push_back(actor{ id, addr, port });
	}

	std::vector<int> get_actor_id_list(void)
	{
		std::vector<int> ids;
		for (auto& s : actor_list) {
			ids.push_back(s.get_id());
		}
		return ids;
	}

	int get_value_id(int id)
	{
		for (auto& s : actor_list) {
			if (s.get_id() == id)
				return s.get_value();
		}
		return 0;
	}
	void set_value_id(int id, int value)
	{
		for (auto& s : actor_list) {
			if (s.get_id() == id) {
				s.set_value(value);
			}
		}
	}

    private:
	actors() = default;
	actors(const actors &) = delete;
	actors(actors &&) = delete;
	actors &operator=(const actors &) = delete;
	std::vector<actor> actor_list;
};
// std::shared_ptr<actors> actors::instance = nullptr;
#endif
