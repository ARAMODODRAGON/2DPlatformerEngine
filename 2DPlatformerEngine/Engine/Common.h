#ifndef ENGINE_COMMON_H
#define ENGINE_COMMON_H

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char ubyte;

#include <string>
using std::string;

#include <iostream>

#define TEXT(value) std::to_string(value)
#define PRINT(message) std::cout << message << std::endl
#define PRINT_ERROR(message) std::cout << "[ERROR]: " << message << std::endl << " -{FILE}: (Line:" << __LINE__ << ") " << __FILE__ << std::endl

// used to quickly create a singleton class
#define SINGLETON(TYPE) private: \
~TYPE(); \
TYPE(); \
TYPE(const TYPE&)				= delete; \
TYPE& operator=(const TYPE&)	= delete; \
TYPE(TYPE&&)					= delete; \
TYPE& operator=(TYPE&&)			= delete; \
public: \
static TYPE* GetSingleton() { \
	static TYPE singleton; \
	return &singleton; \
} \
private:

#define SINGLETON_HIDE_CONSTRUCTOR(TYPE) private: \
~TYPE() { } \
TYPE() { } \
TYPE(const TYPE&)				= delete; \
TYPE& operator=(const TYPE&)	= delete; \
TYPE(TYPE&&)					= delete; \
TYPE& operator=(TYPE&&)			= delete; \
public: \
static TYPE* GetSingleton() { \
	static TYPE singleton = TYPE(); \
	return &singleton; \
} \
private:


#define QUICK_GETTER(TYPE, VARIABLE_NAME, PROPERTY_NAME) \
TYPE Get##PROPERTY_NAME() const { return VARIABLE_NAME; }

#define QUICK_SETTER(TYPE, VARIABLE_NAME, PROPERTY_NAME) \
void Set##PROPERTY_NAME(const TYPE& PROPERTY_NAME) { VARIABLE_NAME = PROPERTY_NAME; }


#endif // !ENGINE_COMMON_H