#pragma once
#include <tuple>
#include <memory>
#include <stdexcept>

class empty_optional : public std::runtime_error {
public:
	empty_optional(std::string mess)
		:std::runtime_error(mess)
	{}
};

class none_t {};

template <typename T>
class Optional {
	std::unique_ptr<T> m_ptr;

public:
	Optional(none_t t) {}

	template<typename... Args>
	Optional(Args&&... args) 
		:m_ptr(make_unique<T>(std::forward<Args>(args)...))
	{}

	Optional() 
		:m_ptr(std::make_unique<T>())
	{}

	operator bool() const {
		return bool(m_ptr);
	}

	T& operator*() {
		return *m_ptr;
	}

	const T& operator*() const {
		return *m_ptr;
	}

	T& get() {
		if (!m_ptr) {
			throw empty_optional(typeid(T).name());
		}
		return *m_ptr;
	}

	const T& get() const {
		if (!m_ptr) {
			throw empty_optional(typeid(T).name());
		}
		return *m_ptr;
	}

};