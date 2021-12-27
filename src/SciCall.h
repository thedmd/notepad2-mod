/******************************************************************************
*
*
* Notepad2
*
* SciCall.h
*   Inline wrappers for Scintilla API calls, arranged in the order and grouping
*   in which they appear in the Scintilla documentation.
*
* The use of these inline wrapper functions with declared types will ensure
* that we get the benefit of the compiler's type checking.
*
*
******************************************************************************/
#include <cstdint>
#include <string>
#include <string_view>
#include <Scintilla.h>
#include <ScintillaTypes.h>
#include <ScintillaMessages.h>
#include <ScintillaCall.h>



//=============================================================================
//
//  g_hScintilla
//
//
extern Scintilla::ScintillaCall g_Scintilla;
