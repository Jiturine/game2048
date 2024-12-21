#include "Text.h"

glm::mat4 Text::projection;
std::map<char, Text::Character> Text::Characters;
VertexArray *Text::vertexArray;
VertexBuffer *Text::vertexBuffer;
Shader *Text::shader;

void Text::Init(unsigned int screenWidth, unsigned int screenHeight)
{
	Text::projection = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight));
	// 生成VBO，VAO
	vertexArray = new VertexArray;
	vertexArray->Bind();
	vertexBuffer = new VertexBuffer(nullptr, sizeof(float) * 6 * 4, VertexBuffer::DataMode::DYNAMIC);
	VertexBufferLayout layout;
	layout.Push<float>(4);
	vertexArray->AddBuffer(*vertexBuffer, layout);
	shader = new Shader("shaders/text_shader/text_vertex_shader.vs",
						"shaders/text_shader/text_fragment_shader.fs");
}

void Text::LoadFont(const std::string &fontName, int fontHeight)
{
	// 加载字体
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		LOG_ERROR("FREETYPE: Could not init FreeType Library");
	FT_Face face;
	std::string fontPath = std::format("{}/fonts/{}", PATH, fontName);
	if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
		LOG_ERROR("FREETYPE: Failed to load font");
	// 设置字体大小
	FT_Set_Pixel_Sizes(face, 0, fontHeight);
	// 生成纹理并保存
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 禁用字节对齐限制
	for (GLubyte c = 0; c < 128; c++)
	{
		// 加载字符的字形
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			LOG_ERROR("FREETYTPE: Failed to load Glyph");
			continue;
		}
		// 生成纹理
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);
		// 设置纹理选项
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// 储存字符供之后使用
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<unsigned int>(face->glyph->advance.x)};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	// 清理资源
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void Text::Render(const std::string &text, float x, float y, float scale, glm::vec3 color)
{
	shader->Bind();
	shader->SetUniform("textColor", color);
	shader->SetUniform("projection", projection);
	glActiveTexture(GL_TEXTURE0);
	vertexArray->Bind();
	for (std::string::const_iterator c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// 对每个字符更新VBO
		float vertices[6][4] = {
			{xpos, ypos + h, 0.0, 0.0},
			{xpos, ypos, 0.0, 1.0},
			{xpos + w, ypos, 1.0, 1.0},

			{xpos, ypos + h, 0.0, 0.0},
			{xpos + w, ypos, 1.0, 1.0},
			{xpos + w, ypos + h, 1.0, 0.0}};
		// 在四边形上绘制字形纹理
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// 更新VBO内存的内容
		vertexBuffer->ChangeData(vertices, sizeof(vertices));
		// 绘制四边形
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// 更新位置到下一个字形的原点，注意单位是1/64像素
		x += (ch.advance >> 6) * scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
	}
}