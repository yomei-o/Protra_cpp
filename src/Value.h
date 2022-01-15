// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// 
// This program is part of Protra.
//
// Protra is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
// 


#ifndef DF_VALUE_H_
#define DF_VALUE_H_

#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include "RuntimeException.h"


#if 0

bool operator ==(Value& v)
{
	switch (ValueType) {
	case ValueType::Null:
		switch (v.ValueType) {
		case ValueType::Null:
			break;
		case ValueType::Int:
			break;
		case ValueType::Float:
			break;
		case ValueType::String:
			break;
		case ValueType::Array:
			break;
			}
		break;
	case ValueType::Float:
		switch (v.ValueType) {
		case ValueType::Null:
			break;
		case ValueType::Int:
			break;
		case ValueType::Float:
			break;
		case ValueType::String:
			break;
		case ValueType::Array:
			break;
		}
		break;
	case ValueType::String:
		switch (v.ValueType) {
		case ValueType::Null:
			break;
		case ValueType::Int:
			break;
		case ValueType::Float:
			break;
		case ValueType::String:
			break;
		case ValueType::Array:
			break;
		}
		break;
	case ValueType::Array:
		switch (v.ValueType) {
		case ValueType::Null:
			break;
		case ValueType::Int:
			break;
		case ValueType::Float:
			break;
		case ValueType::String:
			break;
		case ValueType::Array:
			break;
		}
		break;
		}
	return false;
	

#endif

namespace Protra {
namespace Lib {
namespace Lang {

namespace ValueType{
enum ValueType {
	Null,
	Int,
	Float,
	String,
	Array,
	CPointer,
};
}


class Value{
public:
	//init
	Value()
	{
		ValueType = ValueType::Null;
		IntValue = 0;
		FloatValue = 0;
	}
	Value(bool val)
	{
		ValueType = ValueType::Int;
		IntValue = val;
		FloatValue = 0;
	}
	Value(int val)
	{
		ValueType = ValueType::Int;
		IntValue = val;
		FloatValue = 0;
	}
	Value(double val)
	{
		ValueType = ValueType::Float;
		IntValue = 0;
		FloatValue = val;
	}
	Value(std::string& val)
	{
		ValueType = ValueType::String;
		IntValue = 0;
		FloatValue =0;
		StringValue = val;
	}
	Value(const Value& v)
	{
		ValueType = v.ValueType;
		IntValue = v.IntValue;
		FloatValue = v.FloatValue;
		StringValue = v.StringValue;
		ArrayValue = v.ArrayValue;
	}
	Value(ValueType::ValueType t,int sz)
	{
		int i;
		ValueType = ValueType::Array;
		IntValue = 0;
		FloatValue = 0;
		ArrayValue = std::shared_ptr<std::vector<std::shared_ptr<Value> > >(new (std::vector<std::shared_ptr<Value> >));
		for (i = 0; i < sz; i++)ArrayValue->push_back(std::shared_ptr<Value>(new Value()));
	}
	//ok
	bool IsTrue() {
		switch (ValueType) {
		case ValueType::Int:
			if (IntValue)return true;
			return false;
		case ValueType::Float:
			if (FloatValue)return true;
			return false;
		case ValueType::String:
			return true;
		case ValueType::Null:
			return false;
		case ValueType::Array:
			return true;
		}
		return false;
	}
	//ok
	bool IsFalse() {
		return !IsTrue();
	}
	//ok
	bool IsNull() {
		switch (ValueType) {
		case ValueType::Null:
			return true;
		}
		return false;
	}
	//ok
	Value InnerValue() {
		return *this;
	}
	//ok
	std::string toString() {
		char buf[64];
		std::string ret;
		switch (ValueType) {
		case ValueType::Null:
			ret = "null";
			break;
		case ValueType::String:
			ret = StringValue;
			break;
		case ValueType::Int:
			sprintf(buf,"%d",IntValue);
			ret = buf;
			break;
		case ValueType::Float:
			sprintf(buf, "%g", FloatValue);
			ret = buf;
			break;
		}
		return ret;
	}
	//ok
	int toInt() {
		int r = 0;
		switch (ValueType) {
		case ValueType::Null:
			return 0;
		case ValueType::Int:
			return IntValue;
			break;
		case ValueType::Float:
			return (int)FloatValue;
		case ValueType::String:
			sscanf(StringValue.c_str(), "%d", &r);
			return r;
		case ValueType::Array:
			throw std::runtime_error(RuntimeException("array casted"));
			break;
		}
		return 0;
	}
	//ok
	double toFloat() {
		double r = 0;
		switch (ValueType) {
		case ValueType::Null:
			return 0;
		case ValueType::Int:
			return (double)IntValue;
			break;
		case ValueType::Float:
			return FloatValue;
		case ValueType::String:
			sscanf(StringValue.c_str(), "%lf", &r);
			return r;
		case ValueType::Array:
			throw std::runtime_error(RuntimeException("array casted"));
			break;
		}
		return 0;
	}
	//ok
	Value Cast(ValueType::ValueType type) {
		Value ret;
		switch (type) {
		case ValueType::Null:
			break;
		case ValueType::Int:
			ret.ValueType = ValueType::Int;
			ret.IntValue = toInt();
			break;
		case ValueType::Float:
			ret.ValueType = ValueType::Float;
			ret.FloatValue = toFloat();
			break;
		case ValueType::String:
			ret.ValueType = ValueType::String;
			ret.StringValue = toString();
			break;
		case ValueType::Array:
			throw std::runtime_error(RuntimeException("array casted"));
			break;
		}
		//TODO
		return ret;
	}
	//ok
	int Length() {
		switch (ValueType) {
		case ValueType::Null:
		case ValueType::Int:
		case ValueType::Float:
		case ValueType::String:
			throw std::runtime_error(RuntimeException("Length for non-array"));
			break;
		case ValueType::Array:
			return (int)ArrayValue->size();
		}
		return 0;
	}
	//op2
	//ok
	Value& operator =(Value& v)
	{
		ValueType = v.ValueType;
		IntValue = v.IntValue;
		FloatValue = v.FloatValue;
		StringValue = v.StringValue;
		ArrayValue = v.ArrayValue;
		return *this;
	}
	//ok
	bool operator ==(Value& v)
	{
		switch (ValueType) {
		case ValueType::Null:
			switch (v.ValueType) {
			case ValueType::Null:
				return true;
			}
			return false;
		case ValueType::Int:
			switch (v.ValueType) {
			case ValueType::Null:
				return false;
			case ValueType::Int:
				return IntValue == v.IntValue;
			case ValueType::Float:
				return toFloat() == v.FloatValue;
			case ValueType::String:
				throw std::runtime_error("can not compare");
				//return toString() == v.StringValue;
			case ValueType::Array:
				throw std::runtime_error("can not compare");
			}
			break;
		case ValueType::Float:
			switch (v.ValueType) {
			case ValueType::Null:
				return false;
			case ValueType::Int:
				return FloatValue == v.toFloat();
			case ValueType::Float:
				return FloatValue == v.FloatValue;
			case ValueType::String:
				throw std::runtime_error("can not compare");
				//return toString() == v.StringValue;
			case ValueType::Array:
				throw std::runtime_error("can not compare");
			}
			break;
		case ValueType::String:
			switch (v.ValueType) {
			case ValueType::Null:
			case ValueType::Int:
			case ValueType::Float:
				return false;
			case ValueType::String:
				return StringValue == v.StringValue;
			case ValueType::Array:
				return false;
			}
			break;
		case ValueType::Array:
			switch (v.ValueType) {
			case ValueType::Null:
			case ValueType::Int:
			case ValueType::Float:
			case ValueType::String:
				return false;
			case ValueType::Array:
				return ArrayValue.get() == v.ArrayValue.get();
			}
			break;
		}
		return false;
	}
	//ok
	bool operator !=(Value& v)
	{
		return !(*this==v);
	}
	//ok
	int CompareTo(Value& v)
	{
		if (ValueType == ValueType::Array || v.ValueType == ValueType::Array){
			throw std::runtime_error(RuntimeException("array compared"));
		}
		double f;
		switch (ValueType) {
		case ValueType::Int:
			switch (v.ValueType) {
			case ValueType::Int:
				return IntValue - v.IntValue;
			case ValueType::Float:
				f = (double)IntValue - v.FloatValue;
				if (f > 0)return 1;
				if (f < 0)return -1;
				return 0;
			case ValueType::String:
				throw std::runtime_error(RuntimeException("int compared with string"));
			}
			break;
		case ValueType::Float:
			switch (v.ValueType) {
			case ValueType::Int:
				f = FloatValue - (double)v.IntValue;
				if (f > 0)return 1;
				if (f < 0)return -1;
				return 0;
			case ValueType::Float:
				f = FloatValue - v.FloatValue;
				if (f > 0)return 1;
				if (f < 0)return -1;
				return 0;
			case ValueType::String:
				throw std::runtime_error(RuntimeException("float compared with string"));
			}
			break;
		case ValueType::String:
			switch (v.ValueType) {
			case ValueType::Int:
				throw std::runtime_error(RuntimeException("string compared with int"));
			case ValueType::Float:
				throw std::runtime_error(RuntimeException("string compared with float"));
			case ValueType::String:
				return strcmp(StringValue.c_str(), v.StringValue.c_str());
			}
			break;
		}
		return false;
	}
	//ok
	bool operator <=(Value& v)
	{
		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("null compared"));
		}
		return CompareTo(v) <= 0;
	}
	//ok
	bool operator >=(Value& v)
	{
		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("null compared"));
		}
		return CompareTo(v) >= 0;
	}
	//ok
	bool operator <(Value& v)
	{
		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("null compared"));
		}
		return CompareTo(v) < 0;
	}
	//ok
	bool operator >(Value& v)
	{
		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("null compared"));
		}
		return CompareTo(v) > 0;
	}
	Value operator +(Value& v)
	{
		Value r;

		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("binary operator '+' isn't defined for null"));
		}
		if (ValueType == ValueType::Array || v.ValueType == ValueType::Array) {
			throw std::runtime_error(RuntimeException("binary operator '+' isn't defined for array"));
		}

		switch (ValueType) {
		case ValueType::Int:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Int;
				r.IntValue = IntValue + v.IntValue;
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::Float;
				r.FloatValue = (double)IntValue + v.FloatValue;
				return r;
			case ValueType::String:
				r.ValueType = ValueType::String;
				r.StringValue = toString() + v.StringValue;
			}
			break;
		case ValueType::Float:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Float;
				r.FloatValue = FloatValue + v.IntValue;
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::Float;
				r.FloatValue = FloatValue + v.FloatValue;
				return r;
			case ValueType::String:
				r.ValueType = ValueType::String;
				r.StringValue = toString() + v.StringValue;
			}
			break;
		case ValueType::String:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::String;
				r.StringValue = StringValue + v.toString();
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::String;
				r.StringValue = StringValue + v.toString();
				return r;
			case ValueType::String:
				r.ValueType = ValueType::String;
				r.StringValue = StringValue + v.StringValue;
			}
			break;
		}
		return r;
	}
	Value operator -(Value& v)
	{
		Value r;

		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("binary operator '-' isn't defined for null"));
		}
		if (ValueType == ValueType::Array || v.ValueType == ValueType::Array) {
			throw std::runtime_error(RuntimeException("binary operator '-' isn't defined for array"));
		}
		if (ValueType == ValueType::String || v.ValueType == ValueType::String) {
			throw std::runtime_error(RuntimeException("binary operator '-' isn't defined for string"));
		}

		switch (ValueType) {
		case ValueType::Int:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Int;
				r.IntValue = IntValue - v.IntValue;
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::Float;
				r.FloatValue = (double)IntValue - v.FloatValue;
				return r;
			}
			break;
		case ValueType::Float:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Float;
				r.FloatValue = FloatValue - v.IntValue;
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::Float;
				r.FloatValue = FloatValue - v.FloatValue;
				return r;
			}
			break;
		}
		return r;
	}
	Value operator *(Value& v)
	{
		Value r;

		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("binary operator '*' isn't defined for null"));
		}
		if (ValueType == ValueType::Array || v.ValueType == ValueType::Array) {
			throw std::runtime_error(RuntimeException("binary operator '*' isn't defined for array"));
		}
		if (ValueType == ValueType::String || v.ValueType == ValueType::String) {
			throw std::runtime_error(RuntimeException("binary operator '*' isn't defined for string"));
		}

		switch (ValueType) {
		case ValueType::Int:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Int;
				r.IntValue = IntValue * v.IntValue;
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::Float;
				r.FloatValue = (double)IntValue * v.FloatValue;
				return r;
			}
			break;
		case ValueType::Float:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Float;
				r.FloatValue = FloatValue * v.IntValue;
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::Float;
				r.FloatValue = FloatValue * v.FloatValue;
				return r;
			}
			break;
		}
		return r;
	}
	Value operator /(Value& v)
	{
		Value r;

		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("binary operator '/' isn't defined for null"));
		}
		if (ValueType == ValueType::Array || v.ValueType == ValueType::Array) {
			throw std::runtime_error(RuntimeException("binary operator '/' isn't defined for array"));
		}
		if (ValueType == ValueType::String || v.ValueType == ValueType::String) {
			throw std::runtime_error(RuntimeException("binary operator '/' isn't defined for string"));
		}

		switch (ValueType) {
		case ValueType::Int:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Int;
				r.IntValue = IntValue / v.IntValue;
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::Float;
				r.FloatValue = (double)IntValue / v.FloatValue;
				return r;
			}
			break;
		case ValueType::Float:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Float;
				r.FloatValue = FloatValue / v.IntValue;
				return r;
			case ValueType::Float:
				r.ValueType = ValueType::Float;
				r.FloatValue = FloatValue / v.FloatValue;
				return r;
			}
			break;
		}
		return r;
	}
	Value operator %(Value& v)
	{
		Value r;

		if (ValueType == ValueType::Null || v.ValueType == ValueType::Null) {
			throw std::runtime_error(RuntimeException("binary operator '%' isn't defined for null"));
		}
		if (ValueType == ValueType::Array || v.ValueType == ValueType::Array) {
			throw std::runtime_error(RuntimeException("binary operator '%' isn't defined for array"));
		}
		if (ValueType == ValueType::String || v.ValueType == ValueType::String) {
			throw std::runtime_error(RuntimeException("binary operator '%' isn't defined for string"));
		}
		if (ValueType == ValueType::Float || v.ValueType == ValueType::Float) {
			throw std::runtime_error(RuntimeException("binary operator '%' isn't defined for float"));
		}

		switch (ValueType) {
		case ValueType::Int:
			switch (v.ValueType) {
			case ValueType::Int:
				r.ValueType = ValueType::Int;
				r.IntValue = IntValue % v.IntValue;
				return r;
			}
			break;
		}
		return r;
	}
	//ok
	std::shared_ptr<Value> operator [](int idx)
	{
		std::shared_ptr<Value> r;

		if (idx < 1) {
			throw std::runtime_error(RuntimeException("assigned null for index"));
		}
		switch (ValueType) {
		case ValueType::Null:
		case ValueType::Int:
		case ValueType::Float:
		case ValueType::String:
			throw std::runtime_error(RuntimeException("assigned index for non-array"));
			break;
		case ValueType::Array:
			r = (*ArrayValue.get())[idx];
			break;
		}
		return r;
	}
	//op1
	//ok
	Value operator +()
	{
		Value ret;
		switch (ValueType) {
		case ValueType::Null:
			throw std::runtime_error(RuntimeException("unary operator '+' isn't defined for null"));
			break;
		case ValueType::String:
			throw std::runtime_error(RuntimeException("unary operator '+' isn't defined for string"));
			break;
		case ValueType::Array:
			throw std::runtime_error(RuntimeException("unary operator '+' isn't defined for array"));
			break;
		case ValueType::Int:
			ret = *this;
			break;
		case ValueType::Float:
			ret = *this;
			break;
		}
		return ret;
	}
	//ok
	Value operator -()
	{
		Value ret;
		switch (ValueType) {
		case ValueType::Null:
			throw std::runtime_error(RuntimeException("unary operator '-' isn't defined for null"));
			break;
		case ValueType::String:
			throw std::runtime_error(RuntimeException("unary operator '-' isn't defined for string"));
			break;
		case ValueType::Array:
			throw std::runtime_error(RuntimeException("unary operator '-' isn't defined for array"));
			break;
		case ValueType::Int:
			ret = *this;
			ret.IntValue = -ret.IntValue;
			break;
		case ValueType::Float:
			ret = *this;
			ret.FloatValue = -ret.FloatValue;
			break;
		}
		return ret;
	}
	//ok
	Value operator !()
	{
		Value ret(ValueType == ValueType::Null || IsFalse());
		return ret;
	}
	//cast
	//ok
	operator int()
	{
		return toInt();
	}
	//ok
	operator std::string()
	{
		return toString();
	}

	int IntValue;
	double FloatValue;
	std::string StringValue;
	std::shared_ptr<std::vector<std::shared_ptr<Value> > > ArrayValue;
	ValueType::ValueType ValueType;
};

}
}
}


#endif

