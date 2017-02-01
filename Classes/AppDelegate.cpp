#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "LogoScene.h"
#include "MenuScene.h"

//static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size designResolutionSize = cocos2d::Size(320, 480);
static cocos2d::Size smallResolutionSize = cocos2d::Size(1080, 1920);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1440, 2560);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1600, 2560);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	//if (!glview) {
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	//		glview = GLViewImpl::createWithRect("avoidGame", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
	//#else
	//		glview = GLViewImpl::create("avoidGame");
	//#endif
	//		director->setOpenGLView(glview);
	//}

	if (!glview) {
		glview = GLViewImpl::create("My Game");
		director->setOpenGLView(glview);
	}

	// 1. 사용자가 디자인하는 해상도 --> 비율 정의 STD_DIV_WH
	// 2. 디바이스의 최대 사이즈 --> 비율 정의 DVI_DIV_WH
	// 3. 사용자가 디자인하는 해상도가 크다면 (디바이스의 최대 사이즈가 더 작다면)
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);

	//1.
	auto _width = 1080;
	auto _height = 1920;
	float custom_ratio = (_width / _height);

	//2.
	auto screenSize = glview->getFrameSize();
	float screen_ratio = (screenSize.width/screenSize.height);

	//3.
	if (custom_ratio > screen_ratio) {
		director->setContentScaleFactor(screenSize.width / _width);
	}

	//std::vector <std::string> searchPaths;
	//cocos2d::FileUtils::getInstance()->setSearchPaths(searchPaths);

	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / 60);
	register_all_packages();

	// create a scene. it's an autorelease object
	auto scene = MenuScene::createScene();	
	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}