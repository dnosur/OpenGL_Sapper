#pragma once
struct Size
{
	int width, height;
public:

	Size();
	Size(int width, int height);

	int GetWidth();
	int GetHeight();

	void SetWidth(int width);
	void SetHeight(int height);

	bool operator==(const Size& other) const;
	bool operator!=(const Size& other) const;
	Size& operator=(const Size& other);
};