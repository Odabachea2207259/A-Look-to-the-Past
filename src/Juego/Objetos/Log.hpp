#pragma once
#include <SFML/Graphics.hpp>
#include "../../Motor/Utils/Utils.hpp"
#include "../../Motor/Utils/Vector2D.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"

#include<memory>
namespace IVJ
{
    class Log
    {
        public:
            static Log& Get(void);
            static void Terminar(void);
            
            Log();
            static inline Log* instancia =nullptr;
            
            std::unique_ptr<IVJ::Rectangulo> log;
            std::unique_ptr<std::vector<std::shared_ptr<CE::ITexto>>> textos;
            std::unique_ptr<std::string> texto;

            std::vector<std::shared_ptr<CE::ITexto>>& GetTextos();

            void acomodarTextos();
    };
}
