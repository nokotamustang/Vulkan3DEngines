@echo off

REM Look for any .vert .geom or .frag file and compile them to SPIR-V
for /R %%f in (*.vert *.geom *.frag) do (
	echo %%f
	C:/VulkanSDK/1.3.290.0/Bin/glslc.exe %%f -o %%f.spv
)

pause