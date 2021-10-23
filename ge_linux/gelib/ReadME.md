用来练习静态库和动态库

生成静态库 

1.gcc -c wcr_splitter.c
-c告诉gcc只编译，不链接

2.ar rcs wcr_splitter.a wcr_splitter.o 
r - 如果存在则替换c 
c - 如果目标不存在则创建
s -为目标文件创建索引

使用静态库
gcc -g3 -o testlib testlib.c wcr_splitter.a
想提供.c那样提供给gcc就行了

===================================================================================================================

生成动态库
gcc -fPIC -shared -o libwcr_splitter.so wcr_splitter.c

构建时使用动态库

gcc -g3 -o testdlib testlib.c -L. -lwcr_splitter
-L 指定搜索so的路径 -l 指定要链接的so,lib前缀可以省略

ld搜索so的顺序 
构建时指定的位置->LD_LIBRARY_PATH变量定义的位置->/etc/ld.so.cache定义的位置*->默认位置/lib和usr/lib(/lib64和/usr/lib64)

5种动态库的使用方法

1.sudo cp libwcr_splitter.so /usr/lib •使用默认位置

2.构建时使用rpath指定

3.临时指定LD_LIBRARY_PATH

4.通过bashrc脚本修改LD_LIBRARY_PATH

5.向ld.so.conf.d目录放入文件
