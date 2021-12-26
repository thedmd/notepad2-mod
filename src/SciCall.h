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

//typedef intptr_t Position;
//typedef intptr_t Line;


//=============================================================================
//
//  g_hScintilla
//
//
extern Scintilla::ScintillaCall g_Scintilla;

extern sptr_t       g_hScintilla;
extern SciFnDirect  g_hScintilla_DirectFunction;

__forceinline void InitScintillaHandle(HWND hwnd)
{
  g_Scintilla.SetFnPtr(
    (SciFnDirectStatus)SendMessage(hwnd, SCI_GETDIRECTSTATUSFUNCTION, 0, 0),
    (intptr_t)SendMessage(hwnd, SCI_GETDIRECTPOINTER, 0, 0)
  );

  g_hScintilla = (sptr_t)SendMessage(hwnd, SCI_GETDIRECTPOINTER, 0, 0);
  g_hScintilla_DirectFunction = (SciFnDirect)SendMessage(hwnd, SCI_GETDIRECTFUNCTION, 0, 0);
}
