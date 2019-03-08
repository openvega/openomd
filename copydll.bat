if exist "target\nar\lib\amd64-Windows-msvc\shared\*.dll" (
	copy /Y target\nar\lib\amd64-Windows-msvc\shared\*.dll %1
) else (
	echo "no dll"
)