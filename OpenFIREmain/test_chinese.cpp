#include "OpenFIREdisplay.h"
#include "OpenFIREChinese.h"

/**
 * @brief 中文显示测试函数
 * @param display ExtDisplay对象指针
 */
void TestChineseDisplay(ExtDisplay* display) {
  if(display == nullptr) return;

  // 清除屏幕
  display->display->clearDisplay();

  // 测试中文显示
  display->PrintUTF8("中文菜单测试", 0, 0, 16);
  display->PrintUTF8("这是一个测试", 0, 20, 16);
  display->PrintUTF8("校准", 0, 40, 16);
  display->PrintUTF8("选择配置文件", 0, 60, 16);

  // 显示到屏幕
  display->display->display();

  // 延迟2秒
  delay(2000);
}