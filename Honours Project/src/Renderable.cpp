#include "Renderable.h"
#include "GeometryUtil.h"
void Renderable::from_json(const nlohmann::json & j)
{
}

Renderable::Renderable() : model(nullptr), effect(new Effect()), Component("Rendererable")
{
}

Renderable::~Renderable()
{
}

void Renderable::SetPlane(float spacing, unsigned int xSize, unsigned int ySize)
{
	model = GeometryUtil::BuildPlane(spacing,xSize,ySize);

}

void Renderable::SetCube(float size)
{
	model = GeometryUtil::BuildCube(size);
}

void Renderable::SetModel(std::string location)
{
	model = new Model(location);
}

void Renderable::SetEffect(std::string texName)
{
	effect->texture = Shader::Get().AddTexture(texName);
	effect->shader = "Phong";
	Shader::Get().AddShader("Phong");
}

void Renderable::Render()
{
	GameEngine::Get().Render(GetTransform(),*model, *effect);
}
