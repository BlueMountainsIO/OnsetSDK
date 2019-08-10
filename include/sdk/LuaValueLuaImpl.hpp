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

namespace Lua
{
	static void PushValueToLua(LuaValue const &value, lua_State *state)
	{
		switch (value.GetType())
		{
		case LuaValue::Type::NIL:
			lua_pushnil(state);
			break;
		case LuaValue::Type::INTEGER:
			lua_pushinteger(state, static_cast<lua_Integer>(value.GetValue<int>()));
			break;
		case LuaValue::Type::NUMBER:
			lua_pushnumber(state, static_cast<lua_Number>(value.GetValue<double>()));
			break;
		case LuaValue::Type::BOOLEAN:
			lua_pushboolean(state, value.GetValue<bool>());
			break;
		case LuaValue::Type::STRING:
		{
			auto str = value.GetValue<std::string>();
			lua_pushlstring(state, str.c_str(), str.length());
		} break;
		case LuaValue::Type::TABLE:
			value.GetValue<LuaTable_t>()->PushToLua(state);
			break;
		case LuaValue::Type::FUNCTION:
			value.GetValue<LuaFunction_t>()->PushToLua(state);
			break;
		case LuaValue::Type::INVALID:
			// do nothing
			break;
		}
	}

	static LuaValue ParseValueFromLua(lua_State *state, int index)
	{
		switch (lua_type(state, index))
		{
		case LUA_TNIL:
			return LuaValue(nullptr);
		case LUA_TNUMBER:
			if (lua_isinteger(state, index))
				return LuaValue(lua_tointeger(state, index));
			else
				return LuaValue(lua_tonumber(state, index));
		case LUA_TBOOLEAN:
			return LuaValue(lua_toboolean(state, index) != 0);
		case LUA_TSTRING:
			return LuaValue(lua_tostring(state, index));
		case LUA_TTABLE:
		{
			LuaTable_t table(new LuaTable);
			if (index < 0)
				index += lua_gettop(state) + 1;
			table->ParseFromLua(state, index);
			return LuaValue(table);
		}
		case LUA_TFUNCTION:
		{
			LuaFunction_t func(new LuaFunction(state));
			func->ParseFromLua(index);
			return LuaValue(func);
		}
		default:
			luaL_error(state, "unsupported type %s in table",
				lua_typename(state, lua_type(state, index)));
		}
		return LuaValue();
	}
}
