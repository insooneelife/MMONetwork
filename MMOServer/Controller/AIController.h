#pragma once
//------------------------------------------------------------------------
//
//  Name:   AIController.h
//
//  Desc:   Controller for AI entity.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "ControllerBase.h"


class AIController : public ControllerBase
{
public:
	AIController();

	virtual ~AIController();

	virtual void execute();

private:
};