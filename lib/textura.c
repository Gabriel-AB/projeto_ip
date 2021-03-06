#include <raylib.h>
#include "tela.h"
#include "textura.h"

Sprite spriteConstructor(const char *endereco, int largura_frame, int altura_frame, int fps){
    Sprite sprite;
    sprite.textura = LoadTexture(endereco);
    sprite.fps = fps;

    sprite.colunas = sprite.textura.width/altura_frame;
    sprite.linhas = sprite.textura.height/largura_frame;
    sprite.frameAtual = 0;
    sprite.recorte = (Rectangle){ 0,  0,  largura_frame,  altura_frame};

    return sprite;
}
//Anima de forma continua um sprite linha
void animaSpriteLinha(Sprite *sprite){
    if(!sprite->fps) sprite->fps = 1;
    
    if(TEMPO - sprite->timer > 1/sprite->fps){
        sprite->timer = TEMPO;
        sprite->frameAtual++;
        sprite->recorte = (Rectangle){
            sprite->frameAtual * sprite->textura.width/sprite->colunas , 
            0, 
            sprite->textura.width / sprite->colunas, 
            sprite->textura.height / sprite->linhas
        };
    }
    if(sprite->frameAtual >= sprite->colunas) sprite->frameAtual = 0;
}

// Animação geral para sprite dentro de um spritesheet  vide textura.h
// Lê da esquerda para a direita no segmento dado.
void animaSprite(Sprite *sprite, Segmento segmento[]){
    if(!sprite->fps) sprite->fps = 1;

    if(sprite->frameAtual < segmento[sprite->n_segmento].inicio) {
        sprite->frameAtual = segmento[sprite->n_segmento].inicio;
    }

    if(TEMPO -sprite->timer > 1/sprite->fps){
        sprite->timer = TEMPO;
        sprite->frameAtual++;

        sprite->recorte.x = sprite->frameAtual * sprite->recorte.width;
        sprite->recorte.y = segmento[sprite->n_segmento].linha * sprite->recorte.height;

    }
    if(sprite->frameAtual >= segmento[sprite->n_segmento].fim){
        sprite->frameAtual = segmento[sprite->n_segmento].inicio;
    }
}