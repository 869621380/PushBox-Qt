# 推箱子小游戏
本项目是基于Qt开发的推箱子小游戏，仅供学习交流之用
使用Qt5.14.2完成开发
## 开发流程
1.设置基础地图样式，完成初始化与渲染环节<br>
2.完成侧边按钮的布局<br>
3.实现键盘按键使人物进行移动<br>
4.实现游戏胜利的判断<br>
5.设置步数计数以及当前关卡的显示<br>
6.实现侧边栏的回退功能<br>
7.在结束后添加胜利提醒对话框<br>
8.优化下一关卡按钮，只有在解锁下一关卡的时候才能使用此按钮<br>
9.实现初始游戏模式选择界面<br>
10.在游戏内框添加返回主菜单按钮<br>
11.创建游戏登陆，退出登录，开始游戏按钮<br>
12.实现退出登录，开始游戏功能<br>
13.创建数据库<br>
14.实现登录按钮<br>
15.实现游戏账号数据与数据库的连接，对最大通关数进行保存<br>
16.对代码结构进行优化,对游戏交互性进行优化<br>
17.更新数据库内容，实现对排行榜数据的处理<br>
18.实现排行榜按钮，完成对排行榜页面布局的编写<br>
19.添加自由设计模式<br>
20.添加背景音乐<br>
21.界面优化<br>
## 项目介绍
项目结构分为四部分：登陆界面，游戏界面，排行榜界面，自主设计模式界面<br>

![alt text](/image/res1.png)
### 登录界面
1.游戏使用SQLite数据库管理账号信息<br>
2.登录按钮根据用户提供的凭据查询数据库并验证其有效性。<br>
3.注册按钮检查用户名唯一性并插入新账号信息到数据库，来实现新账号的创建。<br>
4.账号内包含当前账号最大通关数，当前账号上(排行)榜数据等内容,实现账号数据的存储<br>

![alt text](/image/res2.png)
### 游戏界面
1.玩家通过上下左右键控制角色移动，将所有箱子推入指定地点<br>
2.设计重玩与回退按钮<br>
3.使用数据库记录每个账号的最大通关数，通过上下关卡按钮实现已通关关卡的直接跳转。<br>
![alt text](/image/res3.png)
### 排行榜界面
关卡内设置步数统计<br>
设置排行榜系统，排行榜只记录步数最少的十人，相同步数依照时间顺序进行排序。<br>
![alt text](/image/res4.png)
### 自主设计模式
该模式玩家可以自主设计游戏关卡并对其进行挑战，暂未设计模式数据保存与共享功能<br>
![alt text](/image/res5.png)
