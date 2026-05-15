
#include "Core/Graphic/Renderer.hpp"
#include "Core/Graphic/TextureManager.hpp"
#include "Core/Graphic/Text.hpp"

#include "TextBlock.hpp"

TextBlock::TextBlock()
{
    TextArea2D = Area2D();
    text = nullptr;
}

TextBlock::~TextBlock()
{
    delete text;
    text = nullptr;
}

void TextBlock::RenderText(Renderer& inRenderer)
{
    if (TextArea2D && text)
    {
        inRenderer.DrawText(text, TextArea2D);
    }
}

void TextBlock::RenderCustomText(Renderer& inRenderer, Text* inText, Area2D inArea2D)
{

}