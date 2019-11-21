#include <raylib.h>
#include "tela.h"
#include "define.h"

void telaCheia()
{
    if(!is_fullscreen){
        telaAnterior.width = GetScreenWidth();
        telaAnterior.height = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    }
    ToggleFullscreen();

    if(is_fullscreen){
        SetWindowSize(telaAnterior.width, telaAnterior.height);
        SetWindowPosition(tela.x, tela.y);
    }
    is_fullscreen = !is_fullscreen; 
    
    tela.width = GetScreenWidth();
    tela.height = GetScreenHeight();
}
// (Rectangle){tela.width/4, tela.height/4 ,tela.width/2, tela.height/2};

//Camera segue o target quando o mesmo tenta sair do retangulo dado
//(WINDOWS)
void cameraSegue(Camera2D *cam, Rectangle rec)
{
    if(cam->target.x + cam->offset.x < rec.x) cam->offset.x   += VEL_MAX_PERSONAGEM;
    if(cam->target.y + cam->offset.y < rec.y) cam->offset.y  += VEL_MAX_PERSONAGEM;

    if(cam->target.x + cam->offset.x > rec.x + rec.width) cam->offset.x    -= VEL_MAX_PERSONAGEM;
    if(cam->target.y + cam->offset.y > rec.y + rec.height) cam->offset.y   -= VEL_MAX_PERSONAGEM;
}

//-------------- BACKGROUND ---------------//
void setImageBackground(char* imagePath) {
    pathImageBackground = imagePath;
}

void updateBackground() {
    Image backgroundImage = LoadImage(pathImageBackground);
    ImageResize(&backgroundImage, tela.width, tela.height);  
    background = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);
}


//-------------- HUD ---------------//

void setVidaSprite(char* spritePath){
    Image vidaImage =  LoadImage(spritePath);
    ImageResize(&vidaImage, 30 , 30);
    vida = LoadTextureFromImage(vidaImage);
    UnloadImage(vidaImage);
}


void drawHUD(int quantidadeVida){
    for (int i = 0; i < quantidadeVida; i++)
    {
        DrawTexture(vida, 10+35*i, 10, GRAY);
    }
}