/***********************************************************************************************
 * @file ImageManager.h
 * @brief Declaração da classe ImageManager, responsável por gerenciar imagens e interações com elas.
 *
 * A classe ImageManager é responsável por carregar, exibir, manipular e interagir com imagens
 * na interface gráfica. Ela oferece funcionalidades para carregar imagens, mover imagens pela
 * tela, rotacionar, exibir histogramas e canais RGB, entre outras.
 *
 ***********************************************************************************************/

#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "Bmp.h"

class ImageManager
{
    private:
        std::vector<Bmp*> images; /**< Vetor de ponteiros para imagens */
        int imagemSelecionada; /**< Índice da imagem selecionada */
        bool mostrarHistogramas; /**< Flag para mostrar ou ocultar histogramas */
        bool mostrarRGB; /**< Flag para mostrar ou ocultar canais RGB */
        bool mostrarImagem; /**< Flag para mostrar ou ocultar imagens */
        int xStartMainPanel; /**< Coordenada x do início do painel principal */
        int xEndMainPanel; /**< Coordenada x do final do painel principal */
        int yStartMainPanel; /**< Coordenada y do início do painel principal */
        int yEndMainPanel; /**< Coordenada y do final do painel principal */
        int click_x; /**< Coordenada x da diferença do clique do mouse com x do inicio da imagem*/
        int click_y; /**< Coordenada y da diferença do clique do mouse com y do inicio da imagem*/

    public:
        /**
        * @brief Construtor da classe ImageManager.
        * @param numImages O número de imagens a serem carregadas.
        */
        ImageManager(int numImages);

        /**
        * @brief Destrutor da classe ImageManager.
        */
        virtual ~ImageManager();

        /**
        * @brief Verifica se há uma imagem selecionada.
        * @return True se houver uma imagem selecionada, False caso contrário.
        */
        bool temImagemselecionada();

        /**
        * @brief Renderiza o gerenciador de imagens na tela.
        */
        void Render();

        /**
        * @brief Carrega imagens na tela.
        */
        void carregarImagem();

        /**
        * @brief Chama a funcao de da classe Bmp que faz a rotação horizontal da imagem.
        */
        void rotacaoHorizontal();

        /**
        * @brief Chama a funcao de da classe Bmp que faz a rotação vertical da imagem.
        */
        void rotacaoVertical();

        /**
        * @brief Define a variável que permite exibição de imagem em canais RGB seperados e escala cinza como True.
        */
        void exibirCanaisRGB();

        /**
        * @brief Define a variável que permite exibição dos histogramas da imagem como True.
        */
        void exibirHistograma();

        /**
        * @brief Verifica se houve um clique do mouse em alguma imagem.
        * @param mx Coordenada x do clique do mouse.
        * @param my Coordenada y do clique do mouse.
        */
        void verificaClique(int mx, int my);

        /**
        * @brief Move a imagem selecionada com o mouse.
        * @param x Coordenada x do movimento do mouse.
        * @param y Coordenada y do movimento do mouse.
        */
        void Motion(int x, int y);

};

#endif // IMAGEMANAGER_H
