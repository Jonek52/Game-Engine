#pragma once

#include <deque>
#include "renderer2d.h"

namespace sparky {
	namespace graphics {

		class Simple2DRenderer : public Renderer2D {
		public:
			virtual void Submit (const Renderable2D *renderable) override;
			virtual void Flush () override;
		
		private:
			std::deque<const Renderable2D *> m_RenderQueue;
		};
	}
}