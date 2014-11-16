//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "FontManager.h"
#include "TextureManager.h"

class GraphicsManager : public FontManager, public TextureManager
{
public:
	GraphicsManager(Display* display, Camera& camera, Logger *logger) : FontManager(display, camera, logger), TextureManager(display, camera, logger)
	{
		this->logger = logger;

		imageBasepath = "";
		animationBasepath = "";
		fontBasepath = "";
	}

	//TODO: Clean up
	void AddGraphicScript(const std::string& filepath)
	{
		std::cout << "Warning! The Graphics Script System was written for an older version of the engine! It MAY not work properly!" << std::endl
			<< "Update coming soon!" << std::endl;

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
									logger->LogLine("Syntax error, invalid basepath in graphics script ", filepath, " at line ", lineNum);
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
									logger->LogLine("Syntax error, invalid basepath in graphics script ", filepath, " at line ", lineNum);
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
									logger->LogLine("Syntax error, invalid basepath in graphics script ", filepath, " at line ", lineNum);
							}
							else
								logger->LogLine("Syntax error, invalid basepath type in graphics script ", filepath, " at line ", lineNum);
						}
						else
							logger->LogLine("Syntax error, invalid basepath in graphics script ", filepath, " at line ", lineNum);
					}
					else if (data == "i")
					{
						if (!(linedata.size() - 1 < i + 1))
						{
							std::string imagepath = linedata[i + 1];

							if (!(linedata.size() - 1 < i + 2))
							{
								std::string imagekey = linedata[i + 2];

								//TODO: Rework this
								AddTexture(imageBasepath + imagepath, TextToNumber(imagekey.c_str()));

								i += 2;
								continue;
							}
							else
								logger->LogLine("Syntax error, invalid image key in graphics script ", filepath, " at line ", lineNum);
						}
						else
							logger->LogLine("Syntax error, invalid image path in graphics script ", filepath, " at line ", lineNum);

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
										logger->LogLine("Syntax error, invalid font size not a number in graphics script ", filepath, " at line ", lineNum);
								}
								else
									logger->LogLine("Syntax error, invalid font size in graphics script ", filepath, " at line ", lineNum);
							}
							else
								logger->LogLine("Syntax error, invalid font key in graphics script ", filepath, " at line ", lineNum);
						}
						else
							logger->LogLine("Syntax error, invalid font path in graphics script ", filepath, " at line ", lineNum);
					}
					else
						logger->LogLine("Syntax error, invalid command in graphics script ", filepath, " at line ", lineNum);
				}

				lineNum++;
			}
		}
		else
			logger->LogLine("Couldn't load graphics script: ", filepath);
	}

private:
	Logger *logger;

	std::string imageBasepath;
	std::string fontBasepath;
	std::string animationBasepath;
};

#endif