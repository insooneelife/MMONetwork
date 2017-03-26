#pragma once
//------------------------------------------------------------------------
//
//  Name:		Arguments.h
//
//  Desc:		For store arguments in one argument
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <iostream>
#include <map>
#include <memory>
#include <SDL/SDL.h>
#include "Reference.h"
#include "Protobuf/generated/Base.pb.h"
#include "Math/Vec2.h"

class Arguments
{
public:
	unsigned int calcDataSize() const 
	{
		unsigned int size = 0;
		for (auto e = std::begin(arguments_); e != std::end(arguments_); ++e)
		{
			size += sizeof(e->first);
			size += sizeof(e->second);
			//size += e->second->ByteSize();
		}
		return size;
	}

	// add
	void add(const std::string& name, bool data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_bool_(data);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, char data) 
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_char_(data);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, int data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_int32(data);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, long long int data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_int64(data);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, unsigned int data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_uint32(data);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, unsigned long long int data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_uint64(data);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, float data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_float_(data);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, double data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_double_(data);
	}

	void add(const std::string& name, const Vec2& data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		auto vec2 = pdata->mutable_vec2();
		vec2->set_x(data.x);
		vec2->set_y(data.y);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, const SDL_Color& data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		auto color = pdata->mutable_color();
		color->set_a(data.a);
		color->set_r(data.r);
		color->set_g(data.g);
		color->set_b(data.b);
		arguments_.emplace(name, std::move(pdata));
	}

	void add(const std::string& name, IReference* data)
	{
		std::unique_ptr<Data::PrimitiveData> pdata(new Data::PrimitiveData());
		pdata->set_reference(data->getReference().getID());
		arguments_.emplace(name, std::move(pdata));
	}

	// query
	bool query(const std::string& name, bool& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
			data = it->second->bool_();
	}

	bool query(const std::string& name, char& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
			data = it->second->char_();
	}

	bool query(const std::string& name, int& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
			data = it->second->int32();
	}

	bool query(const std::string& name, long long int& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
			data = it->second->int64();
	}

	bool query(const std::string& name, unsigned int& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
			data = it->second->uint32();
	}

	bool query(const std::string& name, unsigned long long int& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
			data = it->second->uint64();
	}

	bool query(const std::string& name, float& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
			data = it->second->float_();
	}

	bool query(const std::string& name, double& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
			data = it->second->double_();
	}

	bool query(const std::string& name, Vec2& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
		{
			data.x = it->second->vec2().x();
			data.y = it->second->vec2().y();
		}
	}

	bool query(const std::string& name, SDL_Color& data) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return false;
		else
		{
			data.a = it->second->color().a();
			data.r = it->second->color().r();
			data.g = it->second->color().g();
			data.b = it->second->color().b();
		}
	}

	IReference* query(const std::string& name) const
	{
		auto it = arguments_.find(name);
		if (it == std::end(arguments_))
			return nullptr;
		else
		{
			return Reference::queryReference(it->second->reference());
		}
	}

private:
	std::map<std::string, std::unique_ptr<Data::PrimitiveData> > arguments_;
};
