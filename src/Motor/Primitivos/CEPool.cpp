#include "CEPool.hpp"
#include "../../Juego/Dinosaurios/Dinosaurio.hpp"
#include <algorithm>

namespace CE
{
	Pool::Pool(int size)
	:max_size{size}
	{
		objetos.reserve(max_size);
	}
	void Pool::agregarPool(const std::shared_ptr<Objeto>& obj)
	{
		if(objetos.size() == max_size)
		{
			max_size += max_size;
			objetos.reserve(max_size);
		}
		objetos.emplace_back(obj);
	}

	void Pool::borrarPool()
	{
		for(auto & ente : objetos)
		{
			if(ente->esDino && !ente->estaVivo())
			{
				auto c = ente->getComponente<CE::IControl>();
					c->muerte = true;
			}
		}
	}

	std::shared_ptr<Objeto>& Pool::operator[](std::size_t idx)
	{
		return objetos[idx];
	}

	const std::shared_ptr<Objeto>& Pool::operator[](std::size_t idx) const
	{
		return objetos[idx];
	}
}
