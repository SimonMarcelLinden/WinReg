/**
 * @editor     CLion
 * @since      0.0.1
 * @package    ./WinReg
 * @subpackage ./includes
 *
 * @author Simon Marcel Linden <linden@snerve.de>
 * @date 20.10.2019
 *
 */

#ifndef WINREG_H
#define WINREG_H

#include <windows.h>        // Windows Platform SDK
#include <iostream>

namespace WinReg {
    class RegKey {
    public:
        RegKey(HKEY hKeyParent, const std::wstring &subKey);
        ~RegKey();

        DWORD GetDwordValue(const LPCTSTR valueName);
        BOOL SetDwordValue(const LPCTSTR valueName, DWORD value);

    private:
        HKEY m_hKey{ nullptr };
    };
    class WinRegException : public std::runtime_error{
    public:
        WinRegException(const char* message, LONG errorCode) : std::runtime_error{ message } , m_errorCode{ errorCode } {}
        WinRegException(const std::string& message, LONG errorCode) : std::runtime_error{ message } , m_errorCode{ errorCode } {}

        // Get the error code returned by Windows registry APIs
        LONG ErrorCode() const noexcept;

    private:
        // Error code, as returned by Windows registry APIs
        LONG m_errorCode;
    };
}

#endif //WINREG_H