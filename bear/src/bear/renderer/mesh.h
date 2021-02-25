#pragma once

#include "bear/core/core.h"

namespace bear
{
	class Mesh
	{
	public:
		virtual ~Mesh() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<Mesh> Create(const char* file_path);
	};
}