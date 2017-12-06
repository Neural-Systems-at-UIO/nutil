!DEC$ IF DEFINED (_M_X64)
include 'libxl_x64.f90'
!DEC$ ELSE
include 'libxl_x32.f90'
!DEC$ ENDIF

