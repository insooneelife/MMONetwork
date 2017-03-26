#pragma once
//------------------------------------------------------------------------
//
//  Name:		GenericFactory.h
//
//  Desc:		For create entity with no coupling.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------
#include <map>
#include <functional>
#include "Entity/Entity.h"

class GenericFactory
{
public:
	static GenericFactory& getInstance()
	{
		static GenericFactory instance;
		return instance;
	}

	template<class EntityType>
	void addCreateMethod()
	{
		auto class_id = typeid(EntityType).hash_code();
		auto it = create_map_.find(class_id);
		assert(it == std::end(create_map_) && "classID does not matches!");

		create_map_[class_id] = EntityType::create;
	}

	template<typename EntityType>
	Entity* create(Entity::Args* args)
	{
		size_t class_id = typeid(EntityType).hash_code();
		std::cout <<"template : "<< class_id << std::endl;

		auto it = create_map_.find(class_id);
		if (it == std::end(create_map_))
			return nullptr;
		else
		{
			return it->second(args);
		}
	}

	Entity* create(size_t class_id, Entity::Args* args)
	{
		std::cout << "non : " << class_id << std::endl;

		auto it = create_map_.find(class_id);
		if (it == std::end(create_map_))
			return nullptr;
		else
		{
			return it->second(args);
		}
	}

	// base function
	template<typename EntityType>
	static void addCreateMethods(EntityType* e) 
	{
		GenericFactory::getInstance().addCreateMethod<EntityType>();
	}

	// recursive variadic function
	template<typename EntityType, typename... EntityTypes>
	static void addCreateMethods(EntityType* e, EntityTypes*... etypes) 
	{
		GenericFactory::getInstance().addCreateMethod<EntityType>();
		addCreateMethods(etypes...);
	}

private:
	GenericFactory() {}
	std::map<size_t, std::function<Entity*(Entity::Args*)>> create_map_;
};