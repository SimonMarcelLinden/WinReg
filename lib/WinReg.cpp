/**
 * @editor     CLion
 * @since      0.0.1
 * @package    ./WinReg
 * @subpackage ./lib
 *
 * @author Simon Marcel Linden <linden@snerve.de>
 * @date 22.10.2019
 *
 */

#include "WinReg.h"

using namespace WinReg;

RegKey::RegKey(HKEY hKeyParent, const std::wstring& subKey) {
    DWORD dwDisposition; //It verify new key is created or open existing key
    HKEY hKey;
    DWORD retCode;

    retCode = RegCreateKeyEx(hKeyParent, "Software\\GioTest", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, 0);

    if (retCode != ERROR_SUCCESS) {
        std::cout << "Error opening or creating new key." << std::endl;
        throw WinRegException{ "RegCreateKeyEx failed.", (LONG) retCode};
    }

    this->m_hKey = hKey;
}
RegKey::~RegKey() {
    RegCloseKey(this->m_hKey); //close the key
}

DWORD RegKey::GetDwordValue(const LPCTSTR valueName) {
    DWORD dwNumber  = 0;
    DWORD dwData    = sizeof(DWORD);
    DWORD retValue;

    retValue =  RegQueryValueExA(this->m_hKey, valueName , 0, 0, (BYTE*)&dwNumber, &dwData);

    if (retValue != ERROR_SUCCESS) {
//        std::cout << "Cannot get DWORD value: RegGetValue failed." << std::endl;
        throw WinRegException{ "Cannot get DWORD value: RegGetValue failed.", (LONG) retValue };
    }

    return dwNumber;
}
BOOL RegKey::SetDwordValue(const LPCTSTR valueName, DWORD value) {

    DWORD retCode;

    retCode = RegSetValueEx(this->m_hKey, valueName, 0, REG_DWORD, (BYTE*) & value, sizeof(DWORD));
    if (retCode != ERROR_SUCCESS) {
        //std::cout << "Cannot set DWORD value: RegSetValueEx failed." << std::endl;
        throw WinRegException{"Cannot set DWORD value: RegSetValueEx failed.", (LONG) retCode};
    }

    return GetDwordValue(valueName) == value;
}

std::string RegKey::GetStringValue(LPCTSTR valueName) const{
    DWORD dwData       = 256;
    BYTE cData[256]    = "";
    DWORD retCode;

    retCode = RegQueryValueEx(this->m_hKey, valueName, 0, 0, cData, &dwData);

    if (retCode != ERROR_SUCCESS) {
        //std::cout << "Cannot get string value: RegGetValue failed." << std::endl;
        throw WinRegException{"Cannot get string value: RegGetValue failed.", (LONG) retCode};
    }

    std::string result((char *)cData);
    return result;
}

BOOL RegKey::SetStringValue(char* valueName, char* value){

    DWORD retCode;
    retCode = RegSetValueEx (this->m_hKey, valueName, 0, REG_SZ, (LPBYTE)value, std::strlen(value)+1);

    if (retCode != ERROR_SUCCESS) {
        //std::cout << "Cannot set DWORD value: RegSetValueEx failed." << std::endl;
        throw WinRegException{"Cannot set REGSZ value: RegSetValueEx failed.", (LONG) retCode};
    }

    return GetStringValue(valueName) == value;
}