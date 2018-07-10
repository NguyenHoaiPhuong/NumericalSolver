#pragma once
#include <iostream>
#include <unordered_map>
#include <typeinfo>

namespace op
{
	// Singleton operation factory
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

		// Return an operation by arguments' types
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
}

namespace op
{
	template <typename R, class Name, typename... OArgs>
	class operation
	{
	public:
		// Destructor
		virtual ~operation();

		virtual R operator()(OArgs&...) = 0;

		static R perform(OArgs&...args);		
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


namespace op
{
	template <typename O, typename... IArgs>
	class implementation : public O {};

	template <typename R, class Name, typename... OArgs, template<class, typename...> class O, typename... IArgs>
	class implementation<O<R, Name, OArgs...>, IArgs...> : public O<R, Name, OArgs...>
	{
	private:
		static implementation<O<R, Name, OArgs...>, IArgs...> _instance;
		implementation()
		{
			if (type_convert_t<OArgs...>::template valid<IArgs...>())
			{
				factory_t<O<R, Name, OArgs...>>::get().template reg<IArgs...>(this);
			}
			else
			{
				throw std::runtime_error(util::str("Invalid operation registration of : ", util::demangle(typeid(this).name())));
			}
		}
	public:
		static implementation<O<R, Name, OArgs...>, IArgs...>& get() { return _instance; };
		virtual R operator()(OArgs&...);
	};
}