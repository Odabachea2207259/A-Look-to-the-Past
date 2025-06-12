#include "Pais.hpp"

namespace IVJ
{
    Pais::Pais(float ancho, float largo, const sf::Color& relleno, const sf::Color& contorno, bool desbloqueado, int precio)
    :Rectangulo{ancho,largo,relleno,contorno},desbloqueado{desbloqueado},precio{precio}
    {

    }

    void Pais::dinosCan()
    {
        dinosaurios.push_back(std::make_shared<Parasaurolophus>(1));
    }
    void Pais::dinosUsa()
    {
        dinosaurios.push_back(std::make_shared<Pachycephalosaurus>(1));
    }
    void Pais::dinosMex()
    {
        dinosaurios.push_back(std::make_shared<Centrosaurus>(1));
    }
    void Pais::dinosArg()
    {
        dinosaurios.push_back(std::make_shared<Carnotauro>(1));
    }
}