@echo off 
del *.htm /s
del *.obj /s
del *.lnp /s
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