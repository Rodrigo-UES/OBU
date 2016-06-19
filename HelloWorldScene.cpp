#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <unistd.h>

#include "Nivel2.h"
#include "sqlite3.h"
USING_NS_CC;

Scene* HelloWorld::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    pdb=NULL;//1
    std::string path= FileUtils::getInstance()->getWritablePath()+"obu.s3db";//2

    
    
    result=sqlite3_open(path.c_str(),&pdb);//3
    if(result!=SQLITE_OK)
    {
        CCLOG("open database failed,  number%d",result);
    }

    sql="create table game(ID text primary key,puntaje text,nivel integer)";//1
    result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);//1
    if(result!=SQLITE_OK)
        CCLOG("create table failed");




//sqlite3_close(pdb);
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


	cerrar = Sprite::create("CloseSelected.png"); 
	cerrar->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

   	addChild(cerrar);
   	
   	//felicidades = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
   	//felicidades->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
   	
   	
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    label = Label::createWithTTF("puntaje: 0", "fonts/Marker Felt.ttf", 20);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(40,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
	salud = Label::createWithTTF("Salud", "fonts/Marker Felt.ttf", 25);   
    salud->setPosition(Vec2(50,230));
    
    this->addChild(salud, 2);
    
    numNivel = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 25);  
    
     
    Size TM = Director::getInstance()->getWinSize();

    AN = TM.width;
    AL = TM.height;
    
    CCLOG("alto: %f  ancho: %f",AL,AN);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Elementos.plist");
    
    fondo = Sprite::createWithSpriteFrameName("cielo.png");
    fondo->setPosition(Vec2(225, 150));
    fondo->setScaleY(AL*1.0/fondo->getContentSize().height);
    fondo->setScaleX(AN*1.1/fondo->getContentSize().width);
	addChild(fondo);
	
	
	BarraVertical = Sprite::createWithSpriteFrameName("barra.png");
    BarraVertical->setPosition(Vec2(105, 150));
    //BarraVertical->setScaleY(AL*0.8/BarraVertical->getContentSize().height);
    //BarraVertical->setScaleX(AN*0.08/BarraVertical->getContentSize().width);
    BarraVertical->setScale(AL*1.1/BarraVertical->getContentSize().height);
	addChild(BarraVertical);	
	
	/*BarraHorizontal = Sprite::createWithSpriteFrameName("barra 2.png");
    BarraHorizontal->setPosition(Vec2(105, 250));
    BarraHorizontal->setScale(AL*0.07/BarraHorizontal->getContentSize().height);
	addChild(BarraHorizontal);*/

  	Spausa = Sprite::createWithSpriteFrameName("botonPausa.png");
    Spausa->setPosition(Vec2(134, 25));
    Spausa->setScale(AL*0.05/Spausa->getContentSize().height);
	addChild(Spausa);
  
	explosion = Sprite::createWithSpriteFrameName("explosion.png");
 	//explosion->setAnchorPoint(Vec2(0.1, 0.1));
	explosion->setPosition(Vec2(110, 110));
   	explosion->setScale(AL*0.2/explosion->getContentSize().height);
   	explosion->setVisible(false);
   	fondo:addChild(explosion);
	 
	
	vida1 = Sprite::createWithSpriteFrameName("vida+1.png");
 	//explosion->setAnchorPoint(Vec2(0.1, 0.1));
	vida1->setPosition(Vec2(50, 180));
   	vida1->setScale(AL*0.15/vida1->getContentSize().height);
   	addChild(vida1);
	   
	vida2 = Sprite::createWithSpriteFrameName("vida+2.png");
 	//explosion->setAnchorPoint(Vec2(0.1, 0.1));
	vida2->setPosition(Vec2(50, 160));
   	vida2->setScale(AL*0.15/vida2->getContentSize().height);
   	
   	addChild(vida2);  
	
	vida3 = Sprite::createWithSpriteFrameName("vida+3.png");
 	//explosion->setAnchorPoint(Vec2(0.1, 0.1));
	vida3->setPosition(Vec2(50, 140));
   	vida3->setScale(AL*0.15/vida3->getContentSize().height);
   	
   	addChild(vida3);
   	
   	
   	nivel = Sprite::createWithSpriteFrameName("hexagono vida.png");
 	nivel->setPosition(Vec2(50, 80));
   	nivel->setScale(AL*0.2/nivel->getContentSize().height);
   	
   	addChild(nivel);
   	
   	numNivel->setPosition(Vec2(50,80));
    
    this->addChild(numNivel, 3);
	
	dark.reserve(6);
	light.reserve(3);
	
	for (int i=2;i < dark.capacity()+4; i++){
		
		if(i%2==0){
			ranOXmin+=(AN-130)/10;
			ranOXmax = ranOXmin+20;
			
			CCLOG("minimo X: %i",ranOXmin);

		}else{
			ranOXmin+=(AN-130)/10 +5;
			ranOXmax= ranOXmin+15;

			CCLOG("minimo X: %i",ranOXmin);
		}

		ranx = cocos2d::RandomHelper::random_int(ranOXmin, ranOXmax);
		rany = cocos2d::RandomHelper::random_int(30, 275);	
		
		
	if(i==3 || i== 6 || i==9){
		
		luz = Sprite::createWithSpriteFrameName("luz.png");
    	//luz->setAnchorPoint(Vec2(0.1, 0.1));
		luz->setPosition(Vec2(ranx, rany));
    	luz->setScale(AL*0.1/luz->getContentSize().height);
    	luz->setTag(i);
    
    	light.push_back(luz);
    
		addChild(luz);	
		
	}else
	{
		oscuridad1 = Sprite::createWithSpriteFrameName("oscuridad.png");
    	//oscuridad1->setAnchorPoint(Vec2(0.1, 0.1));
		oscuridad1->setPosition(Vec2(ranx, rany));
    	oscuridad1->setScale(AL*0.1/oscuridad1->getContentSize().height);
    	oscuridad1->setTag(i);
    
    	dark.push_back(oscuridad1);
    
		addChild(oscuridad1);	
	}
   	
		
	}
	
	obu = Sprite::createWithSpriteFrameName("obu.png");
    obu->setAnchorPoint(Vec2(0.1, 0.1));
	obu->setPosition(Vec2(125, 200));
    obu->setScale(AL*0.1/obu->getContentSize().height);
    
    addChild(obu);
   	
   	 obuPausa = Sprite::createWithSpriteFrameName("obu.png");
     obuPausa->setAnchorPoint(Vec2(0.1, 0.1));
	 obuPausa->setPosition(Vec2(200, 100));
     obuPausa->setScale(AL*0.1/obu->getContentSize().height);
     obuPausa->setVisible(false);
    
	 addChild(obuPausa);
	 
	 siguiente = Sprite::createWithSpriteFrameName("siguiente.png");
     siguiente->setAnchorPoint(Vec2(0.1, 0.1));
	 siguiente->setPosition(Vec2(125, 100));
     siguiente->setScale(AL*0.2/obu->getContentSize().height);
     siguiente->setVisible(false);
    
	 addChild(siguiente);
	 
	 
	 SPausa = Sprite::createWithSpriteFrameName("pausa.png");
	 SPausa->setAnchorPoint(Vec2(0.1, 0.1));
	 SPausa->setPosition(Vec2(AN/2 - 40, AL/2+50));
	 SPausa->setScale(AL*0.3/SPausa->getContentSize().height);
	 SPausa->setVisible(false);
	    	
	 addChild(SPausa);
	 
	 CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/explo.mp3");
	

	

	/*FUNCION DE LLAMADO Y GENERADOR DE EVENTO DEL ACELEROMETRO*/
	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	
	
	
	
	
	CCLOG("SE TERMINO EL INIT");
	
    return true;
}




/*comienza metodo de acelerometro*/
void HelloWorld::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
    
    /*posX y posY obtienen la variable acelerometro al imprimir esta devuelve un valor entre 0 y 1*/
    float posX= acc->x;
	float posY =acc->y;	


	/*obtengo el tama�o de la pantalla*/
	Size screenSize = Director::getInstance()->getWinSize();

    float w = screenSize.width;
    float h = screenSize.height;
    
  
         
   	   
   	   
   	if(puntaje!=3 && vida>0 && pausa==0)   {
   		obu->setVisible(true);
   		SPausa->setVisible(false); 
   		siguiente->setVisible(false); 
   		obuPausa->setVisible(false); 
   		
		   /*obtengo la posicion actual de la figura*/	
   		 float X = obu->getPosition().x;
    	 float Y = obu->getPosition().y;
    
    	
    	/*caculo el movimiento y velocidad de la figura posicion, actual mas el movimiento generado*/
    	X = X + (posX* w *0.03);
    	Y = Y + (posY* h *0.03);
    	
    	 CCLOG("aca es X: %f", X);
   	     CCLOG("aca es Y: %f", Y);
   		
   		/*condicion que restringe el movimiento no se puede salir de estos margenes si eso sucede la figura no se mueve*/
   		  if(   (X<AN-25 && Y<AL-40)  && (X>115 && Y>15)  )  {
   		  	
   		  	/*posiciono la figura dentro de los valores obtenidos con la formula anterior*/
    			obu->setPosition(X, Y);
    			
    		/*finaliza los pasos para mover una figura con el acelerometro todo el codigo restante es sobre la logica del juego*/
    			degradado = degradado -10;
    	
    			if(degradado<=0){
    					degradado =0;
    			}
				explosion->setOpacity(degradado);
    		}
    		
    		
    		/*choque con radio*/
    		/*obtengo el tama�o en X y Y de la figura*/
    		float ancho = obu->getScaleX(); 
			float alto = obu->getScaleY();
		
			/*genero una caja del tama�o de la figura eso se hace para identificar el area de choque*/
    		Rect bbObu = obu->getBoundingBox();	

			
			/*funcion que recorre el vector que almacena las figuras de la oscuridad lo hace con un for-each*/
			for(auto sp : dark){	
				
				/*vuelve visibles todos los objetos ya que mas adelante se encuentra una opcion que los oculta*/
				sp->setVisible(true);
				
				/*se obtine el area cuadrada de la oscuridad en el cual se genera un choque*/
				Rect bbOscuridad = sp->getBoundingBox();
				
				/*obtengo la posicion en X y Y de la oscuridad*/
				float X = sp->getPosition().x;
		    	float Y = sp->getPosition().y;
		    	
		    	/*obtengo el centro de la oscuridad solo su centro*/
		    	float r = sp->getScaleX();
		
				/*compruebo si la caja de obu genera un contacto con el area de la oscuridad*/
				if(bbObu.intersectsCircle( Vec2(X, Y) , r+2.0) ){
					
					/*sonido de explosion*/
				    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/explo.mp3");
					degradado =250;
					explosion->setOpacity(degradado);
					
					/*obtengo la posicion actual de obu*/
					float posx = obu->getPosition().x;
					float posy = obu->getPosition().y;
					
					/*vuelvo a obu invisible*/
					obu->setVisible(false);
					/*pone la explosion en la posicion anteriormente obtenida de obu de esta manera se crea el efecto de obu explotando*/
					explosion->setPosition(Vec2(posx, posy));
					explosion->setVisible(true);
				
					/*regresa a obu a la posicion de origen y lo vuelve a la normalidad*/
					obu->setPosition(Vec2(120, 200));
					obu->setVisible(true);
						
					vida--;
					
					if(vida==2){
						vida3->setVisible(false);
					}else if(vida==1){
						vida2->setVisible(false);
					}else if(vida==0){
						vida1->setVisible(false);
						siguiente->setPosition(390, AL/2-80);	
					
						obu->setPosition(200, AL/2-70);
					}
					
				}
	

			}
	
	
			for(auto sp : light){

				Rect bbLuz= sp->getBoundingBox();
			
				float X = sp->getPosition().x;
		    	float Y = sp->getPosition().y;
		    	
		    	float r = sp->getScaleX();
		    		
				
				if(bbObu.intersectsCircle( Vec2(X, Y) , r+2.0) ){
				
				
					if(sp->isVisible()){
						
						sp->setVisible(false);
					
						puntaje++;
			
						std::string punt = StringUtils::format("puntaje: %d",this->puntaje);
					
						label->setString(punt);
						
						if(puntaje==3){
							obu->setPosition(200, AL/2-30);
							
											 		
					   		/*INSERTA EN LA TABLA*/
					   		
					   		   char **re;
				    			int r,c;
				    		
					   		
					   		sqlite3_get_table(pdb,"select * from game",&re,&r,&c,NULL);
					   		
					   		lvl1=r+1;
					   		
					 
					   		std::string llave = StringUtils::format("%d",this->lvl1);
							std::string score = StringUtils::format("%d",this->puntaje);
			
					   		sql="insert into game  values('"+ llave +  "','" + score + "',1)";
					   		    
				    			result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
				    				if(result!=SQLITE_OK)
				        				CCLOG("FALLO DE INSERCION!");
				        	/*INSERTA EN LA TABLA*/
					   		
					   		
					   		/*SACA DE LA BASE*/
					   		 
				    			sqlite3_get_table(pdb,"select * from game",&re,&r,&c,NULL);//1
				    				CCLOG("row is %d,column is %d",r,c);
				
							    for(int i=1;i<=r;i++)//2
							    {
							        for(int j=0;j<c;j++)
							        {
							            CCLOG("%s",re[i*c+j]);
							        }
							    }
							    sqlite3_free_table(re);
							/*SACA DE LA BASE*/
						}
					
					}
	
				
				}
	
			}	
		
	
			Rect Rcerrar = cerrar->getBoundingBox();
			Rect Rpausa = Spausa->getBoundingBox();
			
			/*se comprueba un choque por medio de area de cajas es una deteccion automatica y sensilla*/
			if(bbObu.intersectsRect(Rcerrar)){
				/*de chocar este invoca el metodo de cerrar el juego*/
				HelloWorld::cerrarPantalla();
			}else if(bbObu.intersectsRect(Rpausa)){
				pausa = 1;
				obu->setPosition(X, 175);
			}
    		
   		}else if(vida==0){
 			obu->setVisible(true);
	   		SPausa->setVisible(false); 
	   		obuPausa->setVisible(false); 
	   		
	   		
	   		float XP = obu->getPosition().x;
	   		 XP = XP + (posX* w *0.03);

	   			if(XP>120 && XP<400){
	   				obu->setPosition(XP, AL/2-70);	
	   			}
	   			
    			degradado = degradado -10;
    	
    			if(degradado<=0){
    					degradado =0;
    				}
				explosion->setOpacity(degradado);
	   		
	   		
	   		/*recorre los vectores y elimina los sprite*/
	   		for(auto sp : dark) {
	   			this->removeChild(sp,true);
	   		}
	   		/*elimina el espacio de memoria usado para los sprite*/
	   		dark.erase(dark.begin(),dark.end());	
	   		
	   		for(auto sp: light){
	   			this->removeChild(sp,true);
	   		}
	   		
	   		light.erase(light.begin(),light.end());
	   		
	   			   		
	   		HPV = Sprite::createWithSpriteFrameName("adiosVaquero.png");
	    	//gano->setAnchorPoint(Vec2(0.1, 0.1));
			HPV->setPosition(Vec2(AN/2 +50, AL/2 +70));
	    	HPV->setScale(AL*0.4/HPV->getContentSize().height);
	    	
	    	addChild(HPV);
	    	
	    	
	   		siguiente->setVisible(true); 
	   		
	   		Rect obuP = obu->getBoundingBox();
	   		Rect SPe =  siguiente->getBoundingBox();
	   		
	   		if(obuP.intersectsRect(SPe)){
	   			
	   			HelloWorld::reiniciar();
	   			
	   		}
	   		
	   		
   		
	   	}else if(puntaje==3){
	  
				   		
	   		obu->setVisible(true);
	   		SPausa->setVisible(false); 
	   		obuPausa->setVisible(false); 
	   		
	   		
	   		float X1 = obu->getPosition().x;
	   		 X1 = X1 + (posX* w *0.03);
	   		 
	   			
	   		
	   			if(X1>120 && X1<400){
	   				obu->setPosition(X1, AL/2-30);	
	   			}
	   			
    			degradado = degradado -10;
    	
    			if(degradado<=0){
    					degradado =0;
    				}
				explosion->setOpacity(degradado);
	   		
	   		
	   		
	   		for(auto sp : dark) {
	   			this->removeChild(sp,true);
	   		}
	   		
	   		dark.erase(dark.begin(),dark.end());	
	   		
	   		for(auto sp: light){
	   			this->removeChild(sp,true);
	   		}
	   		
	   		light.erase(light.begin(),light.end());
	   		
	   	
	   		
	   		gano = Sprite::createWithSpriteFrameName("felicitaciones.png");
	    	//gano->setAnchorPoint(Vec2(0.1, 0.1));
			gano->setPosition(Vec2(AN/2 +50, AL/2 +60));
	    	gano->setScale(AL*0.2/gano->getContentSize().height);
	    	
	    	addChild(gano);	
	    	
	    	siguiente->setPosition(390, AL/2-40);	
	   		siguiente->setVisible(true); 
	   		
	   		Rect obuS = obu->getBoundingBox();
	   		Rect Si =  siguiente->getBoundingBox();
	   		
	   		if(obuS.intersectsRect(Si)){
	   			
	   			//std::chrono::seconds duration( 2 ); 
				//std::this_thread::sleep_for( duration );
				//usleep(2000000);
				/*for(float q=0;q<1000000000;q++){
					
				}*/
	   			HelloWorld::siguienteNivel();
	   			
	   		}
	    
	    	
	   	}
	   	else if(pausa==1){
	   		
	   		for (auto sp : dark){
	   			sp->setVisible(false);
	   		}
	   		
	   		obu->setVisible(false);
	   		
	   		float X1 = obuPausa->getPosition().x;
	   		 X1 = X1 + (posX* w *0.03);
	   			
	   			if(X1>120 && X1<400){
	   				obuPausa->setPosition(X1, AL/2-30);	
	   			}
	   		
	   		obuPausa->setVisible(true); 
	   		
	   		siguiente->setPosition(390, AL/2-40);	
	   		siguiente->setVisible(true); 
	   		SPausa->setVisible(true);
	   		
	   		Rect OB = obuPausa->getBoundingBox();
	   		Rect S =  siguiente->getBoundingBox();
	   		
	   		if(OB.intersectsRect(S)){
	   			pausa=0;
	   			 obuPausa->setPosition(Vec2(200, 100));
	   			
	   		}
	   	
	   		
	   	}
   			 

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



void HelloWorld::cerrarPantalla(){
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::reiniciar(){
	auto scene = HelloWorld::createScene();
	Director::getInstance()->pushScene(scene);
}


void HelloWorld::siguienteNivel(){
	auto scene = Nivel2::createScene();
	Director::getInstance()->pushScene(scene);
	}

    /*
    else{
    	
    	
    	if(X>460){
    		auto choqueXD = MoveTo::create(1,Point(X-25,Y));
    		obu->runAction(choqueXD);
    	}else
     	if(X<115){
    		auto choqueXI = MoveTo::create(1,Point(X+25,Y));	
    		obu->runAction(choqueXI);
    	}else
    	if(Y>280){
    		auto choqueYA = MoveTo::create(1,Point(X,Y-25));
    		obu->runAction(choqueYA);
    	}else
    	if(Y<15){
    		auto choqueYAb = MoveTo::create(1,Point(X,Y+25));
    		obu->runAction(choqueYAb);
    	}
  	
    	
    }*/
    
		
		/*
		if(puntaje==20){
			HelloWorld::crearViento();
		}else if(puntaje==30){
			HelloWorld::crearFuego();
		}else if(puntaje==40){
			HelloWorld::crearAgua();
		}else if(puntaje==50){
			HelloWorld::crearLuz();
		}else if(puntaje==60){
			HelloWorld::crearTierra();
		}else if(puntaje==70){
			HelloWorld::crearPlanta();
		}*/
