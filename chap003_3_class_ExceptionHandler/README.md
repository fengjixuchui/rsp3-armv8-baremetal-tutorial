# 关于
本节介绍中断处理器，中断处理器使用中断管理器来管理中断。
这样划分主要是因为，不同的实现具有不同的中断控制机制，相比而言，GIC比树莓派3使用的
中断控制器要复杂得多。中断管理器是对中断控制器的抽象。

中断管理器提供的方法包括：对中断进行屏蔽，中断结束等。

本节还介绍如何模板实例化中断处理器。

（下节应当介绍输入中断，定时中断）
# 状态
已完成
树莓派：已测试