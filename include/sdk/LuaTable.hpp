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
#include <unordered_map>
#include <type_traits>
#include <functional>

#include "LuaValue.hpp"


namespace Lua
{
	class LuaTable
	{
	private:
		std::unordered_map<LuaValue, LuaValue, LuaValue::Hash> _table;

	public:
		template<typename T, typename U>
		inline void Add(T key, U value)
		{
			_table[LuaValue(key)] = LuaValue(value);
		}

		template<typename T>
		inline bool Exists(T key)
		{
			return _table.find(LuaValue(key)) != _table.end();
		}
		
		inline int Count()
		{
			return static_cast<int>(_table.size());
		}

		template<typename T, typename U>
		bool TryGet(T key, U &dest)
		{
			auto it = _table.find(LuaValue(key));
			if (it == _table.end())
				return false;

			return it->second.TryGetValue(dest);
		}

		inline void ForEach(std::function<void(LuaValue const &, LuaValue const &)> func)
		{
			for (auto const &e : _table)
				func(e.first, e.second);
		}

		void ParseFromLua(lua_State *state, int index)
		{
			static int recurse_counter = 0;
			if (recurse_counter > 3)
				return;

			recurse_counter++;
			_table.clear();

			int counter = 0;
			lua_pushnil(state);
			while (lua_next(state, index) != 0)
			{
				_table[ParseValueFromLua(state, -2)] = ParseValueFromLua(state, -1);
				lua_pop(state, 1);
				if (++counter >= 1000)
				{
					lua_pop(state, 1);
					break;
				}
			}
			recurse_counter--;
		}

		void PushToLua(lua_State *state) const
		{
			lua_createtable(state, static_cast<int>(_table.size()), 0);
			for (auto const &e : _table)
			{
				PushValueToLua(e.first, state);
				PushValueToLua(e.second, state);
				lua_rawset(state, -3);
			}
		}

	public: // static helper func
		static inline LuaTable_t Create()
		{
			return LuaTable_t(new LuaTable);
		}
	};
}
