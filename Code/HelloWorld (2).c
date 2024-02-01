// for gBS
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/FileHandleLib.h>

#include <Protocol/SimpleFileSystem.h>

void PrintFileInfo(EFI_FILE_PROTOCOL *File){
    EFI_FILE_INFO *FileInfo = FileHandleGetInfo(File);
    Print(L"File Size: %ld bytes\n", FileInfo->FileSize);
    Print(L"File Name: %s\n", FileInfo->FileName);
    // Add other information you want to print
}

UINTN is_file(EFI_FILE_PROTOCOL *File){
    EFI_FILE_INFO *FileInfo = FileHandleGetInfo(File);
    if (FileInfo->Attribute & EFI_FILE_DIRECTORY){
        return 0;
    }
    return 1;
}

void PrintGetPosition(EFI_FILE_HANDLE File){
    UINT64 Result;
    FileHandleGetPosition(File, &Result);
    Print(L"Result: %lld\n", Result);
}

EFI_STATUS GetStringFromIndex(CHAR16* Buffer, UINTN BufferSize, UINTN index){
    EFI_STATUS status;
    EFI_INPUT_KEY Key;
    UINTN Pos = index;
    UINTN Index = 0;
    Buffer[index] = '\0';

    while(Index < BufferSize - 1){
        status = gBS->WaitForEvent(1, &gST->ConIn->WaitForKey, &Index);
        if(EFI_ERROR(status)){
            return status;
        }
        status = gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
        if(EFI_ERROR(status)){
            return status;
        }
        if(Key.UnicodeChar == L'\r'){
            break;
        }
        if(Key.ScanCode == SCAN_DELETE){
            if(Pos > 0){
                Pos --;
                Buffer[Pos] = L'\0';
                gST->ConOut->OutputString(gST->ConOut, L"\b \b");
            }
            continue;
        }
        Buffer[Pos] = Key.UnicodeChar;
        Pos = Pos + 1;
        Buffer[Pos] = L'\0';
        gST->ConOut->OutputString(gST->ConOut, Buffer+Pos-1);
    }
    Buffer[Pos] = L'\0';
    return EFI_SUCCESS;
}

EFI_STATUS GetString(CHAR16* Buffer, UINTN BufferSize){
    return GetStringFromIndex(Buffer, BufferSize, 0);
}

EFI_STATUS MakeDirectory(EFI_FILE_PROTOCOL *Curr_Dir, CHAR16* Name, EFI_FILE_PROTOCOL **New_Directory){
    EFI_STATUS status;
    status = Curr_Dir->Open(
        Curr_Dir, New_Directory,
        Name, // Directory name
        EFI_FILE_MODE_CREATE | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ,
        EFI_FILE_DIRECTORY
    );
    return status;
}

EFI_STATUS OpenOnlyRead(EFI_FILE_PROTOCOL *Curr_Dir, CHAR16* Name, EFI_FILE_PROTOCOL **New_Directory){
    EFI_STATUS status;
    status = Curr_Dir->Open(
        Curr_Dir, New_Directory,
        Name, // Directory name
        EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ,
        0
    );
    return status;
}

BOOLEAN isThereFile(EFI_FILE_PROTOCOL *Curr_Dir, CHAR16* Name){
    EFI_FILE_PROTOCOL *File;
    EFI_STATUS status = OpenOnlyRead(Curr_Dir, Name, &File);
    if(status == EFI_SUCCESS){
        return TRUE;
    }else{
        return FALSE;
    }
}

EFI_STATUS OpenDirectory(EFI_FILE_PROTOCOL *Curr_Dir, CHAR16* Name, EFI_FILE_PROTOCOL **Opened_Directory){
    EFI_STATUS status;
    status = Curr_Dir->Open(
        Curr_Dir, Opened_Directory,
        Name, // Directory name
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
        EFI_FILE_DIRECTORY
    );
    return status;
}

EFI_STATUS OpenFileOnlyRead(EFI_FILE_PROTOCOL *Curr_Dir, CHAR16* Name, EFI_FILE_PROTOCOL **File){
    EFI_STATUS status;
    status = Curr_Dir->Open(
        Curr_Dir, File,
        Name,
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
        EFI_FILE_ARCHIVE
    );
    return status;
}

EFI_STATUS OpenFileOrDir(EFI_FILE_PROTOCOL *Curr_Dir, CHAR16* Name, EFI_FILE_PROTOCOL **File){
    EFI_STATUS status;
    status = Curr_Dir->Open(
        Curr_Dir, File,
        Name,
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
        0
    );
    return status;
}

EFI_STATUS OpenFileCreate(EFI_FILE_PROTOCOL *Curr_Dir, CHAR16* Name, EFI_FILE_PROTOCOL **File){
    EFI_STATUS status;
    status = Curr_Dir->Open(
        Curr_Dir, File,
        Name,
        EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
        EFI_FILE_ARCHIVE
    );
    return status;
}

UINTN GetSize(CHAR16* str){
    for(UINTN i = 0; ;i++){
        if(str[i] == '\0'){
            return (i+1)*2;
        }
    }
}

UINTN is_name_file(EFI_FILE_PROTOCOL *Curr_Dir, CHAR16* Name){
    EFI_FILE_PROTOCOL *File;
    EFI_STATUS status = OpenFileOrDir(Curr_Dir, Name, &File);
    if(status == EFI_SUCCESS){
        return is_file(File);
    }else{
        return -1;
    }
}

void PrintFiles(CHAR16 *Files[], UINTN size){
    for(UINTN i=0; i<size; i++){
        Print(L"file: %s\n", Files[i]);
    }
}

void PrintDirectories(CHAR16* Directories[], UINTN size){
    for(UINTN i=0; i<size; i++){
        Print(L"directory: %s\n", Directories[i]);
    }
}

// Compare two strings using StrCmp
INTN StringCompare(const CHAR16 *Str1, const CHAR16 *Str2) {
    return StrCmp(Str1, Str2);
}

// Swap two pointers
VOID SwapStrings(CHAR16 **Ptr1, CHAR16 **Ptr2) {
    CHAR16 *Temp = *Ptr1;
    *Ptr1 = *Ptr2;
    *Ptr2 = Temp;
}

// Bubble Sort algorithm for sorting an array of strings
VOID BubbleSortStrings(CHAR16 **StringArray, UINTN ArraySize) {
    UINTN i, j;

    for (i = 0; i < ArraySize - 1; i++) {
        for (j = 0; j < ArraySize - i - 1; j++) {
            if (StringCompare(StringArray[j], StringArray[j + 1]) > 0) {
                SwapStrings(&StringArray[j], &StringArray[j + 1]);
            }
        }
    }
}


void PrintDirectoryInfo(EFI_FILE_PROTOCOL *Directory, UINTN flag){
    CHAR16 *Directories[256];
    CHAR16 *Files[256];
    UINTN DirectoriesSize = 0;
    UINTN FilesSize = 0;
    EFI_FILE_INFO *FileInfo;
    EFI_STATUS status;
    UINTN BufferSize;
    CHAR16 FileName[256];

    Directory->SetPosition(Directory, 0);

    do{
        BufferSize = sizeof(EFI_FILE_INFO) + sizeof(FileName);
        FileInfo = AllocatePool(BufferSize);
        

        if(FileInfo == NULL){
            status = EFI_OUT_OF_RESOURCES;
            break;
        }

        status = Directory->Read(Directory, &BufferSize, FileInfo);

        if(!EFI_ERROR(status) && BufferSize > 0){
            StrCpyS(FileName, sizeof(FileName)/sizeof(FileName[0]), FileInfo->FileName);
            CHAR16* nameCopy = AllocatePool((StrLen(FileName) + 1) * sizeof(CHAR16));
            StrCpyS(nameCopy, StrLen(FileName) + 1, FileName);
            if (is_name_file(Directory, FileName)){
                Files[FilesSize] = nameCopy;
                FilesSize++;
            }else{
                Directories[DirectoriesSize] = nameCopy;
                DirectoriesSize++;
            }
        }


        FreePool(FileInfo);

    }while (!EFI_ERROR(status) && BufferSize > 0);

    if(flag == 1){
        BubbleSortStrings(Files, FilesSize);
        BubbleSortStrings(Directories, DirectoriesSize);
    }else if(flag == 2){

    }

    PrintFiles(Files, FilesSize);
    PrintDirectories(Directories, DirectoriesSize);
}

EFI_STATUS DeleteFileOrDir(EFI_FILE_PROTOCOL *File_or_Dir){
    EFI_STATUS status;
    if(is_file(File_or_Dir)){
        status = File_or_Dir->Delete(File_or_Dir);
    }else{
        EFI_FILE_INFO *FileInfo;
        UINTN BufferSize;
        CHAR16 FileName[256];

        File_or_Dir->SetPosition(File_or_Dir, 0);

        do{
            BufferSize = sizeof(EFI_FILE_INFO) + sizeof(FileName);
            FileInfo = AllocatePool(BufferSize);
            

            if(FileInfo == NULL){
                status = EFI_OUT_OF_RESOURCES;
                break;
            }

            status = File_or_Dir->Read(File_or_Dir, &BufferSize, FileInfo);

            if(!EFI_ERROR(status) && BufferSize > 0){
                if (StrCmp(FileInfo->FileName, L".") != 0 && StrCmp(FileInfo->FileName, L"..") != 0){
                    StrCpyS(FileName, sizeof(FileName)/sizeof(FileName[0]), FileInfo->FileName);
                    EFI_FILE_PROTOCOL *DeletingFile;
                    status = OpenFileOrDir(File_or_Dir, FileName, &DeletingFile);
                    if(status == EFI_SUCCESS){
                        status = DeleteFileOrDir(DeletingFile);
                    }else{
                        return status;
                    }
                }
            }
            FreePool(FileInfo);

        }while (!EFI_ERROR(status) && BufferSize > 0);
        status = File_or_Dir->Delete(File_or_Dir);
    }
    return status;
}

EFI_STATUS CopyFile(EFI_FILE_PROTOCOL *SourceFile, EFI_FILE_PROTOCOL *DestFile) {
    EFI_STATUS Status;
    CHAR8 Buffer[1024];
    UINTN Size;

    do {
        Size = sizeof(Buffer);
        Status = SourceFile->Read(SourceFile, &Size, Buffer);

        if (!EFI_ERROR(Status) && Size > 0) {
            Status = DestFile->Write(DestFile, &Size, Buffer);
            if (EFI_ERROR(Status)) {
                break;
            }
        }
    } while (!EFI_ERROR(Status) && Size > 0);

    return Status;
}

EFI_STATUS CopyDirectoryRecursive(EFI_FILE_PROTOCOL *SourceFileOrDir, EFI_FILE_PROTOCOL *DestDir) {
    EFI_STATUS status;
    EFI_FILE_INFO *FileInfo;

    if(is_file(SourceFileOrDir)){
        EFI_FILE_PROTOCOL *File;
        FileInfo = FileHandleGetInfo(SourceFileOrDir);
        status = OpenFileCreate(DestDir, FileInfo->FileName, &File);
        CopyFile(SourceFileOrDir, File);
    }else{
        EFI_FILE_PROTOCOL *CreatedDirectory;
        FileInfo = FileHandleGetInfo(SourceFileOrDir);
        MakeDirectory(DestDir, FileInfo->FileName, &CreatedDirectory);

        UINTN BufferSize;
        CHAR16 FileName[256];

        SourceFileOrDir->SetPosition(SourceFileOrDir, 0);

        do{
            BufferSize = sizeof(EFI_FILE_INFO) + sizeof(FileName);
            FileInfo = AllocatePool(BufferSize);
            

            if(FileInfo == NULL){
                status = EFI_OUT_OF_RESOURCES;
                break;
            }

            status = SourceFileOrDir->Read(SourceFileOrDir, &BufferSize, FileInfo);

            if(!EFI_ERROR(status) && BufferSize > 0){
                if (StrCmp(FileInfo->FileName, L".") != 0 && StrCmp(FileInfo->FileName, L"..") != 0){
                    StrCpyS(FileName, sizeof(FileName)/sizeof(FileName[0]), FileInfo->FileName);
                    EFI_FILE_PROTOCOL *CopyingFile;
                    status = OpenFileOrDir(SourceFileOrDir, FileName, &CopyingFile);
                    if(status == EFI_SUCCESS){
                        status = CopyDirectoryRecursive(CopyingFile, CreatedDirectory);
                    }else{
                        return status;
                    }
                }
            }
            FreePool(FileInfo);

        }while (!EFI_ERROR(status) && BufferSize > 0);
    }
    return status;
}

void help(){
    Print(L"Supported commands are:\n");
    Print(L"ls - list all files and directories in the current directory\n");
    Print(L"ls -n - list all files and directories in the current directory with alphabetical order\n");
    Print(L"rm <file_name> - remove file or directory\n");
    Print(L"mkdir <directory_name> - create a new directory\n");
    Print(L"cd <directory_name> - change current directory\n");
    Print(L"nano <file_name> - create or edit a file\n");
    Print(L"info <file_name> - print name and size of a file\n");
    Print(L"cat <file_name> - print content of a file\n");
    Print(L"copy <file_name> - copy a file or directory\n");
    Print(L"cut <file_name> - cut a file or directory\n");
    Print(L"paste - paste a file or directory\n");
    Print(L"search <sub_name> - show files and directories that contains this substring\n");
    Print(L"quit - exit the program\n");
}

BOOLEAN isSubString(CHAR16* Substring, CHAR16* String) {
    return (StrStr(String, Substring) != NULL);
}


EFI_STATUS SearchFiles(EFI_FILE_PROTOCOL *Current_Dir, CHAR16* file_name, CHAR16* founded_files[], UINTN* count, CHAR16* current_path){
    EFI_FILE_INFO *FileInfo;
    EFI_STATUS status;
    UINTN BufferSize;
    CHAR16 FileName[256];

    Current_Dir->SetPosition(Current_Dir, 0);

    do{
        BufferSize = sizeof(EFI_FILE_INFO) + sizeof(FileName);
        FileInfo = AllocatePool(BufferSize);
        

        if(FileInfo == NULL){
            status = EFI_OUT_OF_RESOURCES;
            break;
        }

        status = Current_Dir->Read(Current_Dir, &BufferSize, FileInfo);

        if(!EFI_ERROR(status) && BufferSize > 0){
            if (StrCmp(FileInfo->FileName, L".") != 0 && StrCmp(FileInfo->FileName, L"..") != 0){
                StrCpyS(FileName, sizeof(FileName)/sizeof(FileName[0]), FileInfo->FileName);
                CHAR16* nameCopy = AllocatePool((StrLen(FileName) + 1) * sizeof(CHAR16));
                StrCpyS(nameCopy, StrLen(FileName) + 1, FileName);

                CHAR16 *NextPath;

                // Allocate memory for the next path
                NextPath = AllocateZeroPool(StrSize(current_path) + StrSize(FileInfo->FileName) + 2);
                if (NextPath == NULL) {
                    FreePool(FileInfo);
                    return EFI_OUT_OF_RESOURCES;
                }

                // Create the next path
                StrCpyS(NextPath, StrSize(current_path) + StrSize(FileInfo->FileName) + 2, current_path);
                StrCatS(NextPath, StrSize(current_path) + StrSize(FileInfo->FileName) + 2, L"\\");
                StrCatS(NextPath, StrSize(current_path) + StrSize(FileInfo->FileName) + 2, FileInfo->FileName);

                if(isSubString(file_name, nameCopy)){
                    founded_files[*(count)] = NextPath;
                    *(count) = *(count) + 1;
                }
                if (is_name_file(Current_Dir, FileName) == 0){
                    EFI_FILE_PROTOCOL *New_Dir;
                    status = OpenDirectory(Current_Dir, FileName, &New_Dir);
                    if(status == EFI_SUCCESS){
                        status = SearchFiles(New_Dir, file_name, founded_files, count, NextPath);
                    }else{
                        return status;
                    }
                }
            }
        }
        FreePool(FileInfo);

    }while (!EFI_ERROR(status) && BufferSize > 0);

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UefiMain (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS status;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    status = gBS->LocateProtocol(
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        (VOID**)&FileSystem
    );
    Print(L"Boot was: %r\n", status);
    EFI_FILE_PROTOCOL *Root;
    status = FileSystem->OpenVolume(FileSystem, &Root);
    Print(L"Location Root was: %r\n", status);
    if (EFI_ERROR(status)) {
        return status;
    }
    //PrintFileInfo(FileHandleGetInfo (Root));

    EFI_FILE_PROTOCOL *Current_Dir = Root;
    UINTN Copy_Cut_Flag = 0;
    EFI_FILE_PROTOCOL *Copied_Dir_Or_File;
    CHAR16 Buffer[256];


    while(1){
        // Print(L"Input Your command\n");
        status = GetString(Buffer, sizeof(Buffer)/sizeof(Buffer[0]));
        if(EFI_ERROR(status)){
            Print(L"Error Reading String: %r\n", status);
        }else{
            Print(L"\n>> %s\n", Buffer);
        }
        if (StrCmp(Buffer, L"quit") == 0){
            Print(L"Bye!\n");
            return EFI_SUCCESS;
        }else if(StrCmp(Buffer, L"ls") == 0){
            PrintDirectoryInfo(Current_Dir, 0);
        }else if(StrnCmp(Buffer, L"ls -", 4) == 0){
            if(GetSize(Buffer) == 12){
                if(Buffer[4] == 'n'){
                    PrintDirectoryInfo(Current_Dir, 1);
                }else if(Buffer[4] == 's'){
                    PrintDirectoryInfo(Current_Dir, 2);
                }else{
                    Print(L"Enter a valid flag\n");
                }
            }else{
                Print(L"Etner a valid flag\n");
            }
        }else if(StrnCmp(Buffer, L"rm ", 3) == 0){
            EFI_FILE_PROTOCOL *File_or_Dir;
            status = OpenFileOrDir(Current_Dir, Buffer+3, &File_or_Dir);
            if(EFI_ERROR(status)){
                Print(L"Error finding the file: %r\n", status);
                continue;
            }
            status = DeleteFileOrDir(File_or_Dir);
            Print(L"Delete status: %r\n", status);
        }else if(StrnCmp(Buffer, L"mkdir ", 6) == 0){
            if(isThereFile(Current_Dir, Buffer+6)){
                Print(L"Already Exists\n");
                continue;
            }
            EFI_FILE_PROTOCOL *New_Directory;
            status = MakeDirectory(Current_Dir, Buffer+6, &New_Directory);
            Print(L"Directory status: %r\n", status);
        }else if(StrnCmp(Buffer, L"cd ", 3) == 0){
            EFI_FILE_PROTOCOL *New_Directory;
            status = OpenDirectory(Current_Dir, Buffer+3, &New_Directory);
            Print(L"Open Directory status: %r\n", status);
            if(status == EFI_SUCCESS){
                if (is_name_file(Current_Dir, Buffer+3) != 0){
                    Print(L"Error. You need to call cd on a directory\n");
                    continue;
                }
                Current_Dir = New_Directory;
            }
        }else if(StrnCmp(Buffer, L"nano ", 5) == 0){
            EFI_FILE_PROTOCOL *File;
            status = OpenFileOnlyRead(Current_Dir, Buffer+5, &File);
            if(status == EFI_SUCCESS){
                if (is_name_file(Current_Dir, Buffer+5) != 1){
                    Print(L"Error. You need to call nano on a file\n");
                    continue;
                }
                Print(L"Already Exists\n");
                CHAR16 ReadData[256];
                UINTN Size = sizeof(ReadData);
                status = File->Read(File, &Size, ReadData);
                if(status == EFI_SUCCESS){
                    Print(L"Write on the file\n");
                    Print(L"%s", ReadData);
                    File->SetPosition(File, 0);
                    status = GetStringFromIndex(ReadData, sizeof(ReadData)/sizeof(ReadData[0]), (GetSize(ReadData)/2)-1);
                    if(EFI_ERROR(status)){
                        Print(L"Error Reading String: %r\n", status);
                    }else{
                        Print(L"\nYou Entered: %s\n", ReadData);
                        UINTN size = GetSize(ReadData);
                        Print(L"%d\n", size);
                        File->SetPosition(File, 0);
                        status = File->Write(File, &size, ReadData);
                        Print(L"write status :%r\n", status);
                    }
                }else{
                    Print(L"Read from file: %s\n", ReadData);
                }
            }else{
                status = OpenFileCreate(Current_Dir, Buffer+5, &File);
                Print(L"Open New File\n");
                Print(L"Write whatever you want\n");
                CHAR16 FileBuffer[256];
                status = GetString(FileBuffer, sizeof(FileBuffer)/sizeof(FileBuffer[0]));
                if(EFI_ERROR(status)){
                    Print(L"Error Reading String: %r\n", status);
                }else{
                    Print(L"\nYou Entered: %s\n", FileBuffer);
                    UINTN size = GetSize(FileBuffer);
                    Print(L"%d\n", size);
                    status = File->Write(File, &size, FileBuffer);
                    Print(L"write status :%r\n", status);
                }
            }
        }else if(StrnCmp(Buffer, L"info ", 5) == 0){
            EFI_FILE_PROTOCOL *File;
            status = OpenFileOnlyRead(Current_Dir, Buffer+5, &File);
            if (is_name_file(Current_Dir, Buffer+5) != 1){
                Print(L"Error. You need to call info on a file\n");
                continue;
            }
            if(status == EFI_SUCCESS){
                Print(L"File Opened successfully\n");
                PrintFileInfo(File);
            }else{
                Print(L"File Open status: %r\n", status);
            }
        }else if(StrnCmp(Buffer, L"cat ", 4) == 0){
            EFI_FILE_PROTOCOL *File;
            status = OpenFileOnlyRead(Current_Dir, Buffer+4, &File);
            if (is_name_file(Current_Dir, Buffer+4) != 1){
                Print(L"Error. You need to call cat on a file\n");
                continue;
            }
            if(status == EFI_SUCCESS){
                Print(L"File Opened successfully\n");
                CHAR16 ReadData[256];
                UINTN Size = sizeof(ReadData);
                status = File->Read(File, &Size, ReadData);
                Print(L"read status %r\n", status);
                if(status == EFI_SUCCESS){
                    Print(L"Read from file: %s\n", ReadData);
                }
            }else{
                Print(L"File Open status: %r\n", status);
            }
        }else if(StrnCmp(Buffer, L"copy ", 5) == 0){
            status = OpenFileOrDir(Current_Dir, Buffer+5, &Copied_Dir_Or_File);
            if(status == EFI_SUCCESS){
                Print(L"File copied successfully\n");
                Copy_Cut_Flag = 1;
            }else{
                Print(L"File copy status: %r\n", status);
                Copy_Cut_Flag = 0;
            }
        }else if(StrnCmp(Buffer, L"cut ", 4) == 0){
            status = OpenFileOrDir(Current_Dir, Buffer+4, &Copied_Dir_Or_File);
            if(status == EFI_SUCCESS){
                Print(L"File cut successfully\n");
                Copy_Cut_Flag = 2;
            }else{
                Print(L"File cut status: %r\n", status);
                Copy_Cut_Flag = 0;
            }
        }else if(StrCmp(Buffer, L"paste") == 0){
            if(Copy_Cut_Flag == 0){
                Print(L"Nothing has Been copied yet\n");
                continue;
            }
            EFI_FILE_INFO *FileInfo = FileHandleGetInfo(Copied_Dir_Or_File);
            if(isThereFile(Current_Dir, FileInfo->FileName)){
                Print(L"Already Exists\n");
                continue;
            }
            status = CopyDirectoryRecursive(Copied_Dir_Or_File, Current_Dir);
            if(status == EFI_SUCCESS){
                Print(L"File Pasted successfully\n");
                if(Copy_Cut_Flag == 2){
                    Copy_Cut_Flag = 0;
                    status = DeleteFileOrDir(Copied_Dir_Or_File);
                }
            }
        }
        else if (StrCmp(Buffer, L"help") == 0){
            help();
        }else if (StrnCmp(Buffer, L"search ", 7)==0){
            CHAR16 *files[256];
            CHAR16 *path = L".";
            UINTN count = 0;
            status = SearchFiles(Current_Dir, Buffer+7, files, &count, path);
            if(status == EFI_SUCCESS){
                if(count != 0){
                    for(UINTN i = 0; i < count; i++){
                        Print(L"%s\n", files[i]);
                    }
                }else{
                    Print(L"nothing found\n");
                }
            }else{
                Print(L"status: %r", status);
            }
        }else {
            Print(L"Invalid command.\n");
            help();
        }
    }
    return EFI_SUCCESS;
}