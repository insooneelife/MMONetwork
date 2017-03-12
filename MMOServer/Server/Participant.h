#pragma once



class Participant
{
public:
	inline void setID(unsigned int id) { id_ = id; }
	inline unsigned int getID() const { return id_; }

	Participant() : id_(0) {}

	virtual ~Participant() {}
	virtual void send(const unsigned char* buffer, unsigned int length) = 0;

private:
	unsigned int id_;
};