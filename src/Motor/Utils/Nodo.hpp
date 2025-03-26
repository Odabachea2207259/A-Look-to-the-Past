#pragma once
#include <memory>
namespace CE
{
	template<typename T> class Lista;
	template<typename T> class Nodo
	{
		friend class Lista<T>;

		protected:
			Nodo(T d)
			: dato{d}
			{
				m_next = nullptr;
				m_prev = nullptr;
			}
		public:
			T dato;
			std::shared_ptr<Nodo<T>> m_prev;
			std::shared_ptr<Nodo<T>> m_next;
			unsigned int size;
	};
}
