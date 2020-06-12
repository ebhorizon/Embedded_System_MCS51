<<<<<<< HEAD
@echo off 
del *.htm /s
del *.obj /s
del *.lnp /s
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
=======
@echo off 
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
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
pause