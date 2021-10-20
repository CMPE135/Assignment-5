#include "RPSFrame.hpp"

RPSFrame::RPSFrame() 
        : wxFrame(NULL, wxID_ANY, "Rock Paper Scissors: 20 rounds/game", wxPoint(50,50), wxSize(450,340)),
          computer{},
          round(0), tie(0), humanWin(0), computerWin(0) {
    this->Bind(wxEVT_CLOSE_WINDOW, &RPSFrame::OnClose, this);
    // Frame
    wxSizer *frameSizer = new wxBoxSizer(wxVERTICAL);
    
    // Main
    wxPanel *mainPanel = new wxPanel(this);
    wxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // Round
    wxPanel *roundPanel = new wxPanel(mainPanel);
    roundPanel->SetFont(roundPanel->GetFont().Scale(1.5).Bold());
    wxSizer *roundSizer = new wxGridSizer(2, 0, 5);
    wxStaticText *roundLabel = new wxStaticText(roundPanel, wxID_ANY, "Round:");
    roundCount = new wxStaticText(roundPanel, wxID_ANY, "0");
    roundSizer->Add(roundLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
    roundSizer->Add(roundCount);
    roundPanel->SetSizer(roundSizer);

    // Human
    wxPanel *humanPanel = new wxPanel(mainPanel);
    wxSizer *humanSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *humanTitle = new wxStaticText(humanPanel, wxID_ANY, "Human");
    humanTitle->SetFont(humanTitle->GetFont().Larger().Bold());
    // Human button
    wxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *chooseText = new wxStaticText(humanPanel, wxID_ANY, "Choose:");
    wxButton *rockButton = new wxButton(humanPanel, wxID_ANY, "Rock");
    wxButton *paperButton = new wxButton(humanPanel, wxID_ANY, "Paper");
    wxButton *scissorsButton = new wxButton(humanPanel, wxID_ANY, "Scissors");
    rockButton->Bind(wxEVT_BUTTON, &RPSFrame::OnRock, this);
    paperButton->Bind(wxEVT_BUTTON, &RPSFrame::OnPaper, this);
    scissorsButton->Bind(wxEVT_BUTTON, &RPSFrame::OnScissors, this);
    buttonSizer->Add(chooseText, 0, wxALIGN_CENTER_VERTICAL, 0);
    buttonSizer->AddSpacer(5);
    buttonSizer->Add(rockButton, 0, 0, 0);
    buttonSizer->AddSpacer(5);
    buttonSizer->Add(paperButton, 0, 0, 0);
    buttonSizer->AddSpacer(5);
    buttonSizer->Add(scissorsButton, 0, 0, 0);
    // Human choice
    wxSizer *humanChoiceSizer = new wxGridSizer(2, 0, 5);
    wxStaticText *humanChoiceLabel = new wxStaticText(humanPanel, wxID_ANY, "Human chooses:");
    humanChoiceName = new wxStaticText(humanPanel, wxID_ANY, "");
    humanChoiceName->SetFont(humanChoiceName->GetFont().Larger());
    humanChoiceSizer->Add(humanChoiceLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
    humanChoiceSizer->Add(humanChoiceName, 0, 0, 0);
    // End Human
    humanSizer->Add(humanTitle, 0, wxALIGN_CENTER, 0);
    humanSizer->AddSpacer(5);
    humanSizer->Add(buttonSizer, 0, wxALIGN_CENTER, 0);
    humanSizer->Add(humanChoiceSizer, 0, wxALIGN_CENTER, 0);
    humanPanel->SetSizer(humanSizer);

    // Computer
    wxPanel *computerPanel = new wxPanel(mainPanel);
    wxSizer *computerSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *computerTitle = new wxStaticText(computerPanel, wxID_ANY, "Computer");
    computerTitle->SetFont(computerTitle->GetFont().Larger().Bold());
    wxSizer *computerBodySizer = new wxGridSizer(2, 0, 5);
    // Computer prediction
    wxStaticText *predictLabel = new wxStaticText(computerPanel, wxID_ANY, "Predicted human choice:");
    predictChoiceName = new wxStaticText(computerPanel, wxID_ANY, "");
    computerBodySizer->Add(predictLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
    computerBodySizer->Add(predictChoiceName, 0, 0, 0);
    // Computer choice
    wxStaticText *computerChoiceLabel = new wxStaticText(computerPanel, wxID_ANY, "Therefore computer chooses:");
    computerChoiceName = new wxStaticText(computerPanel, wxID_ANY, "");
    computerChoiceName->SetFont(computerChoiceName->GetFont().Larger());
    computerBodySizer->Add(computerChoiceLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
    computerBodySizer->Add(computerChoiceName, 0, 0, 0);
    // End Computer
    computerSizer->Add(computerTitle, 0, wxALIGN_CENTER, 0);
    computerSizer->Add(computerBodySizer, 0, wxALIGN_CENTER, 0);
    computerPanel->SetSizer(computerSizer);

    // Winner
    wxPanel *winnerPanel = new wxPanel(mainPanel);
    wxSizer *winnerSizer = new wxGridSizer(2, 0, 5);
    wxStaticText *winnerLabel = new wxStaticText(winnerPanel, wxID_ANY, "The winner:");
    winnerLabel->SetFont(winnerLabel->GetFont().Larger().Bold());
    winnerName = new wxStaticText(winnerPanel, wxID_ANY, "");
    winnerName->SetFont(winnerName->GetFont().Larger());
    winnerSizer->Add(winnerLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
    winnerSizer->Add(winnerName, 0, 0, 0);
    winnerPanel->SetSizer(winnerSizer);
    
    // Statistics
    wxPanel *statPanel = new wxPanel(mainPanel);
    wxSizer *statSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *statTitle = new wxStaticText(statPanel, wxID_ANY, "Statistics");
    statTitle->SetFont(statTitle->GetFont().Larger().Bold());
    wxSizer *statBodySizer = new wxGridSizer(2, 0, 5);
    wxStaticText *humanWinLabel = new wxStaticText(statPanel, wxID_ANY, "Human wins:");
    humanWinCount = new wxStaticText(statPanel, wxID_ANY, "0");
    wxStaticText *computerWinLabel = new wxStaticText(statPanel, wxID_ANY, "Computer wins:");
    computerWinCount = new wxStaticText(statPanel, wxID_ANY, "0");
    wxStaticText *tieLabel = new wxStaticText(statPanel, wxID_ANY, "Tie:");
    tieCount = new wxStaticText(statPanel, wxID_ANY, "0");
    statBodySizer->Add(humanWinLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
    statBodySizer->Add(humanWinCount, 0, 0, 0);
    statBodySizer->Add(computerWinLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
    statBodySizer->Add(computerWinCount, 0, 0, 0);
    statBodySizer->Add(tieLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 0);
    statBodySizer->Add(tieCount, 0, 0, 0);
    statSizer->Add(statTitle, 0, wxALIGN_CENTER, 0);
    statSizer->Add(statBodySizer, 0, wxALIGN_CENTER, 0);
    statPanel->SetSizer(statSizer);

    // End Main
    mainSizer->Add(roundPanel, 0, wxALIGN_CENTER, 0);
    mainSizer->AddSpacer(20);
    mainSizer->Add(humanPanel, 0, wxALIGN_CENTER, 0);
    mainSizer->AddSpacer(20);
    mainSizer->Add(computerPanel, 0, wxALIGN_CENTER, 0);
    mainSizer->AddSpacer(20);
    mainSizer->Add(winnerPanel, 0, wxALIGN_CENTER, 0);
    mainSizer->AddSpacer(20);
    mainSizer->Add(statPanel, 0, wxALIGN_CENTER, 0);
    mainPanel->SetSizer(mainSizer);

    // End Frame
    frameSizer->AddSpacer(10);
    frameSizer->Add(mainPanel, 0, wxALIGN_CENTER, 0);
    SetSizerAndFit(frameSizer);
    
    // Status Bar
    CreateStatusBar();
    SetStatusText("Welcome to the Rock Paper Scissors game!");
}

void RPSFrame::OnRock(wxCommandEvent& event) {
    endRound(ROCK);
}

void RPSFrame::OnPaper(wxCommandEvent& event) {
    endRound(PAPER);
}

void RPSFrame::OnScissors(wxCommandEvent& event) {
    endRound(SCISSORS);
}

// Update information of the round when human made a choice
void RPSFrame::endRound(Choice humanChoice) {
    if (round == 20) return;
    updateComputerChoices();
    humanChoiceName->SetLabelText(toString(humanChoice));
    if(humanChoice == computerChoice) {
        tie++;
        winnerName->SetLabelText("Tie");
        tieCount->SetLabelText(to_string(tie));
    } else if (humanChoice > computerChoice ) {
        humanWin++;
        winnerName->SetLabelText("Human");
        humanWinCount->SetLabelText(to_string(humanWin));
    } else {
        computerWin++;
        winnerName->SetLabelText("Computer");
        computerWinCount->SetLabelText(to_string(computerWin));
    }
    round++;
    roundCount->SetLabelText(to_string(round));
    computer.feedOpponentChoice(humanChoice);
}

void RPSFrame::updateComputerChoices() {
    predictChoice = computer.predictChoice();
    computerChoice = Choice((predictChoice + 1) % 3);
    predictChoiceName->SetLabelText(toString(predictChoice));
    computerChoiceName->SetLabelText(toString(computerChoice));
}

// Let computer save frequency table when window is closed
void RPSFrame::OnClose(wxCloseEvent& event) 
{
    computer.postGame();
    this->OnCloseWindow(event);
}


