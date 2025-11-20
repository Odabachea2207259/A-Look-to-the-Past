#pragma once
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Primitivos/Escena.hpp"
#include "../Componentes/IJComponentes.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace IVJ
{

	const int MAX_ENTES = 6;

	const std::string entes[MAX_ENTES] = {
		"Pachycephalosaurus",
		"Parasaurolophus",
		"Centrosaurus",
		"Carnotauro",
		"Coty",
		"Anteosaurus"};

	class EscenaBestiario : public CE::Escena
	{
		public:
			EscenaBestiario():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};
            bool mouse,mousePressed,mousePrev = false;

            std::shared_ptr<Entidad> fondo;
            std::shared_ptr<Rectangulo> izq;
            std::shared_ptr<Rectangulo> der;

			std::shared_ptr<CE::ITexto> textoPrueba;
			std::shared_ptr<CE::ITexto> periodo;
			std::shared_ptr<CE::ITexto> nombreEnte;
			std::shared_ptr<IVJ::Rectangulo> infoEnte;

			std::shared_ptr<CE::ITexto> noDescubierto;

			json descubiertos;
			json info;

			int numPagina = 0;
            bool salir = false,salida = false,mov = false, descubierto;
	};
}
