#pragma once
#include <memory>
#include <vector>

class SceneController;
struct Input;

// fade in out �̍ۂɎg�p
enum class Fade
{
	In,
	Out,
	Max
};

class BaseScene
{
public:
	BaseScene(SceneController& sCon);
	~BaseScene();

	virtual void UpDate(const std::vector<std::shared_ptr<Input>>& input) = 0;
	virtual void Initialize(void) = 0;
	virtual void Draw(void) = 0;

	static void SetLoadSize(int size);
	static int& GetLoadSize(void)
	{
		return loadSize_;
	}

private:
	
protected:
	SceneController& sceneCtl_;
	static int loadSize_;

	// ̪��޲݂Ʊ�Ă̐؂�ւ�
	Fade fade_;
};

