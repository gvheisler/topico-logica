/***********************************************************************************************
 * \class ManagerBotoes
 * \brief Classe responsável por gerenciar e renderizar os botões na interface gráfica.
 *
 * A classe ManagerBotoes é responsável por criar, gerenciar e renderizar os botões na
 * interface gráfica. Ela também lida com os cliques do mouse nos botões e executa as ações
 * correspondentes.
 *
 ***********************************************************************************************/

#ifndef MANAGERBOTOES_H
#define MANAGERBOTOES_H

#include <vector>
#include "Botao.h"
#include "ImageManager.h"

class ManagerBotoes
{
    private:
        ImageManager* imageManager; /**< Ponteiro para o gerenciador de imagens. */
        std::vector<Botao> botoes; /**< Vetor contendo os botões. */
        int widthBotao; /**< Largura dos botões. */
        int heightBotao; /**< Altura dos botões. */
        int startY; /**< Posição Y dos botões. */
        int startX; /**< Posição inicial X dos botões. */

    public:

        /**
        * \brief Construtor da classe.
        * \param im Ponteiro para o gerenciador de imagens.
        */
        ManagerBotoes(ImageManager* im);

        /**
        * \brief Destrutor da classe.
        */
        virtual ~ManagerBotoes();

        /**
        * \brief Renderiza os botões na tela.
        */
        void renderizaBotoes();

        /**
        * \brief Verifica se houve um clique do mouse em algum botão e executa a ação correspondente.
        * \param mx Coordenada X do clique do mouse.
        * \param my Coordenada Y do clique do mouse.
        */
        void verificaClique(int mx, int my);
};

#endif // MANAGERBOTOES_H
