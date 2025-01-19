#pragma once
#include"common.h"
#include <map>
#include<vector>

enum ShaderType :int {
	UNDEFINE_SHADER = 0x00,
	VERTEX_SHADER = 0x01, // 0x01
	FRAGMENT_SHADER = 0x02, // 0x02
	GEOMETRY_SHADER = 0x04, // 0x04
	MIX_SHADER 
};

class ShaderLoader {
public:


	ShaderLoader(unsigned int type, std::string filePath);
	ShaderLoader(unsigned int type, std::vector<std::string> filePaths);

	virtual ~ShaderLoader();

	static void linkShader(unsigned int programId);
	static void setUnifromF(unsigned int programId, std::string name, float value);
	static void setMat4F(unsigned int programId, std::string name, glm::mat4 value);
	static void setInt(unsigned int programId, const std::string& name, int value);
	static void setVec3(unsigned int programId, const std::string& name, glm::vec3 value);


    bool hasShaderType(ShaderType type) const {
        return (shader_type_ & static_cast<unsigned int>(type)) != 0;
    }

	std::map<std::string, std::string> getShaderSourceMap();
	std::map<std::string, int> getShaderIDMap();

	void useShaderWithName(std::string name);
	int buildShader(std::string shader, ShaderType type);
	int attachShader(std::vector<std::string> linkNames, unsigned int programId=0);
	void deleteShader(std::vector<std::string> deleteNames);

	int buildProgram(std::map<std::string, ShaderType> shader_names_type);

	int getUseId(std::string name);
private:
	unsigned int shader_type_{ 0 };
	std::map<std::string, std::string> name_shader_map_;
	std::map<std::string, int> name_id_map_;

};