#include "core/object/staticmesh.h"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "debug.h"

namespace Core
{
	StaticMesh::StaticMesh(
		std::vector<Vertex> vertices, 
		std::vector<unsigned int> indices, 
		std::vector<Texture> textures)
        : vao(0), vbo(0), ebo(0)
        , vertices(vertices), indices(indices), textures(textures)
	{
        if (vertices.size() <= 0)
        {
            Logger::LOG(Logger::LogPriority::Critical, "List of Vertices while constructing StaticMesh are empty");
            return;
        }

        if (indices.size() <= 0)
        {
            Logger::LOG(Logger::LogPriority::Critical, "List of Indices while constructing StaticMesh are empty");
            return;
        }

        if (textures.size() <= 0)
        {
            Logger::LOG(Logger::LogPriority::Warn, "List of Textures while constructing StaticMesh are empty");
        }

        // Generate Buffers and Data 
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() *
            sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() *
            sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Vertex Positions 
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)0);

        // Vertex Normals 
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)offsetof(Vertex, normal));

        // Vertex Texture Coords 
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)offsetof(Vertex, texCoords));

        glBindVertexArray(0);
	}

	void StaticMesh::Draw(uint32_t shaderID)
	{
        glUseProgram(shaderID);
        glBindVertexArray(vao);

        for (uint32_t i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            if (textures[i].type == "diffuse")
            {
                glUniform1ui(glGetUniformLocation(shaderID,
                    "texture_diffuse"), i);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }
            if (textures[i].type == "specular")
            {
                glUniform1ui(glGetUniformLocation(shaderID,
                    "texture_specular"), i);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }
            if (textures[i].type == "normal")
            {
                glUniform1ui(glGetUniformLocation(shaderID,
                    "texture_normal"), i);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }
        }

        // Draw Mesh
        glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        App::Instance().AddVertCount((uint32_t)indices.size());
        App::Instance().AddDrawCalls(1);
	}

    void StaticMeshObject::Draw(uint32_t shaderID)
    {
        if (meshes.size() <= 0)
            return;

        // Update shader with model matrix (transform)
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "uObject"), 
            1, false, glm::value_ptr(GetLocalModelMatrix()));

        // Draw all meshes
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shaderID);
    }
}