/*
Copyright (C) 2019 Blue Mountains GmbH

This program is free software: you can redistribute it and/or modify it under the terms of the Onset
Open Source License as published by Blue Mountains GmbH.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the Onset Open Source License for more details.

You should have received a copy of the Onset Open Source License along with this program. If not,
see https://bluemountains.io/Onset_OpenSourceSoftware_License.txt
*/

#pragma once

#include "LuaTypes.hpp"

namespace Onset
{
	class IBaseInterface
	{
	public:
	};

	class IServerPlugin : public IBaseInterface
	{
	public:
		// Print message to console and server log file
		virtual void Log(const char *format, ...) = 0;

		// Get passed seconds since server start
		virtual double GetTimeSeconds() = 0;

		// Get server frame time
		virtual float GetDeltaSeconds() = 0;

		// Call an event in Lua which was defined by AddEvent
		virtual bool CallEvent(const char *EventName, Lua::LuaArgs_t *Arguments = nullptr) = 0;

		// Call a remote event
		virtual void CallRemoteEvent(const char *EventName, Lua::LuaArgs_t *Arguments = nullptr) = 0;

		virtual ~IServerPlugin() { }
	};

	class Plugin
	{
	protected:
		static IServerPlugin *_instance;

	public:
		Plugin() = default;
		~Plugin() = default;

		inline static void Init(IBaseInterface *base)
		{
			_instance = static_cast<IServerPlugin *>(base);
		}

		inline static IServerPlugin *Get()
		{
			return _instance;
		}

		inline static void Destroy()
		{
			if (_instance != nullptr)
			{
				delete _instance;
				_instance = nullptr;
			}
		}
	};
}
