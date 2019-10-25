set(Sources WinReg.h WinReg.cpp WinRegException.cpp)

add_library(WinReg SHARED ${Sources})
set_target_properties(WinReg PROPERTIES PREFIX "")