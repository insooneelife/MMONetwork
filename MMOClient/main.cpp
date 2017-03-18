#include <iostream>
#include <chrono>
#include "Client/Client.h"
#include "Client/NetworkManagerClient.h"

using namespace std;
using boost::asio::ip::tcp;
using namespace std::chrono;

int main(int argc, char** argv)
{
	// for game time
	const double MsPerUpdate = 0.02;
	const double ReplicateTerm = 0.2;
	duration<double> prev = system_clock::now().time_since_epoch();
	duration<double> delta(0);
	duration<double> lag(0);
	double accum_delta = 0;

	try
	{
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ "61.77.82.237", "8000" });
		//Client client(io_service, endpoint_iterator);
		
		std::vector<std::unique_ptr<Client> > clients;
		for (int i = 0; i < 200; i++)
		{
			clients.emplace_back(new Client(io_service, endpoint_iterator));
		}

		for (int i = 0; i < 1; i++)
		{
			std::thread t([&io_service]() { io_service.run(); });
			t.detach();
		}
		
		while (1)
		{
			// for game time
			duration<double> current = system_clock::now().time_since_epoch();
			delta = current - prev;
			prev = current;
			lag += delta;

			while (lag.count() >= MsPerUpdate)
			{
				// update
				lag -= duration<double>(MsPerUpdate);
			}

			// render


			// network io
			//client.processRecv();
			for (auto c = std::begin(clients); c != std::end(clients); ++c)
			{
				(*c)->processRecv();
			}
			
			accum_delta += delta.count();
			if (accum_delta > ReplicateTerm)
			{
				//client.processSend();
				for (auto c = std::begin(clients); c != std::end(clients); ++c)
				{
					(*c)->processSend();
				}

				accum_delta = 0;
			}

		}

		//client.close();
		for (auto c = std::begin(clients); c != std::end(clients); ++c)
		{
			(*c)->close();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	
	return 0;
}