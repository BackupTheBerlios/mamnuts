/* ************************************************************
 * tmore for Mamnuts
 * Mamnuts - http://mamnuts.blogspot.com (c) Mind Booster Noori
 *
 * Based on:
 * tmore - copywrite (c) PPires Duarte - 2006 xppires@gmail.com
 * based on transilvania2000 - http://trans.pione.net
 * nuts 332 
 * ***********************************************************/
 
#define MOREVER "1.0.1 Mar 2k" 
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <sys/time.h> 
#include <time.h> 
#include "defines.h"
#include "globals.h"
#include "commands.h"
#include "prototypes.h"
#include "tmore.h"


/********************************************* 
	Stuff to be used by buffer 
**********************************************/   

/******************  
  alloc buffer  
 ******************/ 
BU_OBJ create_buf() 
{ 
BU_OBJ buf; 

 
if ((buf=(BU_OBJ)malloc(sizeof(struct buf_struct)))==NULL) { 
	write_syslog(SYSLOG,0,"ERROR: Memory allocation failure in create_buf().\n"); 
	
	return NULL; 
	} 
 
/* Append object into linked list. */ 
if (buf_first==NULL) {   
	buf_first=buf;  buf->prev=NULL;   
	} 
else {   
	buf->prev=buf_last; buf_last->next=buf;     
	} 
buf->next=NULL; 
buf_last=buf; 
 
if ((buf->ini=malloc(NBB+2))==NULL){ 
	write_syslog(SYSLOG,0,"Error creating buffer_more\n"); 
	return NULL; 
	} 
buf->pos=buf->ini; 
buf->pd=0; 
buf->sock=0; 
buf->bc=0; 
buf->more=13; 
 
return buf; 
} 

 
/*** Puts more info on separator ***/ 
int V_more(BU_OBJ b,int mode){ 
 int go=0; 
 char vis[40]; 
	if ( b->pos - b->ini == 0 ){  
		if ( b->more !=0  || mode==1) { 
			sprintf(vis,"7[22;3H[1m[34m--------[0m8"); 
	   		b->more=0; 
	   		go=1; 
	   		} 
	  	} else { 
	  		if ( b->more !=1 || mode==1 ) {	 
	  			sprintf(vis,"7[22;3H[1m[31m[07m[ More ][0m8"); 
				b->more=1; 
	   			go=1; 
	   			} 
	   		} 
	if(go) write(b->sock,vis,strlen(vis)); 
return 1;	 
} 


 
/**********************  
   Looks for a page   
 **********************/  
int find_pag(BU_OBJ b){ 
   int linha=1,pos=0; 
   char *c; 
 
   	c=b->ini; 
	while((int)(c) < (int)(b->pos)){ 
	 	if (*c++ == '\n' )  linha++ ; 
	 	if (linha > 20) return pos; 
	 	pos++; 
	 	} 
	return pos; 
} 


 
/*************************************** 
  Send a page to user's screen 
 ***************************************/ 
void envia_pagina(BU_OBJ b){ 
int len; 
 
	/* identifica 1 pagina  */ 
	len=find_pag(b);	 
	 
	if (len>0) {	 
		write(b->sock,"7[1;21r[21;1H",16);   /*  <janela>  */ 
				 
		/* Envia uma pagina para Socket */ 
		write(b->sock,b->ini,len); 
	 
		write(b->sock,"[23;r8",8);       /*  <janela>  */ 
		 
		/* Indexa o Buffer do More  */ 
		memcpy(b->ini,b->ini+len,b->pos-(b->ini+len) ); 
		b->pos -= len; 
		} 
}  


 
/********************************* 
	Tira do Buffer  
**********************************/ 
void debufferiza(){ 
BU_OBJ b; 
 
	b=buf_first; 
	if (b == NULL) return;
	while(b){ 
		if (b->pd== 1 && b->bc==0) { 
			envia_pagina(b); 
			V_more(b,0); 	/* [more]  */ 
			b->pd=0; 
			}		 
		b=b->next; 
		continue;  
		} 
} 

 
/*********************************** 
	Procura Buffer 
 ***********************************/ 
 BU_OBJ find_buffer(int s){ 
 BU_OBJ b; 
 	for(b=buf_first;b!=NULL;b=b->next) if (b->sock==s ) return b; 
 	return NULL; 	  
 } 
  
 /********************************** 
	Coloca no Buffer o texto 
  **********************************/ 

void bufferiza(BU_OBJ b,const char *str,int len){ 
int pos=0; 

	b->bc=1; /* Buffer Rules on */	 
	while(pos <len){ 
		*b->pos++ = *str++; 
		pos++; 
		/* Caso termine o buffer envia uma pagina */ 
		if ( b->pos - b->ini >= NBB ) { 
			envia_pagina(b); 
			b->pd=0; 
			} 
			 
		} 
		 
	if (b->pd==1 && b->bc==0){ 
		envia_pagina(b); 
		b->pd=0; 
		}     
	b->bc=0; 			/* Buffer Rules off */ 
	V_more(b,0); 			/* visualiza [more] */ 
	}  
 
/****************************** 
	Despeja Buffer 
 ******************************/ 
void despeja_buffer(BU_OBJ b){ 
   int len=0; 
   char *c; 
   char *cf; 
    
   	c=b->ini; 
   	cf=b->pos; 
   	 
   	write(b->sock,"7[1;r8",9); /* mete Janela ok */ 
	while(c <cf ){ 
 		if (cf - c < OUT_BUFF_SIZE) len= cf - c;  
 			else len= OUT_BUFF_SIZE; 
 		write(b->sock,c,len); 
		c +=len; 
		} 
	write(b->sock,"7[1;r8",9); /* mete Janela ok */ 
	b->sock= -1; 
	free(b->ini); 
	b->ini=NULL; 
	 
	/* indexando */ 
	if(b==buf_first){ 
		buf_first=b->next; 
		if (b==buf_last) buf_last=NULL; 
			else buf_first->prev=NULL; 
		} 
	else{ 
		b->prev->next=b->next; 
		if (b== buf_last) { 
			buf_last=b->prev;  buf_last->next=NULL; 
			} 
		else b->next->prev=b->prev;	 
		} 
	free(b); 
} 
 
/***  Coloca Barra no ecran  ***/ 
void poem_barra(int sock){ 
BU_OBJ b; 

         
 
	sprintf(texto,"7[22;1H[1m[34m+---------- %.12s ----------------------------------------- [32m %2d [1m[5m:[0m[1m[32m %2d [1m[34m-+[0m8",TALKER_NAME,thour,tmin);    
	write(sock,texto, strlen(texto) ); 
	if ((b=find_buffer(sock))!=NULL) V_more(b,1); 
} 


/* after login do visual initial */
void  inicia_visual(user)
UR_OBJECT user;
{
 BU_OBJ b; 

	if (user->visual ==0 ) return;

	write_user(user,"~OL~FRVisual ON.\n~OL~FR~LIIf you will have problems with this type of visualizacao \n~OL~FR~LI .visual Executa to desactivar this function \n\n\n\n\n"); 
 	poem_barra(user->socket); 
    
	/* buffermore 13 */ 
	if ((b=create_buf())!=NULL) { 
		b->sock=user->socket; 
		write_sock(b->sock," [23;r 8");
		} else {  
			user->visual=0;  
			write_user(user,"~OL~FR~LISystem: little memoria .\n");  
			return; 
			} 

}



/*** Toggle user chat window  on and off ***/ 
void visual(user,mode) 
UR_OBJECT user; 
int mode; 
{ 
BU_OBJ b; 
/*
if (user->ixweb ){
	user->visual=0;
	write_user(user,"~OL~FTVisual ~FROFF.\n");
	return; 
	}
*/

if (user->visual==1 && mode < 2) { 
        user->visual=0; 
	if ( (b=find_buffer(user->socket)) ) despeja_buffer(b); 
	write(b->sock,"7[1;r8",9);	 
	write_user(user,"~OL~FTVisual ~FROFF.\n");   
	} 
else { 

	user->visual=1;
	inicia_visual(user);
 
	} 
} 
 

