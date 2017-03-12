#pragma once

#include <memory>
#include <iostream>
#include <map>
#include <queue>
#include <mutex>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include "Participant.h"

class Room
{
public:
	enum { IDNotSet = 0 };

	inline unsigned int getGenID() const { return gen_id_; }

	Room();

	void insert(std::shared_ptr<Participant> participant);
	void remove(std::shared_ptr<Participant> participant);

	void sendTo(unsigned int id, const unsigned char* buffer, unsigned int length);
	void broadcast(const unsigned char* buffer, unsigned int length);

	template<typename NetworkManager>
	void copyPacketsTo(NetworkManager& to)
	{
		que_mutex_.lock();
		to.copyPackets(recv_queue_);
		que_mutex_.unlock();
	}
	void enqueue(const GamePacket<ProtobufStrategy>& packet);

private:
	std::mutex map_mutex_;
	std::map<unsigned int, std::shared_ptr<Participant> > participants_;
	unsigned int gen_id_;

	std::mutex que_mutex_;
	std::queue<GamePacket<ProtobufStrategy> > recv_queue_;

	
};