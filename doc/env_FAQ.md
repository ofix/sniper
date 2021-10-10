## CodeBlocks配色方案改变方法
[https://blog.csdn.net/xrinosvip/article/details/82084842?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163378343916780274134048%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163378343916780274134048&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-82084842.pc_search_ecpm_flag&utm_term=codeblocks+%E9%85%8D%E8%89%B2&spm=1018.2226.3001.4187](https://blog.csdn.net/xrinosvip/article/details/82084842?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163378343916780274134048%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163378343916780274134048&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-82084842.pc_search_ecpm_flag&utm_term=codeblocks+%E9%85%8D%E8%89%B2&spm=1018.2226.3001.4187)

## 修正错误 fatal error: wx/setup.h: No such file or directory
```cpp
// 菜单路径 Project > Build Options > Search directories > Compiler|Linker 添加以下路径
$(#wx)\wxMSW-3.1.5_gcc810_x64_Dev\lib\gcc810_x64_dll\mswud
$(#wx)\wxWidgets-3.1.5-headers\include
```
## 修正错误 fatal error: wx/msw/wx.rc: No such file or directory
```
// 菜单路径 Project > Build Options > Search directories > Resource compiler 添加以下路径
$(#wx)\wxWidgets-3.1.5-headers\include
// 详情请参考链接 https://forums.codeblocks.org/index.php?topic=9959.0
```

## 由于找不到vcruntime140.dll无法继续执行代码的解决方法
```
下载最新版的VC库即可解决问题
https://docs.microsoft.com/zh-CN/cpp/windows/latest-supported-vc-redist?view=msvc-160
https://aka.ms/vs/16/release/vc_redist.x64.exe
```

## 添加wxWidgets项目依赖
直接修改文件*.cbp工程文件,可以进行批量修改
```
libwxmsw31u_richtext.a   
libwxscintilla.a 
libwxmsw31u_stc.a       
libwxbase31u.a              
libwxbase31u_net.a          
libwxbase31u_xml.a          
libwxbase31ud.a             
libwxbase31ud_net.a       
libwxbase31ud_xml.a       
libwxexpat.a              
libwxexpatd.a             
libwxjpeg.a               
libwxjpegd.a              
libwxmsw31u_adv.a         
libwxmsw31u_core.a        
libwxmsw31u_html.a        
libwxmsw31u_media.a       
libwxmsw31u_propgrid.a    
libwxmsw31u_ribbon.a      
libwxscintillad.a
libwxmsw31u_webview.a  
libwxmsw31u_xrc.a      
libwxmsw31ud_adv.a     
libwxmsw31ud_aui.a     
libwxmsw31ud_core.a    
libwxmsw31ud_gl.a      
libwxmsw31ud_html.a    
libwxmsw31ud_media.a   
libwxmsw31ud_propgrid.a
libwxmsw31ud_ribbon.a  
libwxmsw31ud_richtext.a
libwxmsw31ud_webview.a 
libwxpng.a             
libwxpngd.a            
libwxregexu.a          
libwxregexud.a   
libwxtiff.a         
libwxtiffd.a  
libwxzlib.a   
libwxzlibd.a 
```
### 打开Notepad++ 正则替换得到完整的wxWidgets链接lib依赖路径
>查找目标: `^`  
替换为:   `<Add library="$\(#wx\)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/`
查找目标: `\s*$`  
替换为:   `" />`

替换后的完整路径为:
```
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_richtext.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxscintilla.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_stc.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxbase31u.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxbase31u_net.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxbase31u_xml.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxexpat.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxjpeg.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_propgrid.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_adv.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_core.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_html.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_media.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_ribbon.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_webview.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_xrc.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxpng.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxregexu.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxtiff.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxzlib.a" />

-----------------------------------------------------------------------------------------------

<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_richtext.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxscintillad.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxbase31ud.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxbase31ud_net.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxbase31ud_xml.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxexpatd.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxjpegd.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_propgrid.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_adv.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_core.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_html.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_media.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_ribbon.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_webview.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31u_stc.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_aui.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxmsw31ud_gl.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxpngd.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxregexud.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxtiffd.a" />
<Add library="$(#wx)/wxMSW-3.1.5_gcc810_x64_Dev/lib/gcc810_x64_dll/libwxzlibd.a" />
```