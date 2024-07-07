#pragma once

template <typename T>
class Singleton {
protected:
	Singleton() = default;
	virtual ~Singleton(){};
	Singleton(const Singleton& r) = default;
	Singleton& operator=(const Singleton& r) = default;

public:
	static T* Get_Instance() {
		static T inst;
		return &inst;
	};
};