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

#ifndef __PLUGINSDK_H
#define __PLUGINSDK_H

#define PLUGIN_API_VERSION 0x1

#ifdef _MSC_VER
#define LIBRARY_EXPORT __declspec(dllexport)
#define LIBRARY_IMPORT __declspec(dllimport)
#define CALLING_CONVENTION __stdcall
#else
#define LIBRARY_EXPORT __attribute__ ((visibility ("default")))
#define LIBRARY_IMPORT __attribute__ ((visibility ("default")))
#define CALLING_CONVENTION
#endif

#ifdef __cplusplus
#define SYMTAB_PREFIX extern "C"

#else
#define SYMTAB_PREFIX
#endif

// Functions exported to be called by the server
#define EXPORT(t) SYMTAB_PREFIX LIBRARY_EXPORT t CALLING_CONVENTION

// Functions imported to be called by the plugin
#define IMPORT(t) SYMTAB_PREFIX LIBRARY_IMPORT t CALLING_CONVENTION

#ifdef __cplusplus
#include <Lua/lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

#ifdef __cplusplus
#include "sdk/LuaFunctionUtils.hpp"
#include "sdk/LuaTable.hpp"
#include "sdk/LuaFunction.hpp"
#include "sdk/LuaValueLuaImpl.hpp"
#include "sdk/PluginApi.hpp"
#endif

#define LUA_DEFINE(func) static int func(lua_State *L)
#define LUA_FUNCTION(func) int func(lua_State *L)


#endif /* __PLUGINSDK_H */
