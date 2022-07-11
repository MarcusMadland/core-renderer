#pragma once

#include "core/app.h"
#include "config.h"

#if CORE_INSTRUMENT
	#include "core/debug/instrumentor.h"	

	#define PROFILE_SCOPE_ONSCREEN(name) Core::InstrumentationTimer timerandlog##__LINE__(name, [&](Core::TimerResult result) { Core::App::Instance().GetTimerResults().push_back(result); }, false)
	#define PROFILE_SCOPE(name) Core::InstrumentationTimer timer##__LINE__(name, [&](Core::TimerResult result) { }, true)
	#define PROFILE_BEGIN_SESSION(name, filepath) Core::Instrumentor::Get().BeginSession(name, filepath)
	#define PROFILE_END_SESSION() Core::Instrumentor::Get().EndSession()
#else
	#define PROFILE_SCOPE_ONSCREEN(name)
	#define PROFILE_SCOPE(name)
	#define PROFILE_BEGIN_SESSION(name, filepath) 
	#define PROFILE_END_SESSION() 
#endif

#if CORE_LOGGER
	#include "core/debug/logger.h"			
#endif