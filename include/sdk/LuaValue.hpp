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


#ifdef _MSC_VER
#pragma warning(push)
// disable union "constructor/desructor not called implicitly" warning
#pragma warning(disable: 4582 4583)
#endif


namespace Lua
{
	class LuaValue
	{
	public:
		enum class Type
		{
			INVALID,
			NIL,
			INTEGER,
			NUMBER,
			BOOLEAN,
			STRING,
			TABLE,
			FUNCTION
		};

	private:
		Type _type;
		union
		{
			lua_Integer Integer;
			lua_Number Number;
			bool Boolean;
			std::string String;
			LuaTable_t Table;
			LuaFunction_t Function;
		};

	public:
		struct Hash
		{
			std::size_t operator()(LuaValue const &e) const
			{
				std::size_t hash = 0;

				using EnumType = std::underlying_type<Type>::type;
				hash ^= std::hash<EnumType>()(static_cast<EnumType>(e._type))
					+ 0x9e3779b9 + (hash << 6) + (hash >> 2);

				std::size_t value_hash = 0;
				bool skip_value = false;
				switch (e._type)
				{
				case Type::INTEGER:
					value_hash = std::hash<lua_Integer>()(e.Integer);
					break;
				case Type::NUMBER:
					value_hash = std::hash<lua_Number>()(e.Number);
					break;
				case Type::BOOLEAN:
					value_hash = std::hash<bool>()(e.Boolean);
					break;
				case Type::STRING:
					value_hash = std::hash<std::string>()(e.String);
					break;
				case Type::TABLE:
					value_hash = std::hash<LuaTable_t>()(e.Table);
					break;
				case Type::FUNCTION:
					value_hash = std::hash<LuaFunction_t>()(e.Function);
					break;
				case Type::INVALID:
				case Type::NIL:
					// skip, the type hash is enough for these
					skip_value = true;
					break;
				}

				if (!skip_value)
					hash ^= value_hash + 0x9e3779b9 + (hash << 6) + (hash >> 2);
				return hash;
			}
		};

	public:
		LuaValue() : _type(Type::INVALID)
		{ }
		LuaValue(std::nullptr_t) : _type(Type::NIL)
		{ }
		template<typename T, typename std::enable_if<
			std::is_integral<T>::value && !std::is_same<T, bool>::value, int>::type = 0>
			LuaValue(T value) :
			_type(Type::INTEGER),
			Integer(static_cast<lua_Integer>(value))
		{ }
		LuaValue(double value) :
			_type(Type::NUMBER),
			Number(static_cast<lua_Number>(value))
		{ }
		LuaValue(bool value) :
			_type(Type::BOOLEAN),
			Boolean(value)
		{ }
		LuaValue(const char *value)
		{
			if (value == nullptr)
			{
				_type = Type::NIL;
			}
			else
			{
				_type = Type::STRING;
				new(&String) std::string(value);
			}
		}
		LuaValue(std::string value) :
			_type(Type::STRING)
		{
			new(&String) std::string(value);
		}
		LuaValue(LuaTable_t value) :
			_type(Type::TABLE)
		{
			new(&Table) std::shared_ptr<LuaTable>(std::move(value));
		}
		LuaValue(LuaFunction_t value) :
			_type(Type::FUNCTION)
		{
			new(&Function) std::shared_ptr<LuaFunction>(std::move(value));
		}

		LuaValue(LuaValue const &rhs) : _type(rhs._type)
		{
			switch (_type)
			{
			case Type::NIL:
				// do nothing
				break;
			case Type::INTEGER:
				Integer = rhs.Integer;
				break;
			case Type::NUMBER:
				Number = rhs.Number;
				break;
			case Type::BOOLEAN:
				Boolean = rhs.Boolean;
				break;
			case Type::STRING:
				new(&String) std::string(rhs.String);
				break;
			case Type::TABLE:
				new(&Table) std::shared_ptr<LuaTable>(rhs.Table);
				break;
			case Type::FUNCTION:
				new(&Function) std::shared_ptr<LuaFunction>(rhs.Function);
				break;
			case Type::INVALID:
				// skip
				break;
			}
		}
		LuaValue &operator=(LuaValue const &rhs)
		{
			_type = rhs._type;
			switch (_type)
			{
			case Type::NIL:
				// do nothing
				break;
			case Type::INTEGER:
				Integer = rhs.Integer;
				break;
			case Type::NUMBER:
				Number = rhs.Number;
				break;
			case Type::BOOLEAN:
				Boolean = rhs.Boolean;
				break;
			case Type::STRING:
				new(&String) std::string(rhs.String);
				break;
			case Type::TABLE:
				new(&Table) std::shared_ptr<LuaTable>(rhs.Table);
				break;
			case Type::FUNCTION:
				new(&Function) std::shared_ptr<LuaFunction>(rhs.Function);
				break;
			case Type::INVALID:
				// skip
				break;
			}
			return *this;
		}

		LuaValue(LuaValue &&rhs) : _type(rhs._type)
		{
			switch (_type)
			{
			case Type::NIL:
				// do nothing
				break;
			case Type::INTEGER:
				Integer = rhs.Integer;
				break;
			case Type::NUMBER:
				Number = rhs.Number;
				break;
			case Type::BOOLEAN:
				Boolean = rhs.Boolean;
				break;
			case Type::STRING:
				new(&String) std::string(std::move(rhs.String));
				break;
			case Type::TABLE:
				new(&Table) std::shared_ptr<LuaTable>(std::move(rhs.Table));
				break;
			case Type::FUNCTION:
				new(&Function) std::shared_ptr<LuaFunction>(std::move(rhs.Function));
				break;
			case Type::INVALID:
				// skip
				break;
			}
		}
		LuaValue &operator=(LuaValue &&rhs)
		{
			_type = rhs._type;
			switch (_type)
			{
			case Type::NIL:
				// do nothing
				break;
			case Type::INTEGER:
				Integer = rhs.Integer;
				break;
			case Type::NUMBER:
				Number = rhs.Number;
				break;
			case Type::BOOLEAN:
				Boolean = rhs.Boolean;
				break;
			case Type::STRING:
				new(&String) std::string(std::move(rhs.String));
				break;
			case Type::TABLE:
				new(&Table) std::shared_ptr<LuaTable>(std::move(rhs.Table));
				break;
			case Type::FUNCTION:
				new(&Function) std::shared_ptr<LuaFunction>(std::move(rhs.Function));
				break;
			case Type::INVALID:
				// skip
				break;
			}
			return *this;
		}

		~LuaValue()
		{
			if (_type == Type::STRING)
				String.~basic_string();
			else if (_type == Type::TABLE)
				Table.~shared_ptr();
			else if (_type == Type::FUNCTION)
				Function.~shared_ptr();
		}

		bool operator==(LuaValue const &rhs) const
		{
			if (_type != rhs._type)
				return false;

			switch (_type)
			{
			case Type::NIL:
				return true;
			case Type::INTEGER:
				return Integer == rhs.Integer;
			case Type::NUMBER:
				return Number == rhs.Number;
			case Type::BOOLEAN:
				return Boolean == rhs.Boolean;
			case Type::STRING:
				return String.compare(rhs.String) == 0;
			case Type::TABLE:
				return Table == rhs.Table;
			case Type::FUNCTION:
				return false; // functions are not comparable
			case Type::INVALID:
				return false; // invalid type is not comparable
			}

			return false;
		}

	public:
		inline Type GetType() const
		{
			return _type;
		}

		inline bool IsNil() const
		{
			return _type == Type::NIL;
		}

		inline bool IsInteger() const
		{
			return _type == Type::INTEGER;
		}

		inline bool IsNumber() const
		{
			return _type == Type::NUMBER;
		}

		inline bool IsBoolean() const
		{
			return _type == Type::BOOLEAN;
		}

		inline bool IsString() const
		{
			return _type == Type::STRING;
		}

		inline bool IsTable() const
		{
			return _type == Type::TABLE;
		}

		inline bool IsFunction() const
		{
			return _type == Type::FUNCTION;
		}


		template<typename T, typename std::enable_if<
			std::is_integral<T>::value && !std::is_same<T, bool>::value, int>::type = 0>
		bool TryGetValue(T &dest) const
		{
			if (_type != Type::INTEGER)
				return false;

			dest = static_cast<T>(Integer);
			return true;
		}

		bool TryGetValue(double &dest) const
		{
			if (_type != Type::NUMBER)
				return false;

			dest = static_cast<double>(Number);
			return true;
		}

		bool TryGetValue(float &dest) const
		{
			if (_type != Type::NUMBER)
				return false;

			dest = static_cast<float>(Number);
			return true;
		}

		bool TryGetValue(bool &dest) const
		{
			if (_type != Type::BOOLEAN)
				return false;

			dest = Boolean;
			return true;
		}

		bool TryGetValue(std::string &dest) const
		{
			if (_type != Type::STRING)
				return false;

			dest = String;
			return true;
		}

		bool TryGetValue(LuaTable_t &dest) const
		{
			if (_type != Type::TABLE)
				return false;

			dest = Table;
			return true;
		}

		bool TryGetValue(LuaFunction_t &dest) const
		{
			if (_type != Type::FUNCTION)
				return false;

			dest = Function;
			return true;
		}

		template<typename T>
		T GetValue() const
		{
			T value;
			TryGetValue(value);
			return value;
		}
	};

	static void PushValueToLua(LuaValue const &value, lua_State *state);
	static LuaValue ParseValueFromLua(lua_State *state, int index);
}


#ifdef _MSC_VER
#pragma warning(pop)
#endif
