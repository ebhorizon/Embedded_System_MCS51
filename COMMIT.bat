@echo off 
del *.lst /s
del *.m51 /s
del *.htm /s
del *.obj /s
del *.lnp /s
del *.Administrator /s
for /f "delims=" %%i in ('dir /ad /b /s "OBJ"') do (
   rd /s /q "%%i"
)
for /f "delims=" %%i in ('dir /ad /b /s "Listings"') do (
   rd /s /q "%%i"
)
set input=
set /p input=�������ύ��Ϣ:
echo ��ʼ�������
git add .
echo ��ʼ�ύ
git commit -m %input%
echo ��ʼ�ϴ�
echo �ȴ���������
git push -u origin master
echo �ϴ��ɹ�
pause