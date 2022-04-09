#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(101, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MineSweeper Lab", wxPoint(30, 30), wxSize(800, 600))
{
	btn = new wxButton * [gridWidth * gridHeight];
	wxGridSizer* grid = new wxGridSizer(gridWidth, gridHeight, 0, 0);

	mineField = new int[gridWidth * gridHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			btn[y * gridWidth + x] = new wxButton(this, 10000 + (y * gridWidth + x));
			btn[y * gridWidth + x]->SetFont(font);
			grid->Add(btn[y * gridWidth + x], 1, wxEXPAND | wxALL);

			btn[y * gridWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			mineField[y * gridWidth + x] = 0;
			btn[y * gridWidth + x]->SetBackgroundColour(*wxLIGHT_GREY);
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain()
{
	delete[]btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % gridWidth;
	int y = (evt.GetId() - 10000) / gridHeight;

	if (firstBtnClicked)
	{
		int mines = 30;

		while (mines)
		{
			int randX = rand() % gridWidth;
			int randY = rand() % gridHeight;

			if (mineField[randY * gridWidth + randX] == 0 && randX != x && randY != y)
			{
				// set position to a mine
				mineField[randY * gridWidth + randX] = -1;
				mines--;
			}
		}
		firstBtnClicked = false;
	}
	btn[y * gridWidth + x]->Enable(false);

	// check if mine is present
	if (mineField[y * gridWidth + x] == -1)
	{
		wxMessageBox("You Hit a Mine!!! Please Try Again");
		firstBtnClicked = true;
		for (int x = 0; x < gridWidth; x++)
		{
			for (int y = 0; y < gridHeight; y++)
			{
				mineField[y * gridWidth + x] = 0;
				btn[y * gridWidth + x]->SetLabel("");
				btn[y * gridWidth + x]->Enable(true);
				btn[y * gridWidth + x]->SetBackgroundColour(*wxLIGHT_GREY);
			}
		}
	}
	else
	{
		// count neighbouring mines
		int neighbouringMinesCount = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (x + 1 >= 0 && x + i < gridWidth && y + j < gridHeight)
				{
					if (mineField[(y + j) * gridWidth + (x + i)] == -1)
					{
						neighbouringMinesCount++;
					}
				}
			}

		if (neighbouringMinesCount > 0)
		{
			btn[y * gridWidth + x]->SetLabel(std::to_string(neighbouringMinesCount));
		}
		
		if (neighbouringMinesCount == 0)
		{
			btn[y * gridWidth + x]->SetBackgroundColour(*wxBLACK);
			btn[y * gridWidth + x]->SetLabel(std::to_string(neighbouringMinesCount));
		}
		else if (neighbouringMinesCount == 1)
		{
			btn[y * gridWidth + x]->SetBackgroundColour(*wxBLUE);
		}
		else if (neighbouringMinesCount == 2)
		{
			btn[y * gridWidth + x]->SetBackgroundColour(*wxGREEN);
		}
		else if(neighbouringMinesCount >= 3)
		{
			btn[y * gridWidth + x]->SetBackgroundColour(*wxRED);
		}

	}
	evt.Skip();
}

