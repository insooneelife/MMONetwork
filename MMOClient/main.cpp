#include <iostream>
#include <chrono>
#include "Client/Client.h"
#include "Client/NetworkManagerClient.h"

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char** argv)
{
	
	try
	{
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ "61.77.82.237", "8000" });
		Client c(io_service, endpoint_iterator);
		
		std::thread t([&io_service]() { io_service.run(); });
		t.detach();
		
		while (1)
		{
			std::chrono::duration<double> start = std::chrono::system_clock::now().time_since_epoch();

			c.update();

			std::chrono::duration<double> end = std::chrono::system_clock::now().time_since_epoch();
			
		}

		c.close();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	
	return 0;
}