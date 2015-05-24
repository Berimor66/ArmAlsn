//������� ������� �������� � ��������� ������ (����������� ������� ����� ������, ������� ���������� � �����-����):


// ������ ����������� �����
function fnLoadContent(filename)
{
    fileObj = new ActiveXObject("Scripting.FileSystemObject");
    var ForReading = 1, ForWriting = 2, ForAppending = 8;
    var TristateUseDefault = -2, TristateTrue = -1, TristateFalse = 0;
    
    f = fileObj.GetFile(filename);
    ts = f.OpenAsTextStream(ForReading, TristateUseDefault);
    var s = ts.ReadAll();         // ��������� � ������� ���� ����
    ts.Close();                   // ������� ��������� �����
    return s;
}




function IncrementRCVersion(strRCFileName, iVersion)
{    
    var objStream = objFileSystem.OpenTextFile(strRCFileName, 1);
    var objOutStream = objFileSystem.CreateTextFile(strRCFileName + ".new", true);
    
    var arrToSearch = [
        "^(\\s*FILEVERSION\\s+)(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(.*)$",
        "^(\\s*PRODUCTVERSION\\s+)(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(.*)$",
        "^(\\s*VALUE\\s*\"FolderVersion\"\\s*,\\s*\")(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(\".*)",
        "^(\\s*VALUE\\s*\"FileVersion\"\\s*,\\s*\")(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(\".*)",
        "^(\\s*VALUE\\s*\"ProductVersion\"\\s*,\\s*\")(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(,\\s*)(\\d+)(\".*)"
    ];
    
    while (!objStream.AtEndOfStream)
    {
        var strLine = objStream.ReadLine(); 

        for (var i=0; i<arrToSearch.length; ++i)
        {
            var objRegExp = new RegExp(arrToSearch[i], "");
                        
            if (objRegExp.exec(strLine) != null)
            {
                var strMonth = "" + ((new Date()).getMonth() + 1);
                var strDay = "" + ((new Date()).getDate());
                if (typeof(iVersion) == "undefined")
                {
                    iVersion = parseInt(RegExp.$8, 10) + 1;
                }
                var strBuild = "" + iVersion;
                strLine = RegExp.$1 + 
                    "1" + RegExp.$3 + // Version
                    strMonth + RegExp.$5 + // Month
                    strDay + RegExp.$7 + // Day
                    strBuild + RegExp.$9; // Version number (auto-increment)
            }
        }
        
        objOutStream.WriteLine(strLine);
    }
    objStream.Close();
    objOutStream.Close();
    
    // Replace RC file
    CopyFile(strRCFileName + ".new", strRCFileName);    
    
    // Remove temporary file
    objFileSystem.DeleteFile(strRCFileName + ".new");
    
    return iVersion;
}
// �������� ���������
function main()
{
    var sFileToParse = "..\\..\\ArmAlsn.rc";
    // ������� ����
    var strRCFileName = fnLoadContent(sFileToParse);
    // ��������� ����� �������
    strRCFileName = IncrementRCVersion(strRCFileName, 6)
    
    // ������� ������ FileSystemObject.
    var objStream = new ActiveXObject("Scripting.FileSystemObject")
    // ������� ������ TextStream.
    var objOutStream = objStream.OpenTextFile(sFileToParse, 2, true)
    // �������� � ���� ���������
    myTextStream.Write(strRCFileName);
}

// ����
main();