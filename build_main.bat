del main.exe 
cl.exe lib\lua5.1.lib lib\lua51.lib main.cpp 
link.exe lib\lua5.1.lib lib\lua51.lib main.obj
del main.obj 
