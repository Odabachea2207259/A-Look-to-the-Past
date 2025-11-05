#pragma once
#include <string>
#include <cinttypes>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../Utils/Vector2D.hpp"
//#include "../../Juego/Estados/Estados.hpp"
#include <map>

namespace IVJ{
	enum TipoEnte{
		Atacante,
		Healer
	};
	class Entidad;
	class Estado;
	class Habilidad;
}

namespace CE
{
	class IComponentes
	{
		public:
			virtual ~IComponentes()=default;
	};

	class INombre : public IComponentes
	{
		public:
			explicit INombre(const std::string& nom);
			~INombre() override{};
		public:
			std::string nombre;
	};

	class ITransform :public IComponentes
	{
		public:
			ITransform();
			ITransform(const Vector2D& pos, const Vector2D& vel, float ang);
			~ITransform() override{};
		public:
			Vector2D posicion;
			Vector2D pos_prev;
			Vector2D velocidad;
			Vector2D pos_original;
			float angulo;
			int dirX = 1;
			int dirY = 1;
	};

	class ITimer : public IComponentes
	{
		public:
			explicit ITimer();
			~ITimer() override{};
		public:
			int frame_actual;
	};

	class IStats : public IComponentes
	{
		public:
			~IStats() override{};

			float hp;
			float hp_max;
			
			float str;
			float str_max;

			float def;
			float def_max;

			float agi;
			float agi_max;
	};

	class ITexto : public IComponentes
	{
		public:
			ITexto(const sf::Font& font, const std::string& texto);
			~ITexto()override{};

			sf::Text m_texto;
	};

	class ISprite : public IComponentes
	{
		public:
			ISprite(const sf::Texture& textura, float escala);
			ISprite(const sf::Texture&, int w, int h, float escala);
			~ISprite()override{};

		public:
			sf::Sprite m_sprite;
			int width;
			int height;
			float escala;
		private:
			sf::Texture m_texture;
	};

    class IShader : public IComponentes
    {
        public:
            enum class ShaderVars
            {
                FLOAT,
                VEC2F,
                VEC3F,
                VEC4F,
                MAT3,
                MAT4,
                TEX
            };
        public:
            explicit IShader(const std::string& vert, const std::string& frag);
            ~IShader() override{};
            void setEscalar(const std::string& key, float* valor);
            void setVector2(const std::string& key, sf::Vector2f* valor);
            void setVector3(const std::string& key, sf::Vector3f* valor);
            void setVector4(const std::string& key, sf::Glsl::Vec4* valor);
            void setMat3(const std::string& key, sf::Glsl::Mat3* valor);
            void setMat4(const std::string& key, sf::Glsl::Mat4* valor);
            void setTextura(const std::string& key, sf::Texture* valor);
            void cambiarShader(const std::string& vert, const std::string& frag);
        public:
            sf::Shader m_shader;
            std::string m_fragshaderFile;
            std::string m_vertshaderFile;
            //al sacarlo hay que castear a un tipo de dato
            //m_vars["tiempo"] = &tiempo; (float*)m_vars["tiempo"];
            //m_vars["textura"] = &sprite->getTexture(); (sf::Texture*)m_vars["textura"];
            std::map<std::string,std::pair<IShader::ShaderVars,void*>> m_vars;
    };

	class IControl : public IComponentes
	{
		public:
			explicit IControl();
			~IControl() override{};
		public:
			bool arr;
			bool abj;
			bool izq;
			bool der;
			bool acc; //Ataque
			bool sacc; //Habilidad
			bool damage; //Daño
			bool muerte;
			bool muerto;
			bool accion;
			bool salto;
			bool saltando;

			std::string ataque = "Ataque";
			std::string mov = "";

			bool nextPage;
			bool prevPage;
			bool abrir;
			bool cerrar;
			bool cambiar;
	};

	class IEstados : public IComponentes
	{
		public:
			explicit IEstados(){}
			std::vector<std::shared_ptr<IVJ::Estado>> estados;
			bool dormido = false;
            bool aturdido = false;

			int cantidad = 0;
	};

	class IHabilidades : public IComponentes
	{
		public:
			explicit IHabilidades(){}

			std::vector<std::shared_ptr<IVJ::Habilidad>> movimientos;

			std::shared_ptr<IVJ::Habilidad> habilidadSelecc;
			std::shared_ptr<IVJ::Habilidad> habilidadEspecial;
	};

	class IJugador : public IComponentes{
		public:
			explicit IJugador(){}
			int dinoPuntos = 15;
			float medidor = 0;
	};

	class ISelectores : public IComponentes
	{
		public:
			explicit ISelectores(){}

			sf::RectangleShape vida;
            sf::RectangleShape vida_max;

            sf::RectangleShape seleccion;
	};

	class IPersonaje : public IComponentes
	{
		public:
			explicit IPersonaje(){}

		    float nivel;
            bool turno = false;
			bool especial = false;

            bool tieneAtaquesGratis = true;
            int numDino;
			std::shared_ptr<IVJ::Entidad> target;
            
            IVJ::TipoEnte tipo;
	};
	
	class IBoundingBox : public IComponentes
	{
		public:
			explicit IBoundingBox(const Vector2D& dim);
			Vector2D tam;
			Vector2D mitad;
	};

	class IRespawn: public IComponentes
	{
		public:
			IRespawn(int max, int w, int h, IVJ::Entidad *pre);
			IRespawn(std::vector<std::shared_ptr<IComponentes>>& lista_comp,int max);

			int timer_actual;
			int timer_maximo;
			int num_objetos;
			int max_objetos;

			IVJ::Entidad* prefab;
			int width;
			int height;
			std::vector<std::shared_ptr<IComponentes>> componentes;
	};

	class IPaths : public IComponentes
	{
		public:
			explicit IPaths(int total_frames);

			void addCurva(Vector2D p1, Vector2D p2, Vector2D p3);
		public:
			std::vector<Vector2D> puntos;
			int offset;
			int frame_total_curva;
			int frame_actual_curva; 
			int id_curva;
	};
}
