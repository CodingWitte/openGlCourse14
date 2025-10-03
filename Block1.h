#pragma once
#ifndef Block_CLASS_H
#define BLOCK_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include"Texture.h"
#include"VBO.h"
#include"VAO.h"
#include"EBO.h"



Texture* TEXarray;
VAO* VAOarray;
VBO* VBOarray;
EBO* EBOarray;
int* activeTex;
int numOfRendBlocks;

int NODT; // Number of different Textures // temporary
Block(int* posAndOrien, int blockType);
void addBlocks(int numberOfaddedBlocks);
void createBlock(int* posAndOrien, int block);
GLfloat* coordToVert(int* posAndOrie);
void drawBlocks();
void delEverything();

#endif
//ballad of the beaconsfield miners