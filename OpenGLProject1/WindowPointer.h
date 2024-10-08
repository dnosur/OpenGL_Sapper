#pragma once
#include <iostream>

template <typename T>
struct WindowPointer
{
private:
	char* title;
	T value;
	bool undefined;

public:

	WindowPointer();
	WindowPointer(const char* title, T value);

	const char* GetTitle();

	void SetValue(T value);
	T GetValue();

	const bool IsUndefined();

	bool operator==(const WindowPointer& other) const;
	bool operator!=(const WindowPointer& other) const;
	WindowPointer& operator=(const WindowPointer& other);
};

template<typename T>
inline WindowPointer<T>::WindowPointer()
{
	title = (char*)"Undefined";
	undefined = true;
}

template<typename T>
inline WindowPointer<T>::WindowPointer(const char* title, T value)
{
	this->title = new char[strlen(title) + 1];
	strcpy_s(this->title, strlen(title) + 1, title);

	this->value = value;
	undefined = false;
}

template<typename T>
inline const char* WindowPointer<T>::GetTitle()
{
	return title;
}

template<typename T>
inline void WindowPointer<T>::SetValue(T value)
{
	this->value = value;
}

template<typename T>
inline T WindowPointer<T>::GetValue()
{
	return value;
}

template<typename T>
inline const bool WindowPointer<T>::IsUndefined()
{
	return undefined;
}

template<typename T>
inline bool WindowPointer<T>::operator==(const WindowPointer& other) const
{
	return value == other.value && strcmp(title, other.title) && undefined == other.undefined;
}

template<typename T>
inline bool WindowPointer<T>::operator!=(const WindowPointer& other) const
{
	return !(*this == other);
}

template<typename T>
inline WindowPointer<T>& WindowPointer<T>::operator=(const WindowPointer& other)
{
	if (this != &other)
	{
		value = other.value;
		title = other.title;
		undefined = other.undefined;
	}
	return *this;
}
