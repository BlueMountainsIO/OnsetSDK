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

#include <string>
#include <vector>

#include "LuaTable.hpp"
#include "LuaValue.hpp"
#include "PluginApi.hpp"


namespace Lua
{
	namespace _internal
	{
		class EventArguments
		{
		private:
			std::vector<LuaValue> _arguments;

		public:
			inline void Push(LuaValue &&value)
			{
				_arguments.push_back(std::move(value));
			}
		};

		template<typename T, typename... Args, 
			typename = typename std::enable_if<!std::is_same<T, LuaArgs_t>::value>::type>
		void CallEvent(const char *event_name, EventArguments *event_args,
			T value, Args&&... args)
		{
			event_args->Push(LuaValue(value));
			CallEvent(event_name, event_args, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void CallEvent(const char *event_name, EventArguments *event_args,
			LuaArgs_t &value, Args&&... args)
		{
			for (auto &e : value)
				event_args->Push(std::move(e));
			value.clear(); // invalidate
			CallEvent(event_name, event_args, std::forward<Args>(args)...);
		}


		template<typename... Args>
		void CallEvent(const char *event_name, EventArguments *event_args)
		{
			hrzn::Plugin::Get()->CallEvent(event_name, event_args);
		}
	}

	template<typename... Args>
	void CallEvent(const char *event_name, Args&&... args)
	{
		_internal::CallEvent(event_name, new _internal::EventArguments, 
			std::forward<Args>(args)...);
	}
}
