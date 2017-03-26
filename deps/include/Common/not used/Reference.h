#pragma once
//------------------------------------------------------------------------
//
//  Name:		ReferenceMap.h
//
//  Desc:		For help making argument of reference type.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------
#include <random>
#include <map>

#define Stringify(x) #x
#define ToString(x) Stringify(x) 

class Reference;
class IReference
{
public:
	virtual const Reference& getReference() const = 0;
};

class Reference
{
private:
	static std::map<unsigned int, IReference*> references_;
	static unsigned int gen_id_;

public:
	static IReference* queryReference(unsigned int id)
	{
		auto it = references_.find(id);
		if (it != std::end(references_))
		{
			return it->second;
		}
		return nullptr;
	}

	inline unsigned int getID() const { return id_; }
	Reference(IReference* ref)
		:
		id_(gen_id_++)
	{
		references_.emplace(id_, ref);
	}

	~Reference()
	{
		references_.erase(id_);
	}

private:
	unsigned int id_;
};

