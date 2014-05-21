/*
 * AESingleton.hpp
 *
 *  Created on: Apr 28, 2014
 *      Author: ross
 */

#ifndef AESINGLETON_HPP_
#define AESINGLETON_HPP_

#include <assert.h>

/**
This class is a very useful and common data structure, especially in games.
A singleton is a nice way of making an object "global", without the hassle of
making variables global and externing them all over the place.  If a class is
derived from AESingleton, and then an instance is created, you can access the
object from anywhere by calling the getSingleton method of the class.
*/

template <typename T> class AESingleton {

	//The one and only instance of this class
	static T* msSingleton;

public:

	//Constructs our one and only instance
	AESingleton() {

		assert(!msSingleton);

		int offset = (int)(T*)1 - (int)(AESingleton<T>*)(T*)1;
		msSingleton = (T*)((int)this + offset);
	}

	//Destroys the one and only instance
	~AESingleton() {

		assert(msSingleton);

		msSingleton = 0;
	}

	//Return the singleton
	static T& getSingleton() {

		assert(msSingleton);

		return (*msSingleton);
	}

	//Return a pointer to the singleton
	static T* getSingletonPtr() {

		return msSingleton;
	}
};

//Initialize the static T* msSingleton member for each new singleton type
template <typename T> T* AESingleton<T>::msSingleton = 0;

#endif /* AESINGLETON_HPP_ */
