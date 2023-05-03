#include "pnpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Prunus
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Prunus::ShaderDataType::None:		return GL_FLOAT;
			case Prunus::ShaderDataType::Float:		return GL_FLOAT;
			case Prunus::ShaderDataType::Float2:	return GL_FLOAT;
			case Prunus::ShaderDataType::Float3:	return GL_FLOAT;
			case Prunus::ShaderDataType::Float4:	return GL_FLOAT;
			case Prunus::ShaderDataType::Mat3:		return GL_FLOAT;
			case Prunus::ShaderDataType::Mat4:		return GL_FLOAT;
			case Prunus::ShaderDataType::Int:		return GL_INT;
			case Prunus::ShaderDataType::Int2:		return GL_INT;
			case Prunus::ShaderDataType::Int3:		return GL_INT;
			case Prunus::ShaderDataType::Int4:		return GL_INT;
			case Prunus::ShaderDataType::Bool:		return GL_BOOL;
		}

		PRUNUS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		glBindVertexArray(m_RendererID);
		buffer->Bind();

		PRUNUS_CORE_ASSERT(buffer->GetLayout().GetEelements().size(), "Vertex Buffer has no layout!");

		uint32_t index = 0;
		const auto& layout = buffer->GetLayout();
		
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetElementCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(buffer);
	}
	
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
	const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}