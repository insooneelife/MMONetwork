#pragma once

#include "generated/HeaderData.pb.h"

class ProtobufStrategy
{
public:
	typedef Data::HeaderData HeaderType;

	static inline Data::HeaderData createHeader(int body_size, int packet_type)
	{
		Data::HeaderData header;
		header.set_size(body_size);
		header.set_type(packet_type);
		return header;
	}

	template <typename ProtoData>
	static inline size_t size(const ProtoData& data)
	{
		return data.ByteSize();
	}

	template <typename ProtoData>
	static inline bool serialize(const ProtoData& in, unsigned char* out)
	{
		return in.SerializeToArray(out, in.ByteSize());
	}

	template <typename ProtoData>
	static inline bool parse(ProtoData& out, const unsigned char* in, unsigned int len)
	{
		google::protobuf::io::CodedInputStream is(in, len);
		return out.MergePartialFromCodedStream(&is);
	}
};