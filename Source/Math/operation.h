#pragma once
#include <iostream>
#include <unordered_map>
#include <typeinfo>

/*************************** INTRODUCTION *******************************/
/* factory class: a family of all specific factory<OPERATION> class		*/
/* factory<OPERATION>: Singleton partern								*/
/* factory<OPERATION> & operation<R, Name, OArgs>: Observer partern		*/
/* implementation<O<R, Name, OArgs...>, IArgs...>: O<R, Name, OArgs...> */
/************************************************************************/


// Singleton operation factory
namespace op
{	
	// Declaration
	template<class OPERATION>
	class factory
	{
	private:
		std::unordered_map<std::string, OPERATION*> map_;

		// Constructor
		factory();

		// Convert a hex to string
		static std::string to_hex(size_t i);

		// Type info
		template<typename T>
		struct hash_by_type 
		{ 
			std::string operator()() 
			{
				return to_hex(typeid(T).hash_code());
			}
		};
		template<typename T>
		struct hash_by_type<std::reference_wrapper<T>>
		{
			std::string operator()()
			{
				return "R" + hash_by_type<T>()();
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
		struct hash_by_type<const std::vector<T>>
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
		template<typename T>
		std::string hash_by_variable(std::reference_wrapper<T>& t)
		{
			return "R" + hash_by_variable(t.get());
		}
		template<typename T>
		std::string hash_by_variable(const std::reference_wrapper<T>& t)
		{
			return "R" + hash_by_variable(t.get());
		}
		template<typename T>
		std::string hash_by_variable(std::vector<T>& v)
		{
			if (!std::is_fundamental<T>::value) {
				if (v.size() > 0) {
					std::string h = hash_by_variable(v.at(0));
					if (std::all_of(v.begin() + 1, v.end(), [&](T& t) { return h == hash_by_variable(t); }))
						return "V" + h;
				}
			}
			return "V" + hash_by_type<T>()();
		}
		template<typename T>
		std::string hash_by_variable(const std::vector<T>& v)
		{
			if (!std::is_fundamental<T>::value) {
				if (v.size() > 0) {
					std::string h = hash_by_variable(v.at(0));
					if (std::all_of(v.begin() + 1, v.end(), [&](const T& t) { return h == hash_by_variable(t); }))
						return "V" + h;
				}
			}
			return "V" + hash_by_type<T>()();
		}

	public:
		// Register the operation into the map_
		template<typename... Ts>
		void reg(OPERATION* A)
		{
			std::string hash;
			for (auto h : { hash_by_type<Ts>()()... }) hash.append(h);
			map_.insert(make_pair(hash, A));
		}

		// Return the operation by arguments' types
		template<class... Ts>
		OPERATION* operation(Ts&... ts)
		{
			std::string hash;
			for (auto h : { hash_by_variable(ts)... }) hash.append(h);
			auto it = map_.find(hash);
			if (it == map_.end()) return 0;
			else return it->second;
		}

		static factory<OPERATION>& get()
		{
			static factory<OPERATION> instance;
			return instance;
		}
	};

	// Definition
	template<class OPERATION>
	factory<OPERATION>::factory()
	{
		map_ = {};
	}

	template<class OPERATION>
	std::string factory<OPERATION>::to_hex(size_t i)
	{
		std::ostringstream oss;
		oss << std::setfill('0') << std::setw(16) << std::hex << i;
		return oss.str();
	}
}

// Operation Interface declaration
namespace op
{
	// R: return type, such as void / int / matrix /...
	// Name: 
	// OArgs:	Output arguments
	// Example:
	template <typename R, class Name, typename... OArgs>
	class operation
	{
	public:
		// Destructor
		virtual ~operation() {}

		virtual R operator()(OArgs&...) = 0;

		static R perform(OArgs&...args)
		{
			operation<R, Name, OArgs...>* impl = factory< operation<R, Name, OArgs...> >::get().operation(args...);
			if (impl)
			{
				return (*impl)(args...);
			}
			else
			{
				throw std::runtime_error("Unable to locate implementation!!!");
			}
		}
	};
}

namespace op
{
	template <typename... OArgs>
	class type_convert {
		template<bool...> struct bool_pack;
		template<bool... b>
		using all_true = std::is_same<bool_pack<true, b...>, bool_pack<b..., true>>;

		template<typename T, typename U> 
		struct is_ok
		{
			static constexpr bool value = std::is_convertible<T&, U&>::value; 
		};
		template<typename T, typename U>
		struct is_ok<T*, U*>
		{
			static constexpr bool value = is_ok<T&, U&>::value;
		};
		template<typename T, typename U>
		struct is_ok< std::vector<T>, std::vector<U> >
		{
			static constexpr bool value = is_ok<T, U>::value;
		};
		template<typename T, typename U>
		struct is_ok< std::vector<T> const, std::vector<U> const >
		{
			static constexpr bool value = is_ok<T, U>::value;
		};
		template<typename T, typename U>
		struct is_ok< std::reference_wrapper<T>, std::reference_wrapper<U> >
		{
			static constexpr bool value = is_ok<T, U>::value;
		};
		template<typename T, typename U>
		struct is_ok< std::reference_wrapper<T> const, std::reference_wrapper<U> const >
		{
			static constexpr bool value = is_ok<T, U>::value;
		};
	public:
		template<typename... IArgs>
		static bool valid() { return all_true<is_ok<IArgs, OArgs>::value...>::value; }
	};
}

// Implementation class
namespace op
{
	// O: Operation
	// IArgs: Input Arguments
	template <typename O, typename... IArgs>
	class implementation : public O {};

	// R, Name, OArgs: Input types for Operation O
	template <typename R, class Name, typename... OArgs, template<class, typename...> class O, typename... IArgs>
	class implementation<O<R, Name, OArgs...>, IArgs...> : public O<R, Name, OArgs...>
	{
	private:
		static implementation<O<R, Name, OArgs...>, IArgs...> _instance;
		implementation()
		{
			if (type_convert<OArgs...>::template valid<IArgs...>())
			{
				factory<O<R, Name, OArgs...>>::get().template reg<IArgs...>(this);
			}
			else
			{
				throw std::runtime_error("Invalid operation registration!!!");
			}
		}
	public:
		static implementation<O<R, Name, OArgs...>, IArgs...>& get() { return _instance; };
		virtual R operator()(OArgs&...);
	};

	template <typename R, typename Name, typename... OArgs, template<class, typename...> class O, typename... IArgs>
	implementation<O<R, Name, OArgs...>, IArgs...> implementation<O<R, Name, OArgs...>, IArgs...>::_instance = implementation();


#  define __implementation_name(a,b) a ## b
#  define __implementation_def(op, ...) implementation< op, __VA_ARGS__ >
#  define __implementation_ex(rtn, op, cnt, impl) impl __implementation_name(op,cnt) = impl::get(); template<> rtn impl
#  define __implementation(rtn, op, ...) __implementation_ex( rtn, op, __COUNTER__, __implementation_def(op,__VA_ARGS__) )
}

