/*
 * GlXWindow.h
 *
 *  Created on: Apr 28, 2014
 *      Author: ross
 */

#ifndef GLXWINDOW_H_
#define GLXWINDOW_H_

#include "AERenderWindow.hpp"
#include <X11/Xlib.h>

class GlXWindow {

public:
	GlXWindow();

	void create(const std::string &name, unsigned int width, unsigned int height, bool fullScreen);

	void setFullScreen(bool fullscreen, uint width, uint height);

	void release(void);

	bool isClosed(void) const;

	bool isVisible(void) const;

	void setVisible(bool visible);

	bool isHidden(void) const { return mHidden; }

	void setHidden(bool visible);

	void setVSyncEnabled(bool vsync);

	bool isVSyncEnabled() const;

	void setVSyncInterval(unsigned int interval);

	unsigned int getVSyncInterval() const;

	void reposition(int left, int top);

	void resize(unsigned int width, unsigned int height);

	void swapBuffers();

	bool isPrimary(void) const;

	bool isFullScreen(void) const;

	void getMetrics(unsigned int &width, unsigned int &height, unsigned int &colorDepth, int &left, int &top);

private:

	bool mClosed;
	bool mVisible;
	bool mHidden;
	bool mVSync;
	int mVSyncInterval;
	bool mIsFullScreen;
	bool mIsPrimary;

	::Window mWindow;
	::Display *mxDisplay;

	void switchFullScreen(bool fullscreen);
 };

#endif /* GLXWINDOW_H_ */
