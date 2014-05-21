/*
 * AEWindow.hpp
 *
 *  Created on: Apr 28, 2014
 *      Author: ross
 */

#ifndef AERENDERWINDOW_H_
#define AERENDERWINDOW_H_

#include <string>


class AERenderWindow {

public:

	virtual void create(const std::string &name, unsigned int width, unsigned int height, bool fullScreen) = 0;

	virtual void setFullScreen(bool fullScreen, unsigned int width, unsigned int height)
	{(void)fullScreen; (void)width; (void)height;}

	virtual void release(void) = 0;

	virtual void resize(unsigned int width, unsigned int height) = 0;

	virtual void reposition(int left, int top) = 0;

	virtual bool isVisible(void) const { return true; }

	virtual void setVisible(bool visible) { (void)visible; }

	virtual bool isHidden(void) const { return false; }

	virtual void setHidden(bool hidden) { (void)hidden; }

	virtual void setVSyncEnabled(bool vsync) { (void)vsync; }

	virtual bool isVSyncEnabled() const { return false; }

	virtual void setVSyncInterval(unsigned int interval) { (void)interval; }

	virtual unsigned int getVSyncInterval() const { return 1; }

	virtual bool isClosed(void) const = 0;

	virtual bool isPrimary(void) const;

	virtual bool isFullScreen(void) const;

	virtual void getMetrics(unsigned int &width, unsigned int &height, unsigned int &colorDepth, int &left, int &top);

	virtual void swapBuffers() = 0;

protected:

	AERenderWindow();
	~AERenderWindow() {}
	bool mIsFullScreen;
	bool mIsPrimary;
	int mLeft;
	int mTop;
};

#endif /* AEWINDOW_H_ */
