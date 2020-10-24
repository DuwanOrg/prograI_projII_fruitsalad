#include "salad.h"

Area::Area()
{
	x=0;
	y=0;
	ancho=0;
	alto=0;
}

Area::Area(int x, int y, int ancho, int alto)
{
	this->x=x;
	this->y=y;
	this->ancho=ancho;
	this->alto=alto;
}

bool Area::mouseClick(int mx, int my)
{
	if (mx >= x && mx <= x+ancho-1)
		if (my >= y && my <= y+alto-1) {
			this->mx= mx;
			this->my= my;
			return true;
		}
	mx=-1;
	my=-1;
	return false;
}

void Boton::dibujar()
{
	ImagenDeArchivo::dibujar();//llama el metodo heredado de la clase padre
	int midx = x + ancho/2;
	int midy = y + alto/2+5;
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(EUROPEAN_FONT,HORIZ_DIR,3);
	outtextxy(midx,midy,texto);//escibe el texto del boton si es que lo tiene.
}

Regla::Regla(int v1, int v2, int v3){
	r1Orig=v1;
	r2Orig=v2;
	r3Orig=v3;
	r1Nuev=0;
	r2Nuev=0;
	r3Nuev=0;
}
int Regla::aplicartransformacion(int val){
	 if(val==1){
	 	int resp = rand()%2+1
	 }
}
void Regla::transformarRegla(){
	if(r1Orig!=0)
	aplicartransformacion(r1Orig);
	
	if(r2Orig!=0)
	aplicartransformacion(r2Orig);
	
	if(r3Orig!=0)
	aplicartransformacion(r3Orig);
}
