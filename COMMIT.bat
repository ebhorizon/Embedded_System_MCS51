<<<<<<< HEAD
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
=======
@echo off 
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
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
pause