#pragma once

#include <array>
#include <cstdio>
#include <cassert>

template <typename Strategy, int MaxBodyLength = 100000>
class GamePacket
{
public:

	enum { SizeHeaderLength = 5 };

	enum { TypeHeaderLength = 5 };

	enum { HeaderLength = SizeHeaderLength + TypeHeaderLength };

	enum { BufferLength = MaxBodyLength + HeaderLength };

	GamePacket()
	{
		size_ = 0;
	}

	GamePacket(const GamePacket& copy)
	{
		size_ = copy.size();
		std::memcpy(data_.data(), copy.data(), copy.size());
	}

	inline unsigned char* data()				{ return data_.data(); }
	inline const unsigned char* data() const	{ return data_.data(); }
	inline unsigned char* body()				{ return data_.data() + HeaderLength; }
	inline const unsigned char* body() const	{ return data_.data() + HeaderLength; }
	inline size_t size() const					{ return size_; }
	inline void setSize(size_t size)			{ size_ = size; }

	inline void serializeFrom(int packet_type)
	{
		auto header = Strategy::createHeader(0, packet_type);
		Strategy::serialize(header,	data_.data());
		
		size_ = HeaderLength;
	}

	template <typename BodyType>
	inline void serializeFrom(const BodyType& body, int packet_type)
	{
		assert((Strategy::size(body) < (size_t)BufferLength) && "buffer must be bigger than body!");
		auto header = Strategy::createHeader(Strategy::size(body), packet_type);
		Strategy::serialize(header,	data_.data());
		Strategy::serialize(body, data_.data() + HeaderLength);
		size_ = HeaderLength + Strategy::size(body);
	}

	template <typename HeaderType>
	inline bool parseHeader(HeaderType& out) const
	{
		return Strategy::parse(out, data_.data(), HeaderLength);
	}

	template <typename BodyType>
	inline bool parseBody(BodyType& out, int body_size) const
	{
		return Strategy::parse(out, body(), body_size);
	}

private:
	std::array<unsigned char, BufferLength> data_;
	size_t size_;
};