#include "shader_loader.h"

ShaderLoader::ShaderLoader(unsigned int type, std::string filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file." << std::endl;
        return ;
    }
    shader_type_ = type;

    std::string line;
    std::string currentShaderName;
    std::stringstream shaderCode;
    ShaderType currentType = ShaderType::UNDEFINE_SHADER;

    while (getline(file, line)) {
        // 检查shader类型标记
        if (line.find("@shader_vertex") != std::string::npos) {
            currentType = ShaderType::VERTEX_SHADER;
            if (line.find("@shader_vertex_uid") != std::string::npos) {
                currentShaderName = line.substr(line.rfind("=")+1, line.npos);
            }
            continue;
        }
        else if (line.find("@shader_fragment") != std::string::npos) {
            currentType = ShaderType::FRAGMENT_SHADER;
            if (line.find("@shader_fragment_uid") != std::string::npos) {
                currentShaderName = line.substr(line.rfind("=") + 1, line.npos);
            }
            continue;
        }
        else if (line.find("@shader_geometry") != std::string::npos) {
            currentType = ShaderType::GEOMETRY_SHADER;
            if (line.find("@shader_geometry_uid") != std::string::npos) {
                currentShaderName = line.substr(line.rfind("=") + 1, line.npos);
            }
            continue;
        }
        else if (line.find("@shader_end") != std::string::npos) {
            // 保存当前shader代码
            if (!currentShaderName.empty()) {
                name_shader_map_[currentShaderName] = shaderCode.str();
                shaderCode.str(std::string()); // 清空stringstream
            }
            int id = buildShader(name_shader_map_[currentShaderName],currentType);
            name_id_map_[currentShaderName] = id;
            currentShaderName.clear();
            continue;
        }

        // 忽略空行和注释行
        if (line.empty() /*|| line[0] == '#'*/) {
            continue;
        }

        // 收集shader代码
        shaderCode << line << "\n";
    }

    file.close();
    return;
}


ShaderLoader::~ShaderLoader() {
     for (auto &&it: name_id_map_) {
         glDeleteShader(it.second);
     }
}

std::map<std::string, std::string> ShaderLoader::getShaderSourceMap() {
    return name_shader_map_;
}

std::map<std::string, int> ShaderLoader::getShaderIDMap() {
    return name_id_map_;
}


int ShaderLoader::buildShader(std::string shader, ShaderType type) {
    unsigned int shaderprogram ;
    if (type== ShaderType::VERTEX_SHADER) {
        shaderprogram = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == ShaderType::FRAGMENT_SHADER) {
        shaderprogram = glCreateShader(GL_FRAGMENT_SHADER);
    }
    else if (type == ShaderType::GEOMETRY_SHADER) {
        return 0;
    }
    const GLchar* shaderSource = shader.c_str();
    glShaderSource(shaderprogram, 1, &shaderSource, NULL);
    glCompileShader(shaderprogram);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderprogram, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderprogram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shaderprogram;
}


int ShaderLoader::attachShader(std::vector<std::string> linkNames, unsigned int programId)
{
    unsigned int shaderProgram = programId;
    if (shaderProgram ==0) {
        shaderProgram= glCreateProgram();
    }
    for (auto it:linkNames) {
        glAttachShader(shaderProgram, name_id_map_[it]);
    }
    return shaderProgram;
}


void ShaderLoader::linkShader(unsigned int programId) {
    glLinkProgram(programId);
    int success = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    char infoLog[512];
    if (!success) {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderLoader::deleteShader(std::vector<std::string> deleteNames) {
    for (auto it : deleteNames) {
        glDeleteShader(name_id_map_[it]);
    }
}

void ShaderLoader::useShaderWithName(std::string name) {
    if (!name_id_map_.count(name)) {
        return;
    }

    if (name_id_map_[name]==-1) {
        
    }
    glUseProgram(name_id_map_[name]);
}


void ShaderLoader::setUnifromF(unsigned int programId,std::string name, float value) {
    int shaderLocation = glGetUniformLocation(programId, name.c_str());
    glUseProgram(programId);
    glUniform4f(shaderLocation, 0.0f, value, 0.0f, 1.0f);
}

void ShaderLoader::setMat4F(unsigned int programId, std::string name, glm::mat4 value) {
    int shaderLocation = glGetUniformLocation(programId, name.c_str());
    glUseProgram(programId);
    glUniformMatrix4fv(shaderLocation, 1, GL_FALSE, glm::value_ptr(value));
}