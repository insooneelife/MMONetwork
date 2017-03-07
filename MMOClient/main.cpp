#include <iostream>
#include "Client.h"

using namespace std;
using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ "61.77.82.237", "8000" });
		Client c(io_service, endpoint_iterator);

		std::thread t([&io_service]() { io_service.run(); });

		while (1)
		{
		}

		c.close();
		t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}