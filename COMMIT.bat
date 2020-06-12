@echo off 
del *.lst /s
del *.m51 /s
del *.htm /s
del *.obj /s
del *.lnp /s
del *.Administrator /s
set input=
set /p input=请输入提交信息:
echo 开始添加整体
git add .
echo 开始提交
git commit -m %input%
echo 开始上传
echo 等待输入密码
git push -u origin master
echo 上传成功
pause