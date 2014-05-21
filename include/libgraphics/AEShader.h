//#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>

namespace aeg {

	/**
	Represents a compiled Shader
	*/

	class AEShader {

	public:

		enum ShaderType{

			AE_VERTEX_SHADER,
			AE_FRAGMENT_SHADER,
			AE_GEOMETRY_SHADER
		};

		/**
		Creates a shader from a text file
		
		@param filePath		The path to the text file containing the shader source.
		@param shaderType	Type of shader to be created.

		@throws std::exception if an error occurs
		*/
		AEShader shaderFromFile(const std::string& filePath, ShaderType shaderType);

		/**
		Creates a shader from a string of shader source code.

		@param shaderCode	The source code of the shader.
		@param shaderType	Type of shader to be created.

		@throws std::exception if an error occurs.
		*/
		AEShader(const std::string& shaderCode, ShaderType shaderType);

		/**
		@result		The shader's object ID
		*/
		unsigned int object() const;

		//aeg::AEShader objects can be copied and assigned because they are referenced counted
		//like a shadered pointer
		AEShader(const AEShader& other);
		AEShader& operator =(const AEShader& other);
		~AEShader();

	private:

		unsigned int mShaderObject;
		unsigned* mRefCount;

		void retain();
		void release();
	};
}
