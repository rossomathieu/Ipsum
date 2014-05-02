/*
 * GlXWindow.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: ross
 */

#include "GlXWindow.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdexcept>

GlXWindow::GlXWindow() {

	mWindow = 0;

	mIsFullScreen = false;
	mClosed = false;
	//mActive = false;
	mHidden = false;
	mVSync = false;
	mVSyncInterval = 1;
}

GlXWindow::~GlXWindow() {

}

void GlXWindow::create(const std::string &name, uint width, uint height, bool fullScreen) {

	Display *mxDisplay = XOpenDisplay(NULL);
	std::string title = name;
	//uint samples = 0;
	//short frequency = 0;
	bool vsync = false;
	bool hidden = false;
	unsigned int vsyncInterval = 1;
	//int gamma = 0;
	::GLXContext glxContext = 0;
	::GLXDrawable glxDrawable = 0;
	Window externalWindow = 0;
	Window parentWindow = DefaultRootWindow(mxDisplay);
	int left = DisplayWidth(mxDisplay, DefaultScreen(mxDisplay)) / 2 - width / 2;
	int top = DisplayHeight(mxDisplay, DefaultScreen(mxDisplay)) / 2 - height / 2;

	mIsFullScreen = fullScreen;

	//Validate parentWindowHandle
	if(parentWindow != DefaultRootWindow(mxDisplay)) {

		XWindowAttributes windowAttrib;

		if(!XGetWindowAttributes(mxDisplay, parentWindow, &windowAttrib) ||
				windowAttrib.root != DefaultRootWindow(mxDisplay)) {

			throw std::exception("Invalid parentWindowHandle (wrong server or screen");
		}
	}

	//Validate externalWindowHandle
	if(externalWindow != 0) {

		XWindowAttributes windowAttrib;

		if(!XGetWindowAttributes(mxDisplay, externalWindow, &windowAttrib) ||
				windowAttrib.root != DefaultRootWindow(mxDisplay)) {

			throw std::exception("Invalid externalWindowHandle (wrong server or screen");
		}

		glxDrawable = externalWindow;
	}

	XSetWindowAttributes attr;
	ulong mask;
	XVisualInfo *visualInfo;

	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.colormap = XCreateColormap(mxDisplay, DefaultRootWindow(mxDisplay), visualInfo->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | VisibilityChangeMask | FocusChangeMask;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

	mWindow = XCreateWindow(mxDisplay, parentWindow, left, top, width, height, 0,
			visualInfo->depth, InputOutput, visualInfo->visual, mask, &attr);

	XFree(visualInfo);

	if(!mWindow) {

		throw std::exception("Unable to create an X Window");
	}

	glxDrawable = mWindow;

	setHidden(hidden);
	XFlush(mxDisplay);

	setVSyncInterval(vsyncInterval);
	setVSyncEnabled(vsync);
}

void GlXWindow::setFullscreen(bool fullscreen, uint width, uint height) {


}

void GlXWindow::release(void) {


}

bool GlXWindow::isClosed(void) const {

	return mClosed;
}

bool GlXWindow::isVisible(void) const {

	return mVisible;
}

void GlXWindow::setVisible(bool visible) {

	mVisible = visible;
}

void GlXWindow::setHidden(bool hidden) {

	mHidden = hidden;

	if(hidden) {

		XUnmapWindow(mxDisplay, mWindow);
	} else {

		XMapWindow(mxDisplay, mWindow);

		if(mIsFullScreen) {

			switchFullScreen(true);
		}
	}
}

void GlXWindow::setVSyncEnabled(bool vsync) {

	mVSync = vsync;

	::GLXDrawable oldDrawable = glXGetCurrentDrawable();
	::GLXContext oldContext = glXGetCurrentContext();

	//glXSwapIntervalSGI(vsync ? mVSyncInterval : 0);

	glXMakeCurrent(mxDisplay, oldDrawable, oldContext);

}

bool GlXWindow::isVSyncEnabled() const {

	return mVSync;

}

void GlXWindow::setVSyncInterval(unsigned int interval) {

	mVSyncInterval = interval;

		if(mVSync)
			setVSyncEnabled(true);

}

unsigned int GlXWindow::getVSyncInterval() const {

	return mVSyncInterval;
}

void GlXWindow::reposition(int left, int top) {

	if(mClosed)
		return;

	XMoveWindow(mxDisplay, mWindow, left, top);
}

void GlXWindow::resize(unsigned int width, unsigned int height) {

	if(mClosed)
		return;

	XResizeWindow(mxDisplay, mWindow, width, height);
}

void GlXWindow::swapBuffers() {


}

