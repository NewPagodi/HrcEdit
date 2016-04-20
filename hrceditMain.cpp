/***************************************************************
 * Name:      hrceditMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2016-04-18
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__


#include <wx/textfile.h>
#include <wx/textdlg.h>
#include <wx/filename.h>
#include <wx/dirdlg.h>

#include "hrceditMain.h"

//Global helper functions

template <typename Iter>
Iter next_it(Iter iter)
{
    return ++iter;
}

template <typename Iter, typename Cont>
bool is_last(Iter iter, const Cont& cont)
{
    return (iter != cont.end()) && (next_it(iter) == cont.end());
}

template <class type>
int GetPno(type* a)
{
    int sel = a->GetSelection();

    if(sel!=wxNOT_FOUND)
    {
        return reinterpret_cast<int>(a->GetClientData(sel));
    }
    else
    {
        return wxNOT_FOUND;
    }
}

template <class type>
void AppendAndSelect(type* a,int selection, const wxString& name, int pno)
{
    int sel = a->Append( name, reinterpret_cast<void*>(pno) );
    if(selection==pno)
    {
        a->Select(sel);
    }
}

void CleanBones(std::vector<bone*>& bones)
{
    for(std::vector<bone*>::iterator it=bones.begin();it!=bones.end();it++)
    {
        delete *it;
    }

    bones.clear();
}

bool BonesAreCompatible(std::vector<bone*>& set1,std::vector<bone*>& set2)
{
    bool match(true),same_left,same_right;
    size_t sz(set1.size());

    if( sz==set2.size() )
    {
        for(size_t i=0;i<sz;i++)
        {
            same_left = set1[i]->GetLeft()==set2[i]->GetLeft();
            same_right = set1[i]->GetRight()==set2[i]->GetRight();

            if( !(same_left&&same_right) )
            {
                match=false;
                break;
            }
        }
    }
    else
    {
        match=false;
    }

    return match;
}

void MergeBones(std::vector<bone*>& profile_bones,std::vector<bone*>& other_bones)
{
    size_t sz(profile_bones.size());

    for(size_t i=0;i<sz;i++)
    {
        other_bones[i]->SetLength( profile_bones[i]->GetLength() );
    }
}

int ParseHeader(wxTextFile* file, wxString& header)
{
    wxString str;
    int total_bones(-3);

    //read until we run out of file or we find the first empty line
    for ( str = file->GetFirstLine(); !file->Eof(); str = file->GetNextLine() )
    {
         header << str << "\r\n";

         if(str.Left(7)==":BONES ")
         {
            long temp;

            if( str.Right(str.length()-str.Find(" ")-1).ToLong(&temp) )
            {
                total_bones=temp;
            }
         }

         if( str.IsEmpty() )
         {
             break;
         }
    }

    if(file->Eof())
    {
        return -2;
    }
    else
    {
        return total_bones;
    }
}

bone* ParseBone(wxTextFile* file)
{
    int left(-1),right(-1),len(-1),i(0);
    std::vector<wxString> data;
    double length;
    wxString str;

    //read until we run out of file or find the first empty line
    while(!file->Eof())
    {
        str=file->GetNextLine();
        data.push_back(str);

        if(str.Left(1)!="#")
        {
            if(left==-1)
            {
                left=i;
            }
            else if(right==-1)
            {
                right=i;
            }
            else if(len==-1)
            {
                len=i;
            }
        }

        if(str.IsEmpty())
        {
            break;
        }

        i++;
    }

    //we need to make sure of all of the following:
    //1) at least 5 things were found (4 pieces of info + 1 empty line)
    //2) left, right, and len were found
    //3) we can convert the len item to a double
    //4) the last string is empty.

    if(data.size()<5)
    {
        return NULL;
    }
    else if( left==-1||right==-1||len==-1 )
    {
        return NULL;
    }
    else if(!data[len].ToDouble(&length))
    {
        return NULL;
    }
    else if(!data.back().IsEmpty())
    {
        return NULL;
    }
    else
    {
        return new bone(data,left,right,len);
    }
}

int ParseHRC(const wxString& filename, wxString& header, std::vector<bone*>& bones, wxString& msg)
{
    wxTextFile file;
    if( !file.Open(filename) )
    {
        file.Close();
        msg = "unable to open file";
        return -1;
    }

    int total_bones=ParseHeader(&file,header);
    int bone_failure(0),i(0);

    if( total_bones>=0 )
    {
        bone* b;
        while(!file.Eof())
        {
            i++;

            if(b=ParseBone(&file))
            {
                bones.push_back(b);
            }
            else
            {
                //something has gone wrong
                bone_failure=i;
                total_bones=-4;
                break;
            }
        }

        if(i!=total_bones)
        {
            //the count of bones listed in the file doesn't match the
            //count from the header or we failed to parse on of the bones

            if(total_bones==0 && i==1)
            {
                if(bones[0]->GetLeft()=="null" && bones[0]->GetRight()=="root")
                {
                    //this is an empty bone list
                }
                else
                {
                    //the header lists 0 bones, but there was something
                    //in the file other than an empty bone list
                    total_bones=-6;
                }
            }
            else if(total_bones!=-4)
            {
                //all bones were parsed, but the counts don't match
                total_bones=-5;
            }
        }

        file.Close();
    }

    if(total_bones>=0)
    {
        msg = wxString::Format("%d bones parsed",total_bones);
    }
    else if(total_bones==-1)
    {
        msg = "unable to open file";
    }
    else if(total_bones==-2)
    {
        msg = "Failed to parse header";
    }
    else if(total_bones==-3)
    {
        msg = "No bone count found in header";
    }
    else if(total_bones==-4)
    {
        msg = wxString::Format("Failed while parsing bone %d",bone_failure);
    }
    else if(total_bones==-5)
    {
        msg = "Bone counts don't match";
    }
    else if(total_bones==-6)
    {
        msg = "Unexpected empty bone list";
    }
    else
    {
        msg = "Unknown parse error";
    }

    return total_bones;
}

bool WriteFile(const wxString& filename, const wxString& header, std::vector<bone*>& bones)
{
    wxString out;

    out << header;

    for(std::vector<bone*>::iterator it=bones.begin();it!=bones.end();it++)
    {
        out << (*it)->ToString();

        if( !is_last(it,bones))
        {
            out << "\r\n";
        }
    }

    wxFile file(filename, wxFile::write);
    bool b=file.Write(out);
    file.Close();

    return b;
}

//impliment bone class
bone::bone(const std::vector<wxString>& v, int l,int r,int ln):left(l),right(r),len(ln)
{
    init(v);
}

bone::bone(const bone& b):left(b.left),right(b.right),len(b.len)
{
    init(b.data);
}

bone::bone(const wxString& l,const wxString& r, const wxString& ln):left(0),right(1),len(2)
{
    data.push_back(l);
    data.push_back(r);
    data.push_back(ln);
}

void bone::init(const std::vector<wxString>& v)
{
  data.reserve( v.size() );
  std::copy( v.begin(), v.end(), std::back_inserter(data) );
}

wxString bone::ToString()
{
    wxString temp;
    for(std::vector<wxString>::iterator it=data.begin();it!=data.end();it++)
    {
        temp << *it;
        if( !is_last(it,data) ) temp << "\r\n";
    }
    return temp;
}

//impliment hrceditFrame class
hrceditFrame::hrceditFrame(wxFrame *frame): GUIFrame(frame),PropertyHeader(NULL)
{
    SetStatusText("Version 0.0.1",0);

    if( !wxFileName::FileExists("profiles.db") )
    {
        //We should probably do something more severe here.
        statusBar->SetStatusText("No profiles found.", 1);
        return;
    }

    db.Open("profiles.db");
    if(db.IsOpen())
    {
        BuildChoiceAndList(1,-1,1);
    }

    HrcOpenButton->SetFocus();
    m_auinotebook1->SetArtProvider( new wxAuiGenericTabArt() );

    BatchList->DragAcceptFiles(true);
    BatchList->Bind( wxEVT_DROP_FILES, &hrceditFrame::OnBatchDnD, this );
}

hrceditFrame::~hrceditFrame()
{
    if(db.IsOpen())
    {
        db.Close();
    }
}

void hrceditFrame::BuildProfileBones(int pno, std::vector<bone*>& profile_bones)
{
    wxSQLite3Statement stmt = db.PrepareStatement("SELECT Left,Right,Length,Bno FROM Bones WHERE PNo=? ORDER BY BNo;");
    stmt.Bind(1,pno);

    wxSQLite3ResultSet result = stmt.ExecuteQuery();
    while( result.NextRow() )
    {
        profile_bones.push_back( new bone(result.GetString(0),result.GetString(1),result.GetString(2)) );
    }
    result.Finalize();
    stmt.Finalize();
}

void hrceditFrame::AddFilesHelper(const wxArrayString& filenames)
{
    BatchList->Freeze();

    wxArrayString already_in= BatchList->GetStrings();

    for(wxArrayString::const_iterator it =filenames.begin();it!=filenames.end();it++ )
    {
        if( already_in.Index(*it,false)==wxNOT_FOUND )
        {
            wxFileName fn(*it);

            if( fn.GetExt().MakeLower()=="hrc" )
            {
                already_in.push_back(*it);
            }
        }
    }

    already_in.Sort();

    BatchList->Clear();
    BatchList->Append(already_in);
    BatchList->Thaw();

    if( BatchList->GetCount()>0 )
    {
        BatchClearFilesButton->Enable(true);

        if(GetPno(BatchChoice)!=wxNOT_FOUND)
        {
            BatchGoButton->Enable(true);
        }
    }
}

void hrceditFrame::HrcSaveFileHelper(const wxString& filename)
{
    std::vector<bone*> pg_bones;
    PG2Vec(pg_bones);
    if( !WriteFile(filename, Header, pg_bones) )
    {
        //This should never occur, but just in case:
        wxMessageDialog msg(this, "An unknown error occured.\nFile not saved.", "Problem...", wxOK|wxCENTRE);
    }
    else
    {
        SetStatusText("File Saved.",1);
    }
    pg_bones.clear();
}

void hrceditFrame::SaveProfileHelper(int pno)
{
    wxSQLite3Statement stmt = db.PrepareStatement
    ("INSERT INTO Bones(Pno,Bno,Left,Right,Length) VALUES (?,?,?,?,?);");

    std::vector<bone*> bones;
    PG2Vec(bones);
    int bone_no(0);

    for(std::vector<bone*>::iterator it=bones.begin();it!=bones.end();it++)
    {
        bone_no++;
        stmt.ClearBindings();
        stmt.Reset();
        stmt.Bind(1,pno);
        stmt.Bind(2,bone_no);
        stmt.Bind(3, (*it)->GetLeft() );
        stmt.Bind(4, (*it)->GetRight() );
        stmt.Bind(5,(*it)->GetLength());

        stmt.ExecuteUpdate();
    }
    stmt.Finalize();
}

void hrceditFrame::BuildChoiceAndList(int choice_selection, int list_selection,int batch_selection)
{
    HrcProfileChoice->Clear();
    ProfilesListBox->Clear();

    int cur_pno;
    wxString cur_profile;
    wxSQLite3Statement stmt = db.PrepareStatement("SELECT Pno,Name FROM Profiles ORDER BY Name;");
    wxSQLite3ResultSet result = stmt.ExecuteQuery();
    while( result.NextRow() )
    {
        cur_profile=result.GetString(1);
        cur_pno=result.GetInt(0);

        AppendAndSelect( HrcProfileChoice, choice_selection, cur_profile, cur_pno);
        AppendAndSelect( ProfilesListBox, list_selection, cur_profile, cur_pno);
        AppendAndSelect( BatchChoice, batch_selection, cur_profile, cur_pno);
    }
    result.Finalize();
    stmt.Finalize();
}

void hrceditFrame::PG2Vec(std::vector<bone*>& bones)
{
    unsigned int child_count = PropertyHeader->GetChildCount();

    wxClientData* cd;
    bone* b;
    wxString s;

    for(unsigned int i =0;i<child_count;i++ )
    {
        cd = PropertyHeader->Item(i)->GetClientObject();
        b=reinterpret_cast<bone*>(cd);
        s=PropertyHeader->Item(i)->GetValue().GetString();

        if(s!=b->GetLength())
        {
            b->SetLength(s);
        }

        bones.push_back(b);
    }
}

void hrceditFrame::Vec2PG(std::vector<bone*>& bones)
{
    BonesGrid->Clear();
    PropertyHeader=BonesGrid->Append( new wxPropertyCategory( "Bones", "Bones" ) );

    wxPGProperty* pg;
    for(std::vector<bone*>::iterator it=bones.begin();it!=bones.end();it++)
    {
        wxString temp( (*it)->GetLeft() + "-" + (*it)->GetRight() );

        pg=BonesGrid->AppendIn( PropertyHeader, new wxFloatProperty(temp,temp) );
        pg->SetValue( (*it)->GetLength() );
        pg->SetClientObject(*it);
    }
}

void hrceditFrame::OnHrcOpen( wxCommandEvent& event )
{
    wxFileDialog openFileDialog(this, _("Open HRC file"), "", "",
                       "HRC files (*.hrc)|*.hrc", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;     // the user changed idea...
    }

    FileName=openFileDialog.GetPath();
    Header.Clear();
    std::vector<bone*> bones;
    wxString msg;
    int parseResult = ParseHRC(FileName,Header,bones,msg);
    SetStatusText(msg, 1);

    if(parseResult>=0)
    {
        Vec2PG(bones);
        HrcSaveButton->Enable(true);
        HrcSavaAsButton->Enable(true);
        SetProfileButton->Enable(true);
        ProfileSaveAsButton->Enable(true);

        if(GetPno(ProfilesListBox)!=wxNOT_FOUND)
        {
            ProfileSaveButton->Enable(true);
        }
    }
    else
    {
        BonesGrid->Clear();
        PropertyHeader=NULL;
        Header.Clear();
        FileName.Clear();
        SetProfileButton->Enable(false);
        HrcSaveButton->Enable(false);
        HrcSavaAsButton->Enable(false);
        ProfileSaveButton->Enable(false);
        ProfileSaveAsButton->Enable(false);

        CleanBones(bones);
    }
}

void hrceditFrame::OnHrcSave( wxCommandEvent& event )
{
   if(PropertyHeader==NULL)
    {
        //it should be impossible to get here, but just in case:
        SetStatusText("No bones are loaded", 1);
        return;
    }

    HrcSaveFileHelper(FileName);
}

void hrceditFrame::OnHrcSaveAs( wxCommandEvent& event )
{
   if(PropertyHeader==NULL)
    {
        //it should be impossible to get here, but just in case:
        SetStatusText("No bones are loaded", 1);
        return;
    }

    wxFileDialog
        saveFileDialog(this, _("Save HRC file"), "", "",
                       "HRC files (*.hrc)|*.hrc", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    HrcSaveFileHelper( saveFileDialog.GetFilename() );
}

void hrceditFrame::OnHrcSetProfile( wxCommandEvent& event )
{
    int pno = GetPno(HrcProfileChoice);

    if(pno==wxNOT_FOUND)
    {
        return;
    }

    std::vector<bone*> pg_bones,profile_bones,pg_copy;
    BuildProfileBones( pno, profile_bones );
    PG2Vec(pg_bones);

    if( BonesAreCompatible(profile_bones,pg_bones) )
    {
        MergeBones(profile_bones,pg_bones);

        //we need to build a copy, because when we call Vec2PG, all
        //the pointers in pg_bones will be deleted;
        for(std::vector<bone*>::iterator it=pg_bones.begin();it!=pg_bones.end();it++)
        {
            pg_copy.push_back( new bone(**it) );
        }

        Vec2PG(pg_copy);
        pg_copy.clear();
    }
    else
    {
        //pop up a warning box
        wxMessageDialog mdlg(this, "This profile is not compatible\nwith this bone set.", "");
        mdlg.ShowModal();
    }

    CleanBones(profile_bones);
    pg_bones.clear();
}

void hrceditFrame::OnProfilesListBox( wxCommandEvent& event )
{
    ProfileDeleteButton->Enable(true);

    if(PropertyHeader!=NULL)
    {
        ProfileSaveButton->Enable(true);
    }
}

void hrceditFrame::OnProfileDelete( wxCommandEvent& event )
{
    int list_pno = GetPno(ProfilesListBox);
    if(list_pno==wxNOT_FOUND)
    {
        return;
    }

    wxMessageDialog msg(this, "Are you sure you want to delete this profile?", "Delete...", wxOK|wxCENTRE|wxCANCEL);

    if(msg.ShowModal()!=wxID_OK)
    {
        return;
    }

    wxSQLite3Statement stmt = db.PrepareStatement("DELETE FROM Profiles WHERE PNo=?;");
    stmt.Bind(1,list_pno);
    stmt.ExecuteUpdate();
    stmt.Finalize();

    stmt = db.PrepareStatement("DELETE FROM Bones WHERE PNo=?;");
    stmt.Bind(1,list_pno);
    stmt.ExecuteUpdate();
    stmt.Finalize();

    BuildChoiceAndList( GetPno(HrcProfileChoice), -1, GetPno(BatchChoice) );
    ProfileDeleteButton->Enable(false);
    ProfileSaveButton->Enable(false);
}

void hrceditFrame::OnProfileSave( wxCommandEvent& event )
{
    int pno = GetPno(ProfilesListBox);


    wxMessageDialog msg(this, "Are you sure you want to update this profile?", "Update...", wxOK|wxCENTRE|wxCANCEL);

    if(msg.ShowModal()!=wxID_OK)
    {
        return;
    }

    wxSQLite3Statement stmt = db.PrepareStatement("DELETE FROM Bones WHERE PNo=?;");
    stmt.Bind(1,pno);
    stmt.ExecuteUpdate();
    stmt.Finalize();

    SaveProfileHelper(pno);
}

void hrceditFrame::OnProfileSaveAs( wxCommandEvent& event )
{
    wxTextEntryDialog te(this, "Save profile as...", "");

    if( te.ShowModal()==wxID_OK )
    {
        if(te.GetValue().IsEmpty())
        {
            return;
        }

        wxSQLite3Statement stmt = db.PrepareStatement("SELECT Count(*) FROM Profiles WHERE Name=?;");
        stmt.Bind(1,te.GetValue());
        int profile_count = stmt.ExecuteScalar();
        stmt.Finalize();

        if(profile_count!=0)
        {
            wxMessageDialog msg(this, "There is already a profile with this name.","Problem...");
            msg.ShowModal();
            return;
        }

        stmt = db.PrepareStatement("INSERT INTO Profiles(PNo,Name) VALUES (null,?);");
        stmt.Bind(1,te.GetValue());
        stmt.ExecuteUpdate();
        stmt.Finalize();

        int pno = db.ExecuteScalar("SELECT last_insert_rowid();");

        SaveProfileHelper(pno);
    }

    BuildChoiceAndList( GetPno(HrcProfileChoice), GetPno(ProfilesListBox), GetPno(BatchChoice) );
}

void hrceditFrame::OnBatchChoice( wxCommandEvent& event )
{
    if(BatchList->GetCount()>0 )
    {
        BatchGoButton->Enable(true);
    }
}

void hrceditFrame::OnBatchList( wxCommandEvent & event )
{
    BatchRemoveFileButton->Enable(true);
}

void hrceditFrame::OnBatchClearFiles( wxCommandEvent& event )
{
    BatchList->Clear();
    BatchGoButton->Enable(false);
    BatchRemoveFileButton->Enable(false);
    BatchClearFilesButton->Enable(false);
}

void hrceditFrame::OnBatchOpenFiles( wxCommandEvent& event )
{
    wxFileDialog openFileDialog(this, _("Open HRC file"), "", "",
                       "HRC files (*.hrc)|*.hrc", wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;     // the user changed idea...
    }

    wxArrayString filenames;
    openFileDialog.GetPaths(filenames);

    AddFilesHelper(filenames);
}

void hrceditFrame::OnBatchDnD( wxDropFilesEvent & event )
{
    wxString* files=event.GetFiles();
    wxArrayString filenames;

    for(int i=0;i<event.GetNumberOfFiles();i++)
    {
        filenames.push_back(files[i]);
    }

    AddFilesHelper(filenames);
}

void hrceditFrame::OnBatchRemoveFile( wxCommandEvent& event )
{
    int sel = BatchList->GetSelection();

    if(sel==wxNOT_FOUND)
    {
        return;
    }

    BatchList->Delete(sel);

    BatchRemoveFileButton->Enable(false);

    if(BatchList->GetCount()==0)
    {
        BatchGoButton->Enable(false);
        BatchClearFilesButton->Enable(false);
    }
}

void hrceditFrame::OnBatchRadio1( wxCommandEvent& event )
{
    BatchBrowseButton->Enable(false);
}

void hrceditFrame::OnBatchRadio2( wxCommandEvent& event )
{
    if( wxFileName::DirExists(BatchFolderTextCtrl->GetValue()) )
    {
        BatchBrowseButton->Enable(true);
    }
    else
    {
        wxDirDialog ddlg(this, wxDirSelectorPromptStr, "");

        if(ddlg.ShowModal()==wxID_OK)
        {
            if( wxFileName::DirExists(ddlg.GetPath()) )
            {
                BatchFolderTextCtrl->SetValue( ddlg.GetPath() );
                BatchBrowseButton->Enable(true);
            }
            else
            {
                BatchRadio1->SetValue(true);
            }
        }
        else
        {
            BatchRadio1->SetValue(true);
        }
    }
}

void hrceditFrame::OnBatchBrowse( wxCommandEvent& event )
{
    wxDirDialog ddlg(this, wxDirSelectorPromptStr, BatchFolderTextCtrl->GetValue());

    if(ddlg.ShowModal()==wxID_OK && wxFileName::DirExists(ddlg.GetPath()))
    {
        BatchFolderTextCtrl->SetValue( ddlg.GetPath() );
    }
}

void hrceditFrame::OnBatchGo( wxCommandEvent& event )
{
    int pno = GetPno(BatchChoice);

    if( pno==wxNOT_FOUND || BatchList->GetCount()==0 )
    {
        //should never happen, but check just in case.
        return;
    }

    wxArrayString filenames = BatchList->GetStrings();
    std::vector<bone*> file_bones,profile_bones;
    wxString header,input,output,msg;

    BuildProfileBones( pno, profile_bones );

    for(wxArrayString::iterator it = filenames.begin();it!=filenames.end();it++ )
    {
        input=*it;

        if(BatchRadio1->GetValue())
        {
            output=*it;
        }
        else
        {
            wxFileName fn(input);
            output=BatchFolderTextCtrl->GetValue() + wxFileName::GetPathSeparator() + fn.GetFullName();
        }

        (*BatchLog) << input << "\t->\t" << output << "\t";

        //open and parse the file
        header.Clear();
        msg.Clear();

        if( ParseHRC(input,header,file_bones,msg)<0 )
        {
            (*BatchLog) << "parse error: " << msg  << "\n";
            CleanBones(file_bones);
            continue;
        }

        //merge the bones
        if( BonesAreCompatible(profile_bones,file_bones) )
        {
            MergeBones(profile_bones,file_bones);
        }
        else
        {
            (*BatchLog) << "the bones of this file are not compatible with the selected profile.\n";
            CleanBones(file_bones);
            continue;
        }

        //write the file:
        if( !WriteFile(output, header, file_bones) )
        {
            //This should never occur, but just in case:
            (*BatchLog) << "An unknown error occured.  File not saved.\n";
        }
        else
        {
            (*BatchLog) << "Bones updated.\n";
        }

        CleanBones(file_bones);
    }

    CleanBones(profile_bones);
}

void hrceditFrame::OnBatchLogClear( wxCommandEvent& event )
{
    BatchLog->Clear();
}
