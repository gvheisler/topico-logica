/*********************************************************************
 * \class Bmp
 * \brief Classe para manipulação de arquivos BMP.
 *
 * A classe Bmp permite carregar, processar e exibir imagens no formato BMP.
 * Ela oferece métodos para carregar uma imagem BMP de um arquivo, processar
 * cores, calcular e desenhar histogramas, realizar rotações na imagem,
 * e renderizar a imagem na tela usando a biblioteca gl_canvas2d.
 *
 * \author Cesar Tadeu Pozzer
 * \date Versão 04/2010
 * Referencia:  http://astronomy.swin.edu.au/~pbourke/dataformats/bmp/
 *
 *********************************************************************/

#ifndef ___BMP__H___
#define ___BMP__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>


#define HEADER_SIZE      14 //sizeof(HEADER) vai dar 16 devido ao alinhamento de bytes
#define INFOHEADER_SIZE  40 //sizeof(INFOHEADER) da 40 e esta correto.
#define uchar unsigned char

typedef struct {
   unsigned short int type;                 /* Magic identifier            */
   unsigned int size;                       /* File size in bytes          */
   unsigned short int reserved1, reserved2;
   unsigned int offset;                     /* Offset to image data em bytes*/
} HEADER;


typedef struct {
   unsigned int size;               /* Header size in bytes      */
   int width,height;                /* Width and height of image */
   unsigned short int planes;       /* Number of colour planes   */
   unsigned short int bits;         /* Bits per pixel            */
   unsigned int compression;        /* Compression type          */
   unsigned int imagesize;          /* Image size in bytes       */
   int xresolution,yresolution;     /* Pixels per meter          */
   unsigned int ncolours;           /* Number of colours         */
   unsigned int impcolours;         /* Important colours         */
} INFOHEADER;

struct CorRGB {
    unsigned char r, g, b;
};

class Bmp
{
private:

    int width, height, imagesize, bytesPerLine, bits;
    unsigned char *data;
    HEADER     header;
    INFOHEADER info;

    void load(const char *fileName);

public:
    CorRGB **matrizCores; /**< Matriz que armazena as cores de cada pixel da imagem */
    enum CanalCor {RED, GREEN, BLUE, GRAY}; /**< Enumeração com os possíeveis valores de canais RGB e cinza. */
    std::vector<int> histogramaRed; /**< Vetor para armazenar o histograma do canal vermelho. */
    std::vector<int> histogramaGreen; /**< Vetor para armazenar o histograma do canal verde. */
    std::vector<int> histogramaBlue; /**< Vetor para armazenar o histograma do canal azul. */
    std::vector<int> histogramaGray; /**< Vetor para armazenar o histograma do canal cinza. */
    int  startX, startY; /**< Coordenadas de início da imagem na tela. */

    /**
    * \brief Construtor da classe. Carrega uma imagem BMP do arquivo especificado.
    * \param fileName O nome do arquivo BMP a ser carregado.
    */
    Bmp(const char *fileName);

    /**
    * \brief Destrutor da classe. Libera a memória alocada para os dados da imagem.
    */
    ~Bmp();

    /**
    * \brief Retorna um ponteiro para os dados da imagem.
    * \return Um ponteiro para os dados da imagem.
    */
    uchar* getImage();

    /**
    * \brief Retorna a largura da imagem.
    * \return A largura da imagem.
    */
    int  getWidth(void);

    /**
    * \brief Retorna a largura da imagem.
    * \return A altura da imagem.
    */
    int  getHeight(void);

    /**
    * \brief Converte a representação da imagem de BGR para RGB.
    */
    void convertBGRtoRGB(void);

    /**
    * \brief Renderiza a imagem na tela.
    * \param x Posição X da imagem na tela.
    * \param y Posição Y da imagem na tela.
    */
    void Render(int x, int y);

    /**
    * \brief Processa as cores da imagem, criando histogramas e convertendo para escala de cinza.
    */
    void processaCores();

    /**
    * \brief Cria um histograma para o canal de cor especificado.
    * \param matrizCores Matriz de cores da imagem.
    * \param width Largura da imagem.
    * \param height Altura da imagem.
    * \param histograma Vetor para armazenar o histograma.
    * \param canal Canal de cor para o qual o histograma será criado.
    */
    void criaHistograma(CorRGB** matrizCores, int width, int height, std::vector<int>& histograma, CanalCor canal);

    /**
    * \brief Desenha o histograma na tela.
    * \param histograma Vetor contendo o histograma.
    * \param canal Canal de cor do histograma.
    * \param startX Posição X inicial do histograma na tela.
    * \param startY Posição Y inicial do histograma na tela.
    */
    void desenhaHistograma(const std::vector<int>& histograma, CanalCor canal, int startX, int startY);

    /**
    * \brief Rotaciona a imagem verticalmente.
    */
    void rotacaoVertical();

    /**
    * \brief Rotaciona a imagem horizontalmente.
    */
    void rotacaoHorizontal();

    /**
    * \brief Desenha as componentes RGB e a imagem em escala de cinza na tela.
    */
    void desenhaRGB();

};

#endif
