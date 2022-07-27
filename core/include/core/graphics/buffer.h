#pragma once

#include <memory>
#include <vector>

namespace Core
{
	enum class ShaderDataType
	{
		None = 0,
		Vec3,
		Vec4,
		Mat4x4,
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Vec3:
				return sizeof(float) * 3;

			case ShaderDataType::Vec4:
				return sizeof(float) * 4;

			case ShaderDataType::Mat4x4:
				return sizeof(float) * (4 * 4);
		}

		return 0;
	}

	struct BufferElement
	{
		ShaderDataType type;
		const char* name;
		uint32_t offset;
		uint32_t size;
		bool normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const char* name, bool normalized = false)
			: type(type), name(name), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
		{}

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
			case ShaderDataType::Vec3:
				return 3;

			case ShaderDataType::Vec4:
				return 4;

			case ShaderDataType::Mat4x4:
				return 4 * 4;
			}

			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements)
		{
			// Calculate Offset and Stride
			uint32_t offset = 0;
			stride = 0;
			for (auto& elem : BufferLayout::elements)
			{
				elem.offset = offset;
				offset += elem.size;
				stride += elem.size;
			}
		}

		inline const std::vector<BufferElement>& GetElements() const { return elements; }
		inline uint32_t GetStride() const { return stride; }

	private:
		std::vector<BufferElement> elements;
		uint32_t stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0; 

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}