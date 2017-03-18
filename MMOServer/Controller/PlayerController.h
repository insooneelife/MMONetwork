#pragma once
//------------------------------------------------------------------------
//
//  Name:   PlayerController.h
//
//  Desc:   Controller for control player entity.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "ControllerBase.h"
#include <Common/Protobuf/generated/UserData.pb.h>

class PlayerController : public ControllerBase
{
public:
	
	PlayerController();
	virtual ~PlayerController();
	virtual void execute();


private:
};