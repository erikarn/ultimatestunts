/***************************************************************************
                          gui.h  -  The graphical user interface: menu's etc.
                             -------------------
    begin                : vr jan 31 2003
    copyright            : (C) 2003 by CJP
    email                : cornware-cjp@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GUI_H
#define GUI_H

#include <vector>
namespace std {}
using namespace std;

#include "widget.h"
#include "guipage.h"
#include "winsystem.h"
#include "vector.h"

/**
  *@author CJP
  */

class CGUI : public CWidget
{
public:
	CGUI(CWinSystem *winsys);
	virtual ~CGUI();

	virtual int onMouseMove(int x, int y, unsigned int buttons);
	virtual int onMouseClick(int x, int y, unsigned int buttons);
	virtual int onKeyPress(int key);
	virtual int onResize(int x, int y, int w, int h);
	virtual int onRedraw();
	virtual int onIdle();

	virtual void start(); //returns when an exit command is given

protected:
	CWinSystem *m_WinSys;
	CGUIPage *m_ChildWidget;

	void enter2DMode();
	void leave2DMode();

	//Meta-function; changes appearance based on metaData
	CString showSettingBox(const CString &field, const CString &deflt, const CString &metaData, bool *cancelled=NULL);

	CString showInputBox(const CString &title, const CString &deflt="", bool *cancelled=NULL);
	CString showKeyInputBox(const CString &title, const CString &deflt="", bool *cancelled=NULL);
	CString showChoiceBox(const CString &title, const vector<CString> &options, const CString &deflt="", bool *cancelled=NULL);
	bool showYNMessageBox(const CString &title, bool *cancelled=NULL);
	void showMessageBox(const CString &title);
	CVector showColorSelect(const CString &title, CVector deflt, bool *cancelled=NULL);
	CString showFileSelect(const CString &title, CString extension, bool *cancelled=NULL);

	//To be implemented in a derived class.
	//Implementation is only required for correct
	//functioning of the key input box
	virtual CString key2name(int key) const;
	virtual int name2key(const CString &name) const;

private:
	bool m_in2DMode;
};

#endif
