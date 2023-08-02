#include"game_level.h"
#include"resource_manager.h"
#include<fstream>
#include<sstream>

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
	//clear oid data
	this->Bricks.clear();
	//load from file
	unsigned int tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int >> tileData;
	if (fstream)
	{
		//std::cout << "打开成功" << std::endl;

		while (std::getline(fstream,line))// 读取关卡文件的每一行
		{
			//std::cout << line << std::endl;
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode) // 读取被空格分隔的每个数字
				row.push_back(tileCode);
			tileData.push_back(row);
			
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}
	else
	{
		std::cout << "关卡打开失败" << std::endl;

	}


}

void GameLevel::Draw(SpriteRenderer& renderer)
{
	for (GameObject& tile : this->Bricks)
		if (!tile.Destroyed)
			tile.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
	for (GameObject& tile : this->Bricks)
		if (!tile.IsSolid && !tile.Destroyed)
			return false;
	return true;
}


void GameLevel::init(std::vector<std::vector<unsigned int>>tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	// 计算每个维度的大小
	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();
	float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / height;
	// 基于tileDataC初始化关卡     
	for (unsigned int  y = 0; y < height; ++y)
	{
		for (unsigned int  x = 0; x < width; ++x)
		{
			// 检查砖块类型
			if (tileData[y][x] == 1)//soild
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
				obj.IsSolid = true;
				this->Bricks.push_back(obj);
			}
			else if(tileData[y][x]>1)
			{
				glm::vec3 color = glm::vec3(1.0f);
				if (tileData[y][x] == 2)
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				else if (tileData[y][x] == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				else if (tileData[y][x] == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				else if (tileData[y][x] == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);

				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
			}
		}
	}
}