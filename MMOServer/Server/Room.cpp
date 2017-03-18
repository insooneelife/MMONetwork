#include "Room.h"
#include "NetworkManagerServer.h"

Room::Room()
{
	gen_id_ = IDNotSet;
}

void Room::insert(std::shared_ptr<Participant> participant)
{
	map_mutex_.lock();
	++gen_id_;
	std::cout << "new client joined   id : " << gen_id_ << std::endl;
	participant->setID(gen_id_);
	participants_.emplace(gen_id_, participant);
	map_mutex_.unlock();
}

void Room::remove(std::shared_ptr<Participant> participant)
{
	unsigned int pid = participant->getID();
	std::cout << "client leaved   id : " << pid << std::endl;

	map_mutex_.lock();
	participants_.erase(pid);
	map_mutex_.unlock();

	Data::UserData disconnected;
	disconnected.set_pid(pid);

	auto packet = NetworkManagerServer::createDisconnectedPacket(disconnected);
	enqueue(packet);
}

void Room::sendTo(unsigned int id,const  unsigned char* buffer, unsigned int length)
{
	auto it = participants_.find(id);
	if (it != std::end(participants_))
	{
		it->second->send(buffer, length);
	}
}

void Room::broadcast(const unsigned char* buffer, unsigned int length)
{
	for (auto participant : participants_)
		participant.second->send(buffer, length);
}

void Room::broadcast(
	const unsigned char* buffer,
	unsigned int length,
	const std::set<unsigned int>& ignore)
{
	for (auto participant : participants_)
	{
		auto find = ignore.find(participant.first);
		if (find != std::end(ignore))
			continue;

		participant.second->send(buffer, length);
	}
}

void Room::enqueue(const RecvPacket& packet)
{
	que_mutex_.lock();
	recv_queue_.emplace(packet);
	que_mutex_.unlock();
}
