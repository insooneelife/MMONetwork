#pragma once

#include <memory>
#include <iostream>
#include <map>
#include <queue>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include "Participant.h"


class Room
{
public:
	enum { IDNotSet = 0 };

	inline unsigned int getGenID() const { return gen_id_; }

	void enqueue(const GamePacket<ProtobufStrategy>& packet)
	{
		recv_queue_.emplace(packet);
	}

	bool dequeue(GamePacket<ProtobufStrategy>& packet)
	{
		if (!recv_queue_.empty())
		{
			packet = recv_queue_.front();
			recv_queue_.pop();
			return true;
		}
		return false;
	}

	Room()
	{
		gen_id_ = IDNotSet;
	}

	void insert(std::shared_ptr<Participant> participant)
	{
		++gen_id_;
		std::cout << "new client joined   id : " << gen_id_ << std::endl;
		participant->setID(gen_id_);
		participants_.emplace(gen_id_, participant);
	}

	void remove(std::shared_ptr<Participant> participant)
	{
		std::cout << "client leaved   id : " << participant->getID() << std::endl;
		participants_.erase(participant->getID());
	}

	void sendTo(unsigned int id, unsigned char* buffer, unsigned int length)
	{
		auto it = participants_.find(id);
		if (it != std::end(participants_))
		{
			it->second->send(buffer, length);
		}
	}

	void broadcast(unsigned char* buffer, unsigned int length)
	{
		for (auto participant : participants_)
			participant.second->send(buffer, length);
	}

private:

	std::map<unsigned int, std::shared_ptr<Participant> > participants_;
	unsigned int gen_id_;

	std::queue<GamePacket<ProtobufStrategy> > recv_queue_;
};