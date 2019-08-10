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
#include "LuaValue.hpp"
#include "LuaTable.hpp"
#include "LuaFunction.hpp"

namespace Lua
{
	struct FunctionCallInfo
	{
		std::string name, source;
		int line;
	};

	inline void RegisterPluginFunction(lua_State *state, const char *function_name, 
		lua_CFunction lua_function)
	{
		lua_pushcclosure(state, lua_function, 0);
		lua_setglobal(state, function_name);
	}

	static bool GetCurrentCallInfo(lua_State *state, FunctionCallInfo &info)
	{
		lua_Debug dbg;
		if (state == nullptr)
			return false;

		if (lua_getstack(state, 1, &dbg) != 1
			|| lua_getinfo(state, "Sl", &dbg) == 0)
		{
			return false;
		}
		info.source = dbg.short_src;
		info.line = dbg.currentline;

		if (lua_getstack(state, 0, &dbg) != 1
			|| lua_getinfo(state, "n", &dbg) == 0)
		{
			return false;
		}
		info.name = dbg.name;

		return true;
	}

	template<typename... Args>
	LuaArgs_t BuildArgumentList(Args&&... args)
	{
		LuaArgs_t arg_list;
		BuildArgumentList(arg_list, std::forward<Args>(args)...);
		return arg_list;
	}

	template<typename T, typename... Args>
	void BuildArgumentList(LuaArgs_t &arg_list, T value, Args&&... args)
	{
		arg_list.emplace_back(value);
		BuildArgumentList(arg_list, std::forward<Args>(args)...);
	}

	static void BuildArgumentList(LuaArgs_t &arg_list)
	{
		(void)arg_list; // unused
	}


	template<int Idx = 1, typename... Args>
	void ParseArguments(lua_State *state, int &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	void ParseArguments(lua_State *state, unsigned int &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	void ParseArguments(lua_State *state, double &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	void ParseArguments(lua_State *state, float &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	void ParseArguments(lua_State *state, bool &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	void ParseArguments(lua_State *state, std::string &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	void ParseArguments(lua_State *state, LuaTable_t &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	void ParseArguments(lua_State *state, LuaFunction_t &arg, Args&... args);
	template<int Idx = 1>
	void ParseArguments(lua_State *state, LuaArgs_t &arg);

	template<int Idx>
	void ParseArguments(lua_State *state)
	{
		(void)state; // unused
	}

	template<int Idx, typename... Args>
	void ParseArguments(lua_State *state, int &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TBOOLEAN || type == LUA_TSTRING)
		{
			arg = static_cast<int>(lua_tointeger(state, Idx));
			ParseArguments<Idx + 1>(state, args...);
		}
		else
		{
			luaL_argerror(state, Idx, "expected integer-like argument");
		}
	}

	template<int Idx, typename... Args>
	void ParseArguments(lua_State *state, unsigned int &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TBOOLEAN || type == LUA_TSTRING)
		{
			arg = static_cast<unsigned int>(lua_tointeger(state, Idx));
			ParseArguments<Idx + 1>(state, args...);
		}
		else
		{
			luaL_argerror(state, Idx, "expected integer-like argument");
		}
	}

	template<int Idx, typename... Args>
	void ParseArguments(lua_State *state, double &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TSTRING)
		{
			arg = static_cast<double>(lua_tonumber(state, Idx));
			ParseArguments<Idx + 1>(state, args...);
		}
		else
		{
			luaL_argerror(state, Idx, "expected number argument");
		}
	}

	template<int Idx, typename... Args>
	void ParseArguments(lua_State *state, float &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TSTRING)
		{
			arg = static_cast<float>(lua_tonumber(state, Idx));
			ParseArguments<Idx + 1>(state, args...);
		}
		else
		{
			luaL_argerror(state, Idx, "expected number argument");
		}
	}

	template<int Idx, typename... Args>
	void ParseArguments(lua_State *state, bool &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TBOOLEAN || type == LUA_TSTRING)
		{
			arg = lua_toboolean(state, Idx) != 0;
			ParseArguments<Idx + 1>(state, args...);
		}
		else
		{
			luaL_argerror(state, Idx, "expected boolean-like argument");
		}
	}

	template<int Idx, typename... Args>
	void ParseArguments(lua_State *state, std::string &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TSTRING || type == LUA_TNUMBER)
		{
			arg.assign(lua_tostring(state, Idx));
			ParseArguments<Idx + 1>(state, args...);
		}
		else
		{
			luaL_argerror(state, Idx, "expected string-like argument");
		}
	}

	template<int Idx, typename... Args>
	void ParseArguments(lua_State *state, LuaTable_t &arg, Args&... args)
	{
		if (lua_istable(state, Idx))
		{
			if (!arg)
				arg.reset(new LuaTable);
			arg->ParseFromLua(state, Idx);
			ParseArguments<Idx + 1>(state, args...);
		}
		else
		{
			luaL_argerror(state, Idx, "expected table");
		}
	}

	template<int Idx, typename... Args>
	void ParseArguments(lua_State *state, LuaFunction_t &arg, Args&... args)
	{
		if (lua_isfunction(state, Idx))
		{
			if (!arg)
				arg.reset(new LuaFunction(state));
			arg->ParseFromLua(Idx);
			ParseArguments<Idx + 1>(state, args...);
		}
		else
		{
			luaL_argerror(state, Idx, "expected function");
		}
	}

	template<int Idx>
	void ParseArguments(lua_State *state, LuaArgs_t &arg)
	{
		int idx = Idx;
		while (lua_type(state, idx) != LUA_TNONE)
			arg.push_back(ParseValueFromLua(state, idx++));
	}


	template<int Idx = 1, typename... Args>
	bool ParseOptionalArguments(lua_State *state, int &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	bool ParseOptionalArguments(lua_State *state, unsigned int &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	bool ParseOptionalArguments(lua_State *state, double &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	bool ParseOptionalArguments(lua_State *state, float &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	bool ParseOptionalArguments(lua_State *state, bool &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	bool ParseOptionalArguments(lua_State *state, std::string &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	bool ParseOptionalArguments(lua_State *state, LuaTable_t &arg, Args&... args);
	template<int Idx = 1, typename... Args>
	bool ParseOptionalArguments(lua_State *state, LuaFunction_t &arg, Args&... args);
	template<int Idx = 1>
	bool ParseOptionalArguments(lua_State *state, LuaArgs_t &arg);

	template<int Idx>
	bool ParseOptionalArguments(lua_State *state)
	{
		(void)state; // unused
		return true;
	}

	template<int Idx, typename... Args>
	bool ParseOptionalArguments(lua_State *state, int &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TBOOLEAN || type == LUA_TSTRING)
		{
			arg = static_cast<int>(lua_tointeger(state, Idx));
			return ParseOptionalArguments<Idx + 1>(state, args...);
		}
		else if (type != LUA_TNONE)
		{
			luaL_argerror(state, Idx, "expected integer-like argument");
		}
		return false;
	}

	template<int Idx, typename... Args>
	bool ParseOptionalArguments(lua_State *state, unsigned int &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TBOOLEAN || type == LUA_TSTRING)
		{
			arg = static_cast<unsigned int>(lua_tointeger(state, Idx));
			return ParseOptionalArguments<Idx + 1>(state, args...);
		}
		else if (type != LUA_TNONE)
		{
			luaL_argerror(state, Idx, "expected integer-like argument");
		}
		return false;
	}

	template<int Idx, typename... Args>
	bool ParseOptionalArguments(lua_State *state, double &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TSTRING)
		{
			arg = static_cast<double>(lua_tonumber(state, Idx));
			return ParseOptionalArguments<Idx + 1>(state, args...);
		}
		else if (type != LUA_TNONE)
		{
			luaL_argerror(state, Idx, "expected number argument");
		}
		return false;
	}

	template<int Idx, typename... Args>
	bool ParseOptionalArguments(lua_State *state, float &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TSTRING)
		{
			arg = static_cast<float>(lua_tonumber(state, Idx));
			return ParseOptionalArguments<Idx + 1>(state, args...);
		}
		else if (type != LUA_TNONE)
		{
			luaL_argerror(state, Idx, "expected number argument");
		}
		return false;
	}

	template<int Idx, typename... Args>
	bool ParseOptionalArguments(lua_State *state, bool &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TNUMBER || type == LUA_TBOOLEAN || type == LUA_TSTRING)
		{
			arg = static_cast<bool>(lua_toboolean(state, Idx));
			return ParseOptionalArguments<Idx + 1>(state, args...);
		}
		else if (type != LUA_TNONE)
		{
			luaL_argerror(state, Idx, "expected boolean-like argument");
		}
		return false;
	}

	template<int Idx, typename... Args>
	bool ParseOptionalArguments(lua_State *state, std::string &arg, Args&... args)
	{
		int type = lua_type(state, Idx);
		if (type == LUA_TSTRING || type == LUA_TNUMBER)
		{
			arg.assign(lua_tostring(state, Idx));
			return ParseOptionalArguments<Idx + 1>(state, args...);
		}
		else if (type != LUA_TNONE)
		{
			luaL_argerror(state, Idx, "expected string-like argument");
		}
		return false;
	}

	template<int Idx, typename... Args>
	bool ParseOptionalArguments(lua_State *state, LuaTable_t &arg, Args&... args)
	{
		if (lua_istable(state, Idx))
		{
			if (!arg)
				arg.reset(new LuaTable);
			arg->ParseFromLua(state, Idx);
			return ParseOptionalArguments<Idx + 1>(state, args...);
		}
		else if (lua_isnone(state, Idx) == 0)
		{
			luaL_argerror(state, Idx, "expected table");
		}
		return false;
	}

	template<int Idx, typename... Args>
	bool ParseOptionalArguments(lua_State *state, LuaFunction_t &arg, Args&... args)
	{
		if (lua_isfunction(state, Idx))
		{
			if (!arg)
				arg.reset(new LuaFunction(state));
			arg->ParseFromLua(Idx);
			return ParseOptionalArguments<Idx + 1>(state, args...);
		}
		else if (lua_isnone(state, Idx) == 0)
		{
			luaL_argerror(state, Idx, "expected function");
		}
		return false;
	}

	template<int Idx>
	bool ParseOptionalArguments(lua_State *state, LuaArgs_t &arg)
	{
		ParseArguments<Idx>(state, arg);
		return true;
	}

	static int ReturnValues(lua_State *state)
	{
		(void)state; // unused
		return 0;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, int arg, Args&&... args)
	{
		lua_pushinteger(state, arg);
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, unsigned int arg, Args&&... args)
	{
		lua_pushinteger(state, static_cast<lua_Integer>(arg));
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, long long arg, Args&&... args)
	{
		lua_pushinteger(state, arg);
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, unsigned long long arg, Args&&... args)
	{
		lua_pushinteger(state, arg);
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, double arg, Args&&... args)
	{
		lua_pushnumber(state, arg);
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, bool arg, Args&&... args)
	{
		lua_pushboolean(state, arg);
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, std::string const &arg, Args&&... args)
	{
		lua_pushlstring(state, arg.c_str(), arg.length());
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, const char *arg, Args&&... args)
	{
		lua_pushstring(state, arg); // pushes nil if arg is nullptr
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, LuaTable_t const arg, Args&&... args)
	{
		arg->PushToLua(state);
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, LuaFunction_t const arg, Args&&... args)
	{
		arg->PushToLua(state);
		return ReturnValues(state, std::forward<Args>(args)...) + 1;
	}

	template<typename... Args>
	int ReturnValues(lua_State *state, LuaArgs_t const &arg, Args&&... args)
	{
		for (auto const &e : arg)
			PushValueToLua(e, state);
		return ReturnValues(state, std::forward<Args>(args)...) 
			+ static_cast<int>(arg.size());
	}
}
