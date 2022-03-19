#include <stdlib.h>
#include <assert.h>

/**
	Simple and so wrong class that tries to representate variable as uniform object.
	No allocations. Only typesafe. 
	There are asserts in wrong usecases.
*/
class var {
public:
	// Default constructor
	var() : data((void*)0), type(undefined), size_(0) 
	{}
	// Const string constructor
	var(const char* cstr) : type(string), size_(strlen(cstr)), data(cstr) 
	{}
	// Character array constructor
	var(char* str) : type(string), size_(strlen(str)), data(str) 
	{}
	// Const pointer constructor with safe explicit size
	var(const void* ptr, long long _size) : type(pointer), size_(_size), data((void*)(ptr)) 
	{}
	// Pointer constructor with safe explicit size
	var(void* ptr, long long _size) : type(pointer), size_(_size), data(ptr) 
	{}
	// Numeric constructor
	var(double _hfp) : type(number), size_(8), data(_hfp) 
	{}
	// Copy constructor
	var(var const& cpy) : data(cpy.data), type(cpy.type) , size_(cpy.size_) 
	{}
	// Copy assignment (idk is this safe enough)
	var& operator=(var const& cpy) {
		type = cpy.type;
		size_ = cpy.size_;
		data = cpy.data;
		return *this;
	}
	// @returns Size of object (specially useful for string objects)
	long long size() const { 
		return size_;
	}
	// Functor operator (idk what the f... this thing doing here..)
	var& operator()(var const& fcpy) {
		type = fcpy.type;
		size_ = fcpy.size_;
		data = fcpy.data;
		return *this;
	}
	// Numeric conversation operator
	operator long double() const { 
		assert(type == number && "var have incompatible type"); 
		return data.num; 
	}
	// Pointer conversation
	operator void* () const { 
		assert(type == pointer && "var have incompatible type"); 
		return data.ptr; 
	}
	// Characters array conversation
	operator char* () const { 
		assert(type == string && "var have incompatible type"); 
		return data.cstr; 
	}
	// String conversation 
	operator const char* () const { 
		assert(type == string && "var have incompatible type"); 
		return data.cstr; 
	}


private:
	// defined by constructor type of data that
	// var handle
	enum {
		undefined,
		pointer,
		string,
		number
	} type;

	// different kinds of data that shares 
	// same space in memory by 'union'
	union data {
		char* cstr;
		long double num;
		void* ptr;

		data(void* _ptr) : ptr(_ptr) {}
		data(const char* _cstr) : cstr((char*)(_cstr)) {}
		data(double d) : num(d) {}
	} data;
	// size of var object
	long long size_;

	// compare operator
	friend bool operator==(var const& a, var const& b);
	// compare operator
	friend bool operator!=(var const& a, var const& b);
};

bool operator==(var const& a, var const& b) {
	if (a.type != b.type) return false;
	if (a.size_ != b.size_) return false;
	if (a.type == var::number)
		return a.data.num == b.data.num;
	else if (a.type == var::pointer)
		return !memcmp(a.data.ptr, b.data.ptr, a.size_);
	else if (a.type == var::string)
		return !strcmp(a.data.cstr, b.data.cstr);
	else
		return true;
}

bool operator!=(var const& a, var const& b) {
	return !(a == b);
}

