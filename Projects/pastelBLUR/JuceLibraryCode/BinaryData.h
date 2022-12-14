/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   box_side_png;
    const int            box_side_pngSize = 2809;

    extern const char*   box_top_png;
    const int            box_top_pngSize = 2812;

    extern const char*   corner_png;
    const int            corner_pngSize = 137;

    extern const char*   knob_blue_noline_png;
    const int            knob_blue_noline_pngSize = 3028;

    extern const char*   knob_pink_noline_png;
    const int            knob_pink_noline_pngSize = 3025;

    extern const char*   Slider_bg_png;
    const int            Slider_bg_pngSize = 2849;

    extern const char*   slider_thumb_png;
    const int            slider_thumb_pngSize = 2827;

    extern const char*   Slider_track_png;
    const int            Slider_track_pngSize = 2848;

    extern const char*   OPTIMA_TTF;
    const int            OPTIMA_TTFSize = 40736;

    extern const char*   OPTIMA_BOLD_TTF;
    const int            OPTIMA_BOLD_TTFSize = 43124;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 10;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
