#include "Protobuf/generated/PreyCreateData.pb.h"
#include "Network/GamePacket.hpp"

void ProtoSendRecvExample()
{
	// make data
	Data::PreyCreateData prey;
	prey.set_entity_id(15);
	auto pos = prey.mutable_pos();
	pos->set_x(55);
	pos->set_y(34);

	// make packet
	GamePacket<Data::PreyCreateData> packet(prey, 5);


	uint8_t buffer[1000];
	packet.serialize(buffer);
	//send

	// recv

	uint8_t size = packet.getHeader().ByteSize();
	Data::HeaderData hdata;
	google::protobuf::io::CodedInputStream his(buffer, size);
	hdata.MergePartialFromCodedStream(&his);
	
	
	std::cout <<"body size : "<< hdata.size() << "   body type : " << hdata.type() << std::endl;

	Data::PreyCreateData bdata;
	google::protobuf::io::CodedInputStream bis(buffer + GamePacket<int>::HeaderLength, hdata.size());
	bdata.MergePartialFromCodedStream(&bis);

	std::cout << "pos : " << bdata.pos().x() << " "<< bdata.pos().y() <<"  eid : "<< bdata.entity_id() << std::endl;

	
}
