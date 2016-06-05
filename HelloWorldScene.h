#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"



class HelloWorld : public cocos2d::Layer
{
private:
	//cocos2d::CCSpriteBatchNode * _batchNode;
	//cocos2d::CCSprite * _ship;
	
	cocos2d::Sprite *puntoVerde;
	cocos2d::Sprite *oscuridad;
	cocos2d::Sprite *explosion;
	cocos2d::Sprite *fondo;
	cocos2d::Label *label;
	float _shipPointsPerSecY;
	int puntaje=0;
	float AN;
	float AL;
	float degradado=250;


	void update(float x, float y);
	void crearViento();
	void crearFuego();
	void crearAgua();
	void crearLuz();
	void crearTierra();
	void crearPlanta();
	
	
	
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void  onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);
};

#endif // __HELLOWORLD_SCENE_H__