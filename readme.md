2017 09 28 创建仓库 移植github

2017 09 29 修改用户模块 初步上线用户注册功能 修复多个bug (用户信息文件)

2017 09 30 完善用户登录功能 (登录时查找用户名是否存在仍未完成)

2017 10 01 加入购物车模块

2017 10 02 加入借阅功能 借阅信息可以存入文件 程序大体完成

2017 10 03 重写大部分界面 修复bug

2017 10 06 加入归还 充值 功能

2017 10 07 完善归还功能 个人中心可以正常显示归还借阅信息 对页面流程进行优化 修复一些bug

2017 10 09 删除无用功能 修复一些bug

2017 10 10 加入用户借阅限制 用户最多只可以借阅20部影片 购物车可以一次借阅一张影片了 可以随时调整借阅影片最大数量

2017 10 14 简化用户查找影片流程

2017 10 16 优化页面输出 以及程序的流程 更改电影数据的代码重用

2017 10 30 更改界面 固定窗口大小 对相应内容增加颜色增加颜色

2017 10 31
- 各个二进制数据文件
    - adminuser : 管理员数据文件(用户名&密码)
    - filmbinary : 电影数据二进制文件
    - filminfo : 电影信息文件
    - vipinfo : 用户信息文件
    - vipuser : 用户数据二进制文件(id 用户名 密码)

- 页面结构

    未登录页面
    - 登录
        - vip登录

                 已登录页面(vip)
                    - 影片查询
                    - 影片归还
                    - 我的购物车
                    - 个人中心
                    - 充值
                    - 退出登录
        - 管理员登录
            
                已登录页面(管理员)
                    - 影片上架
                    - 影片查找
                        - 删除电影
                        - 修改价格
                        - 修改余量
                        - 返回
                    - 显示影片列表
                        - 显示所有影片
                        - 显示特定区间影片
                    - 退出登录
    - 注册
        -  vip注册
    - 退出系统
        - 退出

- BUG以及待添加功能

    - 返回键代码重用
    - 返回键失灵 (需要getchar()吸收回车符)
    - 影片上架批量导入功能改进
    - 用户注册重名检查以及密码输入两次验证
    - 文件打开失败后的异常处理问题 fwrite()或fread()
    - 输入密码backspace符号被记录
    - 密码输错一次 再也无法登录(已解决)
    - 遍历电影文件的代码重用
    - film.c中修改电影信息代码重用
    - 账户充值合法性判断
    - 购物车中影片借阅完毕后清空(已解决)
    - 计费模块计费不准(已解决)
    - 用户切换失败 管理员切换vip(已解决)
    - 局部变量初始化C99兼容性(已解决)
    - 借阅数量限制(已解决)
    - 用户中心 未归还信息显示(已解决)
    - 无法借阅单个影片(已修复)
    - 查询影片页面步骤过于繁琐(已解决)
    - 用户借阅/归还影片余量变化
    - 用户当前借阅的影片数目出错
    - 正确错误操作颜色提示功能添加(已解决)
    - 根据余量判断借阅状态
    - 用户借阅文件读写失败(已解决)
    - 新功能:更改用户借阅电影数
    - 新功能:用户管理 用户查看(管理员视角)
    - 新功能:管理员视角 用户和电影借阅关系