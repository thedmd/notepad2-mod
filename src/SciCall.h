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


//=============================================================================
//
//  SciCall()
//
//
LRESULT WINAPI Scintilla_DirectFunction(HANDLE, UINT, WPARAM, LPARAM);
#define SciCall(m, w, l) g_hScintilla_DirectFunction(g_hScintilla, m, w, l)


//=============================================================================
//
//  DeclareSciCall[RV][0-2] Macros
//
//  R: With an explicit return type
//  V: No return type defined ("void"); defaults to SendMessage's LRESULT
//  0-2: Number of parameters to define
//
//
//#define SciCallAny(fn, ...)  g_Scintilla.fn(__VA_ARGS__)

//#define DeclareSciCallR0(fn, msg, ret)                             inline template <typename... Args> auto SciCall_##fn(Args&&... args) { return g_Scintilla.fn(std::forward<Args>(args)...); }
//#define DeclareSciCallR1(fn, msg, ret, type1, var1)                inline template <typename... Args> auto SciCall_##fn(Args&&... args) { return g_Scintilla.fn(std::forward<Args>(args)...); }
//#define DeclareSciCallR2(fn, msg, ret, type1, var1, type2, var2)   inline template <typename... Args> auto SciCall_##fn(Args&&... args) { return g_Scintilla.fn(std::forward<Args>(args)...); }
//#define DeclareSciCallV0(fn, msg)                                  inline template <typename... Args> auto SciCall_##fn(Args&&... args) { return g_Scintilla.fn(std::forward<Args>(args)...); }
//#define DeclareSciCallV1(fn, msg, type1, var1)                     inline template <typename... Args> auto SciCall_##fn(Args&&... args) { return g_Scintilla.fn(std::forward<Args>(args)...); }
//#define DeclareSciCallV2(fn, msg, type1, var1, type2, var2)        inline template <typename... Args> auto SciCall_##fn(Args&&... args) { return g_Scintilla.fn(std::forward<Args>(args)...); }

#define DeclareSciCallR0(fn, msg, ret)                             \
__forceinline ret SciCall_##fn() {                                 \
  return((ret)SciCall(SCI_##msg, 0, 0));                           \
}
#define DeclareSciCallR1(fn, msg, ret, type1, var1)                \
__forceinline ret SciCall_##fn(type1 var1) {                       \
  return((ret)SciCall(SCI_##msg, (WPARAM)(var1), 0));              \
}
#define DeclareSciCallR2(fn, msg, ret, type1, var1, type2, var2)   \
__forceinline ret SciCall_##fn(type1 var1, type2 var2) {           \
  return((ret)SciCall(SCI_##msg, (WPARAM)(var1), (LPARAM)(var2))); \
}
#define DeclareSciCallV0(fn, msg)                                  \
__forceinline LRESULT SciCall_##fn() {                             \
  return(SciCall(SCI_##msg, 0, 0));                                \
}
#define DeclareSciCallV1(fn, msg, type1, var1)                     \
__forceinline LRESULT SciCall_##fn(type1 var1) {                   \
  return(SciCall(SCI_##msg, (WPARAM)(var1), 0));                   \
}
#define DeclareSciCallV2(fn, msg, type1, var1, type2, var2)        \
__forceinline LRESULT SciCall_##fn(type1 var1, type2 var2) {       \
  return(SciCall(SCI_##msg, (WPARAM)(var1), (LPARAM)(var2)));      \
}


//=============================================================================
//
//  Selection and information
//
//

//DeclareSciCallR0(GetLineCount, GETLINECOUNT, Line);
//DeclareSciCallV2(SetSel, SETSEL, Position, anchorPos, Position, currentPos);
//DeclareSciCallV1(GotoPos, GOTOPOS, Position, position);
//DeclareSciCallV1(GotoLine, GOTOLINE, Line, line);
//DeclareSciCallR0(GetCurrentPos, GETCURRENTPOS, Position);
//DeclareSciCallR1(LineFromPosition, LINEFROMPOSITION, Line, Position, position);


//=============================================================================
//
//  Scrolling and automatic scrolling
//
//
//DeclareSciCallV0(ScrollCaret, SCROLLCARET);
//DeclareSciCallV2(SetXCaretPolicy, SETXCARETPOLICY, int, caretPolicy, int, caretSlop);
//DeclareSciCallV2(SetYCaretPolicy, SETYCARETPOLICY, int, caretPolicy, int, caretSlop);


//=============================================================================
//
//  Style definition
//
//
//DeclareSciCallR1(StyleGetFore, STYLEGETFORE, COLORREF, int, styleNumber);
//DeclareSciCallR1(StyleGetBack, STYLEGETBACK, COLORREF, int, styleNumber);


//=============================================================================
//
//  Margins
//
//
//DeclareSciCallV2(SetMarginType, SETMARGINTYPEN, int, margin, int, type);
//DeclareSciCallV2(SetMarginWidth, SETMARGINWIDTHN, int, margin, int, pixelWidth);
//DeclareSciCallV2(SetMarginMask, SETMARGINMASKN, int, margin, int, mask);
//DeclareSciCallV2(SetMarginSensitive, SETMARGINSENSITIVEN, int, margin, BOOL, sensitive);
//DeclareSciCallV2(SetFoldMarginColour, SETFOLDMARGINCOLOUR, BOOL, useSetting, COLORREF, colour);
//DeclareSciCallV2(SetFoldMarginHiColour, SETFOLDMARGINHICOLOUR, BOOL, useSetting, COLORREF, colour);


//=============================================================================
//
//  Markers
//
//
//DeclareSciCallV2(MarkerDefine, MARKERDEFINE, int, markerNumber, int, markerSymbols);
//DeclareSciCallV2(MarkerSetFore, MARKERSETFORE, int, markerNumber, COLORREF, colour);
//DeclareSciCallV2(MarkerSetBack, MARKERSETBACK, int, markerNumber, COLORREF, colour);


//=============================================================================
//
//  Folding
//
//
//DeclareSciCallR1(GetLineVisible, GETLINEVISIBLE, BOOL, Line, line);
//DeclareSciCallR1(GetFoldLevel, GETFOLDLEVEL, int, Line, line);
//DeclareSciCallV1(SetFoldFlags, SETFOLDFLAGS, int, flags);
//DeclareSciCallR1(GetFoldParent, GETFOLDPARENT, int, Line, line);
//DeclareSciCallR1(GetFoldExpanded, GETFOLDEXPANDED, int, Line, line);
//DeclareSciCallV1(ToggleFold, TOGGLEFOLD, Line, line);
//DeclareSciCallV1(EnsureVisible, ENSUREVISIBLE, Line, line);


//=============================================================================
//
//  Lexer
//
//
//DeclareSciCallV2(SetProperty, SETPROPERTY, const char *, key, const char *, value);
