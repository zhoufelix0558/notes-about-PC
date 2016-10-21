##python软件恢复右键edit with idle功能
1. 打开regedit，然后找到`HKEY_CLASSES_ROOT\SystemFileAssociations`
2. 在上面的路径中新建一个Key，名称叫".py"
3. ".py"下面建立新的一个Key，名称叫"shell"
4. "shell"下面建立一个新的Key，名称叫"edit"
5. "edit"下面建立一个新的Key，名称叫"command"
6. ‘shell’,'edit'的键值均改为"Edit with IDLE"
7. 将’command‘的键值设置成：`c:\Python34\pythonw.exe c:\Python34\Lib\idlelib\idle.pyw -e %1`(每台计算机的python根目录不尽相同)


