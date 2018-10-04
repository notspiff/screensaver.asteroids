////////////////////////////////////////////////////////////////////////////
//
// Author:
//   Joakim Eriksson
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#ifdef WIN32
#include <d3d11.h>
#else
#include "shaders/GUIShader.h"
#endif
/***************************** D E F I N E S *******************************/

#define NUMLINES    100

/****************************** M A C R O S ********************************/
/***************************** C L A S S E S *******************************/

////////////////////////////////////////////////////////////////////////////
//
typedef struct TRenderVertex
{
  f32 x, y, z;
  float col[4];
} TRenderVertex;


////////////////////////////////////////////////////////////////////////////
//
class CConfig
{
public:
  int m_NumColumns;    // Number of character columns
  int m_NumRows;      // Number of character rows

  CRGBA m_CharCol;
  f32 m_FadeSpeedMin;    // How quickly the characters fade out
  f32 m_FadeSpeedMax;
  f32 m_CharDelayMin;    // How long we wait before we add a new char
  f32 m_CharDelayMax;

  CVector2 m_CharSizeTex;    // Size of the characters in the texture
  int m_NumChars;      // Number of characters in the texture

  void SetDefaults();
  void LoadSettings();
};


////////////////////////////////////////////////////////////////////////////
// 
class CRenderD3D
{
public:
  void Init(void* pContext);
  bool RestoreDevice();
  void InvalidateDevice();
  bool Begin();
  bool Draw();
  void DrawLine(const CVector2& pos1, const CVector2& pos2, const CRGBA& col1, const CRGBA& col2);

  s32 m_NumLines;
  int m_Width;
  int m_Height;

  TRenderVertex*       m_Verts;
#ifndef WIN32
  TRenderVertex*       m_VertBuf;
  CGUIShader* m_shader;
#else
  ID3D11DeviceContext* m_pContext;
  ID3D11Buffer*        m_pVBuffer;
  ID3D11PixelShader*   m_pPShader;
#endif
};

/***************************** G L O B A L S *******************************/

extern  CConfig     gConfig;
extern  CRenderD3D  gRender;

/***************************** I N L I N E S *******************************/
