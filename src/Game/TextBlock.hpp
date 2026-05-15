#pragma once

#include "CommonHeader.hpp"
#include "Math/MathUtils.hpp"
#include "Core/CoreStructs.hpp"

class Renderer;
class Text;

class TextBlock
{
public:

    TextBlock();
    ~TextBlock();
    Area2D TextArea2D;

    Text* text = nullptr;

    void SetText(Text* inText) { text = inText; }
    void setArea2D(Area2D inArea2D) { TextArea2D = inArea2D; }

public:

    virtual void RenderText(Renderer& inRenderer);
    void RenderCustomText(Renderer& inRenderer, Text* inText, Area2D inArea2D);

};