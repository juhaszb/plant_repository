#ifndef __rest_api_h__
#define __rest_api_h__

#include <algorithm>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
class rest_api
{
public:
	explicit rest_api(Pistache::Address addr) : endpoint{std ::make_shared<Pistache::Http::Endpoint>(addr)} 
	{
		auto opts = Pistache::Http::Endpoint::options().threads(1);
		endpoint->init(opts);
	}
protected:
	virtual void setup_routes() = 0;
	Pistache::Rest::Router& get_router()
	{
		return router;
	}

	virtual void record_data(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response)
	{
		response.send(Pistache::Http::Code::Ok, "unimplemented feature");
	}

	void serve()
	{
		setup_routes();
		endpoint->setHandler(router.handler());
		endpoint->serve();
	}
private:
	

	std::shared_ptr<Pistache::Http::Endpoint> endpoint;
	Pistache::Rest::Router router;	
};


#endif
