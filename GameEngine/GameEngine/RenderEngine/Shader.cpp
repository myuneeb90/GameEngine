#include "CoreEngine/AppMain.h"

Shader::Shader(string techniqueName, ShaderType type)
{
	EffectPtr = NULL;
	EffectTechnique = NULL;
	TechniqueName = techniqueName;
	InputLayout = NULL;
	InputLayoutDesc = NULL;
	InputLayoutElementCount = 0;
	Type = type;
}

Shader::~Shader()
{
	this->Destroy();
}

void Shader::OutputShaderErrorMessage(ID3D10Blob *errorMessage)
{
	char *compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;

	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("Assets/Logs/ShaderError.txt");

	// Write out the error message.
	for(i = 0; i < bufferSize; i++)
	{
		fout<<compileErrors[i];
	}

	// close the file
	fout.close();

	// Print out the error message.
	GlobalRefs::Debug->Log();
	GlobalRefs::Debug->Log("-------- Shader Error Log -------");
	GlobalRefs::Debug->Log();
	for(i = 0; i < bufferSize; i++)
	{
		GlobalRefs::Debug->Log(compileErrors[i]);
	}
	GlobalRefs::Debug->Log();
	GlobalRefs::Debug->Log("-------- Shader Error Log -------");
	GlobalRefs::Debug->Log();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	DISPLAY_MESSAGE(L"Shader Error !!!", L"Error compiling shader, check the ShaderError.txt or Logs for message");

	return;
}

void Shader::BuildInputLayout()
{
	if(Type == ST_MESH)
	{
		InputLayoutElementCount = 3;

		InputLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[InputLayoutElementCount];

		InputLayoutDesc[0].SemanticName = "POSITION";
		InputLayoutDesc[0].SemanticIndex = 0;
		InputLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		InputLayoutDesc[0].InputSlot = 0;	
		InputLayoutDesc[0].AlignedByteOffset = 0;
		InputLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayoutDesc[0].InstanceDataStepRate = 0;

		InputLayoutDesc[1].SemanticName = "TEXCOORD";
		InputLayoutDesc[1].SemanticIndex = 0;
		InputLayoutDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		InputLayoutDesc[1].InputSlot = 0;	
		InputLayoutDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		InputLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayoutDesc[1].InstanceDataStepRate = 0;

		InputLayoutDesc[2].SemanticName = "NORMAL";
		InputLayoutDesc[2].SemanticIndex = 0;
		InputLayoutDesc[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		InputLayoutDesc[2].InputSlot = 0;	
		InputLayoutDesc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		InputLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayoutDesc[2].InstanceDataStepRate = 0;

		HRESULT result;
		D3DX11_PASS_DESC passDesc;

		EffectTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
		result = GlobalRefs::Graphics->Device->CreateInputLayout(InputLayoutDesc, InputLayoutElementCount, passDesc.pIAInputSignature,
																 passDesc.IAInputSignatureSize, &InputLayout);

		if(FAILED(result))
		{
			GlobalRefs::Debug->Log("Failed To Create Input Layout");
			return;
		}
	}
	else
	if(Type == ST_LINE)
	{
		InputLayoutElementCount = 1;

		InputLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[InputLayoutElementCount];

		InputLayoutDesc[0].SemanticName = "POSITION";
		InputLayoutDesc[0].SemanticIndex = 0;
		InputLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		InputLayoutDesc[0].InputSlot = 0;	
		InputLayoutDesc[0].AlignedByteOffset = 0;
		InputLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayoutDesc[0].InstanceDataStepRate = 0;

		HRESULT result;
		D3DX11_PASS_DESC passDesc;

		EffectTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
		result = GlobalRefs::Graphics->Device->CreateInputLayout(InputLayoutDesc, InputLayoutElementCount, passDesc.pIAInputSignature,
																 passDesc.IAInputSignatureSize, &InputLayout);

		if(FAILED(result))
		{
			GlobalRefs::Debug->Log("Failed To Create Input Layout");
			return;
		}
	}
}

void Shader::BuildShader(WCHAR *fileName)
{
	HRESULT result;
	ID3D10Blob *errorMessage;
	ID3D10Blob *compiledShader;
	DWORD shaderFlags = 0;

	#if defined(DEBUG) || defined(_DEBUG)
		shaderFlags |= D3D10_SHADER_DEBUG;
		shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
	#endif

	result = D3DX11CompileFromFile(fileName, NULL, NULL, NULL, "fx_5_0", shaderFlags, 0, NULL, 
								   &compiledShader, &errorMessage, 0);

	if(FAILED(result))
	{
		// If the shader failed to compile then it should have written something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage);
		}
		else
		{
			// If there was nothing in the error message then it simply could not find the shader file itself.
			GlobalRefs::Debug->Log();
			GlobalRefs::Debug->Log("-------- ShaderFX Error Log -------");
			GlobalRefs::Debug->Log();
			GlobalRefs::Debug->Log("Missing Shader File");
			GlobalRefs::Debug->Log();
			GlobalRefs::Debug->Log("-------- ShaderFX Error Log -------");
			GlobalRefs::Debug->Log();
			DISPLAY_MESSAGE(fileName, L"Missing Shader File");
		}

		return;
	}

	result = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, GlobalRefs::Graphics->Device, &EffectPtr);

	if(FAILED(result))
	{
		GlobalRefs::Debug->Log();
		GlobalRefs::Debug->Log("-------- ShaderFX Error Log -------");
		GlobalRefs::Debug->Log();
		GlobalRefs::Debug->Log("Failed to compile effect");
		GlobalRefs::Debug->Log();
		GlobalRefs::Debug->Log("-------- ShaderFX Error Log -------");
		GlobalRefs::Debug->Log();
		DISPLAY_MESSAGE(fileName, L"Failed to compile effect");
	}

	compiledShader->Release();
	cout<<"Shader Technique Name : "<<TechniqueName.c_str()<<endl;
	EffectTechnique = EffectPtr->GetTechniqueByName(TechniqueName.c_str());
}

void Shader::RenderInputLayout()
{
	if(Type == ST_MESH)
	{
		GlobalRefs::Graphics->DeviceContext->IASetInputLayout(InputLayout);
		GlobalRefs::Graphics->DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	else
	if(Type == ST_LINE)
	{
		GlobalRefs::Graphics->DeviceContext->IASetInputLayout(InputLayout);
		GlobalRefs::Graphics->DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	}
}

void Shader::RenderShader(int indexCount)
{
	D3DX11_TECHNIQUE_DESC techDesc;
	EffectTechnique->GetDesc(&techDesc);

	for(int p = 0; p < techDesc.Passes; p++)
	{
		EffectTechnique->GetPassByIndex(p)->Apply(0, GlobalRefs::Graphics->DeviceContext);
		GlobalRefs::Graphics->DeviceContext->DrawIndexed(indexCount, 0, 0);
	}
}

ShaderType Shader::GetShaderType()
{
	return this->Type;
}

ID3D11InputLayout* Shader::GetInputLayout()
{
	return this->InputLayout;
}

ID3DX11EffectTechnique* Shader::GetEffectTechnique()
{
	return this->EffectTechnique;
}

void Shader::Destroy()
{
	EffectTechnique->Release();
	EffectPtr->Release();
	InputLayout->Release();
	SAFE_DELETE_ARRAY(InputLayoutDesc);
}

void Shader::SetScalar(string name, float value)
{
	ID3DX11EffectScalarVariable *scalarVar = EffectPtr->GetVariableByName(name.c_str())->AsScalar();
	scalarVar->SetFloat(value);
}

void Shader::SetScalar(string name, int value)
{
	ID3DX11EffectScalarVariable *scalarVar = EffectPtr->GetVariableByName(name.c_str())->AsScalar();
	scalarVar->SetInt(value);
}

void Shader::SetScalar(string name, bool value)
{
	ID3DX11EffectScalarVariable *scalarVar = EffectPtr->GetVariableByName(name.c_str())->AsScalar();
	scalarVar->SetBool(value);
}

void Shader::SetVector(string name, Vector4f value)
{
	ID3DX11EffectVectorVariable *vectorVar = EffectPtr->GetVariableByName(name.c_str())->AsVector();
	vectorVar->SetFloatVector(reinterpret_cast<float*>(&value));
}

void Shader::SetMatrix(string name, Matrix4x4f value)
{
	ID3DX11EffectMatrixVariable *matrixVar = EffectPtr->GetVariableByName(name.c_str())->AsMatrix();
	matrixVar->SetMatrix(reinterpret_cast<float*>(&value));
}

void Shader::SetMatrix(string name, Matrix4x4d value)
{
	ID3DX11EffectMatrixVariable *matrixVar = EffectPtr->GetVariableByName(name.c_str())->AsMatrix();
	Matrix4x4f valueF = value.ConvertToMatrix4x4f();
	matrixVar->SetMatrix(reinterpret_cast<float*>(&valueF));
}

void Shader::SetTexture(string name, ID3D11ShaderResourceView *texture)
{
	ID3DX11EffectShaderResourceVariable *textureMap = EffectPtr->GetVariableByName(name.c_str())->AsShaderResource();;
	textureMap->SetResource(texture);
}