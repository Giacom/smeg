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
		Text& text = entity.GetComponent<Text>();

		std::vector<float> vertices;
		std::vector<unsigned short> indices;

		FontLibrary& fontLibrary = serviceContainer->Get<FontLibrary>();
		auto& font = fontLibrary.LoadFont(renderer, "res/arial.ttf", 24);

		TextureLibrary& textureLibrary = serviceContainer->Get<TextureLibrary>();
		auto texture = textureLibrary.LoadFile(renderer, font.textureFontId);

		float x = 0;
		float y = 0;
		int indiceCount = 0;

		for (const char& textCharacter : text.GetText()) {

			if (textCharacter == '\n') {
				y -= font.pixelSize;
				x = 0;
				continue;
			}

			Character character = font.characters[textCharacter];

			Rect normalisedBox = character.boundingBox.GetNormalisedRect(Vector2::New(texture.width, texture.height));

			Vector2 topLeft = normalisedBox.TopLeft();
			Vector2 topRight = normalisedBox.TopRight();
			Vector2 bottomLeft = normalisedBox.BottomLeft();
			Vector2 bottomRight = normalisedBox.BottomRight();

			unsigned short zero = indiceCount++;
			unsigned short first = indiceCount++;
			unsigned short second = indiceCount++;
			unsigned short third = indiceCount++;

			indices.insert(indices.end(), { zero, first, second, second, third, zero});

			float normalisedAdvanceLeft = (x + character.offset.x);
			float normalisedAdvanceRight = x + character.offset.x + character.boundingBox.size.x;

			float normalisedOffsetTop = y + -character.offset.y;
			float normalisedOffsetBottom = y + -character.offset.y + -character.boundingBox.size.y;

			SDL_Log("%f", normalisedOffsetTop);

			// Top left
			vertices.insert(vertices.end(), { normalisedAdvanceLeft, normalisedOffsetTop, 1.0f, /* */ 1.0f, 1.0f, 1.0f, /* */ topLeft.x, topLeft.y });
			vertices.insert(vertices.end(), { normalisedAdvanceLeft, normalisedOffsetBottom, 1.0f, /* */ 1.0f, 1.0f, 1.0f, /* */ bottomLeft.x, bottomLeft.y });

			vertices.insert(vertices.end(), { normalisedAdvanceRight, normalisedOffsetBottom, 1.0f, /* */ 1.0f, 1.0f, 1.0f, /* */ bottomRight.x, bottomRight.y });
			vertices.insert(vertices.end(), { normalisedAdvanceRight, normalisedOffsetTop, 1.0f, /* */ 1.0f, 1.0f, 1.0f, /* */ topRight.x, topRight.y });

			x += character.advance;
		}

		text.vertices = vertices;
		text.indices = indices;

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

		batcher.Batch(texture, text.size, transform.position, text.indices.size(), shaderProgram, text.vbo, text.vao, text.ebo);
	}
}