#include "EntityManager.h"

//std::unique_ptr<EntityManager> EntityManager::instance = nullptr;

//void EntityManager::staticInit()
//{
//	instance.reset(new EntityManager());
//}

EntityManager::EntityManager()
{}

Entity* EntityManager::getEntity(unsigned int id) const
{
	auto ent = _entities.find(id);

	if (std::end(_entities) != ent)
	{
		return ent->second;
	}

	return nullptr;
}

bool EntityManager::exists(unsigned int id) const
{
	auto ent = _entities.find(id);

	if (std::end(_entities) != ent)
	{
		return true;
	}

	return false;
}

void EntityManager::registerEntity(Entity* entity)
{
	_entities.emplace(entity->getID(), entity);
}

void EntityManager::unregisterEntity(Entity* entity)
{
	_entities.erase(entity->getID());
}

void EntityManager::dispatchMsg(
	unsigned int senderId,
	unsigned int receiverId,
	Message::MsgType msgType,
	void* extraInfo)
{
	// Get a pointer to the receiver
	Entity* receiver = getEntity(receiverId);

	// Make sure the receiver is valid
	if (receiver == nullptr)
		return;

	// Create the telegram
	Message msg = Message(senderId, receiverId, msgType, extraInfo);

	// Send the telegram to the recipient
	discharge(receiver, msg);
}

// This method is utilized by DispatchMsg or DispatchDelayedMessages.
// This method calls the message handling member function of the receiving
// entity, pReceiver, with the newly created telegram
void EntityManager::discharge(Entity* receiver, const Message& msg)
{
	if (receiver == nullptr)
		return;

	if (!receiver->handleMessage(msg))
	{}
}
