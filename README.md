# MCS51单片机的例程

By Linkat Horizon
-------

[个人网页](http://ebhorizon.cn)——有问题请在下方留言栏留言~

### 【项目名称】

51单片机例程的整理，代码已经文件化，方便各种调用~

### 【项目列表】

| ID   | Name                                          | Chips                                                        | Platform & Modules                                           |
| ---- | --------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1    | [LED发光二极管相关实验](./1_LED)              | **Main:**<br>1 × STC90C516RD+ (12MHz)                        | **Platform:**<br>1 × Prechin HC6800-EM3 v2.2                 |
| 2    | [中继器实验](./2_Relay)                       | **Main:**<br/>1 × STC90C516RD+ (12MHz)                       | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2                |
| 3    | [LED数码管相关实验](./3_LED_Segment_Displays) | **Main:**<br/>1 × STC90C516RD+ (12MHz)<br>**Others:**<br>1 × 74HC164<br>1 × 74HC573<br>1 × 74HC138 | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2<br/>**Module:**<br/>`1 × Self-designed` |
| 4    | [外部中断实验](./4_External_Interrupt)        | **Main:**<br/>1 × STC90C516RD+ (12MHz)                       | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2                |
| 5    | [定时/计数器实验](./5_Timer_Counter)          | **Main:**<br/>1 × STC90C516RD+ (12MHz)<br/>**Others:**<br/>1 × 74HC138 | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2                |
| 6    | [按键相关实验](./6_Keys)                      | **Main:**<br/>1 × STC90C516RD+ (12MHz)<br />**Others:**<br/>1 × 74HC138 | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2<br/>**Module:**<br/>`1 × Self-designed` |
| 7    | [LED点阵相关实验](./7_LED_Lattice)            | **Main:**<br/>1 × STC90C516RD+ (12MHz)<br />**Others:**<br/>2 × 74HC595 | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2                |
| 8    | [LCD1602实验](./8_LCD1602)                    | **Main:**<br/>1 × STC90C516RD+ (12MHz)<br />**Others:**<br/>(1 × HD44780)<br/>(1 × HD44100) | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2<br/>**Module:**<br/>1 × SCM1602C v2.0<br/>(1 × SCM1602A v3.0) |
| 9    | [蜂鸣器实验](./9_Buzzer)                      | **Main:**<br/>1 × STC90C516RD+ (12MHz)                       | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2                |
| 10   | [电机相关实验](./10_Motor)                    | **Main:**<br/>1 × STC90C516RD+ (12MHz)<br/>**Others:**<br/>1 × ULN2003<br/>1 × UND2916 | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2                |
| 11   | [脉冲发生器实验](./11_Pulse_Generator)        | **Main:**<br/>1 × STC90C516RD+ (12MHz)<br/>**Others:**<br/>1 × NE555 | **Platform:**<br/>1 × Prechin HC6800-EM3 v2.2                |

> 注：
>
> 1. 上表中的型号代表我测试所用的型号，其他型号未测试但是不代表不能用
> 2. 括号中的芯片代表模块中的且不直接操作的芯片（模块有自己的操作方式）
> 3. 括号中的模块代表是实验过程中使用的另一个型号的同种模块
> 4. 模块列中的高亮项目是自己设计/焊接的模块，详情需参见项目的电路图