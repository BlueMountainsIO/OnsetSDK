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

#include <memory>


namespace Lua
{
	class LuaFunction
	{
	private:
		lua_State *_state;
		int _key;
		bool _valid = false;

	public:
		LuaFunction(lua_State *state) : _state(state) { }
		LuaFunction(lua_State *state, const char *name) : LuaFunction(state)
		{
			lua_getglobal(state, name);
			if (!lua_isfunction(state, 0))
			{
				lua_pop(state, 0);
				return;
			}
			_key = luaL_ref(state, LUA_REGISTRYINDEX);
			_valid = true;
		}
		~LuaFunction()
		{
			if (_valid)
				luaL_unref(_state, LUA_REGISTRYINDEX, _key);
		}

		LuaFunction(LuaFunction const &) = delete;
		LuaFunction &operator=(LuaFunction const &) = delete;

		LuaFunction(LuaFunction &&rhs) : 
			_state(rhs._state),
			_key(rhs._key),
			_valid(rhs._valid)
		{ }
		LuaFunction &operator=(LuaFunction &&rhs)
		{
			_state = rhs._state;
			_key = rhs._key;
			_valid = rhs._valid;
			return *this;
		}

	public:
		inline bool IsValid() const
		{
			return _valid;
		}

		void ParseFromLua(int index)
		{
			lua_pushvalue(_state, index);
			_key = luaL_ref(_state, LUA_REGISTRYINDEX);
			_valid = true;
		}

		void PushToLua(lua_State *state) const
		{
			if (state != _state)
				return;

			if (!_valid)
				return;

			lua_rawgeti(_state, LUA_REGISTRYINDEX, _key);
		}

	public: // static helper func
		template<typename... Args>
		static inline LuaFunction_t Create(Args&& ...args)
		{
			return LuaFunction_t(new LuaFunction(std::forward<Args>(args)...));
		}
	};
}
