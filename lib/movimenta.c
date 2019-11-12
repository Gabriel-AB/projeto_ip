#include "movimenta.h"

void movimentarV(Vector2 *coisa){
    if(IsKeyDown(KEY_W)) coisa->y -= 2;
    if(IsKeyDown(KEY_S)) coisa->y += 2;
    if(IsKeyDown(KEY_A)) coisa->x -= 2;
    if(IsKeyDown(KEY_D)) coisa->x += 2;
}

void movimentar(Personagem *fulano, Rectangle *MAPA, float *angle){

    aplicarInercia(fulano);
    atualizarColisao(fulano);

    int naoColisaoCima = !colisaoCima(fulano,MAPA);
    int naoColisaoBaixo = !colisaoBaixo(fulano,MAPA);
    int naoColisaoEsquerda = !colisaoEsquerda(fulano,MAPA);
    int naoColisaoDireita = !colisaoDireita(fulano,MAPA);
    
    if(fulano->velocidade.y > -VELOCIDADE_MAX && naoColisaoCima)
    {
        if(IsKeyDown(KEY_W)) {
            fulano->velocidade.y += -ACELERACAO;
            *angle = 0;
        }
    }

    if(fulano->velocidade.y < VELOCIDADE_MAX && naoColisaoBaixo)
    {
        if(IsKeyDown(KEY_S)) {
            fulano->velocidade.y += ACELERACAO;
            *angle = 180;
        }
    }

    if(fulano->velocidade.x > -VELOCIDADE_MAX && naoColisaoEsquerda)
    {
        if(IsKeyDown(KEY_A)) {
            fulano->velocidade.x += -ACELERACAO;
            *angle = 270;
        }
    }

    if(fulano->velocidade.x < VELOCIDADE_MAX && naoColisaoDireita)
    {
        if(IsKeyDown(KEY_D)) {
            fulano->velocidade.x += ACELERACAO;
            *angle = 90;
        }
    }


    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) {
        *angle = 45;
    }

    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) {
        *angle = 315;
    }

    if(IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) {
        *angle = 135;
    }

    if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) {
        *angle = 225;
    }

    aplicarAtrito(fulano,TAXA_ATRITO);

}
//atualiza caixas de colisao
void atualizarColisao(Personagem *fulano){
    fulano->linhaColisaoCima =                          //  X========
        (Rectangle){                                    //  |       |
            fulano->position.x - fulano->largura/2 +2,  //  |   .   |
            fulano->position.y - fulano->altura/2 -1,   //  |       |
            fulano->largura -4, 1                       //  ---------
        };

    fulano->linhaColisaoBaixo =                         //  ---------
        (Rectangle){                                    //  |       |
            fulano->position.x - fulano->largura/2 +2,  //  |   .   |
            fulano->position.y + fulano->altura/2,      //  |       |
            fulano->largura -4, 1                       //  X========
        };

    fulano->linhaColisaoEsquerda  =                     //  --------X
        (Rectangle){                                    //  |       H
            fulano->position.x -fulano->largura/2 -1,   //  |   .   H
            fulano->position.y -fulano->altura/2 +2,    //  |       H
            1, fulano->altura -4                        //  --------H
        };

    fulano->linhaColisaoDireita =                       //  X--------
        (Rectangle){                                    //  H       |
            fulano->position.x + fulano->largura/2,     //  H   .   |
            fulano->position.y - fulano->altura/2 +2,   //  H       |
            1, fulano->altura -4                        //  H--------
        };
}

//aplica a velocidade a posicao do personagem
void aplicarInercia(Personagem *fulano){
    fulano->position.x += fulano->velocidade.x;
    fulano->position.y += fulano->velocidade.y;
}

//Reduz a velocidade do personagem conforme a taxa de atrito
void aplicarAtrito(Personagem *fulano, float taxa){

    if(fulano->velocidade.x > 0.1) fulano->velocidade.x -= taxa;
    else if(fulano->velocidade.x < -0.1) fulano->velocidade.x += taxa;
    else fulano->velocidade.x = 0;

    if(fulano->velocidade.y > 0.1) fulano->velocidade.y -= taxa;
    else if(fulano->velocidade.y < -0.1) fulano->velocidade.y += taxa;
    else fulano->velocidade.y = 0;
}

//zera a velocidade para cima caso haja uma colisao
int colisaoCima(Personagem *fulano, Rectangle *MAPA){
    for(int i = 0;i < TAM_MAPA; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoCima, MAPA[i]) )
        {
            colideCima = GREEN;//temporario
            if(fulano->velocidade.y < 0)
            {
                fulano->velocidade.y = 0;
            }
            return 1;
        }
    }
    colideCima = RED;//temporario
    return 0;
}

//zera a velocidade para baixo caso haja uma colisao
int colisaoBaixo(Personagem *fulano, Rectangle *MAPA){
    for(int i = 0;i < TAM_MAPA; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoBaixo, MAPA[i]) )
        {
            colideBaixo = GREEN;//temporario
            if(fulano->velocidade.y > 0)
            {
                fulano->velocidade.y = 0;
            }
            return 1;
        }
    }
    colideBaixo = RED; //temporario
    return 0;
}

//zera a velocidade para a esquerda caso haja uma colisao
int colisaoEsquerda(Personagem *fulano, Rectangle *MAPA){
    for(int i = 0;i < TAM_MAPA; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoEsquerda, MAPA[i]) )
        {
            colideEsq = GREEN;//temporario
            if(fulano->velocidade.x < 0)
            {
                fulano->velocidade.x = 0;
            }
            return 1;
        }
    }
    colideEsq = RED;//temporario
    return 0;
}

//zera a velocidade para a direita caso haja uma colisao
int colisaoDireita(Personagem *fulano, Rectangle *MAPA){
    for(int i = 0;i < TAM_MAPA; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoDireita, MAPA[i]) )
        {
            colideDir = GREEN;//temporario
            if(fulano->velocidade.x > 0)
            {
                fulano->velocidade.x = 0;
            }
            return 1;
        }
    }
    colideDir = RED;//temporario
    return 0;
}