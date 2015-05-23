#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(Display* display) : FontManager(display), TextureManager()
{
	imageBasepath = "";
	animationBasepath = "";
	fontBasepath = "";
}

void GraphicsManager::AddGraphicScript(const std::string& filepath)
{
	//TODO: REWORK
	/*
	std::ifstream in;
	in.open(filepath);

	int lineNum = 1;

	if (in.is_open())
	{
		while (!in.eof())
		{
			std::string line;
			std::getline(in, line);

			std::vector<std::string> linedata = SplitString(line, ' ');

			for (int i = 0; i < linedata.size(); i++)
			{
				std::string data = linedata[i];

				if (data[0] == NULL)
					continue;
				else if (data[0] == '#' || (data[0] == '/' && data[1] == '/'))
				{
					break;
				}
				else if (data == "basepath")
				{
					if (!(linedata.size() - 1 < i + 1))
					{
						std::string basepathType = linedata[i + 1];

						if (basepathType == "i")
						{
							if (!(linedata.size() - 1 < i + 2))
							{
								std::string basepath = linedata[i + 2];

								if (basepath == "NONE")
									imageBasepath = "";
								else
									imageBasepath = basepath;

								i += 2;
								continue;
							}
							else
								LOG_ERROR("Syntax error, invalid basepath in graphics script " << filepath << " at line " << lineNum);
						}
						else if (basepathType == "a")
						{
							if (!(linedata.size() - 1 < i + 2))
							{
								std::string basepath = linedata[i + 2];

								if (basepath == "NONE")
									animationBasepath = "";
								else
									animationBasepath = basepath;

								i += 2;
								continue;
							}
							else
								LOG_ERROR("Syntax error, invalid basepath in graphics script " << filepath << " at line " << lineNum);
						}
						else if (basepathType == "f")
						{
							if (!(linedata.size() - 1 < i + 2))
							{
								std::string basepath = linedata[i + 2];

								if (basepath == "NONE")
									fontBasepath = "";
								else
									fontBasepath = basepath;

								i += 2;
								continue;
							}
							else
								LOG_ERROR("Syntax error, invalid basepath in graphics script " << filepath << " at line " << lineNum);
						}
						else
							LOG_ERROR("Syntax error, invalid basepath type in graphics script " << filepath << " at line " << lineNum);
					}
					else
						LOG_ERROR("Syntax error, invalid basepath in graphics script " << filepath << " at line " << lineNum);
				}
				else if (data == "i")
				{
					if (!(linedata.size() - 1 < i + 1))
					{
						std::string imagepath = linedata[i + 1];

						if (!(linedata.size() - 1 < i + 2))
						{
							std::string imagekey = linedata[i + 2];

							AddTexture(imageBasepath + imagepath, TextToNumber(imagekey));

							i += 2;
							continue;
						}
						else
							LOG_ERROR("Syntax error, invalid image key in graphics script " << filepath << " at line " << lineNum);
					}
					else
						LOG_ERROR("Syntax error, invalid image path in graphics script " << filepath << " at line " << lineNum);

				}
				else if (data == "a")
				{
					//TODO: Add animation class and Implement this
				}
				else if (data == "f")
				{
					if (!(linedata.size() - 1 < i + 1))
					{
						std::string fontpath = linedata[i + 1];

						if (!(linedata.size() - 1 < i + 2))
						{
							std::string fontkey = linedata[i + 2];

							if (!(linedata.size() - 1 < i + 3))
							{
								std::string fontsize = linedata[i + 3];

								if (IsNumber(fontsize))
								{
									AddFont(fontBasepath + fontpath, fontkey, TextToNumber(fontsize.c_str()));

									i += 3;
									continue;
								}
								else
									LOG_ERROR("Syntax error, invalid font size not a number in graphics script " << filepath << " at line " << lineNum);
							}
							else
								LOG_ERROR("Syntax error, invalid font size in graphics script " << filepath << " at line " << lineNum);
						}
						else
							LOG_ERROR("Syntax error, invalid font key in graphics script " << filepath << " at line " << lineNum);
					}
					else
						LOG_ERROR("Syntax error, invalid font path in graphics script " << filepath << " at line " << lineNum);
				}
				else
					LOG_ERROR("Syntax error, invalid command in graphics script " << filepath << " at line " << lineNum);
			}

			lineNum++;
		}
	}
	else
		LOG_ERROR("Couldn't load graphics script: " << filepath);
		*/
}
