del adapter.exe
cl.exe lib\lua5.1.lib lib\lua51.lib adapter.cpp 
link.exe lib\lua5.1.lib lib\lua51.lib adapter.obj
del adapter.obj
