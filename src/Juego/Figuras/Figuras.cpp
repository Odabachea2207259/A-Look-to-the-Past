#include "Figuras.hpp"

namespace IVJ
{
    Figuras::Figuras(int l, const sf::Color& relleno, const sf::Color& contorno)
        :CE::Objeto{},lados{l},f_crelleno{relleno},f_ccontorno{contorno}
    {

    }


    Rectangulo::Rectangulo(float ancho, float largo, const sf::Color& relleno, const sf::Color& contorno)
    :Figuras{4,relleno,contorno}, rect_img{sf::RectangleShape({ancho,largo})},w{ancho},h{largo}
    {
        rect_img.setFillColor(f_crelleno);
        rect_img.setOutlineColor(f_ccontorno);
        rect_img.setOutlineThickness(2);
        //rect_img.setOrigin({ancho/2.f,largo/2.f}); //---------->>QUITAR PARA EL JUEGO
	    //nombre->nombre = "Rectangulo "+std::to_string(CE::Objeto::getNumObjetos());
	    nombre->nombre = "Rectangulo";
        this->getStats()->hp = 1.f;
    }

    void Rectangulo::setPosicion(float x, float y)
    {
        rect_img.setPosition({x,y});
        rect_bounding = sf::IntRect({static_cast<int>(x),static_cast<int>(y)},{static_cast<int>(getWidth()),static_cast<int>(getHeight())});
    }

    void Rectangulo::draw(sf::RenderTarget& target, sf::RenderStates state) const 
    {
        state.transform *= getTransform();
        target.draw(rect_img);
    }

    float Rectangulo::getArea()
    {
    	return w * h;
    }

    void Rectangulo::onUpdate(float dt)
    {
    	rect_img.setPosition(
		{
		transform->posicion.x,
		transform->posicion.y
		}
	);
    }

    Circulo::Circulo(float radio, const sf::Color& relleno, const sf::Color& contorno)
    :Figuras{1,relleno,contorno},rect_img{sf::CircleShape({radio})},r{radio}
    {
        rect_img.setFillColor(f_crelleno);
        rect_img.setOutlineColor(f_ccontorno);
        rect_img.setOutlineThickness(3);
        rect_img.setOrigin({radio/2.f,radio/2.f});

	//nombre->nombre = "Circulo "+std::to_string(CE::Objeto::getNumObjetos());
	nombre->nombre = "Circulo";
    }

    //void Circulo::setPosicion(float x, float y)
    //{
    //    img.setPosition({x,y});
    //}

    void Circulo::draw(sf::RenderTarget& target, sf::RenderStates state) const 
    {
        state.transform *= getTransform();
        target.draw(rect_img);
    }

    float Circulo::getArea()
    {
    	return M_PI*r*r;
    }

    void Circulo::onUpdate(float dt)
    {
    	rect_img.setPosition(
		{
		transform->posicion.x,
		transform->posicion.y
		}
	);
    }

    Triangulo::Triangulo(float lado, const sf::Color& relleno, const sf::Color& contorno)
    :Figuras{3,relleno,contorno},rect_img{sf::CircleShape({lado},3)},l{lado}
    {
        rect_img.setFillColor(f_crelleno);
        rect_img.setOutlineColor(f_ccontorno);
        rect_img.setOutlineThickness(3);
        rect_img.setOrigin({lado/2.f,lado/2.f});

	//nombre->nombre = "Triangulo "+std::to_string(CE::Objeto::getNumObjetos());
	nombre->nombre = "Triangulo";
    }

    //void Triangulo::setPosicion(float x, float y)
    //{
    //    img.setPosition({x,y});
    //}

    void Triangulo::draw(sf::RenderTarget& target, sf::RenderStates state) const 
    {
        state.transform *= getTransform();
        target.draw(rect_img);
    }

    float Triangulo::getArea()
    {
    	float h = (lados * sqrt(3))/2;
    	return (lados * h)/2;
    }

    void Triangulo::onUpdate(float dt)
    {
    	rect_img.setPosition(
		{
		transform->posicion.x,
		transform->posicion.y
		}
	);
    }
}
