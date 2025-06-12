#include "IComponentes.hpp"
#include "SFML/Graphics/Rect.hpp"

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

	ITexto::ITexto(const sf::Font& font, const std::string& texto)
	:IComponentes{},m_texto{sf::Text(font,texto)}
	{
	}

	ISprite::ISprite(const sf::Texture& textura, float escala)
	:IComponentes{},m_sprite{textura},escala{escala}
	{
		m_sprite.setScale({escala,escala});
		auto dim = textura.getSize();
		width = dim.x;
		height = dim.y;

		//pivote
		m_sprite.setOrigin({dim.x/2.f,dim.y/2.f});
	}
	ISprite::ISprite(const sf::Texture& textura, int w, int h, float escala)
	:IComponentes{},m_sprite{m_texture},m_texture{textura},width{w},height{h},escala{escala}
	{
		m_texture.setSmooth(true);
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(sf::IntRect{{0,0},{w,h}});
		m_sprite.setScale({escala,escala});
		//pivote
		m_sprite.setOrigin({w/2.f,h/2.f});
	}

    IShader::IShader(const std::string& vert,const std::string& frag)
        :IComponentes{},m_shader{},m_fragshaderFile{frag},m_vertshaderFile{vert}
    {
        if(!vert.empty() && !frag.empty())
        {
            if(!m_shader.loadFromFile(vert,frag))
                exit(EXIT_FAILURE);
        }
        else if(vert.empty())
        {
            if(!m_shader.loadFromFile(frag,sf::Shader::Type::Fragment))
                exit(EXIT_FAILURE);
        }else
        {
            if(!m_shader.loadFromFile(vert,sf::Shader::Type::Vertex))
                exit(EXIT_FAILURE);
        }
    }
    void IShader::setEscalar(const std::string& key, float *valor)
    {
        m_vars[key]=std::pair<IShader::ShaderVars,void*>(IShader::ShaderVars::FLOAT,valor);
        m_shader.setUniform(key,*valor);
    }
    void IShader::setVector2(const std::string& key, sf::Vector2f *valor)
    {
        m_vars[key]=std::pair<IShader::ShaderVars,void*>(IShader::ShaderVars::VEC2F,valor);
        m_shader.setUniform(key,*valor);
    }
    void IShader::setVector3(const std::string& key, sf::Vector3f *valor)
    {
        m_vars[key]=std::pair<IShader::ShaderVars,void*>(IShader::ShaderVars::VEC3F,valor);
        m_shader.setUniform(key,*valor);
    }
    void IShader::setVector4(const std::string& key, sf::Glsl::Vec4 *valor)
    {
        m_vars[key]=std::pair<IShader::ShaderVars,void*>(IShader::ShaderVars::VEC4F,valor);
        m_shader.setUniform(key,*valor);
    }
    void IShader::setMat3(const std::string& key, sf::Glsl::Mat3 *valor)
    {
        m_shader.setUniform(key,*valor);
    }
    void IShader::setMat4(const std::string& key, sf::Glsl::Mat4 *valor)
    {
        m_shader.setUniform(key,*valor);
    }
    void IShader::setTextura(const std::string& key, sf::Texture *valor)
    {
        m_vars[key]=std::pair<IShader::ShaderVars,void*>(IShader::ShaderVars::TEX,valor);
        m_shader.setUniform(key,*valor);
    }

	IControl::IControl()
	{
		arr = false;
		abj = false;
		izq = false;
		der = false;
		acc = false;
		sacc = false;
		damage = false;
		muerte = false;
		muerto = false;
	}
    
    IBoundingBox::IBoundingBox(const Vector2D& dim)
    :tam{dim.x,dim.y},mitad{dim.x/2,dim.y/2}{}
}
