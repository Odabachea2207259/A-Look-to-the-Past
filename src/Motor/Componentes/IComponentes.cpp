#include "IComponentes.hpp"

namespace CE
{
	INombre::INombre(const std::string& nom)
	  :IComponentes{},nombre{nom}
	{}

	ITransform::ITransform()
	  :IComponentes{},
	   posicion{Vector2D{0.f,0.f}},
	   velocidad{Vector2D{0.f,0.f}},
	   angulo{0}
	{}

	ITransform::ITransform(const Vector2D& pos, const Vector2D& vel, float ang)
	  :IComponentes{}, posicion{pos},velocidad{vel},angulo{ang}
	{}

	ITimer::ITimer()
	  :IComponentes{},frame_actual{0}
	{}
}
