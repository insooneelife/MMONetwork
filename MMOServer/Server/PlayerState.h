#pragma once
//------------------------------------------------------------------------
//
//  Name:   PlayerState.h
//
//  Desc:   Controller for control player entity.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include <Common/Protobuf/generated/UserData.pb.h>

class PlayerState
{
public:
	inline const Data::UserData getUserData() const { return user_data_; }
	inline void setUserData(const Data::UserData& user_data) { user_data_ = user_data; }

	PlayerState();
	virtual ~PlayerState();


private:
	Data::UserData user_data_;
};