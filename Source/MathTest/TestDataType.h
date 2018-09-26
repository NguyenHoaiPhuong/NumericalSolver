#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>

#pragma region TestHex2String
std::string to_hex(size_t i)
{
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(16) << std::hex << i;
	return oss.str();
}
void TestHex2String()
{
	std::string str = to_hex(16);
	std::cout << str << std::endl;
}
#pragma endregion

#pragma region TestTypeInfo
struct A {};
struct B : public A {};
struct C : public A {};

template<typename T>
struct hash_by_type
{
	std::string operator()()
	{
		return to_hex(typeid(T).hash_code());
	}
};
template<typename T>
struct hash_by_type<std::vector<T>>
{
	std::string operator()()
	{
		return "V" + hash_by_type<T>()();
	}
};
template<typename T>
std::string hash_by_variable(T& t)
{
	return to_hex(typeid(t).hash_code());
}

using TypeInfoRef = std::reference_wrapper<const std::type_info>;
struct Hasher {
	std::size_t operator()(TypeInfoRef code) const
	{
		return code.get().hash_code();
	}
};
struct EqualTo {
	bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
	{
		return lhs.get() == rhs.get();
	}
};
void TestTypeInfo()
{
	std::unordered_map<TypeInfoRef, std::string, Hasher, EqualTo> typenames;
	typenames[typeid(int)] = "int";
	typenames[typeid(double)] = "double";
	typenames[typeid(A)] = "A";
	typenames[typeid(B)] = "B";
	typenames[typeid(C)] = "C";

	int i;
	std::cout << typeid(i).name() << std::endl;
	std::cout << "Type of i is " << typenames[typeid(i)] << std::endl;
	std::cout << hash_by_type<int>()() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	double d;
	std::cout << typeid(d).name() << std::endl;
	std::cout << "Type of d is " << typenames[typeid(d)] << std::endl;
	std::cout << "Hash by type: " << hash_by_type<double>()() << std::endl;
	std::cout << "Hash by variable: " << hash_by_variable<double>(d) << std::endl;
	std::cout << "---------------------------------" << std::endl;

	A a;
	std::cout << typeid(a).name() << std::endl;
	std::cout << "Type of a is " << typenames[typeid(a)] << std::endl;
	std::cout << "Hash by type: " << hash_by_type<A>()() << std::endl;
	std::cout << "Hash by variable: " << hash_by_variable<A>(a) << std::endl;
	std::cout << "---------------------------------" << std::endl;

	B* b = new B();
	std::cout << typeid(*b).name() << std::endl;
	std::cout << "Type of b is " << typenames[typeid(*b)] << std::endl;
	std::cout << "Hash by type: " << hash_by_type<B>()() << std::endl;
	std::cout << "Hash by variable: " << hash_by_variable<A>(*b) << std::endl;
	std::cout << "---------------------------------" << std::endl;

	A* c = new C();
	std::cout << typeid(*c).name() << std::endl;
	std::cout << "Type of c is " << typenames[typeid(*c)] << std::endl;
	std::cout << "Hash by variable: " << hash_by_variable<A>(*c) << std::endl;
	std::cout << "---------------------------------" << std::endl;

	std::cout << "Hash by type: " << hash_by_type<std::vector<double>>()() << std::endl;
	std::cout << "---------------------------------" << std::endl;
}
#pragma endregion