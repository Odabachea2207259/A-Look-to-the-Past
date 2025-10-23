#pragma once
#include<SFML/Graphics.hpp>
#include "../Componentes/IComponentes.hpp"
#include <memory>

namespace CE
{
    class Objeto: public sf::Drawable, public  sf::Transformable
    {
        public:
		explicit Objeto();
		virtual ~Objeto()=default;
		void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
		bool esDino = false;

		template <typename T> Objeto& copyComponente(const T *componente){
			auto copia = std::make_shared<T>(*componente);
			componentes.push_back(copia);
			return *this;
		}

		Objeto& addComponente(const std::shared_ptr<IComponentes>& componente);
		
		template <typename T> T* getComponente() const
		{
			static_assert(std::is_base_of<IComponentes,T>::value,"Solo derivados de IComponentes");
			for(auto& c : componentes)
			{
				T* comp = dynamic_cast<T*>(c.get());
				if(comp!=nullptr)
					return comp;
			}

			return nullptr;
		};

		template <typename T> bool tieneComponente() const
		{
			static_assert(std::is_base_of<IComponentes,T>::value,"Solo derivados de IComponentes");
			for(auto& c : componentes)
			{
				T* comp = dynamic_cast<T*>(c.get());
				if(comp!=nullptr)
					return true;
			}

			return false;
		};

		template <typename T> void eliminarComponente()
		{
			static_assert(std::is_base_of<IComponentes,T>::value,"Solo derivados de IComponentes");
			int i = 0;
			if(tieneComponente<T>())
			{
				for(auto& c : componentes)
				{
					T* comp = dynamic_cast<T*>(c.get());
					if(comp!=nullptr)
						break;
					i++;
				}

				componentes.erase(componentes.begin()+i);
			}
		};

		static int getNumObjetos()
		{
			return num_objetos;
		}

		std::shared_ptr<INombre> getNombre()
		{
			return nombre;
		}
		std::shared_ptr<ITransform> getTransformada()
		{
			return transform;
		}

		std::string toString() const
		{
			return nombre->nombre;
		}

		void setPosicion(float x, float y);
		CE::Vector2D getPosicion();
		void setVelocidad(float x, float y);
		virtual void onUpdate(float dt){};

		std::shared_ptr<IStats>& getStats()
		{
			return stats;
		}

		//std::shared_ptr<IStats>* getStats() const
		//{
		//	return stats;
		//}

		const bool estaVivo() const
		{
			return stats->hp>0;
		}
	private:
		static int num_objetos;
		protected:
		std::shared_ptr<INombre> nombre;
		std::shared_ptr<ITransform> transform;
		std::shared_ptr<IStats> stats;
		std::vector<std::shared_ptr<IComponentes>> componentes;
    };
}
