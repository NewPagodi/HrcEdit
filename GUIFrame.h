///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 19 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/bmpbuttn.h>
#include <wx/panel.h>
#include <wx/listbox.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/aui/auibook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxStatusBar* statusBar;
		wxAuiNotebook* m_auinotebook1;
		wxPanel* m_panel1;
		wxStaticText* m_staticText1;
		wxChoice* HrcProfileChoice;
		wxButton* SetProfileButton;
		wxPropertyGrid* BonesGrid;
		wxBitmapButton* HrcOpenButton;
		wxBitmapButton* HrcSaveButton;
		wxBitmapButton* HrcSavaAsButton;
		wxPanel* m_panel2;
		wxListBox* ProfilesListBox;
		wxBitmapButton* ProfileDeleteButton;
		wxBitmapButton* ProfileSaveButton;
		wxBitmapButton* ProfileSaveAsButton;
		wxPanel* m_panel3;
		wxStaticText* m_staticText11;
		wxChoice* BatchChoice;
		wxButton* BatchGoButton;
		wxListBox* BatchList;
		wxBitmapButton* BatchOpenFilesButton;
		wxBitmapButton* BatchRemoveFileButton;
		wxBitmapButton* BatchClearFilesButton;
		wxRadioButton* BatchRadio1;
		wxRadioButton* BatchRadio2;
		wxTextCtrl* BatchFolderTextCtrl;
		wxButton* BatchBrowseButton;
		wxTextCtrl* BatchLog;
		wxBitmapButton* BatchLogClearButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnHrcSetProfile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHrcOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHrcSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHrcSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProfilesListBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProfileDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProfileSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProfileSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchGo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchList( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchOpenFiles( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchRemoveFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchClearFiles( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchRadio1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchRadio2( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchBrowse( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBatchLogClear( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("HRC Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 481,466 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUIFrame();
	
};

#endif //__GUIFRAME_H__
