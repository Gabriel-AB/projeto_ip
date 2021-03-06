#include <raylib.h>
#include "tela.h"
#include "define.h"

void telaCheia()
{
    if(!is_fullscreen){
        larguraAnterior = GetScreenWidth();
        alturaAnterior = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    }
    ToggleFullscreen();

    if(is_fullscreen){
        SetWindowSize(larguraAnterior, alturaAnterior);
        SetWindowPosition(tela.x, tela.y);
    }
    is_fullscreen = !is_fullscreen; 
    
    tela.width = GetScreenWidth();
    tela.height = GetScreenHeight();
}

void atualizarCamera(Camera2D *cam, Vector2 posicao)
{
    cam->target.x = 0.9*cam->target.x + 0.1*posicao.x;
    cam->target.y = 0.9*cam->target.y + 0.1*posicao.y;

    #ifdef __WIN32
        cam->offset.x = tela.width/2  -cam->target.x;
        cam->offset.y = tela.height/2 -cam->target.y;
    #endif
}

void verificarTamanhoTela(){
    if(IsWindowResized()){
        tela.width = GetScreenWidth();
        tela.height = GetScreenHeight();
    }
}

//-------------- HUD ---------------//

void drawHUD(int quantidadeVida, int quantidadeArrow){
    for (int i = 0; i < quantidadeVida; i++)
    {
        DrawTexture(vidaTexture, 10+35*i, 10, WHITE);
    }

    for (int i = 0; i < quantidadeArrow; i++)
    {
        DrawTexture(arrowTexture, 10+35*i, 50, WHITE);
    }
}

//-------------- TEXTURE ---------------//

void setTexture(Texture* texture, char* spritePath, int largura, int altura) {
    Image imagem =  LoadImage(spritePath);
    ImageResize(&imagem, largura , altura);
    *texture = LoadTextureFromImage(imagem);
    UnloadImage(imagem);
}

void setTextureCropped(Texture* texture, char* spritePath, Rectangle crop) {
    Image imagem = LoadImage(spritePath);
    ImageCrop(&imagem, crop);
    *texture = LoadTextureFromImage(imagem);
    UnloadImage(imagem);
}


// ------------ SHADERS ----------- //

void setShader(char* shaderPath){
    shader = LoadShader(0, shaderPath);
}


//-------------- FONT ---------------//

void setFont(char* fontPath) {
    font = LoadFont(fontPath);
}


// ------------- CÂMERA ----------- //

void setTargetCamera(Personagem *target)
{
    cam.zoom = 3;
    cam.rotation = 0;
    cam.target = target->posicao;
    cam.offset = (Vector2){0,0};
    cam.offset = (Vector2){tela.width/2 , tela.height/2};
}

