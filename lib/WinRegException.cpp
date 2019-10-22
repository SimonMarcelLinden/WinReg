/**
 * @editor     CLion
 * @since      0.0.1
 * @package    ./WinReg
 * @subpackage ./lib
 *
 * @author Simon Marcel Linden <linden@snerve.de>
 * @date 20.10.2019
 *
 */

#include "WinReg.h"

using namespace WinReg;

LONG WinRegException::ErrorCode() const noexcept{
    return m_errorCode;
}