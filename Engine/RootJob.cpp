#include "RootJob.h"
#include "../PlayScene.h"
RootJob::RootJob()
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	/*PlayScene* pPlayScene;
	pPlayScene = new PlayScene(this);

	pPlayScene->Initialize();
	childList_.push_back(pPlayScene);*/
	Instantiate<PlayScene>(this);
}

void RootJob::Update()
{

}

void RootJob::Draw()
{
	//for (auto& e : childList_)
		//e->Draw();//全部たどる
}

void RootJob::Release()
{
}
