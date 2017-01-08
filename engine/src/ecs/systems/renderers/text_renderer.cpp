#include "SDL.h"
#include <memory>

#include "text_renderer.hpp"
#include "math/rect.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/text.hpp"
#include "service/texture_library.hpp"
#include "service/font_library.hpp"
#include "io/file.hpp"

namespace smeg {

	TextRenderer::TextRenderer(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) :
	                               vertexShaderFilePath(vertexShaderFilePath), fragmentShaderFilePath(fragmentShaderFilePath) {
		types.push_back(std::type_index(typeid(Transform)));
		types.push_back(std::type_index(typeid(Text)));
		executionOrder = System::LATE;
	}

    void TextRenderer::Initialise(OpenGLRenderer &renderer) {
		std::string vertexShaderSource = File::LoadText(vertexShaderFilePath.c_str());
		std::string fragmentShaderSource = File::LoadText(fragmentShaderFilePath.c_str());

		shaderProgram = renderer.GenerateShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
	}

	void TextRenderer::Register(OpenGLRenderer &renderer, Entity &entity) {
		// TextureLibrary& textureLibrary = serviceContainer->Get<TextureLibrary>();
		Text& text = entity.GetComponent<Text>();
		
		//auto texture = textureLibrary.LoadFile(renderer, text.bitmapTextureId);
		Rect normalisedRect = Rect::New(0, 0, 1, 1);
		// if (text.drawRect == Rect()) {
		// 	normalisedRect = Rect::New(0, 0, 1, 1);
		// } else {
		// 	normalisedRect = text.drawRect.GetNormalisedRect(Vector2::New(texture.width, texture.height));
		// }

		Vector2 topLeft = normalisedRect.TopLeft();
		Vector2 topRight = normalisedRect.TopRight();
		Vector2 bottomLeft = normalisedRect.BottomLeft();
		Vector2 bottomRight = normalisedRect.BottomRight();

		text.vertices = {
			// Positions          // Colors          // Texture Coords
			-0.5,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   topLeft.x, topLeft.y,  // Top Left 
			-0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f,   bottomLeft.x, bottomLeft.y, // Bottom Left
			0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   bottomRight.x, bottomRight.y, // Bottom Right
			0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   topRight.x, topRight.y, // Top Right
		};

		text.vbo = renderer.GenerateVertexBufferObject(text.vertices);
		text.vao = renderer.GenerateVertexArrayObject(text.vbo);
		text.ebo = renderer.GenerateElementBufferObject(text.indices);
	}	
	
	void TextRenderer::Deregister(OpenGLRenderer &renderer, Entity &entity) {}

	void TextRenderer::Process(Entity &entity) {}

	void TextRenderer::Render(OpenGLRenderer& renderer, SpriteBatchRenderer &batcher, Entity &entity) {
		Text& text = entity.GetComponent<Text>();
		Transform& transform = entity.GetComponent<Transform>();


		FontLibrary& fontLibrary = serviceContainer->Get<FontLibrary>();
		Font& font = fontLibrary.LoadFont(renderer, "res/arial.ttf", 24);

		TextureLibrary& textureLibrary = serviceContainer->Get<TextureLibrary>();
		auto& texture = textureLibrary.LoadFile(renderer, font.textureFontId);

		batcher.Batch(texture, Vector2::New(512, 512), transform.position, shaderProgram, text.vbo, text.vao, text.ebo);
	}
}