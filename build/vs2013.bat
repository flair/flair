script=$0
curdir="${script%\\*}"
cd curdir

premake5.exe --file=../premake.lua vs2013
