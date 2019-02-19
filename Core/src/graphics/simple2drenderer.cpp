#include "simple2drenderer.h"

namespace sparky {
	namespace graphics {
		void Simple2DRenderer::Submit (const Renderable2D * renderable) {
			m_RenderQueue.push_back (renderable);
		}

		void Simple2DRenderer::Flush () {
			
			while (!m_RenderQueue.empty ()) {

				const Renderable2D * renderable = m_RenderQueue.front ();
				renderable->GetVAO ()->Bind ();
				renderable->GetIBO ()->Bind ();

				renderable->GetShader ().SetUniformMat4 ("ml_matrix", maths::mat4::translation (renderable->GetPosition ()));
				glDrawElements (GL_TRIANGLES, renderable->GetIBO ()->getCount (), GL_UNSIGNED_SHORT, nullptr);

				renderable->GetIBO ()->Unbind ();
				renderable->GetVAO ()->Unbind ();
				
				m_RenderQueue.pop_front ();
			}
		}
	}
}