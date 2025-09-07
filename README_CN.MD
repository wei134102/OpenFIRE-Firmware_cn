# OpenFIRE-Firmware 中文文档
OpenFIRE-Firmware_cn 完整中文文档
项目概述
OpenFIRE 是一个开源的4红外LED光枪系统，是IR-GUN4ALL项目的继任者，基于SAMCO项目进行深度优化和功能扩展。专为RP2040/RP2350微控制器设计，支持多种力反馈设备和高级功能。

核心功能特性
🔫 精准定位系统
4IR技术：支持4个红外LED的精准定位
实时透视调整：支持双光条（推荐）和Xwiigun钻石布局
多模式跟踪：正方形和钻石形红外布局兼容
高刷新率：鼠标位置更新频率高达209Hz（约4.8ms间隔）
🎮 灵活输入系统
多模式输出：
5键绝对定位鼠标
双摇杆游戏手柄 + 方向键
键盘模式
MiSTer FPGA优化：专门的游戏映射
可自定义按键映射：通过配套应用实时配置
💥 力反馈支持
电磁阀控制：12/24V电磁阀驱动，支持自定义脉冲
震动马达：5V游戏手柄震动马达控制
RGB LED：WS2812B NeoPixels实时灯光效果
OLED显示：SSD1306 I2C显示屏支持
🛠️ 高级功能
多核优化：RP2040双核分工，主核处理摄像头，副核处理输入
配置文件：4个独立的校准配置文件
实时配置：通过OpenFIRE桌面应用实时调整
USB标识符：支持多枪识别的自定义USB ID
串口反馈：兼容MAME Hooker等PC力反馈处理器
硬件需求
必需组件
微控制器：RP2040或RP2350（推荐树莓派Pico、KB2040、ItsyBitsy RP2040）
红外摄像头：DFRobot IR定位摄像头 SEN0158
红外LED：4个SFH 4547高功率红外LED + 5.6Ω电阻
可选组件
电磁阀：12/24V + 驱动板
震动马达：5V游戏手柄马达 + 驱动板
RGB LED：WS2812B GRB NeoPixels
OLED显示屏：SSD1306 I2C 128x64
开关：2路SPDT开关用于硬件控制
项目结构

plainText
OpenFIRE-Firmware_cn/
├── OpenFIREmain/              # 主固件目录
│   ├── OpenFIREmain.ino       # 主程序入口
│   ├── OpenFIREmain.h         # 主头文件
│   ├── OpenFIREcommon.*       # 通用功能模块
│   ├── OpenFIREprefs.*        # 配置存储管理
│   ├── OpenFIREserial.*       # 串口通信
│   ├── OpenFIREFeedback.*     # 力反馈控制
│   ├── OpenFIREdisplay.*      # OLED显示
│   ├── OpenFIRElights.*       # LED控制
│   ├── boards/                # 板级支持包
│   └── README.md              # 详细使用说明
├── libraries/                 # 第三方库
├── .github/workflows/         # GitHub Actions构建
├── platformio.ini            # PlatformIO配置
├── README.md                 # 英文项目说明
└── README_CN.MD              # 本中文文档
核心模块详解
1. OpenFIREmain.ino - 主程序
初始化：系统启动、外设初始化、配置文件加载
主循环：摄像头数据读取、位置计算、USB报告发送
模式管理：运行模式切换、校准模式、暂停菜单
2. OpenFIREcommon.h/.cpp - 通用功能
位置计算：IR数据处理和坐标转换
模式切换：游戏模式、校准模式、测试模式
设备控制：LED颜色设置、显示更新
3. OpenFIREprefs.h/.cpp - 配置管理
配置文件：4个独立校准配置文件
存储管理：LittleFS文件系统、EEPROM存储
预设管理：出厂默认设置和用户自定义
4. OpenFIREserial.h/.cpp - 串口通信
命令解析：支持多种串口命令格式
调试输出：实时调试信息和状态报告
MAME Hooker：串口反馈力支持
5. OpenFIREFeedback.h/.cpp - 力反馈
电磁阀控制：精确时序控制、脉冲模式
震动马达：强度调节、自定义脉冲
RGB LED：实时颜色变化、动画效果
6. OpenFIREdisplay.h/.cpp - OLED显示
菜单系统：暂停菜单、配置菜单
游戏反馈：生命值、弹药计数
校准辅助：实时校准界面
安装配置
快速安装
下载固件：从GitHub Releases下载对应板型的.UF2文件
烧录固件：按住BOOTSEL键连接电脑，拖入.UF2文件
首次校准：首次启动时扣动扳机开始校准
高级配置：使用OpenFIRE桌面应用进行详细配置
开发环境搭建

bash
# PlatformIO方式
pio run --target upload

# Arduino CLI方式
arduino-cli compile --fqbn rp2040:rp2040:rpipico
arduino-cli upload --fqbn rp2040:rp2040:rpipico --port COMx
使用指南
基本操作
校准：按住特定按键组合进入校准模式
暂停菜单：游戏中按暂停组合键进入设置菜单
模式切换：通过桌面应用或串口命令切换
按键映射（默认）
扳机：鼠标左键/游戏手柄R2
A键：鼠标右键/游戏手柄R1
B键：鼠标中键/游戏手柄L1
Start：游戏手柄Start
Select：游戏手柄Select
配置文件结构
每个配置文件包含：

4个方向的偏移校准
IR灵敏度设置
红外布局类型
显示比例设置
LED颜色设置
自定义名称
技术规格
性能参数
刷新率：209Hz（4.8ms间隔）
分辨率：1024×768（IR摄像头）
延迟：<5ms系统延迟
精度：±2像素精度
兼容性
操作系统：Windows、Linux、macOS
模拟器：MAME、Dolphin、PCSX2等
游戏：支持绝对定位鼠标的所有游戏
故障排除
常见问题
USB连接问题：检查线缆质量，使用24AWG以上线规
校准失败：确认红外LED位置和亮度
力反馈失效：检查驱动板连接和电源
OLED不显示：确认I2C地址和连接
调试工具
串口监视器：115200波特率查看调试信息
测试模式：实时查看IR摄像头数据
桌面应用：可视化配置和测试
社区资源
GitHub仓库：https://github.com/TeamOpenFIRE/OpenFIRE-Firmware
桌面应用：https://github.com/TeamOpenFIRE/OpenFIRE-App
硬件指南：BOARDS.md 详细板级说明
编译文档：COMPILING.md 开发环境搭建
开源协议
本项目基于GNU Lesser General Public License v3.0开源协议发布，欢迎社区贡献和改进。

致谢
Sam Ballantyne：原始SAMCO项目作者
Mike Lynch：IR-GUN4ALL项目贡献者
That One Seong：OpenFIRE项目主要开发者
社区贡献者：所有参与测试和改进的社区成员
OpenFIRE - 为光枪游戏社区而生，永远免费开源！

=============================
10. 主程序入口模块 (OpenFIREmain.ino)
功能定位：系统主入口，负责初始化、模式管理和主循环 核心职责：

硬件初始化（I2C、USB、PWM定时器）
文件系统和配置加载
双核处理器管理（RP2040）
运行模式切换（运行/校准/暂停/处理模式）
关键特性：

双核架构：Core 0处理IR定位和主逻辑，Core 1处理按钮和串口
中断驱动：使用PWM中断实现300Hz的IR定位更新
动态配置：支持运行时切换配置文件
多模式支持：运行、校准、暂停、处理四种模式
11. 主程序头文件 (OpenFIREmain.h)
功能定位：主程序架构定义和全局声明 核心组件：

TinyUSB设备接口定义
全局变量声明（配置文件选择、暂停模式状态）
RP2040专用中断处理声明
轮询率定义（1ms）
12. 显示实现模块 (OpenFIREdisplay.cpp)
功能定位：OLED显示屏完整功能实现 核心功能：

多I2C接口支持：自动检测I2C0/I2C1
动态屏幕管理：正常、校准、暂停、MAMEHOOKER等多种显示模式
图标系统：包含连接状态、电池、手柄等图标
实时信息更新：弹药数、生命值、温度显示
配置文件选择器：图形化配置文件切换界面
技术特性：

SSD1306 128x64 OLED支持
双缓冲绘制
动态内容刷新
低功耗空闲模式
13. LED控制实现模块 (OpenFIRElights.cpp)
功能定位：RGB LED完整控制实现 支持硬件：

DotStar LED：APA102协议支持
NeoPixel LED：WS2812协议支持
板载LED：RP2040/Pico W板载LED
自定义LED灯带：可配置数量的外部NeoPixel
核心功能：

多LED同步控制
32位打包颜色格式
静态LED配置（最多3个固定颜色）
模式关联颜色（根据运行模式自动切换）
14. 颜色定义模块 (OpenFIREcolors.h)
功能定位：系统颜色常量定义 颜色系统：

Wiki标准颜色定义（橙色、紫色、绿色等）
模式关联颜色（IR可见、校准模式等）
24位RGB格式支持
15. 系统架构总结
整体架构模式

plainText
┌─────────────────────────────────────────┐
│           主程序架构 (OpenFIREmain.ino)    │
├─────────────────────────────────────────┤
│ 初始化层 → 配置加载 → 硬件初始化 → 模式选择 │
│ 主循环层 → 模式管理 → 事件处理 → 状态更新   │
│ 中断层   → IR定时器 → 双核通信 → 实时响应   │
└─────────────────────────────────────────┘
模块协作关系
初始化流程：

OpenFIREmain.ino → OpenFIREprefs.cpp（配置加载）
OpenFIREmain.ino → OpenFIREcommon.cpp（硬件初始化）
OpenFIREmain.ino → OpenFIREdisplay.cpp（显示初始化）
运行时交互：

主循环 ←→ OpenFIREFeedback.cpp（力反馈控制）
主循环 ←→ OpenFIREserial.cpp（串口通信）
主循环 ←→ OpenFIREdisplay.cpp（显示更新）
中断驱动：

PWM中断 → IR定位更新
Core 1 → 按钮处理（并发执行）
性能优化特性
双核并行：充分利用RP2040双核架构
中断驱动：避免轮询开销，提高响应速度
内存管理：动态对象创建/销毁，避免内存泄漏
低功耗：空闲模式自动降频
扩展性设计
模块化架构：各功能模块独立，易于扩展
配置驱动：功能开关通过配置文件控制
硬件抽象：板级支持包屏蔽硬件差异
协议兼容：支持多种通信协议（MAMEHOOKER、自定义串口）
16. 项目完整架构图

plainText
┌─────────────────────────────────────────────────────────┐
│                    OpenFIRE-Firmware_cn                 │
├─────────────────────────────────────────────────────────┤
│ 应用层：主程序 (OpenFIREmain.ino)                        │
│ 功能层：显示、力反馈、LED、串口、配置管理                 │
│ 抽象层：通用功能、板级支持、常量定义                     │
│ 硬件层：RP2040/ESP32、IR摄像头、OLED、LED、力反馈设备      │
└─────────────────────────────────────────────────────────┘
至此，我已经完成了OpenFIRE-Firmware_cn项目的全面模块分析，涵盖了从硬件抽象到应用层的完整架构。项目展现了优秀的嵌入式系统设计，具有高度的可配置性、扩展性和硬件兼容性。
===============================
1. 主程序入口 (OpenFIREmain.ino)
功能定位: 系统初始化和主循环控制 核心职责:

硬件初始化: 设置I2C超时、板级特定引脚配置
存储系统初始化: 加载预设配置、配置文件完整性检查
USB设备标识: 动态设置USB制造商和产品描述符
错误处理: 存储系统不可用的优雅降级
关键初始化流程:


cpp
Apply
1. Wire.setTimeout(100) // I2C超时保护
2. OF_Prefs::LoadPresets() // 加载硬件预设
3. OF_Prefs::InitFS() // 初始化文件系统
4. OF_Prefs::LoadProfiles() // 加载用户配置
5. 配置完整性验证和修复
6. TinyUSB设备描述符设置
2. 主头文件 (OpenFIREmain.h)
功能定位: 全局定义和硬件抽象 核心组件:

硬件兼容性层: 支持RP2040/ESP32-S3等多平台
USB协议栈: TinyUSB集成
IR摄像头驱动: DFRobotIRPositionEx库封装
全局状态管理: 配置文件选择器、暂停菜单状态
3. 通用功能模块 (OpenFIREcommon.*)
功能定位: 核心运行时功能封装 类结构: FW_Common

主要方法:

FeedbackSet(): 力反馈设备初始化
PinsReset(): 引脚状态重置
CameraSet(): IR摄像头配置
SetMode(): 枪模式切换
SetRunMode(): 运行模式设置
ExecCalMode(): 校准模式执行
GetPosition(): 位置数据获取
UpdateLastSeen(): 最后可见时间更新
4. 配置存储管理 (OpenFIREprefs.*)
功能定位: 持久化配置管理 类结构: OF_Prefs

核心数据结构:


cpp
Apply
// 配置文件结构
struct ProfileData_t {
    int topOffset, bottomOffset, leftOffset, rightOffset;  // 透视校正偏移
    float TLled, TRled, adjX, adjY;                        // LED相对位置
    int irSens;                                            // IR灵敏度
    int runMode;                                           // 运行模式
    int irLayout;                                          // IR布局类型
    int aspectRatio;                                       // 宽高比
    uint color;                                            // LED颜色
    char name[16];                                         // 配置名称
};
配置管理功能:

4个独立配置文件: 支持不同游戏场景
系统开关: 12种功能开关状态
引脚映射: 完整的输入输出引脚配置
系统变量: 力反馈强度、时序参数等
5. 串口通信 (OpenFIREserial.*)
功能定位: 多协议串口通信支持 类结构: OF_Serial

通信模式:

桌面应用对接: 完整配置读写支持
MAMEHooker协议: 街机模拟器集成
调试输出: 实时状态监控
数据协议:

批量数据传输: SerialBatchSend()/SerialBatchRecv()
状态报告: PrintResults()
调试信息: PrintDebugSerial()
MAMEHooker集成:

力反馈事件队列管理
LED颜色控制
生命值/弹药数显示
暂停模式状态同步
6. 力反馈控制 (OpenFIREFeedback.*)
功能定位: 多模态力反馈系统 类结构: OF_FFB

反馈类型:

电磁铁: 真实枪械后坐力模拟
振动马达: 力反馈振动
温度保护: 过热自动降功率
连发模式: 自动射击支持
安全机制:

温度监控: TMP36传感器实时监测
功率限制: 基于温度的动态调整
过热保护: 自动停用和恢复
7. OLED显示 (OpenFIREdisplay.*)
功能定位: 实时状态显示界面 类结构: ExtDisplay

显示模式:

正常模式: 实时位置、生命值、弹药数
暂停菜单: 配置切换、校准入口
校准模式: IR点可视化、参数调整
测试模式: 硬件诊断、信号强度
界面元素:

顶部状态栏: 当前配置名称
IR点可视化: 4点位置实时显示
数值显示: 生命值、弹药数大字体
菜单导航: 分层菜单系统
8. LED控制 (OpenFIRElights.*)
功能定位: 智能RGB照明系统 类结构: OF_RGB

支持硬件:

NeoPixel (WS2812B)
DotStar (APA102)
4引脚共阳极RGB
板载LED
功能特性:

模式指示: 不同运行模式对应不同颜色
IR状态: 基于IR可见性的动态颜色
校准状态: 校准模式专用颜色
自定义颜色: 配置文件可配置
9. 板级支持包 (boards/OpenFIREshared.h)
功能定位: 硬件抽象和兼容性层 类结构: OF_Const

板级识别:

自动检测: 基于编译时宏的板型识别
预设配置: 各板型专用引脚预设
通用配置: 未知板型的通用支持
支持的板型:

Raspberry Pi Pico/Pico W/Pico 2/Pico 2W
Adafruit ItsyBitsy RP2040
Adafruit KB2040
Arduino Nano RP2040 Connect
Waveshare RP2040系列
ESP32-S3系列
输入映射系统:

按钮输入: 触发器、A/B/C、开始、选择、方向键
模拟输入: X/Y轴模拟摇杆
专用功能: 踏板、泵动、HOME键
硬件控制: 力反馈设备、LED、I2C设备
模块间协作关系

plainText
OpenFIREmain.ino (主程序)
    ├── OpenFIREcommon.* (核心运行时)
    ├── OpenFIREprefs.* (配置管理)
    ├── OpenFIREserial.* (通信协议)
    ├── OpenFIREFeedback.* (力反馈)
    ├── OpenFIREdisplay.* (显示界面)
    ├── OpenFIRElights.* (LED控制)
    └── boards/OpenFIREshared.h (硬件抽象)
扩展性和可维护性
模块化设计:

每个模块职责单一，接口清晰
硬件抽象层支持新平台快速适配
配置文件系统支持用户自定义
串口协议支持第三方集成
代码组织:

头文件与实现分离
命名空间隔离
条件编译支持不同硬件配置
详尽的API文档注释
=============================
10. 系统配置定义 (OpenFIREDefines.h)
功能定位: 编译时配置开关和构建选项 核心配置项:

调试选项:

PRINT_VERBOSE: 详细运行时调试输出
DEBUG_SERIAL: 串口调试模式（1或2级）
DUAL_CORE: RP2040双核处理支持
USB设备标识:

MANUFACTURER_NAME: "OpenFIRE"（固定）
DEVICE_NAME: "FIRECon"（可配置）
DEVICE_VID: 0xF143（OpenFIRE专用）
PLAYER_NUMBER: 玩家编号（1-4）
功能开关矩阵:

MAMEHOOKER: 街机模拟器MAMEHooker协议支持
USES_SWITCHES: 硬件开关支持
USES_RUMBLE: 振动马达支持
USES_SOLENOID: 电磁铁支持
USES_TEMP: TMP36温度传感器支持
USES_ANALOG: 模拟摇杆支持
FOURPIN_LED: 4引脚RGB LED支持
CUSTOM_NEOPIXEL: 外部NeoPixel支持
USES_DISPLAY: SSD1306 OLED显示支持
11. 系统常量定义 (OpenFIREconstant.h)
功能定位: 运行时枚举和常量定义 核心枚举类型:

枪模式枚举:


cpp
Apply
enum GunMode_e {
    GunMode_Init = -1,      // 初始化模式
    GunMode_Run = 0,        // 正常运行模式
    GunMode_Calibration,    // 校准模式
    GunMode_Verification,   // 验证模式
    GunMode_Pause,          // 暂停模式
    GunMode_Docked          // 桌面应用对接模式
};
运行模式枚举:


cpp
Apply
enum RunMode_e {
    RunMode_Normal = 0,     // 正常模式，无平均
    RunMode_Average = 1,    // 2帧移动平均
    RunMode_Average2 = 2,   // 3帧加权平均
    RunMode_Processing = 3,  // Processing测试模式
    RunMode_Count
};
按钮索引和掩码:

14个标准按钮：触发器、A/B、装弹、开始、选择、方向键等
位掩码系统：支持组合键检测
特殊组合：ESC键组合（装弹+开始）
校准阶段枚举:


cpp
Apply
enum CaliStage_e {
    Cali_Init = 0,    // 初始化
    Cali_Top,         // 顶部校准
    Cali_Bottom,      // 底部校准
    Cali_Left,        // 左侧校准
    Cali_Right,       // 右侧校准
    Cali_Center,      // 中心校准
    Cali_Verify       // 验证校准
};
实现文件深度分析
12. 通用功能实现 (OpenFIREcommon.cpp)
类: FW_Common - 核心运行时管理

FeedbackSet() - 硬件初始化:

力反馈设备引脚模式设置
硬件开关上拉电阻配置
模拟输入分辨率设置（12位）
LED引脚验证和初始化
I2C外设设备检测和初始化
PinsReset() - 引脚重置:

将所有映射引脚恢复为默认输入模式
防止配置切换时的引脚冲突
为同步操作做准备
CameraSet() - 摄像头配置:

IR摄像头位置对象初始化
支持运行时重新配置摄像头引脚
动态适应不同硬件布局
SetMode() - 模式切换:

枪模式状态机管理
模式切换时的清理操作
显示界面同步更新
GetPosition() - 位置获取:

IR摄像头数据读取
坐标转换和边界检查
平滑算法应用
最终坐标计算
13. 配置管理实现 (OpenFIREprefs.cpp)
类: OF_Prefs - 持久化配置管理

文件系统操作:

InitFS(): LittleFS文件系统初始化
LoadProfiles(): 从/profiles.conf加载4个配置文件
SaveProfiles(): 保存配置到持久存储
Load(): 完整配置加载序列
配置数据结构:


cpp
Apply
// 配置文件格式（二进制）
[字符串类型][配置数据]
支持的数据类型：
- ProfileData_t结构体（透视校正参数）
- LED颜色配置
- IR灵敏度设置
- 运行模式选择
- 配置文件名称（16字符）
预设系统:

LoadPresets(): 加载板级硬件预设
支持多板型自动识别
动态引脚映射配置
14. 串口通信实现 (OpenFIREserial.cpp)
类: OF_Serial - 多协议串口通信

MAMEHooker协议支持: 命令解析器:

'S': 启动序列模式
'M': 输入模式切换（鼠标/手柄/MiSTer优化）
'R/G/B': LED颜色控制
'H': 生命值显示
'A': 弹药数显示
'Q': 退出序列模式
批量数据传输:

SerialBatchSend(): 向主机发送批量数据
SerialBatchRecv(): 从主机接收配置数据
支持JSON格式数据交换
桌面应用对接:

SerialProcessingDocked(): 完整配置管理
实时参数调整
配置文件导入导出
15. 力反馈实现 (OpenFIREFeedback.cpp)
类: OF_FFB - 多模态力反馈系统

电磁铁控制: FFBOnScreen() - 屏幕内射击:

首次射击特殊处理
连发模式状态机
自动射击时序控制
温度保护机制
FFBOffScreen() - 屏幕外射击:

振动反馈替代方案
连发模式继续执行
电磁铁安全关闭
FFBRelease() - 触发器释放:

电磁铁立即关闭
连发模式重置
振动马达停止
温度管理系统:

TemperatureUpdate(): 250ms间隔温度读取
4点移动平均滤波
过热自动降功率
三级温度状态：安全/警告/危险
振动马达控制:

RumbleActivation(): 振动时序管理
持续时间控制
强度动态调整
触发器释放检测
连发模式:

BurstFire(): 三连发射击
可配置射击间隔
温度感知功率调整
触发器释放中断
模块间协作架构
数据流架构

plainText
IR摄像头 → OpenFIREcommon → 坐标处理 → USB输出
                     ↓
              力反馈触发 → OpenFIREFeedback → 电磁铁/振动马达
                     ↓
              显示更新 → OpenFIREdisplay → OLED界面
                     ↓
              LED控制 → OpenFIRElights → RGB状态指示
                     ↓
              配置管理 → OpenFIREprefs → 持久化存储
                     ↓
              串口通信 → OpenFIREserial → 桌面应用/MAMEHooker
事件驱动模型
触发器事件:

物理触发器检测
IR可见性检查
屏幕内外判断
力反馈激活
USB事件发送
显示界面更新
配置变更事件:

串口命令接收
配置文件解析
运行时参数更新
硬件状态同步
显示界面刷新
错误处理和恢复机制
硬件故障检测:

IR摄像头通信超时
I2C设备无响应
温度传感器异常
存储系统损坏
自动恢复策略:

摄像头重新初始化
I2C总线重置
默认配置回退
安全模式运行
性能优化特性
双核处理 (RP2040专用):

Core 0: USB输入处理、串口通信
Core 1: I2C外设管理、主逻辑
内存管理:

静态内存分配优先
配置文件懒加载
显示缓冲区复用
字符串常量池化
实时性能:

1ms USB轮询间隔
250ms温度监控
无阻塞I2C操作
中断驱动的力反馈
=============================
## OpenFIREserial.cpp 功能分析

`OpenFIREserial.cpp` 是 OpenFIRE 固件中负责串口通信的核心模块，主要功能包括：

### 1. 串口通信管理
- **串口数据处理**：通过 `Serial.read()` 和 `Serial.write()` 实现与外部设备（如主机或调试工具）的数据收发。
- **命令解析**：支持多种命令格式，例如模式切换、设置保存等。
- **调试信息输出**：使用 `Serial.println` 输出调试信息，例如模式切换提示或错误日志。

### 2. 状态标志操作
- **状态管理**：通过 `FW_Common::stateFlags` 管理设备状态标志，如 `StateFlag_SavePreferencesEn`。
- **串口触发状态变更**：支持通过串口命令触发状态变更。

### 3. 模式切换功能
- **输入模式切换**：支持鼠标/键盘模式、游戏手柄模式等。
- **MiSTer 优化模式**：通过 `FW_Common::buttons.analogOutput` 和 `FW_Common::OLED.mister` 控制输出模式。

### 4. 硬件控制
- **LED 控制**：支持 LED 静态点亮、脉冲效果和颜色切换。
- **震动反馈**：支持震动马达的开关和脉冲控制。
- **电磁阀控制**：支持电磁阀的开关和脉冲控制。

### 5. 数据持久化
- **用户偏好设置**：标记需要保存的用户偏好设置，并通过串口命令触发保存操作。
- **配置文件管理**：支持加载和保存配置文件。

### 6. 多线程支持
- **双核优化**：在双核系统中优化串口数据处理效率。

### 7. 调试与日志
- **调试信息输出**：通过 `DEBUG_SERIAL` 宏输出调试信息，如帧率、IR 位置等。
- **错误处理**：输出错误日志，如串口命令无效或硬件故障。

## 详细功能说明

### 串口命令解析
- **命令格式**：支持多种命令格式，如 `S`（开始信号）、`M`（模式设置）、`F`（力反馈控制）等。
- **参数解析**：通过 `Serial.read()` 读取命令参数，并根据参数执行相应操作。

### 硬件控制逻辑
- **LED 控制**：支持 RGB LED 的静态和动态效果控制。
- **震动反馈**：支持震动马达的开关和脉冲控制，支持自定义脉冲间隔。
- **电磁阀控制**：支持电磁阀的开关和脉冲控制，支持自定义脉冲间隔。

### 数据持久化
- **配置文件保存**：通过 `FW_Common::SavePreferences()` 保存用户偏好设置。
- **配置文件加载**：通过 `OF_Prefs::Load()` 加载配置文件。

### 调试与日志
- **调试信息输出**：通过 `DEBUG_SERIAL` 宏输出调试信息，如帧率、IR 位置等。
- **错误处理**：输出错误日志，如串口命令无效或硬件故障。

## 使用说明
- 通过串口发送特定命令可以触发上述功能。
- 详细命令列表请参考项目 Wiki 或代码注释。