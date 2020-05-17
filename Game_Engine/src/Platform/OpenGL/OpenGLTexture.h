#pragma once

#include "Game_Engine/Renderer/Texture.h"

namespace GameEngine {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string&);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void Bind(uint32_t slot) const override;

	private:
		const std::string& m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};

}