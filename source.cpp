#include <Windows.h>
#include <iostream>
#include <string>

int main()
{
    // Get the serial number of the C: drive
    const char* drive = "C:\\";
    char volumeName[MAX_PATH + 1];
    char fileSystemName[MAX_PATH + 1];
    DWORD serialNumber;
    DWORD maxComponentLength;
    DWORD fileSystemFlags;

    if (GetVolumeInformationA(drive, volumeName, MAX_PATH, &serialNumber, &maxComponentLength, &fileSystemFlags, fileSystemName, MAX_PATH))
    {
        std::cout << "The serial number of the C: drive is: " << serialNumber << std::endl;
		std::string serialNumberString = std::to_string(serialNumber);
		const size_t len = serialNumberString.length() + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), serialNumberString.c_str(), len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
    }
    else
    {
        std::cout << "Failed to get the serial number of the C: drive" << std::endl;
    }
	std::cin.get();
    return 0;
}
