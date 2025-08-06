/*!
 * @file OpenFIREChinese.cpp
 * @brief Chinese character display implementation for OpenFIRE
 *
 * @copyright That One Seong, 2024
 * @copyright GNU Lesser General Public License
 */

#include <Arduino.h>
#include "HZK16.h"

#include "OpenFIREChinese.h"
#include "OpenFIREdisplay.h"

// Static member initialization
Adafruit_SSD1306* OpenFIREChinese::display = nullptr;
bool OpenFIREChinese::fontLoaded = false;
const uint8_t* OpenFIREChinese::fontData = nullptr;
uint32_t OpenFIREChinese::fontSize = 0;

bool OpenFIREChinese::Initialize(Adafruit_SSD1306* displayObj) {
    if (displayObj == nullptr) {
        return false;
    }

    display = displayObj;
    fontLoaded = true;  // 字体已嵌入到代码中
    fontData = HZK16_DATA;
    fontSize = HZK16_DATA_SIZE;

    return true;
}

// 从嵌入式字库中查找字符
const uint8_t* OpenFIREChinese::FindChar(const uint8_t cw[2]) {
    if (fontData == nullptr) {
        return nullptr;
    }

    // 遍历字库查找匹配的字符
    for (uint32_t i = 0; i < fontSize; i += 34) {  // 每个字符占34字节: 2字节编码 + 32字节数据
        if (fontData[i] == cw[0] && fontData[i+1] == cw[1]) {
            return &fontData[i+2];  // 返回字模数据起始位置
        }
    }

    return nullptr;  // 未找到字符
}

// 此函数不再需要，被FindChar替代
/*
uint32_t OpenFIREChinese::GetCharOffset(const uint8_t cw[2], uint8_t size) {
    // HZK font organization: 94 areas, 94 characters per area
    // Each character is size x size pixels, stored as 2 bytes per row
    uint8_t area = cw[0] - 0xA0 - 1;
    uint8_t pos = cw[1] - 0xA0 - 1;
    uint32_t offset = (area * 94 + pos) * size * 2;
    return offset;
}
*/

bool OpenFIREChinese::DrawChar(const uint8_t cw[2], int16_t x, int16_t y, uint8_t size) {
    if (!fontLoaded || display == nullptr) {
        return false;
    }

    // Check if character is within GB2312 range
    if (cw[0] < 0xA1 || cw[0] > 0xF7 || cw[1] < 0xA1 || cw[1] > 0xFE) {
        return false;
    }

    // 查找字符在字库中的位置
    const uint8_t* charData = FindChar(cw);
    if (charData == nullptr) {
        return false;
    }

    // 绘制字符（假设size=16）
    for (int i = 0; i < 16; i++) {
        uint8_t row1 = charData[i * 2];
        uint8_t row2 = charData[i * 2 + 1];

        for (int j = 0; j < 8; j++) {
            if (row1 & (0x80 >> j)) {
                display->drawPixel(x + j, y + i, WHITE);
            }
        }

        for (int j = 0; j < 8; j++) {
            if (row2 & (0x80 >> j)) {
                display->drawPixel(x + j + 8, y + i, WHITE);
            }
        }
    }

    display->display();
    return true;
}

bool OpenFIREChinese::DrawString(const uint8_t* str, int16_t x, int16_t y, uint8_t size) {
    if (!fontLoaded || display == nullptr) {
        return false;
    }

    int16_t currentX = x;
    int16_t currentY = y;

    // Iterate through string (each character is 2 bytes)
    for (int i = 0; str[i] != 0 && str[i+1] != 0; i += 2) {
        uint8_t cw[2] = {str[i], str[i+1]};

        // Draw character
        if (!DrawChar(cw, currentX, currentY, size)) {
            return false;
        }

        // Move to next character
        currentX += size;

        // Check if we need to wrap to next line
        if (currentX + size > SCREEN_WIDTH) {
            currentX = x;
            currentY += size;

            // Check if we're off the bottom of the screen
            if (currentY + size > SCREEN_HEIGHT) {
                return false;
            }
        }
    }

    return true;
}

uint16_t OpenFIREChinese::UTF8ToGB2312(const char* utf8Str, uint8_t* gb2312Str, uint16_t maxLen) {
    // This is a simplified UTF-8 to GB2312 conversion
    // In a real implementation, you would use a proper conversion table
    // or library like iconv

    uint16_t gb2312Len = 0;
    uint8_t* gb2312Ptr = gb2312Str;

    while (*utf8Str && gb2312Len < maxLen - 1) {
        // Check if it's a ASCII character
        if ((*utf8Str & 0x80) == 0) {
            *gb2312Ptr++ = *utf8Str++;
            *gb2312Ptr++ = 0;
            gb2312Len += 2;
        }
        // Check if it's a 3-byte UTF-8 character (most common for Chinese)
        else if ((*utf8Str & 0xE0) == 0xE0) {
            // This is a placeholder. In a real implementation,
            // you would convert the UTF-8 code to GB2312 using a lookup table.
            // For now, we'll just pass through the bytes.
            utf8Str += 3;  // Skip UTF-8 character
            *gb2312Ptr++ = 0xA1;  // Placeholder GB2312 character
            *gb2312Ptr++ = 0xA1;
            gb2312Len += 2;
        }
        // Other UTF-8 formats (2-byte, 4-byte) are not handled here
        else {
            utf8Str += 2;  // Skip 2-byte UTF-8 character
            *gb2312Ptr++ = 0xA1;  // Placeholder GB2312 character
            *gb2312Ptr++ = 0xA1;
            gb2312Len += 2;
        }
    }

    *gb2312Ptr = 0;  // Null terminate
    return gb2312Len;
}

// Cleanup function (optional)
void OpenFIREChinese::Cleanup() {
    if (fontData != nullptr) {
        delete[] fontData;
        fontData = nullptr;
    }
    fontLoaded = false;
    fontSize = 0;
    display = nullptr;
}