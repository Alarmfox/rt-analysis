#pragma once

class Semaphore {

private:
	unsigned int mValue;

public:
	Semaphore(const unsigned int value = 0): mValue(value){}
	//getters setters
	inline const unsigned int getValue()const { return mValue; }
	inline void setValue(const unsigned int value) { mValue = value; }
};