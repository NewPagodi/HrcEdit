///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 19 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

#include "delete.xpm"
#include "fileopen.xpm"
#include "filesave.xpm"
#include "filesaveas.xpm"
#include "minus.xpm"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_auinotebook1 = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, wxT("Profile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer5->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxArrayString HrcProfileChoiceChoices;
	HrcProfileChoice = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, HrcProfileChoiceChoices, 0 );
	HrcProfileChoice->SetSelection( 0 );
	bSizer5->Add( HrcProfileChoice, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	SetProfileButton = new wxButton( m_panel1, wxID_ANY, wxT("Set"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	SetProfileButton->Enable( false );
	SetProfileButton->SetToolTip( wxT("Apply the selected profile lengths") );
	
	bSizer5->Add( SetProfileButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( bSizer5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	BonesGrid = new wxPropertyGrid(m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer6->Add( BonesGrid, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	HrcOpenButton = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( fileopen_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	HrcOpenButton->SetToolTip( wxT("Open an hrc file") );
	
	bSizer12->Add( HrcOpenButton, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	HrcSaveButton = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( filesave_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	HrcSaveButton->Enable( false );
	HrcSaveButton->SetToolTip( wxT("Save the hrc file") );
	
	bSizer12->Add( HrcSaveButton, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	HrcSavaAsButton = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( filesaveas_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	HrcSavaAsButton->Enable( false );
	HrcSavaAsButton->SetToolTip( wxT("Save to a new file") );
	
	bSizer12->Add( HrcSavaAsButton, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer6->Add( bSizer12, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer6, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	m_auinotebook1->AddPage( m_panel1, wxT("Edit hrc file"), true, wxNullBitmap );
	m_panel2 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	ProfilesListBox = new wxListBox( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer3->Add( ProfilesListBox, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	ProfileDeleteButton = new wxBitmapButton( m_panel2, wxID_ANY, wxBitmap( minus_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	ProfileDeleteButton->Enable( false );
	ProfileDeleteButton->SetToolTip( wxT("Delete the selected profile") );
	
	bSizer11->Add( ProfileDeleteButton, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	ProfileSaveButton = new wxBitmapButton( m_panel2, wxID_ANY, wxBitmap( filesave_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	ProfileSaveButton->Enable( false );
	ProfileSaveButton->SetToolTip( wxT("Save the values in the grid to the selected profile") );
	
	bSizer11->Add( ProfileSaveButton, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	ProfileSaveAsButton = new wxBitmapButton( m_panel2, wxID_ANY, wxBitmap( filesaveas_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	ProfileSaveAsButton->Enable( false );
	ProfileSaveAsButton->SetToolTip( wxT("Save the values in the grid to a new profile") );
	
	bSizer11->Add( ProfileSaveAsButton, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer3->Add( bSizer11, 0, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( bSizer3 );
	m_panel2->Layout();
	bSizer3->Fit( m_panel2 );
	m_auinotebook1->AddPage( m_panel2, wxT("Manage profiles"), false, wxNullBitmap );
	m_panel3 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( m_panel3, wxID_ANY, wxT("Profile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer51->Add( m_staticText11, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxArrayString BatchChoiceChoices;
	BatchChoice = new wxChoice( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, BatchChoiceChoices, 0 );
	BatchChoice->SetSelection( 0 );
	bSizer51->Add( BatchChoice, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	BatchGoButton = new wxButton( m_panel3, wxID_ANY, wxT("Go..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	BatchGoButton->Enable( false );
	BatchGoButton->SetToolTip( wxT("Update all the hrc files with\nvalues from the selected profile") );
	
	bSizer51->Add( BatchGoButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer4->Add( bSizer51, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Hrc files") ), wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	BatchList = new wxListBox( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer14->Add( BatchList, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	BatchOpenFilesButton = new wxBitmapButton( sbSizer1->GetStaticBox(), wxID_ANY, wxBitmap( fileopen_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	BatchOpenFilesButton->SetToolTip( wxT("Add hrc files to the list") );
	
	bSizer10->Add( BatchOpenFilesButton, 0, wxTOP|wxBOTTOM, 5 );
	
	
	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	BatchRemoveFileButton = new wxBitmapButton( sbSizer1->GetStaticBox(), wxID_ANY, wxBitmap( minus_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	BatchRemoveFileButton->Enable( false );
	BatchRemoveFileButton->SetToolTip( wxT("Remove the selected hrc file from the list") );
	
	bSizer10->Add( BatchRemoveFileButton, 0, wxTOP|wxBOTTOM, 5 );
	
	BatchClearFilesButton = new wxBitmapButton( sbSizer1->GetStaticBox(), wxID_ANY, wxBitmap( delete_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	BatchClearFilesButton->Enable( false );
	BatchClearFilesButton->SetToolTip( wxT("Clear the file list") );
	
	bSizer10->Add( BatchClearFilesButton, 0, wxTOP|wxBOTTOM, 5 );
	
	
	bSizer14->Add( bSizer10, 0, wxEXPAND, 5 );
	
	
	sbSizer1->Add( bSizer14, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	BatchRadio1 = new wxRadioButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Overwrite"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	BatchRadio1->SetValue( true ); 
	bSizer31->Add( BatchRadio1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	BatchRadio2 = new wxRadioButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Save copy to:"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( BatchRadio2, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	BatchFolderTextCtrl = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer31->Add( BatchFolderTextCtrl, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	BatchBrowseButton = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	BatchBrowseButton->Enable( false );
	BatchBrowseButton->SetToolTip( wxT("Change the folder") );
	
	bSizer31->Add( BatchBrowseButton, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	
	sbSizer1->Add( bSizer31, 0, wxEXPAND, 5 );
	
	
	bSizer4->Add( sbSizer1, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Log") ), wxHORIZONTAL );
	
	BatchLog = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE );
	sbSizer2->Add( BatchLog, 1, wxALL|wxEXPAND, 5 );
	
	BatchLogClearButton = new wxBitmapButton( sbSizer2->GetStaticBox(), wxID_ANY, wxBitmap( delete_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	BatchLogClearButton->SetToolTip( wxT("Clear the log window") );
	
	sbSizer2->Add( BatchLogClearButton, 0, wxALIGN_BOTTOM|wxTOP|wxBOTTOM, 5 );
	
	
	bSizer4->Add( sbSizer2, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	m_panel3->SetSizer( bSizer4 );
	m_panel3->Layout();
	bSizer4->Fit( m_panel3 );
	m_auinotebook1->AddPage( m_panel3, wxT("Batch mode"), false, wxNullBitmap );
	
	bSizer1->Add( m_auinotebook1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	SetProfileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnHrcSetProfile ), NULL, this );
	HrcOpenButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnHrcOpen ), NULL, this );
	HrcSaveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnHrcSave ), NULL, this );
	HrcSavaAsButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnHrcSaveAs ), NULL, this );
	ProfilesListBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( GUIFrame::OnProfilesListBox ), NULL, this );
	ProfileDeleteButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnProfileDelete ), NULL, this );
	ProfileSaveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnProfileSave ), NULL, this );
	ProfileSaveAsButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnProfileSaveAs ), NULL, this );
	BatchChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrame::OnBatchChoice ), NULL, this );
	BatchGoButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchGo ), NULL, this );
	BatchList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( GUIFrame::OnBatchList ), NULL, this );
	BatchOpenFilesButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchOpenFiles ), NULL, this );
	BatchRemoveFileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchRemoveFile ), NULL, this );
	BatchClearFilesButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchClearFiles ), NULL, this );
	BatchRadio1->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUIFrame::OnBatchRadio1 ), NULL, this );
	BatchRadio2->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUIFrame::OnBatchRadio2 ), NULL, this );
	BatchBrowseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchBrowse ), NULL, this );
	BatchLogClearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchLogClear ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	SetProfileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnHrcSetProfile ), NULL, this );
	HrcOpenButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnHrcOpen ), NULL, this );
	HrcSaveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnHrcSave ), NULL, this );
	HrcSavaAsButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnHrcSaveAs ), NULL, this );
	ProfilesListBox->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( GUIFrame::OnProfilesListBox ), NULL, this );
	ProfileDeleteButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnProfileDelete ), NULL, this );
	ProfileSaveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnProfileSave ), NULL, this );
	ProfileSaveAsButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnProfileSaveAs ), NULL, this );
	BatchChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrame::OnBatchChoice ), NULL, this );
	BatchGoButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchGo ), NULL, this );
	BatchList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( GUIFrame::OnBatchList ), NULL, this );
	BatchOpenFilesButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchOpenFiles ), NULL, this );
	BatchRemoveFileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchRemoveFile ), NULL, this );
	BatchClearFilesButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchClearFiles ), NULL, this );
	BatchRadio1->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUIFrame::OnBatchRadio1 ), NULL, this );
	BatchRadio2->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUIFrame::OnBatchRadio2 ), NULL, this );
	BatchBrowseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchBrowse ), NULL, this );
	BatchLogClearButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBatchLogClear ), NULL, this );
	
}
