#pragma once
#include "wx/wx.h";

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
public:
	int gridWidth = 10;
	int gridHeight = 10;
	wxButton **btn;
	int* mineField = nullptr;
	bool firstBtnClicked = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

};

