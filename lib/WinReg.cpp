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