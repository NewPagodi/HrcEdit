/***************************************************************
 * Name:      hrceditMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2016-04-18
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef HRCEDITMAIN_H
#define HRCEDITMAIN_H

#include <wx/wxsqlite3.h>
#include "GUIFrame.h"

class bone:public wxClientData
{
    public:
        bone(const std::vector<wxString>&, int,int,int);
        bone(const wxString&, const wxString&, const wxString&);
        bone(const bone&);

        wxString GetLeft(){return data[left];}
        wxString GetRight(){return data[right];}
        wxString GetLength(){return data[len];}
        void SetLength(const wxString& s){data[len]=s;}
        wxString ToString();

    private:
        void init(const std::vector<wxString>&);

        std::vector<wxString> data;
        int left;
        int right;
        int len;
};

class hrceditFrame: public GUIFrame
{
    public:
        hrceditFrame(wxFrame *frame);
        ~hrceditFrame();
    private:
        //event handlers
        void OnHrcOpen( wxCommandEvent& event );
        void OnHrcSetProfile( wxCommandEvent& event );
        void OnHrcSaveAs( wxCommandEvent& event );
        void OnHrcSave( wxCommandEvent& event );

        void OnProfilesListBox( wxCommandEvent& event );
        void OnProfileSaveAs( wxCommandEvent& event );
        void OnProfileSave( wxCommandEvent& event );
        void OnProfileDelete( wxCommandEvent& event );

        void OnBatchChoice( wxCommandEvent& event );
        void OnBatchList( wxCommandEvent& event );
        void OnBatchClearFiles( wxCommandEvent& event );
        void OnBatchOpenFiles( wxCommandEvent& event );
        void OnBatchDnD( wxDropFilesEvent & event );
        void OnBatchRemoveFile( wxCommandEvent& event );
        void OnBatchRadio1( wxCommandEvent& event );
        void OnBatchRadio2( wxCommandEvent& event );
        void OnBatchBrowse( wxCommandEvent& event );
        void OnBatchGo( wxCommandEvent& event );
        void OnBatchLogClear( wxCommandEvent& event );


        //helpers
        void BuildProfileBones(int,std::vector<bone*>&);
        void AddFilesHelper(const wxArrayString&);
        void HrcSaveFileHelper(const wxString&);
        void SaveProfileHelper(int);
        void BuildChoiceAndList(int,int,int);
        void PG2Vec(std::vector<bone*>&);
        void Vec2PG(std::vector<bone*>&);

        //private data
        wxPGProperty* PropertyHeader;
        wxSQLite3Database db;
        wxString FileName;
        wxString Header;
};

#endif // HRCEDITMAIN_H
