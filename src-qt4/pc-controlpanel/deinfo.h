/**************************************************************************
*   Copyright (C) 2011 by Yuri Momotyuk                                   *
*   yurkis@gmail.com                                                      *
*                                                                         *
*   Permission is hereby granted, free of charge, to any person obtaining *
*   a copy of this software and associated documentation files (the       *
*   "Software"), to deal in the Software without restriction, including   *
*   without limitation the rights to use, copy, modify, merge, publish,   *
*   distribute, sublicense, and/or sell copies of the Software, and to    *
*   permit persons to whom the Software is furnished to do so, subject to *
*   the following conditions:                                             *
*                                                                         *
*   The above copyright notice and this permission notice shall be        *
*   included in all copies or substantial portions of the Software.       *
*                                                                         *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
*   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
*   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*
*   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
*   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
*   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
*   OTHER DEALINGS IN THE SOFTWARE.                                       *
***************************************************************************/

#ifndef DEINFO_F
#define DEINFO_F

#include <QString>
#include <QVector>

//! Class that holds info about DE
struct CDEInfo
{
public:
    QString mName;          ///< De name 'Gnome', 'KDE', etc
    QString mSudoCommand;   ///< native sudo command 'gtksu %s' for example
    bool    misInstalled;   ///< True if DE installed
    bool    misActive;      ///< True if DE is active now
    bool    misXDG;         ///< True if DE is XDG compatible

    CDEInfo(){
        misInstalled=false;
        misActive=false;
        misXDG=false;
    }
};

//! Class that holds list of desktop environments
class CDEList
{
public:
    /**
      Refresh list

      @param isAll- true if we want to fill list by all supported DEs outwice
                     it fills by installed DEs
    */
    int refresh(bool isAll=false);

    /**
      Returns count of DE's descriptions in list
    */
    int size()
        {
            return mvDE.size();
        }

    CDEInfo& operator[](int idx)
        {
            return mvDE[idx];
        }

    /**
      Returns pointer to description of active DE

      @return Pointer to description of active DE or NULL if active DE unknown
    */
    CDEInfo* active();

    /**
      Returns DE description bu DE name

      @param Name - Name to search (case insensative)

      @return Pointer to DE description. NULL if not found
    */
    CDEInfo* byName(QString Name);

protected:
    QVector <CDEInfo> mvDE;
};

///////////////////////////////////////////////////////
// Singleton object for DE list
class CSingleDEList:public CDEList
{
public:
    static CSingleDEList& getRef();
};

static CSingleDEList& InstalledDEList = CSingleDEList::getRef();

#endif // DEINFO_F
