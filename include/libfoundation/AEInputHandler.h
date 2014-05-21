/*
 * AEInputHandler.h
 *
 *  Created on: Apr 29, 2014
 *      Author: ross
 */

#ifndef AEINPUTHANDLER_H_
#define AEINPUTHANDLER_H_

#include "libaepatts/AESingleton.hpp"
#include "libaepatts/AECommand.hpp"
#include "AERenderWindow.hpp"
#include "AEMouse.hpp"
#include "AEKeyboard.hpp"

class AEInputHandler {
public:
	enum AbstractControlIndex{

		AEKEY_A,
		AEKEY_B,
		AEKEY_C,
		AEKEY_D,
		AEKEY_E,
		AEKEY_F,
		AEKEY_G,
		AEKEY_H,
		AEKEY_I,
		AEKEY_J,
		AEKEY_K,
		AEKEY_L,
		AEKEY_M,
		AEKEY_N,
		AEKEY_O,
		AEKEY_P,
		AEKEY_Q,
		AEKEY_R,
		AEKEY_S,
		AEKEY_T,
		AEKEY_U,
		AEKEY_V,
		AEKEY_W,
		AEKEY_X,
		AEKEY_Y,
		AEKEY_Z,
		AEKEY_ESCAPE,
		AEKEY_RETURN,
		AEKEY_SPACE,
		AEKEY_LCONTROL,
		AEKEY_RCONTROL,
		AEKEY_LSHIFT,
		AEKEY_RSHIFT,
		AEKEY_LALT,
		AEKEY_RALT,
		AEKEY_1,
		AEKEY_2,
		AEKEY_3,
		AEKEY_4,
		AEKEY_5,


	};
	AEInputHandler();
	virtual ~AEInputHandler();

	void init(AERenderWindow *window);

	void release();

	void pollEvents();

	bool isKeyboardAwake();

	bool isMouseAwake();

	void setKeyboardAwake(bool awake);

	void setMouseAwake(bool awake);

	bool isKeyPressed(AbstractControlIndex key);

	bool isKeyReleased(AbstractControlIndex key);

	void setViewportSize(int viewportX, int viewportY);

	void getMouseCoordinates(int &mouseX, int &mouseY);

	//Either this function will be stupid... or really useful.. haven't decided.
	//There, however, needs to be a way to remap key functionality.. not sure if
	//this is the correct way yet....
	bool mapKeyToCommand(AbstractControlIndex key, AECommand* command);

	//Need a way to pass platform specific window pointers
	//to input classes, so input classes can be aware of what
	//window to listen to for proper input events.
	//May implement some for of support interface, one for GL
	//and one for DX.  Subclass these with platform specific
	//functionality... so GLXGL support and WGL support, etc.

private:

	AECommand* command;
	int mViewportX;
	int mViewportY;
	int mMouseX;
	int mMouseY;
};

#endif /* AEINPUTHANDLER_H_ */
