#pragma once
#include "../../Motor/Primitivos/Objetos.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace IVJ
{
    class Figuras:public CE::Objeto
    {
    public:
        explicit Figuras(int l, const sf::Color& relleno, const sf::Color& contorno);
        virtual ~Figuras() override{};
	virtual float getArea()=0;
	friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Figuras>& fig)
	{
		os<<"Lados: "<< fig->lados<<
		"\nRelleno: "<< fig->f_crelleno.toInteger()<<
		"\nContorno: "<< fig->f_ccontorno.toInteger()<<
		"\n";

		return os;
	}
        //virtual void setPosicion(float x, float y)=0;
    protected:
    	int dir = 1;
        int lados;
        sf::Color f_crelleno;
        sf::Color f_ccontorno;
    };


    class Rectangulo: public Figuras
    {
        public: 
            explicit Rectangulo(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno);
            ~Rectangulo() override{};
            void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
            //void setPosicion(float x, float y) override;
	    float getArea() override;
	    void onUpdate(float dt) override;
        private:
            sf::RectangleShape rect_img;
            float w;
            float h;
    };

    class Circulo : public Figuras
    {
    	public:
		explicit Circulo(float radio, const sf::Color& relleno,const sf::Color& contorno);
		~Circulo() override{};
		void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
		//void setPosicion(float x, float y);
		float getArea() override;
		void onUpdate(float dt) override;
	private:
		sf::CircleShape rect_img;
		float r;
    };

    class Triangulo : public Figuras
    {
    	public:
		explicit Triangulo(float lado, const sf::Color& relleno, const sf::Color& contorno);
		~Triangulo() override{};
		void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
		//void setPosicion(float x, float y);
		float getArea() override;
		void onUpdate(float dt) override;
	private:
		sf::CircleShape rect_img;
		float l;
    };
}
