////////////////////////////////////////////////////////////////////////////
//
// Asteroids Screensaver for XBox Media Center
// Copyright (c) 2005 Joakim Eriksson <je@plane9.com>
//
// The TestXBS framework and program is made by Warren
//
////////////////////////////////////////////////////////////////////////////
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
////////////////////////////////////////////////////////////////////////////
//

#include <kodi/addon-instance/Screensaver.h>

#ifndef WIN32
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "shaders/GUIShader.h"
#else
#include <d3d11.h>
#endif
#include "main.h"
#include "Asteroids.h"
#include "timer.h"

#include <time.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

CRenderD3D gRender;

class CMyAddon
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceScreensaver
{
public:
  CMyAddon();

  virtual bool Start() override;
  virtual void Stop() override;
  virtual void Render() override;

private:
  CAsteroids* m_asteroids;
  CTimer* m_timer;
};

CMyAddon::CMyAddon()
  : m_asteroids(nullptr),
    m_timer(nullptr)
{
  gRender.Init(Device());
  gRender.m_Width = Width();
  gRender.m_Height = Height();
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us we should get ready to start rendering. This function
// is called once when the screensaver is activated by Kodi.
//
bool CMyAddon::Start()
{
  srand((u32)time(null));
  m_asteroids = new CAsteroids();
  if (!m_asteroids)
    return false;

  m_timer = new CTimer();
  m_timer->Init();
  if (!gRender.RestoreDevice() || !m_asteroids->RestoreDevice(&gRender))
  {
    Stop();
    return false;
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us to render a frame of our screensaver. This is called on
// each frame render in Kodi, you should render a single frame only - the DX
// device will already have been cleared.
//
void CMyAddon::Render()
{
  if (!m_asteroids)
    return;

  gRender.Begin();
  m_timer->Update();
  m_asteroids->Update(m_timer->GetDeltaTime());
  m_asteroids->Draw(&gRender);
  gRender.Draw();
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us to stop the screensaver we should free any memory and release
// any resources we have created.
//
void CMyAddon::Stop()
{
  if (!m_asteroids)
    return;

  gRender.InvalidateDevice();
  m_asteroids->InvalidateDevice(&gRender);
  SAFE_DELETE(m_asteroids);
  SAFE_DELETE(m_timer);
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
const BYTE PixelShader[] =
{
     68,  88,  66,  67,  18, 124,
    182,  35,  30, 142, 196, 211,
     95, 130,  91, 204,  99,  13,
    249,   8,   1,   0,   0,   0,
    124,   1,   0,   0,   4,   0,
      0,   0,  48,   0,   0,   0,
    124,   0,   0,   0, 188,   0,
      0,   0,  72,   1,   0,   0,
     65, 111, 110,  57,  68,   0,
      0,   0,  68,   0,   0,   0,
      0,   2, 255, 255,  32,   0,
      0,   0,  36,   0,   0,   0,
      0,   0,  36,   0,   0,   0,
     36,   0,   0,   0,  36,   0,
      0,   0,  36,   0,   0,   0,
     36,   0,   0,   2, 255, 255,
     31,   0,   0,   2,   0,   0,
      0, 128,   0,   0,  15, 176,
      1,   0,   0,   2,   0,   8,
     15, 128,   0,   0, 228, 176,
    255, 255,   0,   0,  83,  72,
     68,  82,  56,   0,   0,   0,
     64,   0,   0,   0,  14,   0,
      0,   0,  98,  16,   0,   3,
    242,  16,  16,   0,   1,   0,
      0,   0, 101,   0,   0,   3,
    242,  32,  16,   0,   0,   0,
      0,   0,  54,   0,   0,   5,
    242,  32,  16,   0,   0,   0,
      0,   0,  70,  30,  16,   0,
      1,   0,   0,   0,  62,   0,
      0,   1,  73,  83,  71,  78,
    132,   0,   0,   0,   4,   0,
      0,   0,   8,   0,   0,   0,
    104,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,
      3,   0,   0,   0,   0,   0,
      0,   0,  15,   0,   0,   0,
    116,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   1,   0,
      0,   0,  15,  15,   0,   0,
    122,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   2,   0,
      0,   0,   3,   0,   0,   0,
    122,   0,   0,   0,   1,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   2,   0,
      0,   0,  12,   0,   0,   0,
     83,  86,  95,  80,  79,  83,
     73,  84,  73,  79,  78,   0,
     67,  79,  76,  79,  82,   0,
     84,  69,  88,  67,  79,  79,
     82,  68,   0, 171,  79,  83,
     71,  78,  44,   0,   0,   0,
      1,   0,   0,   0,   8,   0,
      0,   0,  32,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   3,   0,   0,   0,
      0,   0,   0,   0,  15,   0,
      0,   0,  83,  86,  95,  84,
     65,  82,  71,  69,  84,   0,
    171, 171
};
#endif
////////////////////////////////////////////////////////////////////////////
//
void CRenderD3D::Init(void* pContext)
{
  m_NumLines = 0;
  m_Verts = null;
#ifdef WIN32
  m_pContext = reinterpret_cast<ID3D11DeviceContext*>(pContext);
  ID3D11Device* pDevice = nullptr;
  m_pContext->GetDevice(&pDevice);

  CD3D11_BUFFER_DESC vbDesc(sizeof(TRenderVertex) * (NUMLINES * 2 + 2 /*safe*/), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
  pDevice->CreateBuffer(&vbDesc, nullptr, &m_pVBuffer);
  pDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), nullptr, &m_pPShader);
  SAFE_RELEASE(pDevice);
#else
  m_shader = new CGUIShader("vert.glsl", "frag.glsl");
#endif
}

////////////////////////////////////////////////////////////////////////////
//
bool CRenderD3D::RestoreDevice()
{
  return true;
}

////////////////////////////////////////////////////////////////////////////
//
void CRenderD3D::InvalidateDevice()
{
#ifdef WIN32
  SAFE_RELEASE(m_pPShader);
  SAFE_RELEASE(m_pVBuffer);
#else
  m_shader->Free();
  delete m_shader;
  m_shader = nullptr;
#endif
}

////////////////////////////////////////////////////////////////////////////
//
bool CRenderD3D::Begin()
{
#ifdef WIN32
  D3D11_MAPPED_SUBRESOURCE res = {};
  if (SUCCEEDED(m_pContext->Map(m_pVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res)))
    m_Verts = (TRenderVertex*)res.pData;
#endif
  return true;
}

////////////////////////////////////////////////////////////////////////////
//
bool CRenderD3D::Draw()
{
  if (m_NumLines == 0)
    return true;
#ifndef WIN32
  m_shader->PushMatrix();
  m_shader->Translatef(0.0,-0.5,0.0);
  m_shader->Enable();
  struct PackedVertex
  {
    GLfloat x, y, z;
    GLfloat r, g, b;
  } vertex[m_NumLines*2];

  GLubyte idx[m_NumLines*2];

  for (size_t j = 0; j < m_NumLines * 2; ++j)
  {
    vertex[j].x = m_VertBuf[j].x;
    vertex[j].y = m_VertBuf[j].y;
    vertex[j].z = 0.0;
    vertex[j].r = m_VertBuf[j].col[0];
    vertex[j].g = m_VertBuf[j].col[1];
    vertex[j].b = m_VertBuf[j].col[2];
    idx[j] = j;
  }

  GLint posLoc = m_shader->GetPosLoc();
  GLint colLoc = m_shader->GetColLoc();

  GLuint vertexVBO;
  GLuint indexVBO;

  glGenBuffers(1, &vertexVBO);
  glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(PackedVertex)*m_NumLines*2, &vertex[0], GL_STATIC_DRAW);

  glVertexAttribPointer(posLoc, 3, GL_FLOAT, 0, sizeof(PackedVertex), BUFFER_OFFSET(offsetof(PackedVertex, x)));
  glVertexAttribPointer(colLoc, 3, GL_FLOAT, 0, sizeof(PackedVertex), BUFFER_OFFSET(offsetof(PackedVertex, r)));

  glEnableVertexAttribArray(posLoc);
  glEnableVertexAttribArray(colLoc);

  glGenBuffers(1, &indexVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*2*m_NumLines, idx, GL_STATIC_DRAW);
  glDrawElements(GL_LINES, m_NumLines*2, GL_UNSIGNED_BYTE, 0);

  glDisableVertexAttribArray(posLoc);
  glDisableVertexAttribArray(colLoc);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vertexVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &indexVBO);

  /*glBegin(GL_LINES);
  for (size_t j = 0; j < m_NumLines * 2; ++j)
  {
    glColor4f(m_VertBuf[j].col[0], m_VertBuf[j].col[1], m_VertBuf[j].col[2], m_VertBuf[j].col[3]);
    glVertex2f(m_VertBuf[j].x, m_VertBuf[j].y);
  }
  glEnd();*/
  m_Verts = m_VertBuf;
  m_shader->Disable();
  m_shader->PopMatrix();
#else
  m_pContext->Unmap(m_pVBuffer, 0);
  m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
  UINT strides = sizeof(TRenderVertex), offsets = 0;
  m_pContext->IASetVertexBuffers(0, 1, &m_pVBuffer, &strides, &offsets);
  m_pContext->PSSetShader(m_pPShader, NULL, 0);
  m_pContext->Draw(m_NumLines * 2, 0);
  Begin();
#endif
  m_NumLines = 0;
  return true;
}

////////////////////////////////////////////////////////////////////////////
//
void CRenderD3D::DrawLine(const CVector2& pos1, const CVector2& pos2, const CRGBA& col1, const CRGBA& col2)
{
  if (m_NumLines >= NUMLINES)
  {
    Draw();
  }
#ifndef WIN32
  if (m_Verts == null)
  {
    m_VertBuf = new TRenderVertex[10000];
    m_Verts = m_VertBuf;
  }
#endif
  m_Verts->x = pos1.x; m_Verts->y = pos1.y; m_Verts->z = 0.0f;
  m_Verts->col[0] = col1.r;
  m_Verts->col[1] = col1.g;
  m_Verts->col[2] = col1.b;
  m_Verts->col[3] = col1.a;  m_Verts++;

  m_Verts->x = pos2.x; m_Verts->y = pos2.y; m_Verts->z = 0.0f;
  m_Verts->col[0] = col2.r;
  m_Verts->col[1] = col2.g;
  m_Verts->col[2] = col2.b;
  m_Verts->col[3] = col2.a;  m_Verts++;

  m_NumLines++;
}

ADDONCREATOR(CMyAddon);
