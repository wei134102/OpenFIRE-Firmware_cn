/*!
 * @file OpenFIREChinese.h
 * @brief Chinese character display support for OpenFIRE
 *
 * @copyright That One Seong, 2024
 * @copyright GNU Lesser General Public License
 */

#ifndef _OPENFIRECHINESE_H_
#define _OPENFIRECHINESE_H_

#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class ExtDisplay;

class OpenFIREChinese {
public:
    /// @brief Initialize Chinese font support
    /// @param display Pointer to Adafruit_SSD1306 object
    /// @return true if initialization is successful
    static bool Initialize(Adafruit_SSD1306* display);

    /// @brief Find a character in the font data
    /// @param cw GB2312 encoded character (2 bytes)
    /// @return Pointer to character data, or nullptr if not found
    static const uint8_t* FindChar(const uint8_t cw[2]);

    /// @brief Display a single Chinese character
    /// @param cw GB2312 encoded character (2 bytes)
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param size Font size (16 for HZK16)
    /// @return true if successful
    static bool DrawChar(const uint8_t cw[2], int16_t x, int16_t y, uint8_t size = 16);

    /// @brief Display a Chinese string
    /// @param str GB2312 encoded string
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param size Font size (16 for HZK16)
    /// @return true if successful
    static bool DrawString(const uint8_t* str, int16_t x, int16_t y, uint8_t size = 16);

    /// @brief Convert UTF-8 string to GB2312
    /// @param utf8Str UTF-8 encoded string
    /// @param gb2312Str Buffer to store GB2312 result
    /// @param maxLen Maximum length of gb2312Str
    /// @return Length of the converted string
    static uint16_t UTF8ToGB2312(const char* utf8Str, uint8_t* gb2312Str, uint16_t maxLen);

    /// @brief Clean up resources used by Chinese font support
    static void Cleanup();

private:
    static Adafruit_SSD1306* display; ///< Pointer to display object
    static bool fontLoaded; ///< Whether font is loaded
    static const uint8_t* fontData; ///< Font data buffer
    static uint32_t fontSize; ///< Size of font data

    /// @brief Get offset of a character in HZK font (deprecated)
    /// @param cw GB2312 encoded character
    /// @param size Font size
    /// @return Offset in font file
    /// @deprecated Use FindChar instead
    static uint32_t GetCharOffset(const uint8_t cw[2], uint8_t size);
};

#endif // _OPENFIRECHINESE_H_