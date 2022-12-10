#pragma once
#include "head.hpp"

interface IRender
{
	virtual ~IRender() = default;
	virtual void InitRender(int argc, char* argv[]) = 0;
	virtual void RenderScene() = 0;
};