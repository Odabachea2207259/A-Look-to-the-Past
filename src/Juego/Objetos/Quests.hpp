#pragma once

#include <stdio.h>
#include <map>
#include <utility>
#include "../Figuras/Figuras.hpp"
#include "QuestStates.hpp"

namespace IVJ
{
    class Quests
    {
        public:
            static Quests& Get(void);
            //std::map<int,std::pair<std::string,States>>& GetQuests(void);
            std::map<std::string,std::pair<std::shared_ptr<CE::ITexto>,States>>& GetQuests(void);
            bool& GetAbierto(void);
            bool& GetCambios(void);
            void addQuest(std::string name, IVJ::States estado, std::string texto);
            void check(void);
            
            std::shared_ptr<IVJ::Rectangulo> rect_1,rect_2;
            std::vector<std::shared_ptr<CE::ITexto>> texto_quests;
            void ordenarTexto();

            void terminarQuest(std::string quest);
        private:
            Quests();
            static inline Quests* instancia =nullptr;

            //std::map<std::string,States> quests;
            std::map<std::string,std::pair<std::shared_ptr<CE::ITexto>,States>> quests;

            static int id;
            std::unique_ptr<bool> cambios;
            std::unique_ptr<bool> abierto;
    };
}