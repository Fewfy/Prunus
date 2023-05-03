#pragma once
#include "Prunus/Renderer/VertexArray.h"

namespace Prunus
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		virtual ~OpenGLVertexArray();
		OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}